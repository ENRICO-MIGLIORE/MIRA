#include "machine.h"


/*
 * this C module is 100% reentrant
 */

int machine__init (subagent__machine_t* machine)
{
	int rc;
	char* fn;


	fn = "machine__init()";


	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "agent is null");
		return -100;
	}

	memset(machine, 0, sizeof(subagent__machine_t));

	///*
	// * init the utils_printf subsystem
	// */
	//rc = utils__printf__init(&subagent->pf);
	//if (rc != 0)
	//{		
	//	utils__printf__error(NULL, fn, -200, "utils__printf__init() returned %d", rc);
	//	return -200;
	//}


	//rc = utils__sdb__init(&subagent->sdb);
	//if (rc != 0)
	//{
	//	utils__printf__error(NULL, fn, -300, "utils__sdb__init() returned %d", rc);
	//	return -300;
	//}

	return 0;
}