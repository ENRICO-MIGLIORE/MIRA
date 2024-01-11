#include "subagent.h"


int subagent__connect_to_machine (subagent_machine_t* machine)
{

	int rc;
	int r;
	const char* fn;
	int md;
	int probability_of_success_of_events_in_simulation_mode;


	fn = "subagent__connect_to_machine()";


	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "machine is null");
		return -100;
	}

	pthread_mutex_lock(&machine->thread_mutex);

	rc = 0;


	if (machine->config_2.networked == 0)
	{	
		utils__printf__info(&machine->pf, fn, 0, "subagent can't connect to machine %s (id = %d) because it's not networked", machine->config_2.name, machine->config_2.id);
	}
	else if (machine->config_2.operating_mode == 1)
	{
		utils__printf__info(&machine->pf, fn, 0, "subagent will connect in a few seconds to machine %s (id = %d)", machine->config_2.name, machine->config_2.id);

		md = machine->config.md;

		rc = machine->config.connect_to_machine(md);
	}
	else
	{
	
		probability_of_success_of_events_in_simulation_mode = SUBAGENT__PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE;

		r = rand();
		r = r % 100;

		if (r <= probability_of_success_of_events_in_simulation_mode)
		{
			machine->connection_status_valid = 1;
		}
		else
		{
			machine->connection_status_valid = 0;
			rc = +100;
		}

		if (machine->connection_status_valid == 1)
		{

			if (r <= probability_of_success_of_events_in_simulation_mode)
			{
				machine->connection_status = 1;
				rc = 0;

				utils__printf__info(&machine->pf, fn, 0, "subagent connected in simulation mode to machine %s (id = %d)", machine->config_2.name, machine->config_2.id);				
			}
			else
			{
				machine->connection_status = 0;
				rc = -1000;
			}
		}			
	}


	pthread_mutex_unlock(&machine->thread_mutex);

    return rc;	
	

}
