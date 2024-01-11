#include "okuma_mt__private.h"

#include <okuma_mt__platform__private.h>




void* okuma_mt__private__thread (void* arg)
{


	int i;
	unsigned int seed;
	time_t t;
	size_t milliseconds;


	arg = arg;   /* keep the compiler happy */

	milliseconds = om->pthread_sleep_time_seconds * 1000;


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



	pthread_mutex_lock(&om->pthread_mutex);

	for (i = 0; i < om->machine_count; i++)
	{
		(void) okuma_mt__private__connect_to_machine(i);
	}
		
	pthread_mutex_unlock(&om->pthread_mutex);


	om->pthread_started = 1;


	while (1)
	{	


		/* 
		 * enter critical section
		 */
		pthread_mutex_lock(&om->pthread_mutex);



		okuma_mt__platform__private__task__read_machine_data_stream();

		okuma_mt__private__task__read_machines_data();

		okuma_mt__private__task__connection_monitor();
		
		okuma_mt__private__task__simulate_machines_data();



		/*
		 * exit critical section
		 */
		pthread_mutex_unlock(&om->pthread_mutex);


		/*
		 * delay
		 */
		utils__platform__sleep_milliseconds(milliseconds);

		
	}

	return NULL;

}

