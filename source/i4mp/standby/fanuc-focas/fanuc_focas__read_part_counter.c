#include "fanuc_focas__private.h"


int fanuc_focas__read_part_counter (size_t machine_id)
{
	int rc;
	size_t fd;


	if (machine_id > ff->machine_count)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	fd = machine_id - 1;


	if (ff->machine[fd].connected == 0)
	{
		return -300;
	}

	rc = ff->machine[fd].read_part_counter(machine_id);

	return rc;
	
}











