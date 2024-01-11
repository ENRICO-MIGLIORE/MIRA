#include "subagent.h"


int subagent__read_machine_part_program_name (subagent_machine_t* machine)
{

	int rc;
	int r;
	int md;
	int probability_of_success_of_events_in_simulation_mode;

	if (machine == NULL)
	{
		return -100;
	}
	

	pthread_mutex_lock(&machine->thread_mutex);    /* enter critical section */


	machine->part_program_name_valid = 0;

	if (machine->config_2.networked == 0)
	{
		;
	}
	else if (machine->config_2.operating_mode == 1)
	{		

		md = machine->config.md;    /* just for code readability */

		rc = machine->config.read_part_program_name(md);

		if (rc == 0)
		{
			machine->part_program_name_valid = 1;
		}
	}
	else
	{
		probability_of_success_of_events_in_simulation_mode = SUBAGENT__PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE;

		r = rand();
		r = r % 100;

		if (r <= probability_of_success_of_events_in_simulation_mode)
		{
			strcpy(machine->part_program_name, machine->config_2.part_program_name_in_simulation_mode);
			machine->part_program_name_valid = 1;			
		}
	}


	pthread_mutex_unlock(&machine->thread_mutex);    /* exit critical section */


	return 0;

}




