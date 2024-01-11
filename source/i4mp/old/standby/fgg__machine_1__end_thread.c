#include "../fgg.h"



int fgg__machine_1__end_thread (size_t index)
{
	if (index > 2)
	{
		return -10;
	}

	if (fgg.cncs->machine[0].thread_status[index] != 1)
	{
		return -11;
	}

	fgg.cncs->machine[0].thread_status[index] = 2;
	
	return 0;
}


