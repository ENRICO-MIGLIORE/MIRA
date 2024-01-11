#include "siemens_open62541__private.h"


int siemens_open62541__set_id (int md, char* buffer, size_t buffer_len)
{

	char* buf;
	size_t buffer_size;
	int rc;

	//pthread_mutex_lock(&so->pthread_mutex);

	//buf = so->machine[md].config.model;
	//buffer_size = sizeof(so->machine[md].config.model) - 1;  /* -1 is the room we need to safely terminate the string */

	//rc = siemens_open62541__private__check_parameters_and_agent_status_2(md, buf, buffer_size, buffer_len);
	//if (rc == 0)
	//{
	//	memcpy(buf, buffer, buffer_len);
	//	buf[buffer_len] = '\0';
	//}

	//pthread_mutex_unlock(&so->pthread_mutex);

	//return rc;
}
