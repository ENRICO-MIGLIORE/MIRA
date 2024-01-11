#include "fanuc_focas__private.h"


void* fanuc_focas__private__thread (void* arg)
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
	
	
	ff->thread_sleep_time_milliseconds = ff->config.thread_sleep_time_seconds * 1000;
	ff->thread_ticks_milliseconds = 0;
	ff->thread_started = 1;


	while (1)
	{	


		/* 
		 * enter critical section
		 */
		pthread_mutex_lock(&ff->thread_mutex);



		fanuc_focas__private__task__read_machines_data();

		fanuc_focas__private__task__connection_monitor();
		
		fanuc_focas__private__task__simulate_machines_data();

		fanuc_focas__private__task__estimate_cycle_time_from_part_counter();


		/*
		 * exit critical section
		 */
		pthread_mutex_unlock(&ff->thread_mutex);

		/* utils__printf__info(&ff->pf, "fanuc_focas__private__thread()", 0, "thread sleep time milliseconds = %zu", ff->thread_sleep_time_milliseconds); */

		ff->thread_ticks_milliseconds += ff->thread_sleep_time_milliseconds;
		
		utils__platform__sleep_milliseconds(ff->thread_sleep_time_milliseconds);
		
		
	}

	return NULL;

}

