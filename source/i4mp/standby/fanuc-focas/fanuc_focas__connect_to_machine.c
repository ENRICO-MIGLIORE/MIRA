#include "fanuc_focas__private.h"


static char* fn = "fanuc_focas__connect_to_machine";


int fanuc_focas__connect_to_machine (size_t machine_id)
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

	ff->machine[fd].connected = 0;

	if (ff->machine[fd].config.enable_communications == 0)
	{
		utils__printf__info(&ff->machine[fd].pf, fn, 0, "machine %zu not connected - see configuration file", machine_id);
		return 0;
	}

	rc = ff->machine[fd].connect_to_machine(machine_id);

	return rc;

}


