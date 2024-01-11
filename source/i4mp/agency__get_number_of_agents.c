#include "agent__fanuc_focas.h"

#include "agency_private.h"



int agency__get_number_of_agents (int* number_of_agents)
{

	int i;
	int rc;


	if (agency == NULL)
	{
		return -100;
	}

	if (agency->started != 1)
	{
		return -200;
	}

	if (number_of_agents == NULL)
	{
		return -300;
	}


	i = 0;

	rc = agent__fanuc_focas__is_agent_configured();
	if (rc == 0)
	{
		i++;
	}


	*number_of_agents = i;

	return 0;
}



