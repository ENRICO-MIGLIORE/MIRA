#include "okuma_mt__private.h"


int okuma_mt__get_machine_count (char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int len;
	size_t buffer_size_min;
	int rc;
	int md;

	md = 0;   /* keep the compiler happy */


	buffer_size_min = OKUMA_MT__CONFIG__BUFFER_SIZE_256;


	rc = okuma_mt__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);


	if ((rc == 0) && (om->machine_count > 0))
	{
		pthread_mutex_lock(&om->thread_mutex);

		len = sprintf(buffer, "%d", om->machine_count);		

		pthread_mutex_unlock(&om->thread_mutex);

		*buffer_len = strlen(buffer);
		
	}
	else
	{
		buffer[0] = '-';
		buffer[1] = '\0';
		*buffer_len = 1;
	}



	return 0;
}