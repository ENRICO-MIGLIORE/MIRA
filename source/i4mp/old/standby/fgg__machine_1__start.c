#include "../fgg.h"
#include "fgg__machine_1.h"



extern void *fgg__machine__1__thread (void *arg);


void *fgg__machine__1__thread (void *arg)
{


	//while (1)

	while (1)
	{
		//printf("carmelo\r\n");
	}

	//Sleep(5000);


	*((int *)arg) = 127;


	pthread_exit(arg);

	/* Never reached. */
	//exit(1);
}


int fgg__machine_1__start (void)
{
	pthread_t id_1;
	pthread_t id_2;
	int rc;
	void *result;
	int ciao;


	ciao = 124;


	result = &ciao;


	rc = pthread_create (&id_1, NULL, fgg__machine__1__thread, result);



	return rc;
}




