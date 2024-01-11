#include "okuma_mt__private.h"


void okuma_mt__private__task__connection_monitor (void)
{

	int i;
	int rc;
	time_t t;

	if (om->config.enable_connection_monitor_task == 0)
	{
		return;
	}

	for (i = 0; i < om->machine_count; i++)
	{

		if (om->machine[i].no_response_flag == 0)
		{
			om->machine[i].connection_monitor_task_state = 0;
		}


		switch (om->machine[i].connection_monitor_task_state)
		{

		case 0:

			if (om->machine[i].no_response_flag == 1)
			{			
				t = time(NULL);
				if (t > 0)
				{
					om->machine[i].no_response_time = t;
					om->machine[i].connection_monitor_task_state = 1;
				}				
			}
			break;

		case 1:

			t = time(NULL);
			if (t > 0)
			{
				if (t < om->machine[i].no_response_time)
				{
					om->machine[i].connection_monitor_task_state = 0;
				}
				else if (t - om->machine[i].no_response_time >= (time_t) om->machine[i].config.no_response_timeout_seconds)
				{
					om->machine[i].connection_status = 0;
					om->machine[i].connection_monitor_task_state = 2;
				}
			}
			break;

		case 2:
			if (om->machine[i].reconnection_attempts >= om->machine[i].config.max_reconnection_attempts)
			{
				om->machine[i].connection_monitor_task_state = 100;
			}
			else
			{
				rc = okuma_mt__private__reconnect_to_machine(i);				
				if (rc == 0)
				{
					om->machine[i].connection_monitor_task_state = 3;
				}
				else
				{

				}
			}
			break;

		case 3:
			//rc = okuma_mt__is_machine_connected(i);
			rc = 0;
			if (rc == 0)
			{
				om->machine[i].connection_status = 1;
				om->machine[i].connection_monitor_task_state = 0;
			}
			else
			{
				t = time(NULL);
				if (t > 0)
				{
					om->machine[i].no_response_time = t;
					om->machine[i].connection_monitor_task_state = 4;
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
				if (t < om->machine[i].no_response_time)
				{
					om->machine[i].connection_monitor_task_state = 0;
				}
				else if (t - om->machine[i].no_response_time >= (time_t) om->machine[i].config.no_response_timeout_seconds)
				{
					om->machine[i].connection_status = 0;
					om->machine[i].connection_monitor_task_state = 2;
				}
			}
			break;

		case 100:
			om->machine[i].connection_monitor_task_state = 100;
			break;


		default:
			om->machine[i].connection_monitor_task_state = 0;
			break;
		}
	}
}