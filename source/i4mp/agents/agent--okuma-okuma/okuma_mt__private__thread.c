#include "okuma_mt__private.h"
#include <okuma_mt__platform__private.h>


void* okuma_mt__private__thread (void* arg)
{


	unsigned int seed;
	time_t t;


	arg = arg;   /* keep the compiler happy */

	/*
	 * srand() must be called once per thread in order to initialize the pseudo random numbers subsystem
	 */
	t = time(NULL);
	if (t < 0)
	{
		seed = 100;
	}
	else
	{
		seed = (unsigned int) t;
	}
	srand(seed);
	
	
	om->thread_sleep_time_milliseconds = om->config.thread_sleep_time_seconds * 1000;
	om->thread_ticks_milliseconds = 0;
	om->thread_started = 1;


	while (1)
	{	


		pthread_mutex_lock(&om->thread_mutex);                     /* enter critical section */


		okuma_mt__private__task__read_machines_data();

		okuma_mt__private__task__connection_monitor();
		
		okuma_mt__private__task__simulate_machines_data();


		pthread_mutex_unlock(&om->thread_mutex);                   /* exit critical section */
		

		om->thread_ticks_milliseconds += om->thread_sleep_time_milliseconds;
		
		utils__platform__sleep_milliseconds(om->thread_sleep_time_milliseconds);


		/* utils__printf__info(&om->pf, "okuma_mt__private__thread()", 0, "sleep time milliseconds = %zu - ticks = %zu", om->thread_sleep_time_milliseconds, om->thread_ticks_milliseconds);   */
		
		
	}

	return NULL;

}

 