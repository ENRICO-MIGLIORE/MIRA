#include "lathe_machines_agent.h"




extern int lathe_machines_agent__check_parameters(lathe_machines_agent_t* proxy, size_t machine_id, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);



int lathe_machine__get_part_counter (lathe_machines_agent_t* proxy, size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int rc;
	size_t fd;


	rc = lathe_machines_agent__check_parameters(proxy, machine_id, buffer, buffer_size, 64, buffer_len);
	if (rc != 0)
	{
		return -100;
	}

	fd = machine_id - 1;


	if (proxy->lathe_machine[fd].connected == 0)
	{
		return -600;
	}

	pthread_mutex_lock(&proxy->pthread_mutex);

	if (proxy->started != 1)
	{
		pthread_mutex_unlock(&proxy->pthread_mutex);
		return -700;
	}


	if (proxy->lathe_machine[fd].part_counter_valid != 1)
	{
		pthread_mutex_unlock(&proxy->pthread_mutex);
		return -800;
	}

	strcpy(buffer, proxy->lathe_machine[fd].part_counter_utf_8);
	*buffer_len = proxy->lathe_machine[fd].part_counter_utf_8_len;

	pthread_mutex_unlock(&proxy->pthread_mutex);


	return 0;
}






