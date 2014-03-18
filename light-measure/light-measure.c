/*
 * light_measure.c
 *
 * Created: 17.03.2014 23:06:00
 *  Author: Markus
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#include "system.h"
#include "internal_led.h"
#include "usart/usart_comm.h"
#include "sn74hc135n.h"

void external_timer0_init()
{
	DDRD  &= ~(1 << DDD4);      /* T0 pin as input */
	PORTD |= (1 << PORTD4);     /* pull-up enabled */
	TIMSK0 |= (1 << TOIE0);     /* enable timer0 interrupt */
	TCCR0B |= (1 << CS02)       /* enabled counter, count on rising edge */
	       |  (1 << CS01) 
	       |  (1 << CS00);
}

volatile uint8_t timer0_ofs = 0;

ISR (TIMER0_OVF_vect)
{
	++timer0_ofs;
}

int main(void)
{
	/* initialize components */
	internal_led_init();
	usart_comm_init();  /* 115200 baud */
	sn74hc135n_init();
	external_timer0_init();
	
	/* enable interrupts */
	sei();
	
	/* whoop, whoop! */
	set_internal_led(0);
	usart_comm_send_zstr("SYSTEM READY.\r\n");
	
	sn74hc135n_strobe_channel_1(1);
	
	int led = 0;
    while(1)
    {
		// uint_fast8_t input = sn74hc135n_read_channel_2();
		// usart_comm_send_char(input);
		
		if (0b00 == (timer0_ofs & 0b11))
		{
			led = !led;
			set_internal_led(led);
		}
    }
}