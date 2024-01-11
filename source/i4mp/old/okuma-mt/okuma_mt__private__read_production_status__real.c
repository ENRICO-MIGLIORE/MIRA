#include "okuma_mt__private.h"


int okuma_mt__private__read_production_status__real (int md)
{


	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}


	om->machine[md].production_status = 0;


	return 0;


}

