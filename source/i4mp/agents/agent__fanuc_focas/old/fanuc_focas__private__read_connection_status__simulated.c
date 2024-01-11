#include "fanuc_focas__private.h"


int fanuc_focas__private__read_connection_status__simulated(int md)
{

	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}

	ff->machine[md].connection_status_valid = ff->machine[md].connection_status_valid_simulated;
	ff->machine[md].connection_status = ff->machine[md].connection_status_simulated;

	return 0;

}

