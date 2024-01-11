#include "siemens_open62541__private.h"


int siemens_open62541__private__read_part_counter__simulated (int md)
{

	if ((md < 0) || (md >= so->machine_count))
	{
		return -1000;
	}
	

	so->machine[md].part_counter_valid = 0;

	if (so->machine[md].part_counter_simulated_valid != 1)
	{
		return -100;
	}

	so->machine[md].part_counter = so->machine[md].part_counter_simulated;
	sprintf(so->machine[md].part_counter_utf_8, "%zu", so->machine[md].part_counter);
	so->machine[md].part_counter_utf_8_len = strlen(so->machine[md].part_counter_utf_8);

	so->machine[md].part_counter_valid = 1;

	return 0;


}


