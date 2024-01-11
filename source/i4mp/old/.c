#include "siemens_open62541__private.h"


int siemens_open62541__check_machine_id_2 (size_t machine_id)
{

	if (machine_id > so->machine_count)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	return 0;
}














