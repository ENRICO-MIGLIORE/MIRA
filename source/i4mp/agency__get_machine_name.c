#include "agency_private.h"
 

int agency__get_machine_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int rc;

	rc = agency__private__get_machine_data(AGENCY__MACHINE_NAME, md, buffer, buffer_size, buffer_len);

	return rc;

}


//int agency__get_machine_name__good(int md, char* buffer, size_t buffer_size, size_t* buffer_len)
//{
//
//	int rc;
//	int i;
//	int j;
//	size_t buffer_size_min;
//
//
//	if (agency == NULL)
//	{
//		return -100;
//	}
//
//	if (agency->started != 1)
//	{
//		return -200;
//	}
//
//	rc = agency__private__convert_machine_descriptor_to_agent_descriptor(md, &i, &j);
//	if (rc != 0)
//	{
//		return -300;
//	}
//
//
//	buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE;
//
//
//	pthread_mutex_lock(&agency->agent[i].machine[j].thread_mutex);
//
//
//	rc = agency__private__check_machine_and_input_parameters(&agency->agent[i].machine[j], buffer, buffer_size, buffer_size_min, buffer_len);
//
//	if (rc == 0)
//	{
//		strcpy(buffer, agency->agent[i].machine[j].config_2.name);
//		*buffer_len = strlen(buffer);
//	}
//	else
//	{
//		buffer[0] = '-';    /* data not available */
//		buffer[1] = '\0';
//		*buffer_len = 1;
//	}
//
//
//	pthread_mutex_unlock(&agency->agent[i].machine[j].thread_mutex);
//
//
//	return 0;
//
//}






