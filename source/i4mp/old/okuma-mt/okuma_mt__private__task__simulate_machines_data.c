#include "okuma_mt__private.h"


static void okuma_mt__simulate_machine_part_counter(int md);
static void okuma_mt__simulate_machine_cycle_time(int md);
static void okuma_mt__simulate_machine_part_program_name(int md);
static void okuma_mt__simulate_machine_connection_status(int md);
static void okuma_mt__simulate_machine_production_status(int md);


void okuma_mt__private__task__simulate_machines_data (void)
{

	int i;

	for (i = 0; i < om->machine_count; i++)
	{

		if (om->machine[i].config.simulation_mode == 1)
		{

			okuma_mt__simulate_machine_connection_status(i);

			okuma_mt__simulate_machine_production_status(i);

			okuma_mt__simulate_machine_part_counter(i);

			okuma_mt__simulate_machine_cycle_time(i);

			okuma_mt__simulate_machine_part_program_name(i);
		}
	}
}



static void okuma_mt__simulate_machine_connection_status(int md)
{
	int r;

	r = rand();
	r = r % 100;
	if (r <= om->percent_of_success_of_events_in_simulation_mode)
	{		
		om->machine[md].connection_status_simulated = 1;
	}
	else
	{
		om->machine[md].connection_status_simulated = 0;
	}

	om->machine[md].connection_status_simulated_valid = 1;

}


static void okuma_mt__simulate_machine_production_status(int md)
{
	int r;
	

	r = rand();
	r = r % 100;
	if (r <= om->percent_of_success_of_events_in_simulation_mode)
	{
		om->machine[md].production_status_simulated = 1;
	}
	else
	{
		om->machine[md].production_status_simulated = 0;
	}

	om->machine[md].production_status_simulated_valid = 1;

}

static void okuma_mt__simulate_machine_part_counter(int md)
{
	int r;	

	om->machine[md].part_counter_simulated++;

	r = rand();
	r = r % 100;	
	if (r <= om->percent_of_success_of_events_in_simulation_mode)
	{
		om->machine[md].part_counter_simulated_valid = 1;
	}
	else
	{
		om->machine[md].part_counter_simulated_valid = 0;
	}
}


static void okuma_mt__simulate_machine_cycle_time(int md)
{
	int r;
	int d;
	double offset;

	r = rand();
	r = r % 100;
	if (r <= om->percent_of_success_of_events_in_simulation_mode)
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
			om->machine[md].cycle_time_simulated = om->machine[md].config.average_cycle_time_in_simulation_mode_seconds + offset;
		}
		else
		{
			om->machine[md].cycle_time_simulated = om->machine[md].config.average_cycle_time_in_simulation_mode_seconds - offset;
		}

		om->machine[md].cycle_time_simulated_valid = 1;
	}
	else
	{
		om->machine[md].cycle_time_simulated_valid = 0;
	}

}


static void okuma_mt__simulate_machine_part_program_name(int md)
{
	int r;
	
	r = rand();
	r = r % 100;
	if (r <= om->percent_of_success_of_events_in_simulation_mode)
	{		
		strcpy(om->machine[md].part_program_name_simulated, om->machine[md].config.part_program_name_in_simulation_mode);

		om->machine[md].part_program_name_simulated_valid = 1;
	}
	else
	{
		om->machine[md].part_program_name_simulated_valid = 0;
	}

}


