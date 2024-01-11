#include "fanuc_focas__private.h"


extern int fanuc_focas__get_communications_enabled_machine_id(size_t* machine_id, size_t machine_count);


static char *fn = "fanuc_focas__allocate_clients()";


int fanuc_focas__allocate_clients (void)
{	

	size_t i;
	int rc;
	int error;
	size_t machine_id;

	//for (i = 0; i < ff->num_machines; i++)
	//{
	//	ff->machine[i].client = UA_Client_new();

	//	if (ff->machine[i].client == NULL)
	//	{			
	//		rc = fanuc_focas__get_machine_id(&machine_id, i);
	//		if (rc != 0)
	//		{
	//			error = -100;
	//			utils__printf__error(&ff->pf, fn, error, "fanuc_focas__get_machine_id() returned %d", rc);
	//			return error;
	//		}

	//		error = -200;
	//		utils__printf__error(&ff->pf, fn, error, "UA_Client_new() returned NULL for machine %zu", machine_id);
	//		return error;
	//	}
	//}

	return 0;
}


