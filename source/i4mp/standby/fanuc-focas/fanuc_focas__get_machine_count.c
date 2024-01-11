#include "fanuc_focas__private.h"


int fanuc_focas__get_machine_count (size_t* machine_count)
{

	if (machine_count == NULL)
	{
		return -100;
	}


	if (ff->configured != 1)
	{
		return -200;
	}


	/*
	 * There's no need to lock the access to "fanuc_focas->num_machines" or "ff->configured"
	 * because nobody modifies them after calling fanuc_focas__config()
	 */
	*machine_count = ff->machine_count;

	return 0;
}

