#include "agent__fanuc_focas.h"

#include "agency_private.h"


int agency__get_number_of_machines (int* number_of_machines)
{

	int i;
	int j;
	int rc;

	if (agency == NULL)
	{
		return -100;
	}

	if (agency->started != 1)
	{
		return -200;
	}

	if (number_of_machines == NULL)
	{
		return -300;
	}


	i = 0;

	rc = agent__fanuc_focas__get_number_of_machines(&j);
	if (rc == 0)
	{
		i += j;
	}


	*number_of_machines = i;

	return 0;
}






