#include "subagent.h"


int subagent__get_machine_run_mode_status (subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE;


	pthread_mutex_lock(&machine->thread_mutex);


	rc = subagent__check_machine_and_input_parameters(machine, buffer, buffer_size, buffer_size_min, buffer_len);

	if (rc == 0)
	{
		if (machine->config_2.operating_mode == 0)
		{
			buffer[0] = '0';   /* machine is in simulation mode */
		}
		else
		{
			buffer[0] = '1';   /* machine is in operating_mode mode */
		}
	}
	else
	{
		buffer[0] = '-';    /* data not available */
	}

	buffer[1] = '\0';
	*buffer_len = 1;


	pthread_mutex_unlock(&machine->thread_mutex);


	return 0;
}

//
//int subagent__get_machine_run_mode_status(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len)
//{
//
//	size_t buffer_size_min;
//	int rc;
//
//
//	buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE;
//
//
//	rc = subagent__check_machine_and_input_parameters(machine, buffer, buffer_size, buffer_size_min, buffer_len);
//
//	//if ((rc == 0) && (machine->number_of_machines > 0))
//	//{
//	//	//pthread_mutex_lock(&delegate->thread_mutex);
//
//	//	if (machine->machine_local[md].config_2.operating_mode == 0)
//	//	{
//	//		buffer[0] = '0';
//	//	}
//	//	else
//	//	{
//	//		buffer[0] = '1';
//	//	}
//
//	//	//pthread_mutex_unlock(&delegate->thread_mutex);
//	//}
//	//else
//	//{
//	//	buffer[0] = '-';
//
//	//}
//
//	buffer[1] = '\0';
//	*buffer_len = 1;
//
//	return 0;
//
//}

