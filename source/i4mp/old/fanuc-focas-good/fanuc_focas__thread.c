#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;
extern int fanuc_focas__connect_to_lathe_machine(size_t machine_id);
extern int fanuc_focas__create_client(void);
extern int fanuc_focas__read_part_counter__real(size_t machine_id);


static char *fn = "fanuc_focas__thread()";


//int siemens_opc_clear_client (UA_Client* client)
//{
//
//	UA_Client_disconnect(client);
//	UA_Client_delete(client);
//
//	return 0;
//}




extern int fanuc_focas__read_part_counter(size_t machine_id);
extern int fanuc_focas__read_cycle_time(size_t machine_id);


void* fanuc_focas__thread (void* arg)
{

	int rc;
	size_t machine_id;
	unsigned int seed;
	time_t t;


	arg = arg;   /* ktch = keep the compiler happy */

	/*
	 * Initialization is called once:   t = time(NULL);
	 * 
	 * In a threaded application we make sure that the generator's state
	 * is stored per thread and seed the generator once for each thread
	 * 
	 */
	t = time(NULL);
	if (t < 0)
	{
		seed = 100;
	}
	else
	{
		seed = (unsigned int) t;
	}
	srand(seed);


	for (machine_id = 1; machine_id <= fanuc_focas->num_machines; machine_id++)
	{
		rc = fanuc_focas__connect_to_lathe_machine(machine_id);
	}
	
	
	fanuc_focas->started = 1;

	while (1)
	{

		utils__platform__sleep_milliseconds(2000);


		pthread_mutex_lock(&fanuc_focas->pthread_mutex);     /* enter thread critical section */


		for (machine_id = 1; machine_id <= fanuc_focas->num_machines; machine_id++)
		{		
		    (void) fanuc_focas__read_part_counter(machine_id);

		    (void) fanuc_focas__read_cycle_time(machine_id);
		}

		pthread_mutex_unlock(&fanuc_focas->pthread_mutex);     /* exit thread critical section */

	}

	return NULL;

}