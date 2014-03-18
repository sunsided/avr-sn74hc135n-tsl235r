/*
 * light_measure.c
 *
 * Created: 17.03.2014 23:06:00
 *  Author: Markus
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#include "system.h"
#include "systick.h"
#include "internal_led.h"
#include "usart/usart_comm.h"
#include "sn74hc135n.h"

void external_timer0_init()
{
	DDRD  &= ~(1 << DDD4);      /* T0 pin as input */
	PORTD  |= (1 << PORTD4);    /* pull-up enabled */
	
	TIMSK0 |= (1 << TOIE0);     /* enable timer0 interrupt */
	TCCR0B |= (1 << CS02)       /* enabled counter, count external on rising edge */
	       |  (1 << CS01) 
	       |  (1 << CS00);
	
	TCNT0 = 0x00;
}

void external_timer1_init()
{
	/* This timer is configured as an 8-bit timer to match resolution of timer0.
	   Note that ICR1 match is used in order to keep OCR1A/OCR1B functionality
	   should it be required later on. */
	
	DDRD  &= ~(1 << DDD5);      /* T1 pin as input */
	PORTD  |= (1 << PORTD5);    /* pull-up enabled */

	TIMSK1 |= (1 << ICIE1);     /* enable timer1 interrupt on input capture match */
	TCCR1B |= (1 << CS12)       /* enabled counter, count external on rising edge */
	       |  (1 << CS11)
	       |  (1 << CS10);
	TCCR1B |= (1 << WGM13)      /* CTC mode, wrap on ICR1 */
	       |  (1 << WGM12);
	
	ICR1  = 0x00FF;              /* wrap when reaching 255 */
	TCNT1 = 0x0000;
}

volatile uint_fast8_t timer0_ofs = 0;
volatile uint_fast8_t timer1_ofs = 0;

ISR (TIMER0_OVF_vect)
{
	++timer0_ofs;
}

ISR (TIMER1_CAPT_vect)
{
	/* note that TIMER1_CAPT_vect is used instead of 
	   TIMER1_OVF_vect because CTC mode on ICR1 is activated */
	++timer1_ofs;
}

int main(void)
{
	/* initialize components */
	internal_led_init();
	usart_comm_init();  /* 115200 baud */
	sn74hc135n_init();

	/* initialize internal reference timer */
	systick_init();

	/* initialize external timers */
	external_timer0_init();
	external_timer1_init();
	
	/* enable interrupts */
	sei();
	
	/* whoop, whoop! */
	set_internal_led(0);
	usart_comm_send_zstr("SYSTEM READY.\r\n");

	sn74hc135n_strobe_channel_1(1);
	sn74hc135n_strobe_channel_2(1);
	
	while(1)
	{
		usart_comm_send_char(timer1_ofs);
	}

#if 0	
	int led = 0;
	uint_fast32_t start_millis = millis();
    while(1)
    {	
		uint_fast32_t current_millis = millis();
		if (current_millis - start_millis >= 1000)
		{
			start_millis = current_millis;

			/* toggle LED */
			led = !led;
			set_internal_led(led);
		}
    }
#endif
}