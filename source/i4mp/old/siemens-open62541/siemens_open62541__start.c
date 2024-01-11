#include "siemens_open62541__private.h"


static char *fn = "siemens_open62541__start()";


int siemens_open62541__start(void)
{
	int i;
	int rc;
	int done;
	size_t milliseconds;


	for (i = 0; i < so->machine_count; i++)
	{
		rc = siemens_open62541__private__allocate_machine_resources(i);
		if (rc != 0)
		{
			utils__printf__error(&so->pf, fn, -100, "siemens_open62541__private__allocate_machine_resources() returned %d", fn, rc);
			return -100;
		}
	}


	/*
	 * Set thread's sleep time to its default vale
	 */
	so->pthread_sleep_time_seconds = 5;


	so->pthread_mutex = PTHREAD_MUTEX_INITIALIZER;
	rc = pthread_create(&so->pthread_id, NULL, siemens_open62541__private__thread, NULL);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -200, "pthread_create() returned %d", fn, rc);
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

		pthread_mutex_lock(&so->pthread_mutex);

		if (so->pthread_started == 1)
		{
			done = 1;
		}

		pthread_mutex_unlock(&so->pthread_mutex);


	} 
	while (done == 0);


	so->started = 1;


	return 0;
}


#if 0
int siemens_open62541__start(void)
{
	int i;
	int rc;
	int done;
	size_t milliseconds;


	for (i = 0; i < so->machine_count; i++)
	{
		rc = siemens_open62541__private__allocate_machine_resources(i);
		if (rc != 0)
		{
			utils__printf__error(&so->pf, fn, -100, "siemens_open62541__private__allocate_machine_resources() returned %d", fn, rc);
			return -100;
		}
	}


	/*
	 * Set thread's sleep time to its default vale
	 */
	so->pthread_sleep_time_seconds = 5;


	so->pthread_mutex = PTHREAD_MUTEX_INITIALIZER;
	rc = pthread_create(&so->pthread_id, NULL, siemens_open62541__private__thread, NULL);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -200, "pthread_create() returned %d", fn, rc);
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

		pthread_mutex_lock(&so->pthread_mutex);

		if (so->pthread_started == 1)
		{
			done = 1;
		}

		pthread_mutex_unlock(&so->pthread_mutex);
	} while (done == 0);


	so->started = 1;


	return 0;
}
#endif