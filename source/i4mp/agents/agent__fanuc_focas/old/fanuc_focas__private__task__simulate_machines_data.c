#include "fanuc_focas__private.h"


static void fanuc_focas__simulate_connection_status(int md);
static void fanuc_focas__simulate_production_status(int md);
static void fanuc_focas__simulate_alarm_status(int md);

static void fanuc_focas__simulate_part_counter(int md);
static void fanuc_focas__simulate_cycle_time(int md);
static void fanuc_focas__simulate_part_program_name(int md);


void fanuc_focas__private__task__simulate_machines_data(void)
{

	int i;

	for (i = 0; i < ff->machine_count; i++)
	{

		if (ff->machine[i].config.simulated == 1)
		{

			fanuc_focas__simulate_connection_status(i);

			fanuc_focas__simulate_production_status(i);

			fanuc_focas__simulate_alarm_status(i);

			fanuc_focas__simulate_part_counter(i);

			fanuc_focas__simulate_cycle_time(i);

			fanuc_focas__simulate_part_program_name(i);
		}
	}
}



static void fanuc_focas__simulate_connection_status(int md)
{
	int r;

	r = rand();
	r = r % 1000;

	if (r <= ff->probability_of_success_of_events_in_simulation_mode_in_percentage)
	{
		ff->machine[md].connection_status_simulated = 1;
	}
	else
	{
		ff->machine[md].connection_status_simulated = 0;
	}

	ff->machine[md].connection_status_valid_simulated = 1;

}


static void fanuc_focas__simulate_production_status(int md)
{
	int r;


	r = rand();
	r = r % 1000;
	if (r <= ff->probability_of_success_of_events_in_simulation_mode_in_percentage)
	{
		ff->machine[md].production_status_simulated = 1;
	}
	else
	{
		ff->machine[md].production_status_simulated = 0;
	}

	ff->machine[md].production_status_valid_simulated = 1;

}


static void fanuc_focas__simulate_alarm_status(int md)
{
	int r;

	r = rand();
	r = r % 1000;
	if (r <= ff->probability_of_success_of_events_in_simulation_mode_in_percentage)
	{
		ff->machine[md].alarm_status_simulated = 0;
	}
	else
	{
		ff->machine[md].alarm_status_simulated = 1;
	}

	ff->machine[md].alarm_status_valid_simulated = 1;

}

static void fanuc_focas__simulate_part_counter(int md)
{
	int r;

	ff->machine[md].part_counter_simulated++;

	r = rand();
	r = r % 1000;
	if (r <= ff->probability_of_success_of_events_in_simulation_mode_in_percentage)
	{
		ff->machine[md].part_counter_simulated_valid = 1;
	}
	else
	{
		ff->machine[md].part_counter_simulated_valid = 0;
	}
}


static void fanuc_focas__simulate_cycle_time(int md)
{
	int r;
	int d;
	double offset;

	r = rand();
	r = r % 1000;
	if (r <= ff->probability_of_success_of_events_in_simulation_mode_in_percentage)
	{

		d = rand();
		d = d % 10;
		offset = (double)d;
		offset /= 10;   /* 10% variance */

		/*
		 * 50-50 chance of adding the offset and 50-50 chance of subtracting the offset
		 */
		if (r % 2 == 0)
		{
			ff->machine[md].cycle_time_simulated = ff->machine[md].config.average_cycle_time_in_simulation_mode_seconds + offset;
		}
		else
		{
			ff->machine[md].cycle_time_simulated = ff->machine[md].config.average_cycle_time_in_simulation_mode_seconds - offset;
		}

		ff->machine[md].cycle_time_simulated_valid = 1;
	}
	else
	{
		ff->machine[md].cycle_time_simulated_valid = 0;
	}

}


static void fanuc_focas__simulate_part_program_name(int md)
{
	int r;

	r = rand();
	r = r % 1000;
	if (r <= ff->probability_of_success_of_events_in_simulation_mode_in_percentage)
	{
		strcpy(ff->machine[md].part_program_name_simulated, ff->machine[md].config.part_program_name_in_simulation_mode);

		ff->machine[md].part_program_name_simulated_valid = 1;
	}
	else
	{
		ff->machine[md].part_program_name_simulated_valid = 0;
	}

}
