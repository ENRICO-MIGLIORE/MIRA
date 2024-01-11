#include "siemens_open62541__private.h"


void siemens_open62541__private__task__connection_monitor (void)
{

	int i;
	int rc;
	time_t t;

	if (so->config.enable_connection_monitor_task == 0)
	{
		return;
	}

	for (i = 0; i < so->machine_count; i++)
	{

		if (so->machine[i].no_response_flag == 0)
		{
			so->machine[i].connection_monitor_task_state = 0;
		}


		switch (so->machine[i].connection_monitor_task_state)
		{

		case 0:

			if (so->machine[i].no_response_flag == 1)
			{			
				t = time(NULL);
				if (t > 0)
				{
					so->machine[i].no_response_time = t;
					so->machine[i].connection_monitor_task_state = 1;
				}				
			}
			break;

		case 1:

			t = time(NULL);
			if (t > 0)
			{
				if (t < so->machine[i].no_response_time)
				{
					so->machine[i].connection_monitor_task_state = 0;
				}
				else if (t - so->machine[i].no_response_time >= (time_t) so->machine[i].config.no_response_timeout_seconds)
				{
					so->machine[i].connection_status = 0;
					so->machine[i].connection_monitor_task_state = 2;
				}
			}
			break;

		case 2:
			if (so->machine[i].reconnection_attempts >= so->machine[i].config.max_reconnection_attempts)
			{
				so->machine[i].connection_monitor_task_state = 100;
			}
			else
			{
				rc = siemens_open62541__private__reconnect_to_machine(i);				
				if (rc == 0)
				{
					so->machine[i].connection_monitor_task_state = 3;
				}
				else
				{

				}
			}
			break;

		case 3:
			//rc = siemens_open62541__is_machine_connected(i);
			rc = 0;
			if (rc == 0)
			{
				so->machine[i].connection_status = 1;
				so->machine[i].connection_monitor_task_state = 0;
			}
			else
			{
				t = time(NULL);
				if (t > 0)
				{
					so->machine[i].no_response_time = t;
					so->machine[i].connection_monitor_task_state = 4;
				}
				else
				{

				}
			}
			break;

		case 4:
			t = time(NULL);
			if (t > 0)
			{
				if (t < so->machine[i].no_response_time)
				{
					so->machine[i].connection_monitor_task_state = 0;
				}
				else if (t - so->machine[i].no_response_time >= (time_t) so->machine[i].config.no_response_timeout_seconds)
				{
					so->machine[i].connection_status = 0;
					so->machine[i].connection_monitor_task_state = 2;
				}
			}
			break;

		case 100:
			so->machine[i].connection_monitor_task_state = 100;
			break;


		default:
			so->machine[i].connection_monitor_task_state = 0;
			break;
		}
	}
}