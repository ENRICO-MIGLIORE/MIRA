#include "agency_private.h"
 

//int agency__private__get_machine_data (int data_id, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//
//int agency__get_machine_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len)
//{
//
//	int rc;
//	//int i;
//	//int j;
//	//size_t buffer_size_min;
//
//	rc = agency__private__get_machine_data(AGENCY__MACHINE_ID, md, buffer, buffer_size, buffer_len);
//
//	return rc;
//
//
//	//if (agency == NULL)
//	//{
//	//	return -100;
//	//}
//
//	//if (agency->started != 1)
//	//{
//	//	return -200;
//	//}
//
//	//rc = agency__private__convert_machine_descriptor_to_agent_descriptor(md, &i, &j);
//	//if (rc != 0)
//	//{
//	//	return -300;
//	//}
//
//
//	//buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE;
//
//
//	//pthread_mutex_lock(&agency->agent[i].machine[j].thread_mutex);
//
//
//	//rc = agency__private__check_machine_and_input_parameters(&agency->agent[i].machine[j], buffer, buffer_size, buffer_size_min, buffer_len);
//
//	//if (rc == 0)
//	//{
//	//	(void)sprintf(buffer, "%d", agency->agent[i].machine[j].config_2.id);
//	//	*buffer_len = strlen(buffer);
//	//}
//	//else
//	//{
//	//	buffer[0] = '-';    /* data not available */
//	//	buffer[1] = '\0';
//	//	*buffer_len = 1;
//	//}
//
//
//	//pthread_mutex_unlock(&agency->agent[i].machine[j].thread_mutex);
//
//
//	//return 0;
//
//}
//

int agency__private__get_machine_data (int data_id, int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int rc;
	int i;
	int j;
	size_t buffer_size_min;
	

	if (agency == NULL)
	{		
		return -100;
	}

	if (agency->started != 1)
	{
		return -200;
	}

	rc = agency__private__convert_machine_descriptor_to_agent_descriptor(md, &i, &j);
	if (rc != 0)
	{
		return -300;
	}
	

	pthread_mutex_lock(&agency->agent[i].machine[j].thread_mutex);
	
	buffer_size_min = AGENCY__CONFIG__BUFFER_SIZE;

	rc = agency__private__check_machine_and_input_parameters(&agency->agent[i].machine[j], buffer, buffer_size, buffer_size_min, buffer_len);
	if (rc == 0)
	{

		buffer[0] = '-';    /* the default is: data not available */
		buffer[1] = '\0';

		switch (data_id)
		{

		case AGENCY__MACHINE_ID:
			(void)sprintf(buffer, "%d", agency->agent[i].machine[j].config_2.id);
			break;

		case AGENCY__MACHINE_NAME:
			strcpy(buffer, agency->agent[i].machine[j].config_2.name);
			break;

		case AGENCY__MACHINE_PART_COUNTER:
			if (agency->agent[i].machine[j].part_counter_valid == 1)
			{
				strcpy(buffer, agency->agent[i].machine[j].part_counter);
			}
			break;

		case AGENCY__MACHINE_CYCLE_TIME:
			if (agency->agent[i].machine[j].cycle_time_valid == 1)
			{
				strcpy(buffer, agency->agent[i].machine[j].cycle_time);
			}
			break;

		case AGENCY__MACHINE_PART_PROGRAM_NAME:
			if (agency->agent[i].machine[j].part_program_name_valid == 1)
			{
				strcpy(buffer, agency->agent[i].machine[j].part_program_name);
			}
			break;		

		case AGENCY__MACHINE_STATUS_RUN:
			if (agency->agent[i].machine[j].machine_status_run_valid == 1)
			{
				strcpy(buffer, agency->agent[i].machine[j].machine_status_run);
			}
			break;

		case AGENCY__MACHINE_STATUS_ALARM:
			if (agency->agent[i].machine[j].machine_status_alarm_valid == 1)
			{
				strcpy(buffer, agency->agent[i].machine[j].machine_status_alarm);
			}
			break;

		default:
			break;
		}

		*buffer_len = strlen(buffer);
	}
	else
	{
		buffer[0] = '-';    /* data not available */
		buffer[1] = '\0';
		*buffer_len = 1;
	}

	pthread_mutex_unlock(&agency->agent[i].machine[j].thread_mutex);


	return 0;

}

