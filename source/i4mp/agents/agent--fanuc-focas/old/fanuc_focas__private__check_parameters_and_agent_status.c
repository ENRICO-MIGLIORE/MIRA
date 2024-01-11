#include "fanuc_focas__private.h"


int fanuc_focas__private__check_parameters_and_agent_status (int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len)
{

	if (ff == NULL)
	{
		return -100;
	}

	if (ff->configured != 1)
	{
		return -200;
	}

	if (md < 0)
	{
		return -300;
	}

	if ((ff->machine_count > 0) && (md >= ff->machine_count))
	{
		return -400;
	}

	if (buffer == NULL)
	{
		return -500;
	}

	if (buffer_size < buffer_size_min)
	{
		return -600;
	}

	if (buffer_len == NULL)
	{
		return -700;
	}

	return 0;

}








