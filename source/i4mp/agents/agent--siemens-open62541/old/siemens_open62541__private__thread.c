#include "siemens_open62541__private.h"

#if 0
void* siemens_open62541__private__thread__good (void* arg)
{

	int i;
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
		seed = (unsigned int)t;
	}
	srand(seed);


	pthread_mutex_lock(&so->thread_mutex);

	for (i = 0; i < so->machine_count; i++)
	{
		(void) siemens_open62541__private__connect_to_machine(i);
	}

	pthread_mutex_unlock(&so->thread_mutex);


	so->thread_sleep_time_milliseconds = so->config.thread_sleep_time_seconds * 1000;
	so->thread_ticks_milliseconds = 0;
	so->thread_started = 1;


	while (1)
	{


		/*
		 * enter critical section
		 */
		pthread_mutex_lock(&so->thread_mutex);		


		siemens_open62541__private__task__read_machines_data();

		siemens_open62541__private__task__connection_monitor();

		siemens_open62541__private__task__simulate_machines_data();


		/*
		 * exit critical section
		 */
		pthread_mutex_unlock(&so->thread_mutex);


		/*
		 * utils__printf__info(&so->pf, "siemens_open62541__private__thread()", 0, "thread sleep time milliseconds = %zu", so->thread_sleep_time_milliseconds);
		 */

		so->thread_ticks_milliseconds += so->thread_sleep_time_milliseconds;

		utils__platform__sleep_milliseconds(so->thread_sleep_time_milliseconds);


	}

	return NULL;

}

#endif