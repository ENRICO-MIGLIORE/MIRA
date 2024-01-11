#include "okuma_mt__private.h"


int okuma_mt__get_production_status (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;
	int flag;

	flag = 0;
	
	buffer_size_min = OKUMA_MT__CONFIG__BUFFER_SIZE_256;

	rc = okuma_mt__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);

	if ((rc == 0) && (om->machine_count > 0) && (om->machine[md].connection_status_valid == 1) && (om->machine[md].connection_status > 0))
	{
		pthread_mutex_lock(&om->thread_mutex);

		if (om->machine[md].production_status_valid == 1)
		{
			flag = 1;

			if (om->machine[md].production_status == 0)
			{
				buffer[0] = '0';    /* machine is not producing */
			}
			else
			{
				buffer[0] = '1';    /* machine is producing */
			}
		}

		pthread_mutex_unlock(&om->thread_mutex);
	}

	if (flag == 0)
	{
		buffer[0] = '-';    /* not available */
	}

	buffer[1] = '\0';
	*buffer_len = 1;


	return 0;
}

