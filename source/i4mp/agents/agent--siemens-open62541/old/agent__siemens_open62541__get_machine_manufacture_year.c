#include "agent__siemens_open62541__private.h"


int agent__siemens_open62541__get_machine_manufacture_year (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int rc;

	if (agent_so == NULL)
	{
		return -100;
	}

	if (agent_so->started != 1)
	{
		return -200;
	}
	
	rc = subagent__get_machine_manufacture_year(&agent_so->subagent.machine[md], buffer, buffer_size, buffer_len);
	
	return rc;
}

