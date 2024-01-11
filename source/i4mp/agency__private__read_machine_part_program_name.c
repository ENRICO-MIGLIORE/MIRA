#include "agency_private.h"


int agency__private__read_machine_part_program_name (machine_t* machine)
{

	int p;
	int initial_value_in_simulation_mode;
	int probability_of_success_of_events_in_simulation_mode;
	int rc;
	int r;
	const char* fn;


	fn = "agency__private__read_machine_part_program_name()";


	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "machine is null");
		return -100;
	}

	 
	pthread_mutex_lock(&machine->thread_mutex);    /* enter critical section */
	
	machine->part_program_name_valid = 0;

	if (machine->config_2.networked == 0)
	{
		;
	}
	else if (machine->config_2.run == 0)
	{
		;
	}
	else if (machine->config_2.run == 1)
	{				
		if (machine->config_2.simulation == 0)
		{
			rc = machine->config.read_machine_part_program_name((void*)machine);
		}
		else
		{
			//initial_value_in_simulation_mode = AGENCY__CONFIG__INITIAL_VALUE_OF_PART_COUNTER_IN_SIMULATION_MODE;
			//probability_of_success_of_events_in_simulation_mode = machine->config_2.probability_of_success_of_events_in_simulation_mode;

			//if (machine->part_counter_simulation_mode_first_time == 0)
			//{
			//	machine->part_counter_native = initial_value_in_simulation_mode;
			//	machine->part_counter_simulation_mode_first_time = 1;
			//}
			//else
			//{
			//	machine->part_counter_native++;
			//}

			//r = rand();
			//p = r % 100;

			//if (p <= probability_of_success_of_events_in_simulation_mode)
			//{
			//	sprintf(machine->part_counter, "%d", machine->part_counter_native);
			//	machine->part_counter_valid = 1;
			//}
		}		
	}
	else
	{		


	}


	pthread_mutex_unlock(&machine->thread_mutex);     /* exit critical section */


	return 0;

}




