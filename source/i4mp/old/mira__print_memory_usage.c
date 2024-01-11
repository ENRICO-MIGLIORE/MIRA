#include "mira__private.h"


int mira__print_memory_usage (void)
{

	if (mira == NULL)
	{
		return -100;
	}

	if (mira->started != 1)
	{
		return -200;
	}
	
	printf("mira memory size = %zu\n", mira->size);

	return 0;
}
