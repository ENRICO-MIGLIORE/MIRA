#include "fanuc_focas__private.h"


int fanuc_focas__private__read_production_status__simulated (int md)
{

	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}

	ff->machine[md].production_status_valid = ff->machine[md].production_status_valid_simulated;
	ff->machine[md].production_status = ff->machine[md].production_status_simulated;

	return 0;

}

