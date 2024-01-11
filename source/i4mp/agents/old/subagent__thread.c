#include "subagent.h"


void* subagent__thread (void* arg)
{


	unsigned int seed;
	time_t t;
	int rc;
	subagent_machine_t* machine;


	if (arg == NULL)
	{
		return NULL;
	}

	machine = (subagent_machine_t*) arg;


	/*
	 * srand() must be called once per thread
	 */
	t = time(NULL);
	if (t < 0)
	{
		seed = 100;
	}
	else
	{
		seed = (unsigned int)t;
	}
	srand(seed);

	

	machine->thread_sleep_time = 1000;
	machine->thread_ticks = 0;	
	machine->thread_stop_request = 0;
	machine->thread_started = 1;
		

	while (machine->thread_stop_request == 0)
	{

		do
		{
			subagent__suspend_thread(machine, machine->thread_sleep_time);

			rc = subagent__connect_to_machine(machine);
			
		} 
		while (rc != 0);


		do
		{			

			(void) subagent__read_machine_part_counter(machine);

			(void) subagent__read_machine_cycle_time(machine);

			(void) subagent__read_machine_part_program_name(machine);
			
			subagent__suspend_thread(machine, machine->thread_sleep_time);

		} 
		while (1);


	

		/*
		 * utils__printf__info(&so->pf, "siemens_open62541__private__thread()", 0, "thread sleep time milliseconds = %zu", so->thread_sleep_time);
		 */


	}

	return NULL;

}