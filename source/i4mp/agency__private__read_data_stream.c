#include "agency_private.h"


int agency__private__read_data_stream (machine_t* machine)
{

	int p;
	int initial_value_in_simulation_mode;
	int probability_of_success_of_events_in_simulation_mode;
	int rc;
	int r;
	const char* fn;


	fn = "agency__private__read_data_stream()";


	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "machine is null");
		return -100;
	}

	if (machine->config.read_machine_data_stream == NULL)
	{
		return -200;
	}

	 
	pthread_mutex_lock(&machine->thread_mutex);    /* enter critical section */
	
	//machine->data_stream_valid = 0;

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
			rc = machine->config.read_machine_data_stream((void*)machine);
		}
		else
		{
			;
		}		
	}
	else
	{		
		; // internal software error
	}


	pthread_mutex_unlock(&machine->thread_mutex);     /* exit critical section */


	return 0;

}




