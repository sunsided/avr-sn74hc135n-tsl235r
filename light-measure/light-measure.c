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

int main(void)
{
	// initialize components
	internal_led_init();
	usart_comm_init();
	
	// enable interrupts
	sei();
	
	// whoop, whoop!
	set_internal_led(0);
	usart_comm_send_zstr("SYSTEM READY.\r\n");
    while(1)
    {
		set_internal_led(1);
    }
}