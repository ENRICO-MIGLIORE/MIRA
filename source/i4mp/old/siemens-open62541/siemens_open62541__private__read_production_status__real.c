#include "siemens_open62541__private.h"


int siemens_open62541__private__read_production_status__real (int md)
{


	if ((md < 0) || (md >= so->machine_count))
	{
		return -1000;
	}


	so->machine[md].production_status = 0;


	return 0;


}

