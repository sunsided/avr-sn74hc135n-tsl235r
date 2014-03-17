/*
 * sn74hc135n.h
 *
 * Created: 18.03.2014 00:51:14
 *  Author: Markus
 */ 


#ifndef SN74HC135N_H_
#define SN74HC135N_H_

#define SN74HC153N_A_PORT   PORTC
#define SN74HC153N_B_PORT   PORTC
#define SN74HC153N_1Gn_PORT PORTC
#define SN74HC153N_2Gn_PORT PORTC
#define SN74HC153N_1Y_PORT  PIND
#define SN74HC153N_2Y_PORT  PIND

#define SN74HC153N_A_DDR    DDRC
#define SN74HC153N_B_DDR    DDRC
#define SN74HC153N_1Gn_DDR  DDRC
#define SN74HC153N_2Gn_DDR  DDRC
#define SN74HC153N_1Y_DDR   DDRD
#define SN74HC153N_2Y_DDR   DDRD

#define SN74HC153N_A_PIN    PORTC0 /* analog input 0 */
#define SN74HC153N_B_PIN    PORTC1 /* analog input 1 */
#define SN74HC153N_1Gn_PIN  PORTC2 /* analog input 2 */
#define SN74HC153N_2Gn_PIN  PORTC3 /* analog input 3 */
#define SN74HC153N_1Y_PIN   PIND4  /* digital pin 4 (T0) */
#define SN74HC153N_2Y_PIN   PIND5  /* digital pin 5 (T1) */

#define SN74HC153N_A_DD     DDC0
#define SN74HC153N_B_DD     DDC1
#define SN74HC153N_1Gn_DD   DDC2
#define SN74HC153N_2Gn_DD   DDC3
#define SN74HC153N_1Y_DD    DDD4
#define SN74HC153N_2Y_DD    DDD5

/*!
	\brief Initializes the communication over the SN74HC135N two-channel 4-to-1 multiplexer
*/
void sn74hc135n_init();

/*!
	\brief Sets or unsets the strobe signal for channel 1
	\param[in] enable Enables the strobe signal (by setting it low) if set to 1 and 
	                  disables it otherwise (by setting it high) .
*/
void sn74hc135n_strobe_channel_1(int enable);

/*!
	\brief Sets or unsets the strobe signal for channel 2
	\param[in] enable Enables the strobe signal (by setting it low) if set to 1 and 
	                  disables it otherwise (by setting it high) .
*/
void sn74hc135n_strobe_channel_2(int enable);

/*!
	\brief Reads the current value from Channel 1
*/
uint_fast8_t sn74hc135n_read_channel_1();

/*!
	\brief Reads the current value from Channel 2
*/
uint_fast8_t sn74hc135n_read_channel_2();

#endif /* SN74HC135N_H_ */