#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;


static char* fn = "fanuc_focas__read_part_counter()";


int fanuc_focas__read_part_counter (size_t machine_id)
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


	if (fanuc_focas->lathe_machine[fd].connected == 0)
	{
		return -300;
	}

	rc = fanuc_focas->lathe_machine[fd].read_part_counter_node(machine_id);

	return rc;
	
}











