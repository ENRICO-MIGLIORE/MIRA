#include "okuma_mt__private.h"


int okuma_mt__private__check_parameters_and_agent_status (int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len)
{

	if (om == NULL)
	{
		return -100;
	}

	if (om->configured != 1)
	{
		return -200;
	}

	if ((md >= om->machine_count) || (md < 0))
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








