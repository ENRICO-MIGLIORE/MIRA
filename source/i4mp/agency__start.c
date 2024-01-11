#include <agent__fanuc_focas.h>

#include "agency_private.h"





int agency__start (void)
{

	int rc;
	int number_of_machines;
	int i;
	int j;
	char agent_name[AGENCY__CONFIG__BUFFER_SIZE];
	size_t agent_name_len;
	const char* fn;
	int done;
	size_t milliseconds;


	fn = "agency__start()";

	if (agency == NULL)
	{
		//utils__printf__error(&agent_so->subagent.pf, fn, -100, "agent__siemens_open62541__private__check_config() returned %d", rc);
		return -100;
	}

	if (agency->configured != 1)
	{
		//utils__printf__error(&agent_so->subagent.pf, fn, -100, "agent__siemens_open62541__private__check_config() returned %d", rc);
		return -200;
	}



	/*
	 * start all agents
	 */
	rc = agent__fanuc_focas__start();


	//agent__fanuc_focas__start();



#if enrico == 1

	for (i = 0; i < agency->number_of_agents; i++)
	{

		for (j = 0; j < agency->agent[i].number_of_machines; j++)
		{

			agency->agent[i].machine[j].thread_mutex = PTHREAD_MUTEX_INITIALIZER;

			rc = pthread_create(&agency->agent[i].machine[j].thread_id, NULL, agency__private__thread, (void*) &agency->agent[i].machine[j]);
			if (rc != 0)
			{
				utils__printf__error(&agency->pf, fn, -200, "pthread_create() returned %d - agent %s - machine id = %d", rc, agency->agent[i].machine[j].config_2.name, agency->agent[i].machine[j].config_2.id);
				return -200;
			}


			/*
			 * Wait for the thread to start
			 */
			done = 0;
			milliseconds = 100;
			do
			{
				utils__platform__sleep(milliseconds);

				pthread_mutex_lock(&agency->agent[i].machine[j].thread_mutex);

				if (agency->agent[i].machine[j].thread_started == 1)
				{
					done = 1;
				}

				pthread_mutex_unlock(&agency->agent[i].machine[j].thread_mutex);


			} while (done == 0);


			agency->agent[i].machine[j].started = 1;
		}

	}

#endif
		//if (agency->agent[i].number_of_machines >= 0)
		//{
		//	agency->agent[i].machine[j].thread_mutex = PTHREAD_MUTEX_INITIALIZER;
		//}
	

	agency->started = 1;
	
#if 0
	/*
	 * call agency' start() function
	 */
	for (i = 0; i < mira->config.agents_max; i++)
	{
		rc = mira->config.i4_agency[i].start();
		if (rc != 0)
		{
			rc = mira->config.i4_agency[i].get_agent_name(agent_name, sizeof(agent_name), &agent_name_len);
			if (rc == 0)
			{
				utils__printf__error(&mira->pf, fn, -700, "start() function of agent %s returned %d - rc = %d", agent_name, rc);
			}
			else
			{
				utils__printf__error(&mira->pf, fn, -700, "start() function of agent %d returned %d - rc = %d", i, rc);
			}	
			return -200;
		}
	}


	for (i = 0; i < mira->config.agents_max; i++)
	{

		rc = mira->config.i4_agency[i].get_agent_total_number_of_machines(&number_of_machines);

		if (rc != 0)
		{			

			rc = mira->config.i4_agency[i].get_agent_name(agent_name, sizeof(agent_name), &agent_name_len);
			if (rc == 0)
			{
				utils__printf__error(&mira->pf, fn, -700, "get_machine_count() function of agent %s returned %d", agent_name, rc);
			}
			else
			{
				utils__printf__error(&mira->pf, fn, -700, "get_machine_count() function of agent %d returned %d", i, rc);
			}
			
			return -300;
		}

		mira->number_of_machines_per_agent[i] = number_of_machines;

	}


	mira->started = 1;

#endif

	return 0;
}

//
//int agent__siemens_open62541__start(void)
//{
//	int rc;
//	int i;
//	int done;
//	size_t milliseconds;
//	const char* fn;
//
//
//	fn = "agent__siemens_open62541__start()";
//
//
//	/*
//	 * create one thread per machine
//	 */
//	for (i = 0; i < agent_so->number_of_machines; i++)
//	{
//		agent_so->subagent.machine[i].thread_mutex = PTHREAD_MUTEX_INITIALIZER;
//
//		rc = pthread_create(&agent_so->subagent.machine[i].thread_id, NULL, subagent__thread, (void*)&agent_so->subagent.machine[i]);
//		if (rc != 0)
//		{
//			utils__printf__error(&agent_so->subagent.pf, fn, -200, "pthread_create() returned %d - machine id = %d", rc, agent_so->subagent.machine[i].config_2.id);
//			return -200;
//		}
//
//		/*
//		 * Wait for the thread to start
//		 */
//		done = 0;
//		milliseconds = 100;
//		do
//		{
//			utils__platform__sleep(milliseconds);
//
//			pthread_mutex_lock(&agent_so->subagent.machine[i].thread_mutex);
//
//			if (agent_so->subagent.machine[i].thread_started == 1)
//			{
//				done = 1;
//			}
//
//			pthread_mutex_unlock(&agent_so->subagent.machine[i].thread_mutex);
//
//
//		} while (done == 0);
//
//
//		agent_so->subagent.machine[i].started = 1;
//	}
//
//	//agent_so->subagent.started = 1;
//	agent_so->started = 1;
//
//	return 0;
//}