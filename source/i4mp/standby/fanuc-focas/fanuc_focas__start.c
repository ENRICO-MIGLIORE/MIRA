#include "fanuc_focas__private.h"


static char *fn = "fanuc_focas__start()";


int fanuc_focas__start (void)
{

	int rc;
	int error;

	rc = fanuc_focas__allocate_clients();
	if (rc != 0)
	{
		error = -100;
		utils__printf__error(&ff->pf, fn, error, "fanuc_focas__allocate_clients() returned %d", rc);
		return error;
	}

	/*
	 * Set sleep time to its default vale
	 */
	ff->pthread_sleep_time_seconds = 5000;


	ff->pthread_mutex = PTHREAD_MUTEX_INITIALIZER;
	rc = pthread_create(&ff->pthread_id, NULL, fanuc_focas__thread, NULL);
	if (rc != 0)
	{
		error = -200;
		utils__printf__error(&ff->pf, fn, error, "pthread_create() returned %d", rc);
		return error;
	}

	utils__printf__info(&ff->pf, fn, 0, "pthread started");

	return 0;
}


