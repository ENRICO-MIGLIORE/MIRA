#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;


int fanuc_focas__get_machine_count (size_t* num_machines)
{


	if (num_machines == NULL)
	{
		return -100;
	}


	if (fanuc_focas->configured != 1)
	{
		return -200;
	}


	/*
	 * There's no need to lock the access to fanuc_focas->num_machines because no body modifies it after fanuc_focas__config()
	 */
	*num_machines = fanuc_focas->num_machines;

	return 0;
}

