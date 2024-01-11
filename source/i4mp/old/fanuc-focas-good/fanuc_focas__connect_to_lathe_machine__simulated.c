#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;


static char* fn = "fanuc_focas__connect_to_lathe_machine__simulated";


int fanuc_focas__connect_to_lathe_machine__simulated (size_t machine_id)
{

	size_t fd;


	if (machine_id > fanuc_focas->num_machines)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	fd = machine_id - 1;

	fanuc_focas->lathe_machine[fd].connected = 1;

	utils__printf__info(&fanuc_focas->lathe_machine[fd].pf, fn, 0, "machine %zu connected in simulation mode - communications enabled", machine_id);


	return 0;

}
