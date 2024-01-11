#include "okuma_mt__private.h"


int okuma_mt__private__read_production_status (int md)
{
	int rc;

	if ((md < 0) || (md >= om->machine_count))
	{
		return -100;
	}

	
	rc = om->machine[md].read_machine_production_status(md);

	//if (rc == 0)
	//{
	//	om->machine[md].no_response_flag = 0;
	//}
	//else
	//{
	//	om->machine[md].no_response_flag = 1;
	//}
	
	return rc;

}












