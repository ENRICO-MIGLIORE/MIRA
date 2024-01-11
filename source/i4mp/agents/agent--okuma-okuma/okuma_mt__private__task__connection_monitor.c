#include "okuma_mt__private.h"


// deve essere gestito da questo task
//om->machine[md].connection_status = 1;


#define INIT                0
#define WAIT_FOR_TIMEOUT    1

void okuma_mt__private__task__connection_monitor (void)
{

	int i;
	int rc;
	time_t t;
	time_t diff;
	size_t timeout_seconds;

	if (om->config.enable_connection_monitor_task == 0)
	{
		return;
	}

	timeout_seconds = 10;

	for (i = 0; i < om->machine_count; i++)
	{

		switch (om->machine[i].connection_monitor_task_state)
		{

		case INIT:

			if ((om->machine[i].connection_status_valid == 1) && (om->machine[i].connection_status > 0))
			{			
				t = time(NULL);
				if (t > 0)
				{
					om->machine[i].connection_monitor_start_time = t;
					om->machine[i].connection_monitor_connection_status = om->machine[i].connection_status;
					om->machine[i].connection_monitor_task_state = WAIT_FOR_TIMEOUT;
				}				
			}
			break;

		case WAIT_FOR_TIMEOUT:
			if (om->machine[i].connection_status_valid == 0)
			{
				om->machine[i].connection_monitor_task_state = INIT;
				break;
			}

			if (om->machine[i].connection_status == 0)
			{
				om->machine[i].connection_monitor_task_state = INIT;
				break;
			}

			if (om->machine[i].connection_status > om->machine[i].connection_monitor_connection_status)
			{
				/*
				 * om->machine[i].connection_status got incremented therefore we go back to init
				 */
				om->machine[i].connection_monitor_task_state = INIT;
				break;
			}

			t = time(NULL);
			if (t > 0)
			{
				if (t < om->machine[i].connection_monitor_start_time)
				{
					om->machine[i].connection_monitor_task_state = INIT;
					break;
				}

				diff = t - om->machine[i].connection_monitor_start_time;				

				if (diff >= timeout_seconds)				    //if (diff >= (time_t) om->machine[i].config.no_response_timeout_seconds)
				{
					/*
					 * no response from machine for more than timeout_seconds
					 */
					om->machine[i].connection_status_valid = 1;
					om->machine[i].connection_status = 0;
					om->machine[i].connection_monitor_task_state = INIT;
				}
			}
			else
			{
				om->machine[i].connection_monitor_task_state = INIT;
			}
			break;

		case 100:
			om->machine[i].connection_monitor_task_state = 100;
			break;


		default:
			om->machine[i].connection_monitor_task_state = INIT;
			break;
		}
	}
}
