#include "mira__private.h"


int mira__print_agents (void)
{

	int i;
	int rc_1;
	int rc_2;
	char buffer[256];
	size_t buffer_len;
	size_t buffer_size;


	if (mira == NULL)
	{
		return -100;
	}

	if (mira->started != 1)
	{
		return -200;
	}



	for (i = 0; i < mira->config.agents_max; i++)
	{		
		
		rc_1 = mira->config.i4_agency[i].get_agent_name(buffer, sizeof(buffer), &buffer_len);

		rc_2 = mira->config.i4_agency[i].get_agent_buffer_size(&buffer_size);

		if ((rc_1 == 0) && (rc_2 == 0))
		{
			printf("agent name = \"%s\" - buffer size = %zu - number of machines = %d\n", buffer, buffer_size, mira->number_of_machines_per_agent[i]);		
		}
		else
		{
			printf("error - can't get agent's %d data\n", i);
		}		
	}


	return 0;
}
