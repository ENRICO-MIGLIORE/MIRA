#include "fanuc_focas__private.h"


void* fanuc_focas__thread (void* arg)
{

	int rc;
	size_t machine_id;
	unsigned int seed;
	time_t t;
	size_t milliseconds;


	arg = arg;   /* ktch = keep the compiler happy */

	/*
	 * Initialization is called once:   t = time(NULL);
	 *
	 * In a threaded application we make sure that the generator's state
	 * is stored per thread and seed the generator once for each thread
	 *
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


	for (machine_id = 1; machine_id <= ff->machine_count; machine_id++)
	{
		rc = fanuc_focas__connect_to_machine(machine_id);
	}

	milliseconds = ff->pthread_sleep_time_seconds * 1000;
	ff->pthread_started = 1;

	while (1)
	{

		pthread_mutex_lock(&ff->pthread_mutex);     /* enter thread critical section */


		for (machine_id = 1; machine_id <= ff->machine_count; machine_id++)
		{
			(void)fanuc_focas__read_part_counter(machine_id);

			(void)fanuc_focas__read_cycle_time(machine_id);
		}

		pthread_mutex_unlock(&ff->pthread_mutex);     /* exit thread critical section */


		utils__platform__sleep_milliseconds(milliseconds);

	}

	return NULL;

}
