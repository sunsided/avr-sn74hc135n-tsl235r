/*
 * light_measure.c
 *
 * Created: 17.03.2014 23:06:00
 *  Author: Markus
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#include "system.h"
#include "timer.h"
#include "internal_led.h"
#include "usart/usart_comm.h"
#include "sn74hc135n.h"

void external_timer0_init()
{
	DDRD  &= ~(1 << DDD4);      /* T0 pin as input */
	PORTD  |= (1 << PORTD4);    /* pull-up enabled */
	TIMSK0 |= (1 << TOIE0);     /* enable timer0 interrupt */
	TCCR0B |= (1 << CS02)       /* enabled counter, count on rising edge */
	       |  (1 << CS01) 
	       |  (1 << CS00);
}

void external_timer1_init()
{
	DDRD  &= ~(1 << DDD5);      /* T1 pin as input */
	PORTD  |= (1 << PORTD5);    /* pull-up enabled */
	TIMSK1 |= (1 << TOIE1);     /* enable timer1 interrupt */
	TCCR1B |= (1 << CS12)       /* enabled counter, count on rising edge */
	       |  (1 << CS11)
	       |  (1 << CS10);
}

volatile uint_fast16_t timer0_ofs = 0;
volatile uint_fast16_t timer1_ofs = 0;

ISR (TIMER0_OVF_vect)
{
	++timer0_ofs;
}

ISR (TIMER1_OVF_vect)
{
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
}