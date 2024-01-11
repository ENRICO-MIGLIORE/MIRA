#include "fanuc_focas__private.h"


int fanuc_focas__get_communications_enabled_machine_id (size_t* machine_id, size_t machine_index)
{


	if (machine_id == NULL)
	{
		return -100;
	}


	if (ff->configured != 1)
	{
		return -200;
	}

	if (machine_index >= ff->machine_count)
	{
		return -300;
	}

	if (ff->machine[machine_index].config.enable_communications == 0)
	{
		return -400;
	}

	*machine_id = ff->machine[machine_index].config.id;

	return 0;


}

