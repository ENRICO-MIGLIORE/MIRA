#include "subagent.h"


int subagent__get_machine_type (subagent__machine_t* machine, int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE_256;


	//rc = subagent__check_machine_and_input_parameters(machine, md, buffer, buffer_size, buffer_size_min, buffer_len);


	//if ((rc == 0) && (machine->machine_count > 0))
	//{
	//	//pthread_mutex_lock(&delegate->thread_mutex);

	//	strcpy(buffer, machine->machine_local[md].config_2.type);

	//	//pthread_mutex_unlock(&delegate->thread_mutex);

	//	*buffer_len = strlen(buffer);
	//}
	//else
	//{
	//	buffer[0] = '-';
	//	buffer[1] = '\0';
	//	*buffer_len = 1;
	//}


	return 0;
}