#include "machine.h"


void subagent__private__task__connection_manager (machine_data_t* machine_local)
{

#if 0
	int rc;
	int md;


	machine_local->config_2.simulated = 1;

	md = machine_local->md;

	machine_local->thread_ticks_milliseconds += machine_local->thread_sleep_time_milliseconds;

	//utils__platform__sleep_milliseconds(machine->thread_sleep_time_milliseconds);
	utils__platform__sleep_milliseconds(1000);

	switch (machine_local->connection_monitor_task_state)
	{

	case 0:
		machine_local->connection_monitor_task_state = 1;
		break;

	case 1:
		pthread_mutex_lock(&machine_local->thread_mutex);

		if (machine_local->config_2.simulated == 1)
		{			
			rc = machine__connect_to_machine(machine_local);
		}
		else
		{
			rc = machine_local->config.connect_to_machine(md);
		}		

		pthread_mutex_unlock(&machine_local->thread_mutex);

		if (rc != 0)
		{
			machine_local->connection_monitor_task_state = 0;
			break;
		}

		machine_local->connection_monitor_task_state = 2;
		
		break;

	case 2:
		machine_local->connection_monitor_task_state = 2;
		break;

	}

	//if (delegate->settings.enable_connection_monitor_task == 0)
	//{
	//	return;
	//}

	//for (i = 0; i < delegate->machine_count; i++)
	//{

	//	if (delegate->machine[i].no_response_flag == 0)
	//	{
	//		delegate->machine[i].connection_monitor_task_state = 0;
	//	}


	//	switch (delegate->machine[i].connection_monitor_task_state)
	//	{

	//	case 0:

	//		if (delegate->machine[i].no_response_flag == 1)
	//		{			
	//			t = time(NULL);
	//			if (t > 0)
	//			{
	//				delegate->machine[i].no_response_time = t;
	//				delegate->machine[i].connection_monitor_task_state = 1;
	//			}				
	//		}
	//		break;

	//	case 1:

	//		t = time(NULL);
	//		if (t > 0)
	//		{
	//			if (t < delegate->machine[i].no_response_time)
	//			{
	//				delegate->machine[i].connection_monitor_task_state = 0;
	//			}
	//			else if (t - delegate->machine[i].no_response_time >= (time_t) delegate->machine[i].config_2.no_response_timeout_seconds)
	//			{
	//				delegate->machine[i].connection_status = 0;
	//				delegate->machine[i].connection_monitor_task_state = 2;
	//			}
	//		}
	//		break;

	//	case 2:
	//		if (delegate->machine[i].reconnection_attempts >= delegate->machine[i].config_2.max_reconnection_attempts)
	//		{
	//			delegate->machine[i].connection_monitor_task_state = 100;
	//		}
	//		else
	//		{
	//			//rc = siemens_open62541__private__reconnect_to_machine(i);				
	//			//if (rc == 0)
	//			//{
	//			//	delegate->machine[i].connection_monitor_task_state = 3;
	//			//}
	//			//else
	//			//{

	//			//}
	//		}
	//		break;

	//	case 3:
	//		//rc = siemens_open62541__is_machine_connected(i);
	//		rc = 0;
	//		if (rc == 0)
	//		{
	//			delegate->machine[i].connection_status = 1;
	//			delegate->machine[i].connection_monitor_task_state = 0;
	//		}
	//		else
	//		{
	//			t = time(NULL);
	//			if (t > 0)
	//			{
	//				delegate->machine[i].no_response_time = t;
	//				delegate->machine[i].connection_monitor_task_state = 4;
	//			}
	//			else
	//			{

	//			}
	//		}
	//		break;

	//	case 4:
	//		t = time(NULL);
	//		if (t > 0)
	//		{
	//			if (t < delegate->machine[i].no_response_time)
	//			{
	//				delegate->machine[i].connection_monitor_task_state = 0;
	//			}
	//			else if (t - delegate->machine[i].no_response_time >= (time_t) delegate->machine[i].config_2.no_response_timeout_seconds)
	//			{
	//				delegate->machine[i].connection_status = 0;
	//				delegate->machine[i].connection_monitor_task_state = 2;
	//			}
	//		}
	//		break;

	//	case 100:
	//		delegate->machine[i].connection_monitor_task_state = 100;
	//		break;


	//	default:
	//		delegate->machine[i].connection_monitor_task_state = 0;
	//		break;
	//	}
	//}

#endif
}