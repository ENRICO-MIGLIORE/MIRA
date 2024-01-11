#include "machine.h"


//static void delegate__simulate_connection_status(delegate_t* delegate, int md);
//static void delegate__simulate_production_status(delegate_t* delegate, int md);
//static void delegate__simulate_alarm_status(delegate_t* delegate, int md);

//static void subagent__simulate_part_counter(subagent__machine_t* machine);

//static void delegate__simulate_cycle_time(delegate_t* delegate, int md);
//static void delegate__simulate_part_program_name(delegate_t* delegate, int md);


void subagent__private__task__simulate_machine (machine_data_t* machine_local)
{



	//if (delegate->machine[i].config_2.simulated == 1)
	{

		//delegate__simulate_connection_status(delegate, i);

		//delegate__simulate_production_status(delegate, i);

		//delegate__simulate_alarm_status(delegate, i);

		//subagent__simulate_part_counter(machine);

		//delegate__simulate_cycle_time(delegate, i);

		//delegate__simulate_part_program_name(delegate, i);
	}

}



//static void delegate__simulate_connection_status(delegate_t* delegate, int md)
//{
//	int r;
//
//	r = rand();
//	r = r % 100;
//
//	if (r <= delegate->probability_of_success_of_events_in_simulation_mode_in_percentage)
//	{		
//		delegate->machine[md].connection_status_simulated = 1;
//	}
//	else
//	{
//		delegate->machine[md].connection_status_simulated = 0;
//	}
//
//	delegate->machine[md].connection_status_valid_simulated = 1;
//
//}


//static void delegate__simulate_production_status(delegate_t* delegate, int md)
//{
//	int r;
//	
//
//	r = rand();
//	r = r % 100;
//
//	//if (r <= delegate->probability_of_success_of_events_in_simulation_mode_in_percentage)
//	//{
//	//	delegate->machine[md].production_status_simulated = 1;
//	//}
//	//else
//	//{
//	//	delegate->machine[md].production_status_simulated = 0;
//	//}
//
//	//delegate->machine[md].production_status_valid_simulated = 1;
//
//}
//
//
//static void delegate__simulate_alarm_status(delegate_t* delegate, int md)
//{
//	int r;
//
//	r = rand();
//	r = r % 100;
//
//	//if (r <= delegate->probability_of_success_of_events_in_simulation_mode_in_percentage)
//	//{
//	//	delegate->machine[md].alarm_status_simulated = 0;
//	//}
//	//else
//	//{
//	//	delegate->machine[md].alarm_status_simulated = 1;
//	//}
//
//	delegate->machine[md].alarm_status_valid_simulated = 1;
//
//}





//static void delegate__simulate_cycle_time(delegate_t* delegate, int md)
//{
//	int r;
//	int d;
//	double offset;
//
//	r = rand();
//	r = r % 100;
//
//	//if (r <= delegate->probability_of_success_of_events_in_simulation_mode_in_percentage)
//	//{
//
//	//	d = rand();
//	//	d = d % 10;
//	//	offset = (double) d;
//	//	offset /= 10;   /* 10% variance */
//
//	//	/* 
//	//	 * 50-50 chance of adding the offset and 50-50 chance of subtracting the offset
//	//	 */
//	//	if (r % 2 == 0)
//	//	{
//	//		delegate->machine[md].cycle_time_simulated = delegate->machine[md].config.average_cycle_time_in_simulation_mode_seconds + offset;
//	//	}
//	//	else
//	//	{
//	//		delegate->machine[md].cycle_time_simulated = delegate->machine[md].config.average_cycle_time_in_simulation_mode_seconds - offset;
//	//	}
//
//	//	delegate->machine[md].cycle_time_simulated_valid = 1;
//	//}
//	//else
//	//{
//	//	delegate->machine[md].cycle_time_simulated_valid = 0;
//	//}
//
//}


//static void delegate__simulate_part_program_name(delegate_t* delegate, int md)
//{
//	int r;
//	
//	r = rand();
//	r = r % 100;
//
//	//if (r <= delegate->probability_of_success_of_events_in_simulation_mode_in_percentage)
//	//{		
//	//	strcpy(delegate->machine[md].part_program_name_simulated, delegate->machine[md].config.part_program_name_in_simulation_mode);
//
//	//	delegate->machine[md].part_program_name_simulated_valid = 1;
//	//}
//	//else
//	//{
//	//	delegate->machine[md].part_program_name_simulated_valid = 0;
//	//}
//
//}


