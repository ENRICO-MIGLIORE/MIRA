#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;


static char* fn = "fanuc_focas__connect_to_lathe_machine";


int fanuc_focas__connect_to_lathe_machine (size_t machine_id)
{

	int rc;
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

	fanuc_focas->lathe_machine[fd].connected = 0;

	if (fanuc_focas->lathe_machine[fd].config.enable_communications == 0)
	{
		utils__printf__info(&fanuc_focas->lathe_machine[fd].pf, fn, 0, "machine %zu is not connected because communications are not enabled", machine_id);
		return 0;
	}

	rc = fanuc_focas->lathe_machine[fd].connect_to_lathe_machine(machine_id);

	return rc;

}




