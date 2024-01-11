#include "mira__private.h"


int mira__get_number_of_machines (int* number_of_machines)
{

	size_t i;
	int rc;
	int machines;


	rc = mira__private__verify_framework_is_started();
	if (rc != 0)
	{
		return -10000;
	}

	if (number_of_machines == NULL)
	{
		return -100;
	}


	machines = 0;

	for (i = 0; i < mira->config.agents_max; i++)
	{
		if (mira->number_of_machines_per_agent[i] < 0)
		{
			return -200;
		}

		machines += mira->number_of_machines_per_agent[i];
	}

	*number_of_machines = machines;

	return 0;
}




