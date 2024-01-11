#include "okuma_mt__private.h"


int okuma_mt__private__read_alarm_status__simulated (int md)
{

	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}

	om->machine[md].alarm_status_valid = om->machine[md].alarm_status_valid_simulated;
	om->machine[md].alarm_status = om->machine[md].alarm_status_simulated;

	return 0;

}

