#include "fanuc_focas__private.h"


static char* fn = "fanuc_focas__connect_to_machine__simulated";


int fanuc_focas__connect_to_machine__simulated(size_t machine_id)
{

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

	ff->machine[fd].connected = 1;

	utils__printf__info(&ff->machine[fd].pf, fn, 0, "machine %zu connected in simulation mode", machine_id);
	
	return 0;

}
