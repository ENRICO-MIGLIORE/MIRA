#include "agency_private.h"


int agency__private__read_machine_cycle_time (machine_t* machine)
{

	int p;
	int initial_value_in_simulation_mode;
	int probability_of_success_of_events_in_simulation_mode;
	int rc;
	int r;
	const char* fn;


	fn = "agency__private__read_machine_cycle_time()";


	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "machine is null");
		return -100;
	}

	 
	pthread_mutex_lock(&machine->thread_mutex);    /* enter critical section */
	

	machine->cycle_time_valid = 0;

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
			rc = machine->config.read_machine_cycle_time((void*)machine);
		}
		else
		{
			//initial_value_in_simulation_mode = AGENCY__CONFIG__INITIAL_VALUE_OF_PART_COUNTER_IN_SIMULATION_MODE;
			//probability_of_success_of_events_in_simulation_mode = machine->config_2.probability_of_success_of_events_in_simulation_mode;

			//if (machine->cycle_time_simulation_mode_first_time == 0)
			//{
			//	machine->cycle_time_native = initial_value_in_simulation_mode;
			//	machine->cycle_time_simulation_mode_first_time = 1;
			//}
			//else
			//{
			//	machine->cycle_time_native++;
			//}

			//r = rand();
			//p = r % 100;

			//if (p <= probability_of_success_of_events_in_simulation_mode)
			//{
			//	sprintf(machine->cycle_time, "%d", machine->cycle_time_native);
			//	machine->cycle_time_valid = 1;
			//}
		}
		
	}
	else
	{		
		; // internal software error

	}


	pthread_mutex_unlock(&machine->thread_mutex);     /* exit critical section */


	return 0;

}




