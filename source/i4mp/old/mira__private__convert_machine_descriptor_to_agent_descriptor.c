#include "mira__private.h"


/*
 * md is i4mp's machine descriptor
 * ad is the subagent's descriptor
 * ag_md is the subagent's machine descriptor
 */

int mira__private__convert_machine_descriptor_to_agent_descriptor (int md, int* ad, int* ag_md)
{

	int i;
	int j;
	int k;
	int agent_descriptor;
	int agent_machine_descriptor;
	int done;
	int number_of_machines;

	number_of_machines = 0;

	for (i = 0; i < mira->config.agents_max; i++)
	{
		number_of_machines += mira->number_of_machines_per_agent[i];
	}

	if ((md < 0) || (md >= number_of_machines))
	{
		return -12000;
	}

	if (ad == NULL)
	{
		return -13000;
	}

	if (ag_md == NULL)
	{
		return -14000;
	}

	
	agent_descriptor = 0;
	agent_machine_descriptor = 0;
	k = 0;
	done = 0;

	for (i = 0; (i < mira->config.agents_max) && (done == 0); i++)
	{	
		for (j = 0; (j < mira->number_of_machines_per_agent[i]) && (done == 0); j++)
		{
			if (k == md)
			{
				agent_descriptor = i;
				agent_machine_descriptor = j;
				done = 1;
			}
			else
			{
				k++;
			}			
		}
	}

	if (done != 1)
	{
		return -16000;
	}

	*ad = agent_descriptor;
	*ag_md = agent_machine_descriptor;

	return 0;
}






