#include "fanuc_focas__private.h"


int fanuc_focas__read_cycle_time (size_t machine_id)
{
	int rc;
	size_t fd;

	rc = fanuc_focas__check_machine_id(machine_id);

	if (rc != 0)
	{
		return -100;
	}

	fd = machine_id - 1;

	rc = ff->machine[fd].read_cycle_time(machine_id);
	
	return rc;

}












