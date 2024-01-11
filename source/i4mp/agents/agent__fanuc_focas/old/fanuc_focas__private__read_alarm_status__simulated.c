#include "fanuc_focas__private.h"


int fanuc_focas__private__read_alarm_status__simulated (int md)
{

	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}

	ff->machine[md].alarm_status_valid = ff->machine[md].alarm_status_valid_simulated;
	ff->machine[md].alarm_status = ff->machine[md].alarm_status_simulated;

	return 0;

}

