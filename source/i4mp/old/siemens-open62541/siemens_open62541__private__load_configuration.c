#include "siemens_open62541__private.h"


static char* fn = "siemens_open62541__private__load_configuration()";


int siemens_open62541__private__load_configuration (void)
{

	int rc;


	memset(&so->config, 0, sizeof(siemens_open62541__private_config_t));


	/*
	 * read the configuration file or buffer and extract data for the agent
	 */
	rc = siemens_open62541__private__load_agent_configuration();
	if (rc != 0)
	{
		printf("%s - error - siemens_open62541__private__load_agent_configuration() returned %d\n", fn, rc);
		return -100;
	}


	/*
	 * read the configuration file or buffer and extract data for the machines
	 */
	rc = siemens_open62541__private__load_machines_configuration();
	if (rc != 0)
	{
		printf("%s - error - siemens_open62541__private__load_machines_configuration() returned %d\n", fn, rc);
		return -200;
	}


	return 0;

}
