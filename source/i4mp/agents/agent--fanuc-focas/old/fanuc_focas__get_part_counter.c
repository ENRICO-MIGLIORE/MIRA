#include "fanuc_focas__private.h"


int fanuc_focas__get_part_counter (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int flag;
	size_t buffer_size_min;
	int rc;

	flag = 0;

	buffer_size_min = FANUC_FOCAS__CONFIG__BUFFER_SIZE_256;

	rc = fanuc_focas__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);

	if ((rc == 0) && (ff->machine_count > 0))
	{
		pthread_mutex_lock(&ff->thread_mutex);

		if (ff->machine[md].part_counter_valid == 1)
		{
			strcpy(buffer, ff->machine[md].part_counter_utf_8);
			*buffer_len = ff->machine[md].part_counter_utf_8_len;
			flag = 1;
		}

		pthread_mutex_unlock(&ff->thread_mutex);
	}


	if (flag == 0)
	{
		buffer[0] = '-';    /* part_counter is unknown */
		buffer[1] = '\0';
		*buffer_len = 1;
	}


	return 0;
}







