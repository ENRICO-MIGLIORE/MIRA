#include "fanuc_focas__private.h"


int fanuc_focas__check_parameters (size_t machine_id, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len)
{

	if (machine_id > ff->machine_count)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	if (buffer == NULL)
	{
		return -300;
	}

	if (buffer_size < buffer_size_min)
	{
		return -400;
	}

	if (buffer_len == NULL)
	{
		return -500;
	}

	return 0;

}






