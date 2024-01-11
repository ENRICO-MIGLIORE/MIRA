#include "siemens_open62541__private.h"


int siemens_open62541__get_communications_enabled_machine_id2 (size_t* machine_id, size_t machine_index)
{
	size_t fd;


	if (so->configured != 1)
	{
		return -100;
	}

	if (machine_id == NULL)
	{
		return -200;
	}

	if (machine_index >= so->machine_count)
	{
		return -300;
	}

	fd = machine_index;

	if (so->machine[fd].config.enable_communications == 0)
	{
		return -400;
	}
	
	*machine_id = so->machine[fd].config.id;

	return 0;
}




