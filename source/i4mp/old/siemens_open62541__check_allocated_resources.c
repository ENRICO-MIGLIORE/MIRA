#include "siemens_open62541__private.h"

//
//extern int siemens_open62541__get_communications_enabled_machine_id(size_t* machine_id, size_t machine_index);
//
//
//static char *fn = "siemens_open62541__allocate_resources()";
//
//
//int siemens_open62541__allocate_resources (size_t fd)
//{	
//
//
//	int rc;
//
//
//	//if (fd >= so->machine_count)
//	//{
//	//	return -100;
//	//}
//
//
//	//if (so->machine[fd].config.enable_communications == 0)
//	//{
//	//	utils__printf__info(&so->pf, fn, 0, "machine %zu not enabled for communications - see configuration file", fd + 1);
//	//	return 0;
//	//}
//
//	rc = so->machine[fd].allocate_resources(fd);
//
//
//	return rc;
//}



int siemens_open62541__check_allocated_resources (void)
{
	int i;

	for (i = 0; i < so->machine_count; i++)
	{
		if ((so->machine[i].config.enable_communications == 1) && (so->machine[i].client_allocated == 0))
		{
			return -100;
		}

		if ((so->machine[i].config.enable_communications == 0) && (so->machine[i].client_allocated == 1))
		{
			return -200;
		}

	}

	return 0;
}