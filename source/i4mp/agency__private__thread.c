#include "agency_private.h"


void* agency__private__thread (void* arg)
{

	int rc;
	unsigned int seed;
	time_t t;
	machine_t* machine;
	const char* fn;
	int done;


	fn = "agency__thread()";


	if (arg == NULL)
	{
		return NULL;
	}

	machine = (machine_t*) arg;


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



	agency__private__suspend_thread(machine);

	machine->thread_started = 1;	
	
		
	while (machine->thread_stop_request == 0)
	{
		
		/*
		 * duty 1: connection
		 */
		done = 0;

		while (done == 0)
		{
		
			rc = agency__private__connect_to_machine(machine);

			if (rc == 0)
			{						
				done = 1;
			}
			else
			{
				agency__private__suspend_thread(machine);
			}
		} 
		

		/*
		 * duty 2: data reading
		 */
		done = 0;

		while (done == 0)
		{
			//read_machine_data_stream

			(void) agency__private__read_data_stream(machine);

			(void) agency__private__read_machine_part_counter(machine);

			(void) agency__private__read_machine_cycle_time(machine);

			(void) agency__private__read_machine_part_program_name(machine);

			(void)agent__siemens_open62541__platform__private__read_machine_status_run(machine);

			(void)agent__siemens_open62541__platform__private__read_machine_status_alarm(machine);
			

			agency__private__suspend_thread(machine);

			//utils__printf__info(&machine->pf, fn, 0, "machine %s is alive", machine->config_2.name);

		}


		//if ((machine->connection_status_valid == 1) && (machine->connection_status == 1))
		//{

		//	do
		//	{

		//		(void) agency__private__read_machine_part_counter(machine);

		//		//(void) subagent__read_machine_cycle_time(machine);

		//		//(void) subagent__read_machine_part_program_name(machine);

		//		agency__private__suspend_thread(machine, machine->thread_sleep_time);

		//		//utils__printf__info(&machine->pf, fn, 0, "machine %s is alive", machine->config_2.name);

		//	} while (1);

		//}


		/*
		 * duty 3: check connection status
		 */
	    

		/*
		 * utils__printf__info(&so->pf, "siemens_open62541__private__thread()", 0, "thread sleep time milliseconds = %zu", so->thread_sleep_time);
		 */

		//utils__printf__info(&machine->pf, fn, 0, "agent  - machine name %s - id %d", machine->config_2.name, machine->config_2.id);
		//utils__printf__error(&agent_so->subagent.pf, fn, -200, "pthread_create() returned %d - machine id = %d", rc, agent_so->subagent.machine[i].config_2.id);


	}

	return NULL;

}
