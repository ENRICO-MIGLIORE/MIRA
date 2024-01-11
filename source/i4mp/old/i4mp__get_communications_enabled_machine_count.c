#include "mira__private.h"


int i4mp__get_communications_enabled_machine_count (size_t* count)
{

	if (count == NULL)
	{
		return -100;
	}

	if (i4mp->configured != 1)
	{
		return -200;
	}

	if (i4mp->started != 1)
	{
		return -300;
	}


	*count = i4mp->communications_enabled_machine_count;


	return 0;
}





