#include "agency_private.h"


int agency__private__connect_to_machine (machine_t* machine)
{

	int rc;
	int r;
	const char* fn;
	int probability;
	size_t diff;


	fn = "agency__connect()";


	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "machine is null");
		return -100;
	}


	rc = -1000;


	pthread_mutex_lock(&machine->thread_mutex);
	

	if (machine->connection_attempts == 0)
	{
		machine->connection_timestamp = time(NULL);
		if (machine->connection_timestamp == (time_t)(-1))
		{
			utils__printf__error(NULL, fn, -100, "the time() function returned -1 - machine % s (id = % d)", machine->config_2.name, machine->config_2.id);
			pthread_mutex_unlock(&machine->thread_mutex);
			return -100;
		}

		machine->connection_timestamp_previous = machine->connection_timestamp;
	}
	else
	{
		machine->connection_timestamp = time(NULL);
		if (machine->connection_timestamp == (time_t)(-1))
		{
			utils__printf__error(NULL, fn, -100, "the time() function returned -1 - machine % s (id = % d)", machine->config_2.name, machine->config_2.id);
			pthread_mutex_unlock(&machine->thread_mutex);
			return -100;
		}

		if (machine->connection_timestamp < machine->connection_timestamp_previous)
		{
			utils__printf__error(NULL, fn, -100, "machine->connection_timestamp < machine->connection_timestamp_previous - machine % s (id = % d)", machine->config_2.name, machine->config_2.id);
			pthread_mutex_unlock(&machine->thread_mutex);
			return -100;
		}

		diff = machine->connection_timestamp - machine->connection_timestamp_previous;

		if (diff <= AGENCY__CONFIG__CONNECTION_TIME_INTERVAL)
		{
			pthread_mutex_unlock(&machine->thread_mutex);
			return 100;
		}

		machine->connection_timestamp_previous = machine->connection_timestamp;
	}


	machine->connection_attempts++;

	machine->connection_status_valid = 0;
	machine->connection_status = 0;


	if (machine->config_2.networked == 0)
	{	
		if (machine->connection_attempts < 2)
		{
		    utils__printf__info(&machine->pf, fn, 0, "agent can't connect to machine %s (id = %d) because networked = no", machine->config_2.name, machine->config_2.id);
		}
	}
	if (machine->config_2.run == 0)
	{
		if (machine->connection_attempts < 2)
		{
			utils__printf__info(&machine->pf, fn, 0, "agent can't connect to machine %s (id = %d) because run = no", machine->config_2.name, machine->config_2.id);
		}
	}
	else if (machine->config_2.run == 1)
	{

		if (machine->config_2.simulation == 0)
		{
			rc = machine->config.connect_to_machine((void*)machine);

			if (rc == 0)
			{
				machine->connection_status_valid = 1;
				machine->connection_status = 1;
				utils__printf__info(&machine->pf, fn, 0, "agent connected to machine %s (id = %d)", machine->config_2.name, machine->config_2.id);
				rc = 0;
			}
			else
			{
				utils__printf__info(&machine->pf, fn, 0, "agent failed to connect to machine %s (id = %d)", machine->config_2.name, machine->config_2.id);
			}
		}
		else
		{
			probability = machine->config_2.probability_of_success_of_events_in_simulation_mode;

			r = rand();
			r = r % 100;

			if (r <= probability)
			{
				machine->connection_status_valid = 1;
				machine->connection_status = 1;
				utils__printf__info(&machine->pf, fn, 0, "agent connected in simulation mode to machine %s (id = %d)", machine->config_2.name, machine->config_2.id);
				rc = 0;
			}
			else
			{
				utils__printf__info(&machine->pf, fn, 0, "agent failed to connect in simulation mode to machine %s (id = %d)", machine->config_2.name, machine->config_2.id);
			}
		}

	}
	else
	{
		utils__printf__info(&machine->pf, fn, 0, "software internal error - machine %s (id = %d)", machine->config_2.name, machine->config_2.id);
	}

	pthread_mutex_unlock(&machine->thread_mutex);

    return rc;	
	

}
