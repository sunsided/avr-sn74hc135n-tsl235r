/*
 * counters.h
 *
 * Created: 18.03.2014 02:22:46
 *  Author: Markus
 */ 


#ifndef COUNTERS_H_
#define COUNTERS_H_

typedef uint_fast16_t counter_t;

extern volatile counter_t counter0_ofvs;

extern volatile counter_t counter1_ofvs;

/*!
	\brief Gets the current value of counter 1
*/
static inline counter_t counter1_get()
{
	return counter0_ofvs;
}

/*!
	\brief Gets the current value of counter 2
*/
static inline counter_t counter2_get()
{
	return counter1_ofvs;
}

/*!
	\brief Initializes counter 1
*/
void counter1_init();

/*!
	\brief Initializes counter 2
*/
void counter2_init();

/*!
	\brief Halts both counters
*/
void counters_halt();

/*!
	\brief Resets and restarts both counters
*/
void counters_reset_restart();

#endif /* COUNTERS_H_ */