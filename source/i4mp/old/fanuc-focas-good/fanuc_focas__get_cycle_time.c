#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;


static char* fn = "fanuc_focas__get_cycle_time()";


int fanuc_focas__get_cycle_time (size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t fd;

	if (machine_id > fanuc_focas->num_machines)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	if (buffer == NULL)
	{
		return -300;
	}

	if (buffer_len == NULL)
	{
		return -400;
	}

	if (buffer_size < 64)
	{
		return -500;
	}



	/*
	 * get machine descriptor
	 */
	fd = machine_id - 1;


	if (fanuc_focas->lathe_machine[fd].connected == 0)
	{
		return -600;
	}


	pthread_mutex_lock(&fanuc_focas->pthread_mutex);

	if (fanuc_focas->started != 1)
	{
		pthread_mutex_unlock(&fanuc_focas->pthread_mutex);
		return -600;
	}

	if (fanuc_focas->lathe_machine[fd].cycle_time_valid != 1)
	{
		pthread_mutex_unlock(&fanuc_focas->pthread_mutex);
		return -700;
	}

	strcpy(buffer, fanuc_focas->lathe_machine[fd].cycle_time_utf_8);
	*buffer_len = fanuc_focas->lathe_machine[fd].cycle_time_utf_8_len;

	pthread_mutex_unlock(&fanuc_focas->pthread_mutex);


	return 0;
}






