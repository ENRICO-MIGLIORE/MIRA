#include "subagent.h"

//
//int subagent__get_total_number_of_machines (subagent_t* subagent, char* buffer, size_t buffer_size, size_t* buffer_len)
//{
//
//	int len;
//	size_t buffer_size_min;
//	int rc;
//
//	buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE_256;
//
//	//rc = subagent__check_subagent_and_input_parameters(subagent, buffer, buffer_size, buffer_size_min, buffer_len);
//
//
//	rc = 0;
//	if (rc == 0)
//	{
//		
//		//pthread_mutex_lock(&delegate->thread_mutex);
//
//		len = sprintf(buffer, "%zu", subagent->number_of_machines);
//
//		//pthread_mutex_unlock(&delegate->thread_mutex);
//
//		*buffer_len = strlen(buffer);
//	}
//	else
//	{
//		buffer[0] = '-';
//		buffer[1] = '\0';
//		*buffer_len = 1;
//	}
//
//	
//	return 0;
//}
