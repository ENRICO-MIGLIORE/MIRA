#include "mira__private.h"


int mira__start (void)
{
	int rc;
	int number_of_machines;
	int i;
	char agent_name[256];
	size_t agent_name_len;
	const char* fn;


	fn = "mira__start()";


	rc = mira__private__verify_framework_is_configured();
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -100, "mira__private__check_configured returned %d", rc);
		return -100;
	}

	

	/*
	 * call i4_agency' start() function
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


	return 0;
}
