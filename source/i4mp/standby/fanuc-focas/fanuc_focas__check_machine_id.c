#include "fanuc_focas__private.h"


int fanuc_focas__check_machine_id (size_t machine_id)
{

	if (machine_id > ff->machine_count)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	return 0;
}














