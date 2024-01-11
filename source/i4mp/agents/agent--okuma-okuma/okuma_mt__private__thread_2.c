#include "okuma_mt__private.h"
#include <okuma_mt__platform__private.h>


void* okuma_mt__private__thread_2 (void* arg)
{

	arg = arg;   /* keep the compiler happy */


	om->thread_2_sleep_time_milliseconds = om->config.thread_sleep_time_seconds * 1000;	
	om->thread_2_ticks_milliseconds = 0;
	om->thread_2_started = 1;

	while (1)
	{		

		/* 
		 * critical sections are handled inside function  read_machine_data_stream()
		 */

		okuma_mt__platform__private__task__read_machine_data_stream();
		

		okuma_mt__private__task__estimate_cycle_time_from_part_counter();




		om->thread_2_ticks_milliseconds += om->thread_2_sleep_time_milliseconds;

		utils__platform__sleep_milliseconds(om->thread_2_sleep_time_milliseconds);

		utils__printf__info(&om->pf, "okuma_mt__private__thread_2()", 0, "sleep time milliseconds = %zu - ticks = %zu", om->thread_2_sleep_time_milliseconds, om->thread_2_ticks_milliseconds);


		if (om->cycle_time_estimation_from_part_counter_in_progress == 1)
		{
			om->thread_2_sleep_time_milliseconds = 1000;                                          /* set thread's sleep time to 1 second */
		}
		else
		{
			om->thread_2_sleep_time_milliseconds = om->config.thread_sleep_time_seconds * 1000;   /* restore thread's sleep time */
		}

	}
	


	return NULL;

}

