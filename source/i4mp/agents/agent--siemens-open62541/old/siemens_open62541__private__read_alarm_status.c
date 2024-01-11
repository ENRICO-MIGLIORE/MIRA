#include "siemens_open62541__private.h"


int siemens_open62541__private__read_alarm_status (int md)
{
	int rc;

	if ((md < 0) || (md >= so->machine_count))
	{
		return -100;
	}
	
	rc = so->machine[md].read_alarm_status(md);
	
	return rc;

}












