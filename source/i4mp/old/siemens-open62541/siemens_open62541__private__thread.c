#include "siemens_open62541__private.h"


void* siemens_open62541__private__thread (void* arg)
{


	int i;
	unsigned int seed;
	time_t t;
	size_t milliseconds;


	arg = arg;   /* keep the compiler happy */

	milliseconds = so->pthread_sleep_time_seconds * 1000;


	/*
	 * srand() must be called once per thread in order to initialize the pseudo random numbers subsystem
	 */
	t = time(NULL);
	if (t < 0)
	{
		seed = 100;
	}
	else
	{
		seed = (unsigned int) t;
	}
	srand(seed);



	pthread_mutex_lock(&so->pthread_mutex);

	for (i = 0; i < so->machine_count; i++)
	{
		(void) siemens_open62541__private__connect_to_machine(i);
	}
		
	pthread_mutex_unlock(&so->pthread_mutex);


	so->pthread_started = 1;


	while (1)
	{	


		/* 
		 * enter thread critical section
		 */
		pthread_mutex_lock(&so->pthread_mutex);               


		siemens_open62541__private__task__read_machines_data();

		siemens_open62541__private__task__connection_monitor();
		
		siemens_open62541__private__task__simulate_machines_data();


		/*
		 * exit thread critical section
		 */
		pthread_mutex_unlock(&so->pthread_mutex);


		/*
		 * delay
		 */
		utils__platform__sleep_milliseconds(milliseconds);

		
	}

	return NULL;

}



//static void siemens_open62541__connection_monitor_task (void)
//{
//
//	int i;
//	int rc;
//	time_t t;
//
//	if (so->config.enable_connection_monitor_task == 0)
//	{
//		return;
//	}
//
//	for (i = 0; i < so->machine_count; i++)
//	{
//
//		if (so->machine[i].no_response_flag == 0)
//		{
//			so->machine[i].connection_monitor_task_state = 0;
//		}
//
//
//		switch (so->machine[i].connection_monitor_task_state)
//		{
//
//		case 0:
//
//			if (so->machine[i].no_response_flag == 1)
//			{			
//				t = time(NULL);
//				if (t > 0)
//				{
//					so->machine[i].no_response_time = t;
//					so->machine[i].connection_monitor_task_state = 1;
//				}				
//			}
//			break;
//
//		case 1:
//
//			t = time(NULL);
//			if (t > 0)
//			{
//				if (t < so->machine[i].no_response_time)
//				{
//					so->machine[i].connection_monitor_task_state = 0;
//				}
//				else if (t - so->machine[i].no_response_time >= (time_t) so->machine[i].config.no_response_timeout_seconds)
//				{
//					so->machine[i].connection_status = SIEMENS_OPEN62541__MACHINE_DISCONNECTED;
//					so->machine[i].connection_monitor_task_state = 2;
//				}
//			}
//			break;
//
//		case 2:
//			if (so->machine[i].reconnection_attempts >= so->machine[i].config.max_reconnection_attempts)
//			{
//				so->machine[i].connection_monitor_task_state = 100;
//			}
//			else
//			{
//				rc = siemens_open62541__reconnect_to_machine(i);				
//				if (rc == 0)
//				{
//					so->machine[i].connection_monitor_task_state = 3;
//				}
//				else
//				{
//
//				}
//			}
//			break;
//
//		case 3:
//			//rc = siemens_open62541__is_machine_connected(i);
//			rc = 0;
//			if (rc == 0)
//			{
//				so->machine[i].connection_status = SIEMENS_OPEN62541__MACHINE_CONNECTED;
//				so->machine[i].connection_monitor_task_state = 0;
//			}
//			else
//			{
//				t = time(NULL);
//				if (t > 0)
//				{
//					so->machine[i].no_response_time = t;
//					so->machine[i].connection_monitor_task_state = 4;
//				}
//				else
//				{
//
//				}
//			}
//			break;
//
//		case 4:
//			t = time(NULL);
//			if (t > 0)
//			{
//				if (t < so->machine[i].no_response_time)
//				{
//					so->machine[i].connection_monitor_task_state = 0;
//				}
//				else if (t - so->machine[i].no_response_time >= (time_t) so->machine[i].config.no_response_timeout_seconds)
//				{
//					so->machine[i].connection_status = SIEMENS_OPEN62541__MACHINE_DISCONNECTED;
//					so->machine[i].connection_monitor_task_state = 2;
//				}
//			}
//			break;
//
//		case 100:
//			so->machine[i].connection_monitor_task_state = 100;
//			break;
//
//
//		default:
//			so->machine[i].connection_monitor_task_state = 0;
//			break;
//		}
//	}
//}