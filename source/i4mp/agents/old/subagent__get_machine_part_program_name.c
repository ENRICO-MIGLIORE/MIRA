#include "subagent.h"


int subagent__get_machine_part_program_name (subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	pthread_mutex_lock(&machine->thread_mutex);      /* enter critical section */

	buffer_size_min = sizeof(machine->part_program_name);

	rc = subagent__check_machine_and_input_parameters(machine, buffer, buffer_size, buffer_size_min, buffer_len);

	if ((rc == 0) && (machine->part_program_name_valid == 1))
	{
		strcpy(buffer, machine->part_program_name);
		*buffer_len = strlen(buffer);
	}
	else
	{
		if (buffer_size >= 2)
		{
			buffer[0] = '-';    /* data not available */
			buffer[1] = '\0';
			*buffer_len = 1;
			rc = 0;
		}
		else
		{
			rc = -1000;
		}
	}


	pthread_mutex_unlock(&machine->thread_mutex);    /* exit critical section */



	return rc;
}