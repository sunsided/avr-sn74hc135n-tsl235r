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
#include "counters.h"

int led = 0;

int main(void)
{
	/* initialize components */
	internal_led_init();
	usart_comm_init();  /* 115200 baud */
	sn74hc135n_init();

	/* initialize internal reference timer */
	systick_init();

	/* initialize external counters */
	counter1_init();
	counter2_init();
	
	/* enable interrupts */
	sei();
	
	/* whoop, whoop! */
	set_internal_led(0);
	usart_comm_send_zstr("SYSTEM READY.\r\n");

	sn74hc135n_strobe_channel_1(1);
	sn74hc135n_strobe_channel_2(1);
	
	uint_fast32_t start_millis = millis();
	while(1)
	{
		uint_fast32_t current_millis = millis();
		
		/* implement 1-second timer */
		if (current_millis - start_millis >= 1000 /* ms/s */)
		{
			start_millis = current_millis;

			/* toggle LED */
			led = !led;
			set_internal_led(led);
		}
		
		/* send counter value */
		uint_fast8_t value = counter1_get();
		usart_comm_send_char(value);
	}
}