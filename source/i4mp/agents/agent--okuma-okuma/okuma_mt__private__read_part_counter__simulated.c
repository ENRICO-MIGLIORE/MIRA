#include "okuma_mt__private.h"


int okuma_mt__private__read_part_counter__simulated (int md)
{

	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}


	om->machine[md].part_counter_valid = 0;

	if (om->machine[md].part_counter_simulated_valid != 1)
	{
		return -100;
	}

	om->machine[md].part_counter = om->machine[md].part_counter_simulated;
	sprintf(om->machine[md].part_counter_utf_8, "%zu", om->machine[md].part_counter);
	om->machine[md].part_counter_utf_8_len = strlen(om->machine[md].part_counter_utf_8);

	om->machine[md].part_counter_valid = 1;

	return 0;

}