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

int main(void)
{
	/* initialize components */
	internal_led_init();
	usart_comm_init();  /* 115200 baud */
	sn74hc135n_init();
	
	/* enable interrupts */
	sei();
	
	/* whoop, whoop! */
	set_internal_led(1);
	usart_comm_send_zstr("SYSTEM READY.\r\n");
	
	sn74hc135n_strobe_channel_2(1);
	
    while(1)
    {
		uint_fast8_t input = sn74hc135n_read_channel_2();
		
		usart_comm_send_char(input);
		// set_internal_led(1);
    }
}