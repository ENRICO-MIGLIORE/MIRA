#include "okuma_mt__private.h"


int okuma_mt__private__read_cycle_time__simulated (int md)
{

	size_t buffer_new_len;	
	int rc;


	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}


	om->machine[md].cycle_time_valid = 0;


	if (om->machine[md].cycle_time_simulated_valid != 1)
	{
		return -100;
	}


	om->machine[md].cycle_time = om->machine[md].cycle_time_simulated;
	sprintf(om->machine[md].cycle_time_utf_8, "%f", om->machine[md].cycle_time_simulated);
	om->machine[md].cycle_time_utf_8_len = strlen(om->machine[md].cycle_time_utf_8);

	rc = utils__libc__trim_string(om->machine[md].cycle_time_utf_8, om->machine[md].cycle_time_utf_8_len, &buffer_new_len, '0');
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
	if (om->machine[md].cycle_time_utf_8[buffer_new_len - 1] == '.')
	{
		buffer_new_len--;
	}

	om->machine[md].cycle_time_utf_8[buffer_new_len] = '\0';

	om->machine[md].cycle_time_utf_8_len = buffer_new_len;

	om->machine[md].cycle_time_valid = 1;

	return 0;


}

