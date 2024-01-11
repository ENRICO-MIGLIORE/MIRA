#include "okuma_mt__private.h"


int okuma_mt__private__read_part_counter (int md)
{
	int rc;


	if ((md < 0) || (md >= om->machine_count))
	{
		return -100;
	}



	rc = om->machine[md].read_part_counter(md);

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











