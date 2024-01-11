#include "machine.h"


int machine__start (subagent__machine_t* machine)
{
	int rc;

	int done;
	size_t milliseconds;
	const char* fn;


	fn = "machine__start()";


	//for (i = 0; i < machine->machine_count; i++)
	{
		if (machine->config_2.networked == 0)
		{
			//utils__printf__info(&machine->pf, fn, 0, "can't connect to %s - machine id = %d is not networked", machine->machine[i].config_2.name, machine->machine[i].config_2.id);
		}
		else if (machine->config_2.simulated == 1)
		{
			//utils__printf__info(&machine->pf, fn, 0, "connected to %s in simulation mode - machine id = %d", machine->machine[i].config_2.name, machine->machine[i].config_2.id);
		}
		else
		{
			//utils__printf__info(&machine->pf, fn, 0, "connecting to %s in a few seconds - machine id = %d", machine->machine[i].config_2.name, machine->machine[i].config_2.id);
		}
	}


	/*
	 * start one thread per machine
	 */
	//for (i = 0; i < machine->machine_count; i++)
	{
		
		machine->thread_mutex = PTHREAD_MUTEX_INITIALIZER;

		rc = pthread_create(&machine->thread_id, NULL, subagent__thread, (void*) machine);
		if (rc != 0)
		{
			//utils__printf__error(&machine->pf, fn, -1000, "pthread_create() returned %d", rc);
			return -1000;
		}


		/*
		 * Wait for the thread to start
		 */
		done = 0;
		milliseconds = 100;
		do
		{
			utils__platform__sleep_milliseconds(milliseconds);

			pthread_mutex_lock(&machine->thread_mutex);

			if (machine->thread_started == 1)
			{
				done = 1;
			}

			pthread_mutex_unlock(&machine->thread_mutex);


		} 
		while (done == 0);

	}


	machine->started = 1;


	return 0;
}