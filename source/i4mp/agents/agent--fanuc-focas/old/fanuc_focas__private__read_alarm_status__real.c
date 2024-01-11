#include "fanuc_focas__private.h"


int fanuc_focas__private__read_alarm_status__real(int md)
{

	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}

	ff->machine[md].alarm_status_valid = 1;
	ff->machine[md].alarm_status = 0;
	
	return 0;

}