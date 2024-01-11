#include "siemens_open62541__private.h"


int siemens_open62541__private__read_part_counter (int md)
{
	int rc;


	if ((md < 0) || (md >= so->machine_count))
	{
		return -100;
	}



	rc = so->machine[md].read_part_counter(md);

	//if (rc == 0)
	//{
	//	so->machine[md].no_response_flag = 0;
	//}
	//else
	//{
	//	so->machine[md].no_response_flag = 1;
	//}

	return rc;
	
}











