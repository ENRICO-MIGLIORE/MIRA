#include "mira__private.h"


int mira__get_machine_networked_status (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int rc;
	int ad;
	int ag_md;


	rc = mira__private__verify_framework_is_started();
	if (rc != 0)
	{
		return -10000;
	}


	rc = mira__private__convert_machine_descriptor_to_agent_descriptor(md, &ad, &ag_md);
	if (rc != 0)
	{
		return -20000;
	}


	rc = mira->config.i4_agency[ad].get_machine_networked_status(ag_md, buffer, buffer_size, buffer_len);


	return rc;

}