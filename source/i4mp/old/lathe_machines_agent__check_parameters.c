#include "lathe_machine.h"



int lathe_machines_agent__check_parameters (lathe_machines_agent_t* agent, size_t machine_id, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len)
{

	if (agent == NULL)
	{
		return -100;
	}

	if (machine_id > agent->num_machines)
	{
		return -200;
	}

	if (machine_id == 0)
	{
		return -300;
	}

	if (buffer == NULL)
	{
		return -400;
	}

	if (buffer_len == NULL)
	{
		return -500;
	}

	if (buffer_size < buffer_size_min)
	{
		return -600;
	}

	return 0;

}

//int lathe_machine__get_part_counter (lathe_machine_application_t *application, size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len)
//{
//
//	int rc;
//	size_t fd;
//
//
//	rc = lathe_machine__check_parameters(application, machine_id, buffer, buffer_size, 64, buffer_len);
//
//	if (rc != 0)
//	{
//		return -100;
//	}
//
//
//	/*
//	 * get machine descriptor
//	 */
//	fd = machine_id - 1;
//
//
//
//	if (application->lathe_machine[fd].connected == 0)
//	{
//		return -600;
//	}
//
//
//	pthread_mutex_lock(&application->pthread_mutex);
//
//	if (application->started != 1)
//	{
//		pthread_mutex_unlock(&application->pthread_mutex);
//		return -700;
//	}
//
//
//	if (application->lathe_machine[fd].part_counter_valid != 1)
//	{
//		pthread_mutex_unlock(&application->pthread_mutex);
//		return -800;
//	}
//
//	strcpy(buffer, application->lathe_machine[fd].part_counter_utf_8);
//	*buffer_len = application->lathe_machine[fd].part_counter_utf_8_len;
//
//	pthread_mutex_unlock(&application->pthread_mutex);
//
//
//	return 0;
//}






