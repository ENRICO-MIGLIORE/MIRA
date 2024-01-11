#include "fanuc_focas__private.h"


int fanuc_focas__private__read_cycle_time__simulated (int md)
{

	size_t buffer_new_len;	
	int rc;


	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}


	ff->machine[md].cycle_time_valid = 0;


	if (ff->machine[md].cycle_time_simulated_valid != 1)
	{
		return -100;
	}


	ff->machine[md].cycle_time = ff->machine[md].cycle_time_simulated;
	sprintf(ff->machine[md].cycle_time_utf_8, "%f", ff->machine[md].cycle_time_simulated);
	ff->machine[md].cycle_time_utf_8_len = strlen(ff->machine[md].cycle_time_utf_8);

	rc = utils__libc__trim_string(ff->machine[md].cycle_time_utf_8, ff->machine[md].cycle_time_utf_8_len, &buffer_new_len, '0');
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
	if (ff->machine[md].cycle_time_utf_8[buffer_new_len - 1] == '.')
	{
		buffer_new_len--;
	}

	ff->machine[md].cycle_time_utf_8[buffer_new_len] = '\0';

	ff->machine[md].cycle_time_utf_8_len = buffer_new_len;

	ff->machine[md].cycle_time_valid = 1;

	return 0;


}

