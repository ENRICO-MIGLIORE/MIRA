#include "subagent.h"


// controllare questo (machine->number_of_machines > 0)


int subagent__get_machine_networked_status (subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE;


	pthread_mutex_lock(&machine->thread_mutex);


	rc = subagent__check_machine_and_input_parameters(machine, buffer, buffer_size, buffer_size_min, buffer_len);

	if (rc == 0)
	{
		if (machine->config_2.networked == 0)
		{
			buffer[0] = '0';   /* machine is not networked */
		}
		else
		{
			buffer[0] = '1';   /* machine is networked */
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

