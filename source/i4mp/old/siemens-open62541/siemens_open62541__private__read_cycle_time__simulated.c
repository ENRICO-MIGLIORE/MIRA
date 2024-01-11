#include "siemens_open62541__private.h"


int siemens_open62541__private__read_cycle_time__simulated (int md)
{

	size_t buffer_new_len;	
	int rc;


	if ((md < 0) || (md >= so->machine_count))
	{
		return -1000;
	}


	so->machine[md].cycle_time_valid = 0;


	if (so->machine[md].cycle_time_simulated_valid != 1)
	{
		return -100;
	}


	so->machine[md].cycle_time = so->machine[md].cycle_time_simulated;
	sprintf(so->machine[md].cycle_time_utf_8, "%f", so->machine[md].cycle_time_simulated);
	so->machine[md].cycle_time_utf_8_len = strlen(so->machine[md].cycle_time_utf_8);

	rc = utils__libc__trim_string(so->machine[md].cycle_time_utf_8, so->machine[md].cycle_time_utf_8_len, &buffer_new_len, '0');
	if (rc != 0)
	{
		return -200;
	}

	if (buffer_new_len == 0)
	{
		return -300;
	}

	/*
	 *   transform 10.0 to 10
	 */
	if (so->machine[md].cycle_time_utf_8[buffer_new_len - 1] == '.')
	{
		buffer_new_len--;
	}

	so->machine[md].cycle_time_utf_8[buffer_new_len] = '\0';


	so->machine[md].cycle_time_valid = 1;


	return 0;


}

