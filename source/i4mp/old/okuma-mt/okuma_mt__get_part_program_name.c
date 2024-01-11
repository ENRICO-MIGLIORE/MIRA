#include "okuma_mt__private.h"


int okuma_mt__get_part_program_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = OKUMA_MT__CONFIG__BUFFER_SIZE_256;

	rc = okuma_mt__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc != 0)
	{
		return rc;
	}


	pthread_mutex_lock(&om->pthread_mutex);

	if (om->machine[md].config.online == 0)
	{
		*buffer_len = 0;            /* part program name is not available because agent is not configured to connect to machine */
	}
	else if (om->machine[md].part_program_name_valid != 1)
	{
		*buffer_len = 0;
	}
	else
	{
		strcpy(buffer, om->machine[md].part_program_name_utf_8);
		*buffer_len = om->machine[md].part_program_name_utf_8_len;
	}

	pthread_mutex_unlock(&om->pthread_mutex);


	return 0;
}

