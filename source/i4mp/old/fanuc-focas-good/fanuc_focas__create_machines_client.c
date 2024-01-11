#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;


static char *fn = "fanuc_focas__create_client()";


//int fanuc_focas__create_client (void)
//{
//	int machine_id;
//	fanuc_focas__lathe_machine_t* m;
//	size_t num_machines;
//
//
//
//
//	num_machines = 1;
//	m = (fanuc_focas__lathe_machine_t*) malloc(sizeof(fanuc_focas__lathe_machine_t) * num_machines);
//	if (m == NULL)
//	{
//		printf("error in function %s - malloc() error\n", fn);
//		return -100;
//	}
//
//	memset(m, '\0', sizeof(sizeof(fanuc_focas__lathe_machine_t) * num_machines));
//
//	fanuc_focas->lathe_machine = m;
//	fanuc_focas->num_machines = num_machines;
//
//	fanuc_focas->lathe_machine[fanuc_focas->num_machines - 1].client = UA_Client_new();
//
//	if (fanuc_focas->lathe_machine[fanuc_focas->num_machines - 1].client == NULL)
//	{
//		return -110;
//	}
//
//	return 0;
//}



//static char* fn = "fanuc_focas__create_client()";




int fanuc_focas__create_machines_client (void)
{	

	size_t i;
	int error;


	for (i = 0; i < fanuc_focas->num_machines; i++)
	{
		//fanuc_focas->lathe_machine[i].client = UA_Client_new();

		//if (fanuc_focas->lathe_machine[i].client == NULL)
		{
			error = -200;
			//utils__printf__error(&fanuc_focas->pf, fn, error, "UA_Client_new() returned NULL for machine %zu", i);
			return error;
		}
	}


	return 0;
}


