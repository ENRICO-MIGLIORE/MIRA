#include "agent__siemens_open62541__private.h"


int agent__siemens_open62541__start (void)
{
	int rc;
	int i;
	int done;
	size_t milliseconds;
	const char* fn;
	

	//fn = "agent__siemens_open62541__start()";


	///*
	// * create one thread per machine
	// */
	//for (i = 0; i < agent_so->number_of_machines; i++)
	//{
	//	agent_so->subagent.machine[i].thread_mutex = PTHREAD_MUTEX_INITIALIZER;

	//	rc = pthread_create(&agent_so->subagent.machine[i].thread_id, NULL, subagent__thread, (void *) &agent_so->subagent.machine[i]);
	//	if (rc != 0)
	//	{
	//		utils__printf__error(&agent_so->subagent.pf, fn, -200, "pthread_create() returned %d - machine id = %d", rc, agent_so->subagent.machine[i].config_2.id);
	//		return -200;
	//	}

	//	/*
	//	 * Wait for the thread to start
	//	 */
	//	done = 0;
	//	milliseconds = 100;
	//	do
	//	{
	//		utils__platform__sleep(milliseconds);

	//		pthread_mutex_lock(&agent_so->subagent.machine[i].thread_mutex);

	//		if (agent_so->subagent.machine[i].thread_started == 1)
	//		{
	//			done = 1;
	//		}

	//		pthread_mutex_unlock(&agent_so->subagent.machine[i].thread_mutex);


	//	} while (done == 0);


	//	agent_so->subagent.machine[i].started = 1;
	//}

	////agent_so->subagent.started = 1;
	//agent_so->started = 1;

	return 0;
}


