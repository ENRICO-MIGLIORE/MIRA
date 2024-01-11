#include "fanuc_focas__private.h"


int fanuc_focas__get_communications_enabled_machine_count (size_t* count)
{
	size_t i;
	size_t cnt;

	if (count == NULL)
	{
		return -100;
	}

	if (ff->configured != 1)
	{
		return -200;
	}

	cnt = 0;
	for (i = 0; i < ff->machine_count; i++)
	{
		if (ff->machine[i].config.enable_communications == 1)
		{
			cnt++;
		}
	}
	*count = cnt;

	return 0;
}
