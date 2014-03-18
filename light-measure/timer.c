/*
 * timer.c
 *
 * Created: 18.03.2014 01:17:12
 *  Author: Markus
 *
 * Borrowed from Arduino code as per
 *  http://ucexperiment.wordpress.com/2012/03/16/examination-of-the-arduino-millis-function/
 */ 

#include <avr/interrupt.h>
#include <util/atomic.h>

#include "timer.h"

/*!
	\brief Number of clock cycles per microsecond
*/
#define CLOCK_CYCLES_PER_MICROSECOND() ( F_CPU / 1000000L )

/*!
	\brief Converts a clock cycle into microseconds
*/
#define CLOCK_CYCLES_TO_MICROSECONDS(a) ( ((a) * 1000L) / (F_CPU / 1000L) )

/*!
	\brief The number of microseconds between each timer overflow
*/
#define MICROSECONDS_PER_TIMER2_OVERFLOW (CLOCK_CYCLES_TO_MICROSECONDS(64 * 256))

/*!
	\brief the whole number of milliseconds per timer2 overflow
*/
#define MILLIS_INC (MICROSECONDS_PER_TIMER2_OVERFLOW / 1000)

/*! 
	The fractional number of milliseconds per timer2 overflow. we shift right
	by three to fit these numbers into a byte. (for the clock speeds we care
	about - 8 and 16 MHz - this doesn't lose precision.)
*/
#define FRACT_INC ((MICROSECONDS_PER_TIMER2_OVERFLOW % 1000) >> 3)

#define FRACT_MAX (1000 >> 3)

static uint_fast32_t timer2_millis = 0;
static uint_fast8_t timer2_fract = 0;

void systick_init()
{
	TIMSK2 |= (1 << TOIE2);     /* enable timer2 interrupt */
	TCCR2B |= (1 << CS22)       /* enabled counter, prescaler 64 */
	|  (0 << CS21)
	|  (0 << CS20);
}

SIGNAL(TIMER2_OVF_vect)
{
	// copy these to local variables so they can be stored in registers
	// (volatile variables must be read from memory on every access)
	uint_fast32_t m = timer2_millis;
	uint_fast8_t  f = timer2_fract;
	
	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}
	
	timer2_fract = f;
	timer2_millis = m;
	// timer2_overflow_count++;
}

unsigned long millis()
{
	uint_fast32_t m;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		m = timer2_millis;
	}
	return m;
}