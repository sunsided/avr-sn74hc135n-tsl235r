/*
 * timers.c
 *
 * Created: 18.03.2014 02:20:55
 *  Author: Markus
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "counters.h"

volatile counter_t counter0_ofvs = 0;

volatile counter_t counter1_ofvs = 0;

void counter1_init()
{
	counter0_ofvs = 0;
	
	DDRD  &= ~(1 << DDD4);      /* T0 pin as input */
	PORTD  |= (1 << PORTD4);    /* pull-up enabled */
	
	TIMSK0 |= (1 << TOIE0);     /* enable timer0 interrupt */
	TCCR0B |= (1 << CS02)       /* enabled counter, count external on rising edge */
	       |  (1 << CS01) 
	       |  (1 << CS00);
	
	TCNT0 = 0x00;
}

void counter2_init()
{
	/* This timer is configured as an 8-bit timer to match resolution of timer0.
	   Note that ICR1 match is used in order to keep OCR1A/OCR1B functionality
	   should it be required later on. */
	
	counter1_ofvs = 0;
	
	DDRD  &= ~(1 << DDD5);      /* T1 pin as input */
	PORTD  |= (1 << PORTD5);    /* pull-up enabled */

	TIMSK1 |= (1 << ICIE1);     /* enable timer1 interrupt on input capture match */
	TCCR1B |= (1 << CS12)       /* enabled counter, count external on rising edge */
	       |  (1 << CS11)
	       |  (1 << CS10);
	TCCR1B |= (1 << WGM13)      /* CTC mode, wrap on ICR1 */
	       |  (1 << WGM12);
	
	ICR1  = 0x00FF;             /* wrap when reaching 255 */
	TCNT1 = 0x0000;
}

/*!
	\brief Halts both counters
*/
void counters_halt()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		TCCR0B = 0;           /* disable counter 0 */
		TCCR1B = 0;           /* disable counter 1 */
		
		TIFR0 = 0;            /* clear interrupts of counter 0 */
		TIFR1 = 0;            /* clear interrupts of counter 1 */
	}
}

/*!
	\brief Resets and restarts both counters
*/
void counters_reset_restart()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		counter1_init();
		counter2_init();
	}
}

ISR (TIMER0_OVF_vect)
{
	++counter0_ofvs;
}

ISR (TIMER1_CAPT_vect)
{
	/* note that TIMER1_CAPT_vect is used instead of 
	   TIMER1_OVF_vect because CTC mode on ICR1 is activated */
	++counter1_ofvs;
}
