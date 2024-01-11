#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;
extern void* fanuc_focas__thread(void* arg);
extern int fanuc_focas__create_machines_client(void);


static char *fn = "fanuc_focas__start()";


int fanuc_focas__start (void)
{

	int rc;
	int error;

	rc = fanuc_focas__create_machines_client();
	if (rc != 0)
	{
		error = -100;
		utils__printf__error(&fanuc_focas->pf, fn, error, "fanuc_focas__create_machines_client() returned %d", rc);
		return error;
	}

	//rc = fanuc_focas__create_client();

	//if (rc != 0)
	//{
	//	return -100;
	//}


	fanuc_focas->pthread_mutex = PTHREAD_MUTEX_INITIALIZER;
	rc = pthread_create(&fanuc_focas->pthread_id, NULL, fanuc_focas__thread, NULL);
	if (rc != 0)
	{
		error = -200;
		utils__printf__error(&fanuc_focas->pf, fn, error, "pthread_create() returned %d", rc);
		return error;
	}

	return 0;
}


