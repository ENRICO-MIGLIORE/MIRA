#include "siemens_open62541__private.h"


static void siemens_open62541__simulate_machine_part_counter(int md);
static void siemens_open62541__simulate_machine_cycle_time(int md);
static void siemens_open62541__simulate_machine_part_program_name(int md);
static void siemens_open62541__simulate_machine_connection_status(int md);
static void siemens_open62541__simulate_machine_production_status(int md);


void siemens_open62541__private__task__simulate_machines_data (void)
{

	int i;

	for (i = 0; i < so->machine_count; i++)
	{

		if (so->machine[i].config.simulation_mode == 1)
		{

			siemens_open62541__simulate_machine_connection_status(i);

			siemens_open62541__simulate_machine_production_status(i);

			siemens_open62541__simulate_machine_part_counter(i);

			siemens_open62541__simulate_machine_cycle_time(i);

			siemens_open62541__simulate_machine_part_program_name(i);
		}
	}
}



static void siemens_open62541__simulate_machine_connection_status(int md)
{
	int r;

	r = rand();
	r = r % 100;
	if (r <= so->percent_of_success_of_events_in_simulation_mode)
	{		
		so->machine[md].connection_status_simulated = 1;
	}
	else
	{
		so->machine[md].connection_status_simulated = 0;
	}

	so->machine[md].connection_status_simulated_valid = 1;

}


static void siemens_open62541__simulate_machine_production_status(int md)
{
	int r;
	

	r = rand();
	r = r % 100;
	if (r <= so->percent_of_success_of_events_in_simulation_mode)
	{
		so->machine[md].production_status_simulated = 1;
	}
	else
	{
		so->machine[md].production_status_simulated = 0;
	}

	so->machine[md].production_status_simulated_valid = 1;

}

static void siemens_open62541__simulate_machine_part_counter(int md)
{
	int r;	

	so->machine[md].part_counter_simulated++;

	r = rand();
	r = r % 100;	
	if (r <= so->percent_of_success_of_events_in_simulation_mode)
	{
		so->machine[md].part_counter_simulated_valid = 1;
	}
	else
	{
		so->machine[md].part_counter_simulated_valid = 0;
	}
}


static void siemens_open62541__simulate_machine_cycle_time(int md)
{
	int r;
	int d;
	double offset;

	r = rand();
	r = r % 100;
	if (r <= so->percent_of_success_of_events_in_simulation_mode)
	{

		d = rand();
		d = d % 10;
		offset = (double) d;
		offset /= 10;   /* 10% variance */

		/* 
		 * 50-50 chance of adding the offset and 50-50 chance of subtracting the offset
		 */
		if (r % 2 == 0)
		{
			so->machine[md].cycle_time_simulated = so->machine[md].config.average_cycle_time_in_simulation_mode_seconds + offset;
		}
		else
		{
			so->machine[md].cycle_time_simulated = so->machine[md].config.average_cycle_time_in_simulation_mode_seconds - offset;
		}

		so->machine[md].cycle_time_simulated_valid = 1;
	}
	else
	{
		so->machine[md].cycle_time_simulated_valid = 0;
	}

}


static void siemens_open62541__simulate_machine_part_program_name(int md)
{
	int r;
	
	r = rand();
	r = r % 100;
	if (r <= so->percent_of_success_of_events_in_simulation_mode)
	{		
		strcpy(so->machine[md].part_program_name_simulated, so->machine[md].config.part_program_name_in_simulation_mode);

		so->machine[md].part_program_name_simulated_valid = 1;
	}
	else
	{
		so->machine[md].part_program_name_simulated_valid = 0;
	}

}


