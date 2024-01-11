#include "siemens_open62541__private.h"


int siemens_open62541__private__read_connection_status (int md)
{
	int rc;

	if ((md < 0) || (md >= so->machine_count))
	{
		return -100;
	}

	//if (so->machine[md].config.connect_to_machine == 0)
	//{
	//	return -200;
	//}
	
	rc = so->machine[md].read_machine_connection_status(md);

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












