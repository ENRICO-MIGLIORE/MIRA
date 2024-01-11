#include "fanuc_focas__private.h"


int fanuc_focas__private__read_connection_status__real (int md)
{

	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}

	ff->machine[md].connection_status_valid = 1;
	ff->machine[md].connection_status = 1;

	return 0;

}

