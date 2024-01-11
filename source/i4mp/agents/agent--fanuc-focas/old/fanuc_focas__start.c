#include "fanuc_focas__private.h"
 

static char *fn = "fanuc_focas__start()";


int fanuc_focas__start(void)
{
	int rc;
	int i;
	int done;
	size_t milliseconds;


	for (i = 0; i < ff->machine_count; i++)
	{
		if (ff->machine[i].config.networked == 0)
		{
			utils__printf__info(&ff->pf, fn, 0, "agent not connected to \"%s(%d)\"", ff->machine[i].config.name, ff->machine[i].config.id);			
		}
		else if (ff->machine[i].config.simulated == 1)
		{
			utils__printf__info(&ff->pf, fn, 0, "agent connected to \"%s(%d)\" in simulation mode", ff->machine[i].config.name, ff->machine[i].config.id);
		}
		else
		{
			utils__printf__info(&ff->pf, fn, 0, "agent will connect to \"%s(%d)\" in a few seconds", ff->machine[i].config.name, ff->machine[i].config.id);
		}		
	}



	ff->thread_mutex = PTHREAD_MUTEX_INITIALIZER;
	rc = pthread_create(&ff->thread_id, NULL, fanuc_focas__private__thread, NULL);
	if (rc != 0)
	{
		utils__printf__error(&ff->pf, fn, -200, "pthread_create() returned %d", rc);
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

		pthread_mutex_lock(&ff->thread_mutex);

		if (ff->thread_started == 1)
		{
			done = 1;
		}

		pthread_mutex_unlock(&ff->thread_mutex);


	} while (done == 0);


	ff->started = 1;


	return 0;
}


