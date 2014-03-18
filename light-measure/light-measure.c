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

/*!
	\bref The LED state for toggling action
*/
int led = 0;

/*!
	\brief The sampling time in milliseconds
*/
uint_fast32_t sampling_time_ms = 1000;

typedef enum {

	INIT,             /*!< initial state */
	SAMPLE_1C0_2C0,   /*!< sampling of channels 1C0 and 2C0 */
	SAMPLE_1C1_2C1,   /*!< sampling of channels 1C1 and 2C1 */
	SAMPLE_1C2_2C2,   /*!< sampling of channels 1C2 and 2C2 */
	SAMPLE_1C3_2C3,   /*!< sampling of channels 1C3 and 2C3 */
	SAMPLING,         /*!< currently sampling data */

} state_t;

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
	
	/* initialize state machine */
	state_t state = INIT;
	state_t next_state_after_period = INIT;
	
	/* begin sampling loop */
	systick_ms_t start_millis = millis();
	while (1)
	{
		switch (state)
		{
			case INIT: /* simply fall through */
			case SAMPLE_1C0_2C0:
			{
				sn74hc135n_strobe_channels(0);
				sn74hc135n_select_lines(LINES_1C0_2C0);
				sn74hc135n_strobe_channels(1);
				
				next_state_after_period = SAMPLE_1C1_2C1;
				state = SAMPLING;
				break;
			}
			
			case SAMPLE_1C1_2C1:
			{
				sn74hc135n_strobe_channels(0);
				sn74hc135n_select_lines(LINES_1C1_2C1);
				sn74hc135n_strobe_channels(1);
				
				next_state_after_period = SAMPLE_1C2_2C2;
				state = SAMPLING;
				break;
			}
			
			case SAMPLE_1C2_2C2:
			{
				sn74hc135n_strobe_channels(0);
				sn74hc135n_select_lines(LINES_1C2_2C2);
				sn74hc135n_strobe_channels(1);
				
				next_state_after_period = SAMPLE_1C3_2C3;
				state = SAMPLING;
				break;
			}
			
			case SAMPLE_1C3_2C3:
			{
				sn74hc135n_strobe_channels(0);
				sn74hc135n_select_lines(LINES_1C3_2C3);
				sn74hc135n_strobe_channels(1);
				
				next_state_after_period = SAMPLE_1C0_2C0;
				state = SAMPLING;
				break;
			}
			
			case SAMPLING:
			{
				/* wait until the sampling time passes */
				systick_ms_t current_millis = millis();
				if ((current_millis - start_millis) >= sampling_time_ms)
				{
					start_millis = current_millis;

					/* toggle LED */
					led = !led;
					set_internal_led(led);
					
					/* switch state */
					state = next_state_after_period;
				}
				
				/* TODO: write counted values into register */
				break;
			}
		}
	}
}