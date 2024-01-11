#include "okuma_mt__private.h"

#include <okuma_mt__platform__private.h>


static char *fn = "okuma_mt__start()";


int okuma_mt__start (void)
{
	int i;
	int rc;
	int done;
	size_t milliseconds;


	rc = okuma_mt__platform__private__start();
	if (rc != 0)
	{
		utils__printf__error(&om->pf, fn, -100, "okuma_mt__platform__private__start() returned %d", fn, rc);
		return -100;
	}


	for (i = 0; i < om->machine_count; i++)
	{
		rc = okuma_mt__private__allocate_machine_resources(i);
		if (rc != 0)
		{			
			utils__printf__error(&om->pf, fn, -200, "okuma_mt__private__allocate_machine_resources() returned %d", fn, rc);
			return -200;
		}
	}



	/*
	 * Set thread's sleep time to its default vale
	 */
	om->pthread_sleep_time_seconds = 5;


	om->pthread_mutex = PTHREAD_MUTEX_INITIALIZER;
	rc = pthread_create(&om->pthread_id, NULL, okuma_mt__private__thread, NULL);
	if (rc != 0)
	{
		utils__printf__error(&om->pf, fn, -200, "pthread_create() returned %d", fn, rc);		
		return -300;
	}


	/*
	 * Wait for the thread to start
	 */
	done = 0;
	milliseconds = 400;
	do
	{
		utils__platform__sleep_milliseconds(milliseconds);

		pthread_mutex_lock(&om->pthread_mutex);

		if (om->pthread_started == 1)
		{
			done = 1;
		}

		pthread_mutex_unlock(&om->pthread_mutex);
	} 
	while (done == 0);
	

	om->started = 1;


	return 0;
}
