#include "subagent.h"


int subagent__read_machine_part_counter (subagent_machine_t* machine)
{

	int rc;
	int r;
	int p;
	int md;
	int part_counter_initial_value_in_simulation_mode;
	int probability_of_success_of_events_in_simulation_mode;

	if (machine == NULL)
	{
		return -100;
	}
	 

	pthread_mutex_lock(&machine->thread_mutex);    /* enter critical section */
	

	machine->part_counter_valid = 0;

	if (machine->config_2.networked == 0)
	{
		;
	}
	else if (machine->config_2.operating_mode == 1)
	{		
		md = machine->config.md;    /* just for code readability */

		rc = machine->config.read_part_counter(md);

		if (rc == 0)
		{
			machine->part_counter_valid = 1;
		}
	}
	else
	{
		part_counter_initial_value_in_simulation_mode = SUBAGENT__PART_COUNTER_INITIAL_VALUE_IN_SIMULATION_MODE;
		probability_of_success_of_events_in_simulation_mode = SUBAGENT__PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE;

		if (machine->part_counter_simulation_mode_first_time == 0)
		{
			machine->part_counter_native = part_counter_initial_value_in_simulation_mode;
			machine->part_counter_simulation_mode_first_time = 1;
		}
		else
		{
			machine->part_counter_native++;
		}

		r = rand();
		p = r % 100;

		if (p <= probability_of_success_of_events_in_simulation_mode)
		{
			sprintf(machine->part_counter, "%d", machine->part_counter_native);
			machine->part_counter_valid = 1;
		}
	}


	pthread_mutex_unlock(&machine->thread_mutex);     /* exit critical section */


	return 0;

}




