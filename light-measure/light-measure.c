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
systick_ms_t sampling_time_ms = 100;

typedef enum {

	INIT,             /*!< initial state */
	SAMPLE_1C0_2C0,   /*!< sampling of lines 1C0 and 2C0 */
	SAMPLE_1C1_2C1,   /*!< sampling of lines 1C1 and 2C1 */
	SAMPLE_1C2_2C2,   /*!< sampling of lines 1C2 and 2C2 */
	SAMPLE_1C3_2C3,   /*!< sampling of lines 1C3 and 2C3 */
	SAMPLING,         /*!< currently sampling data */
	PROCESSING,       /*!< processes sampled data */
	OUTPUT,           /*!< outputs data */
	ADVANCE,          /*!< advances to the next lines */

} state_t;

/*!
	\brief The number of lines used
*/
#define NUM_LINES	4

/*!
	\brief The array of counter overflows per sampling time on channel 1
*/
counter_t channel_1_buffer[NUM_LINES] = {0};

/*!
	\brief The array of counter overflows per sampling time on channel 2
*/
counter_t channel_2_buffer[NUM_LINES] = {0};

/*!
	\brief Gets the channel buffer index from a line pair
*/
uint_fast8_t get_channel_index(sn74hc135n_lines_t line)
{
	/* assuming lines are still 0..3 */
	return (uint_fast8_t)line;
}

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
	sn74hc135n_lines_t current_line;
	
	/* begin sampling loop */
	systick_ms_t start_millis = millis();
	while (1)
	{
		switch (state)
		{
			case INIT: /* simply fall through */
			case SAMPLE_1C0_2C0:
			{
				current_line = LINES_1C0_2C0;
				
				sn74hc135n_strobe_channels(0);
				sn74hc135n_select_lines(LINES_1C0_2C0);
				sn74hc135n_strobe_channels(1);
				
				next_state_after_period = SAMPLE_1C1_2C1;
				state = SAMPLING;
				break;
			}
			
			case SAMPLE_1C1_2C1:
			{
				current_line = LINES_1C1_2C1;
				
				sn74hc135n_strobe_channels(0);
				sn74hc135n_select_lines(LINES_1C1_2C1);
				sn74hc135n_strobe_channels(1);
				
				next_state_after_period = SAMPLE_1C2_2C2;
				state = SAMPLING;
				break;
			}
			
			case SAMPLE_1C2_2C2:
			{
				current_line = LINES_1C2_2C2;
				
				sn74hc135n_strobe_channels(0);
				sn74hc135n_select_lines(LINES_1C2_2C2);
				sn74hc135n_strobe_channels(1);
				
				next_state_after_period = SAMPLE_1C3_2C3;
				state = SAMPLING;
				break;
			}
			
			case SAMPLE_1C3_2C3:
			{
				current_line = LINES_1C3_2C3;
				
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
					/* stop. */
					counters_halt();
					
					/* start processing */
					state = PROCESSING;
				}
				
				break;
			}
			
			case PROCESSING:
			{
				/* register values */
				uint_fast8_t index = get_channel_index(current_line);
				channel_1_buffer[index] = counter1_get();
				channel_2_buffer[index] = counter2_get();
				
				/* switch state */
				state = OUTPUT;
				
				break;
			}
			
			case OUTPUT:
			{
				/* find the largest value */
				counter_t largest_value = 0;
				int_fast8_t index_of_largest = -1;
				
				/* find the index of the largest value */
				for (uint_fast8_t i=0; i<NUM_LINES; ++i)
				{
					counter_t value_of_channel_1 = channel_1_buffer[i];
					counter_t value_of_channel_2 = channel_2_buffer[i];

					/* NOTE that the following check order depends entirely on the board
					   layout. The bottom-most sensor is 2C0, followed by 1C0, then 2C1, 1C1 etc. */

					/* check channel 2 */
					if (value_of_channel_2 >= largest_value)
					{
						largest_value = value_of_channel_2;
						index_of_largest = i*2; /* times two because there are two parallel channels */
					}
					
					/* check channel 1 */
					if (value_of_channel_1 >= largest_value)
					{
						largest_value = value_of_channel_1;
						index_of_largest = i*2 + 1;
					}
				}
				
				/* output the index */
				usart_comm_send_char(index_of_largest);
				
				/* switch state */
				state = ADVANCE;
				
				break;
			}
			
			case ADVANCE:
			{
				/* switch state */
				state = next_state_after_period;
				
				/* Reset timer/counter! */
				counters_reset_restart();

				/* ignore time spent handling this */
				start_millis = millis();
				
				/* toggle LED */
				led = !led;
				set_internal_led(led);
				
				break;
			}
		}
	}
}