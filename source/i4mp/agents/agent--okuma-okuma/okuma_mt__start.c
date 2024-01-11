#include "okuma_mt__private.h"
#include <okuma_mt__platform__private.h>
 

static char *fn = "okuma_mt__start()";


int okuma_mt__start(void)
{
	int rc;
	int i;
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
		if (om->machine[i].config.networked == 0)
		{
			utils__printf__info(&om->pf, fn, 0, "agent not connected to \"%s(%d)\"", om->machine[i].config.name, om->machine[i].config.id);			
		}
		else if (om->machine[i].config.simulated == 1)
		{
			utils__printf__info(&om->pf, fn, 0, "agent connected to \"%s(%d)\" in simulation mode", om->machine[i].config.name, om->machine[i].config.id);
		}
		else
		{
			utils__printf__info(&om->pf, fn, 0, "agent will connect to \"%s(%d)\" in a few seconds", om->machine[i].config.name, om->machine[i].config.id);
		}		
	}



	om->thread_mutex = PTHREAD_MUTEX_INITIALIZER;
	rc = pthread_create(&om->thread_id, NULL, okuma_mt__private__thread, NULL);
	if (rc != 0)
	{
		utils__printf__error(&om->pf, fn, -200, "pthread_create() returned %d", rc);
		return -200;
	}


	/*
	 * Wait for the thread to start
	 */
	done = 0;
	milliseconds = 100;
	do
	{
		utils__platform__sleep_milliseconds(milliseconds);

		pthread_mutex_lock(&om->thread_mutex);

		if (om->thread_started == 1)
		{
			done = 1;
		}

		pthread_mutex_unlock(&om->thread_mutex);


	} 
	while (done == 0);





	om->thread_2_mutex = PTHREAD_MUTEX_INITIALIZER;
	rc = pthread_create(&om->thread_2_id, NULL, okuma_mt__private__thread_2, NULL);
	if (rc != 0)
	{
		utils__printf__error(&om->pf, fn, -300, "pthread_create() returned %d", rc);
		return -300;
	}


	/*
	 * Wait for the thread to start
	 */
	done = 0;
	milliseconds = 100;
	do
	{
		utils__platform__sleep_milliseconds(milliseconds);

		pthread_mutex_lock(&om->thread_2_mutex);

		if (om->thread_2_started == 1)
		{
			done = 1;
		}

		pthread_mutex_unlock(&om->thread_2_mutex);


	} while (done == 0);

	om->started = 1;


	return 0;
}


