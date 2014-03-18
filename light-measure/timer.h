/*
 * timer.h
 *
 * Created: 18.03.2014 01:17:03
 *  Author: Markus
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "system.h"

/*!
	\brief Initializes the system tick (reference) timer.
*/
void systick_init();

/*!
	\brief Gets the number of milliseconds elapsed since the boot.
*/
uint_fast32_t millis();

#endif /* TIMER_H_ */