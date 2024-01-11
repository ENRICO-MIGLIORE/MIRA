#include "siemens_open62541__private.h"


int siemens_open62541__private__read_connection_status__simulated(int md)
{


	if ((md < 0) || (md >= so->machine_count))
	{
		return -1000;
	}


	so->machine[md].connection_status_valid = 0;

	if (so->machine[md].connection_status_simulated_valid != 1)
	{
		return -100;
	}
	
	so->machine[md].connection_status = so->machine[md].connection_status_simulated;
	so->machine[md].connection_status_valid = 1;


	return 0;


}

