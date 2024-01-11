#include "machine.h"


int machine__stop (subagent__machine_t* machine)
{
	int rc;
	int i;
	int done;
	const char* fn;
	size_t milliseconds;


	fn = "machine__stop()";

	//for (i = 0; i < delegate->machine_count; i++)
	//{
	//	if (delegate->machine[i].config.networked == 0)
	//	{
	//		utils__printf__info(&delegate->pf, fn, 0, "subagent not connected to \"%s(%d)\"", delegate->machine[i].config.name, delegate->machine[i].config.id);
	//	}
	//	else if (delegate->machine[i].config.simulated == 1)
	//	{
	//		utils__printf__info(&delegate->pf, fn, 0, "subagent connected to \"%s(%d)\" in simulation mode", delegate->machine[i].config.name, delegate->machine[i].config.id);
	//	}
	//	else
	//	{
	//		utils__printf__info(&delegate->pf, fn, 0, "subagent will connect to \"%s(%d)\" in a few seconds", delegate->machine[i].config.name, delegate->machine[i].config.id);
	//	}
	//}


	//delegate->thread_mutex = PTHREAD_MUTEX_INITIALIZER;	
	//rc = pthread_create(&delegate->thread_id, NULL, thread, NULL);    //rc = pthread_create(&delegate->thread_id, NULL, siemens_open62541__private__thread, NULL);
	//if (rc != 0)
	//{
	//	utils__printf__error(&delegate->pf, fn, -200, "pthread_create() returned %d", rc);
	//	return -200;
	//}


	///*
	// * Wait for the thread to start
	// */
	//done = 0;
	//milliseconds = 100;
	//do
	//{
	//	utils__platform__sleep_milliseconds(milliseconds);

	//	pthread_mutex_lock(&delegate->thread_mutex);

	//	if (delegate->thread_started == 1)
	//	{
	//		done = 1;
	//	}

	//	pthread_mutex_unlock(&delegate->thread_mutex);


	//} while (done == 0);


	//delegate->started = 1;


	return 0;
}