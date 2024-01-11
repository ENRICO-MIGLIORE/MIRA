#include "agent__siemens_open62541__private.h"


int agent__siemens_open62541__get_machine_manufacturer (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
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

	if ((md < 0) || (md >= agent_so->number_of_machines))
	{
		return -300;
	}

	rc = subagent__get_machine_manufacturer(&agent_so->subagent.machine[md], buffer, buffer_size, buffer_len);

	return rc;
}

