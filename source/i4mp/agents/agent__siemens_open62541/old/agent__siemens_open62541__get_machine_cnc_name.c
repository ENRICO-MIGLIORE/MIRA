#include "agent__siemens_open62541__private.h"


int agent__siemens_open62541__get_machine_cnc_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	//size_t buffer_size_min;
	//int rc;


	//buffer_size_min = SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256;

	//rc = agent__siemens_open62541__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);

	//if ((rc == 0) && (so->number_of_machines > 0))
	//{
	//	pthread_mutex_lock(&so->thread_mutex);

	//	strcpy(buffer, so->machine[md].config.cnc_name);

	//	pthread_mutex_unlock(&so->thread_mutex);

	//	*buffer_len = strlen(buffer);
	//}
	//else
	//{
	//	buffer[0] = '-';
	//	buffer[1] = '\0';
	//	*buffer_len = 1;
	//}


	//int rc;

	//rc = delegate__get_cnc_name(so_2->delegate, md, buffer, buffer_size, buffer_len);

	//return rc;

	return 0;
}