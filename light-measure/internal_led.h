/*
 * internal_led.h
 *
 * Created: 17.03.2014 23:25:56
 *  Author: Markus
 */ 


#ifndef INTERNAL_LED_H_
#define INTERNAL_LED_H_


/*! 
	\brief Enables or disables the on-board LED
	
	On Arduino boards the internal LED is attached to Digital Out 13 which is equivalent
	to Port B5 on ATmega168/368 microcontrollers.
	
	\param enabled Determines if the LED should be enabled (\c ON) or disabled (\c OFF)
*/
static inline void set_internal_led(int enabled) 
{
	if (enabled > 0)
		PORTB |= (1 << PORTB5);
	else 
		PORTB &= ~(1 << PORTB5);
}

/*! 
	\brief Initializes the on-board LED
	
	On Arduino boards the internal LED is attached to Digital Out 13 which is equivalent
	to Port B5 on ATmega168/368 microcontrollers.
*/
static inline void internal_led_init()
{
	// Arduino D13 als Ausgang setzen
	DDRB |= (1 << DDB5);
}

#endif /* INTERNAL_LED_H_ */