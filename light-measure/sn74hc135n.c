/*
 * sn74hc135n.c
 *
 * Created: 18.03.2014 00:51:27
 *  Author: Markus
 */ 

#include <avr/io.h>
#include "sn74hc135n.h"

/*!
	\brief Initializes the communication over the SN74HC135N two-channel 4-to-1 multiplexer
*/
void sn74hc135n_init()
{
	/* set data directions for control pins A, B, 1G, 2G */
	SN74HC153N_A_DDR    |= (1 << SN74HC153N_A_DD);
	SN74HC153N_B_DDR    |= (1 << SN74HC153N_B_DD);
	SN74HC153N_1Gn_DDR  |= (1 << SN74HC153N_1Gn_DD);
	SN74HC153N_2Gn_DDR  |= (1 << SN74HC153N_2Gn_DD);
	
	/* set data directions for input pins */
	SN74HC153N_1Y_DDR   &= ~(1 << SN74HC153N_1Y_DD);
	SN74HC153N_2Y_DDR   &= ~(1 << SN74HC153N_2Y_DD);
	
	/* set strobe high to disable */
	SN74HC153N_1Gn_PORT |= (1 << SN74HC153N_1Gn_PIN);
	SN74HC153N_2Gn_PORT |= (1 << SN74HC153N_2Gn_PIN);
}

/*!
	\brief Sets or unsets the strobe signal for channel 1
	\param[in] enable Enables the strobe signal (by setting it low) if set to 1 and 
	                  disables it otherwise (by setting it high) .
*/
void sn74hc135n_strobe_channel_1(int enable)
{
	if (enable)
		SN74HC153N_1Gn_PORT &= ~(1 << SN74HC153N_1Gn_PIN);
	else
		SN74HC153N_1Gn_PORT |= (1 << SN74HC153N_1Gn_PIN);
}

/*!
	\brief Sets or unsets the strobe signal for channel 2
	\param[in] enable Enables the strobe signal (by setting it low) if set to 1 and 
	                  disables it otherwise (by setting it high) .
*/
void sn74hc135n_strobe_channel_2(int enable)
{
	if (enable)
		SN74HC153N_2Gn_PORT &= ~(1 << SN74HC153N_2Gn_PIN);
	else
		SN74HC153N_2Gn_PORT |= (1 << SN74HC153N_2Gn_PIN);
}

/*!
	\brief Sets or unsets the strobe signal for both channels
	\param[in] enable Enables the strobe signal (by setting it low) if set to 1 and 
	                  disables it otherwise (by setting it high) .
*/
void sn74hc135n_strobe_channels(int enable)
{
	sn74hc135n_strobe_channel_1(enable);
	sn74hc135n_strobe_channel_2(enable);
}

/*!
	\brief Reads the current value from Channel 1
*/
uint_fast8_t sn74hc135n_read_channel_1()
{
	return (SN74HC153N_1Y_PORT & (1 << SN74HC153N_1Y_PIN));
}

/*!
	\brief Reads the current value from Channel 2
*/
uint_fast8_t sn74hc135n_read_channel_2()
{
	return (SN74HC153N_2Y_PORT & (1 << SN74HC153N_2Y_PIN));
}

/*!
	\brief Selects a (pair of) lines to multiplex
	\param[in] lines The line pair to enable
*/
void sn74hc135n_select_lines(sn74hc135n_lines_t lines)
{
	switch (lines)
	{
		case LINES_1C0_2C0:
		{
			SN74HC153N_A_PORT &= ~(1 << SN74HC153N_A_PIN);
			SN74HC153N_B_PORT &= ~(1 << SN74HC153N_B_PIN);
			break;
		}
		
		case LINES_1C1_2C1:
		{
			SN74HC153N_A_PORT |=  (1 << SN74HC153N_A_PIN);
			SN74HC153N_B_PORT &= ~(1 << SN74HC153N_B_PIN);
			break;
		}
		
		case LINES_1C2_2C2:
		{
			SN74HC153N_A_PORT &= ~(1 << SN74HC153N_A_PIN);
			SN74HC153N_B_PORT |=  (1 << SN74HC153N_B_PIN);
			break;
		}
		
		case LINES_1C3_2C3:
		{
			SN74HC153N_A_PORT |=  (1 << SN74HC153N_A_PIN);
			SN74HC153N_B_PORT |=  (1 << SN74HC153N_B_PIN);
			break;
		}
		
		/* TODO: exceptional default case */
	}
}