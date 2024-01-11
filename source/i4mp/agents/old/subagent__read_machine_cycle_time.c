#include "subagent.h"


int subagent__read_machine_cycle_time (subagent_machine_t* machine)
{

	int rc;
	int r;
	int d;
	int p;
	int sign;
	double delta;
	int md;
	double average_cycle_time_in_simulation_mode;
	int probability_of_success_of_events_in_simulation_mode;

	if (machine == NULL)
	{
		return -100;
	}


	pthread_mutex_lock(&machine->thread_mutex);    /* enter critical section */


	machine->cycle_time_valid = 0;

	if (machine->config_2.networked == 0)
	{
		;
	}
	else if (machine->config_2.operating_mode == 1)
	{
		md = machine->config.md;    /* just for code readability */

		rc = machine->config.read_cycle_time(md);

		if (rc == 0)
		{
			machine->cycle_time_valid = 1;
		}
	}
	else
	{	
		probability_of_success_of_events_in_simulation_mode = SUBAGENT__PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE;
		average_cycle_time_in_simulation_mode = SUBAGENT__AVERAGE_CYCLE_TIME_IN_SIMULATION_MODE;

		machine->cycle_time_native = average_cycle_time_in_simulation_mode;

		r = rand();		
		sign = r % 2;
		d = r % 10;
		p = r % 100;

		delta = ((double) d) / 10;

		if (sign == 0)
		{
			machine->cycle_time_native -= delta;
		}
		else
		{
			machine->cycle_time_native += delta;
		}

		if (p <= probability_of_success_of_events_in_simulation_mode)
		{
			sprintf(machine->cycle_time, "%.1f", machine->cycle_time_native);
			machine->cycle_time_valid = 1;			
		}
	}


	pthread_mutex_unlock(&machine->thread_mutex);     /* exit critical section */


	return 0;

}




