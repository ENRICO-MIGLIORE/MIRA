#include "fanuc_focas__private.h"


// deve essere gestito da questo task
//ff->machine[md].connection_status = 1;


void fanuc_focas__private__task__connection_monitor (void)
{

	int i;
	int rc;
	time_t t;

	if (ff->config.enable_connection_monitor_task == 0)
	{
		return;
	}

	for (i = 0; i < ff->machine_count; i++)
	{

		if (ff->machine[i].no_response_flag == 0)
		{
			ff->machine[i].connection_monitor_task_state = 0;
		}


		switch (ff->machine[i].connection_monitor_task_state)
		{

		case 0:

			if (ff->machine[i].no_response_flag == 1)
			{			
				t = time(NULL);
				if (t > 0)
				{
					ff->machine[i].no_response_time = t;
					ff->machine[i].connection_monitor_task_state = 1;
				}				
			}
			break;

		case 1:

			t = time(NULL);
			if (t > 0)
			{
				if (t < ff->machine[i].no_response_time)
				{
					ff->machine[i].connection_monitor_task_state = 0;
				}
				else if (t - ff->machine[i].no_response_time >= (time_t) ff->machine[i].config.no_response_timeout_seconds)
				{
					ff->machine[i].connection_status = 0;
					ff->machine[i].connection_monitor_task_state = 2;
				}
			}
			break;

		case 2:
			if (ff->machine[i].reconnection_attempts >= ff->machine[i].config.max_reconnection_attempts)
			{
				ff->machine[i].connection_monitor_task_state = 100;
			}
			else
			{
				//rc = fanuc_focas__private__reconnect_to_machine(i);				
				//if (rc == 0)
				//{
				//	ff->machine[i].connection_monitor_task_state = 3;
				//}
				//else
				//{

				//}
			}
			break;

		case 3:
			//rc = fanuc_focas__is_machine_connected(i);
			rc = 0;
			if (rc == 0)
			{
				ff->machine[i].connection_status = 1;
				ff->machine[i].connection_monitor_task_state = 0;
			}
			else
			{
				t = time(NULL);
				if (t > 0)
				{
					ff->machine[i].no_response_time = t;
					ff->machine[i].connection_monitor_task_state = 4;
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
				if (t < ff->machine[i].no_response_time)
				{
					ff->machine[i].connection_monitor_task_state = 0;
				}
				else if (t - ff->machine[i].no_response_time >= (time_t) ff->machine[i].config.no_response_timeout_seconds)
				{
					ff->machine[i].connection_status = 0;
					ff->machine[i].connection_monitor_task_state = 2;
				}
			}
			break;

		case 100:
			ff->machine[i].connection_monitor_task_state = 100;
			break;


		default:
			ff->machine[i].connection_monitor_task_state = 0;
			break;
		}
	}
}