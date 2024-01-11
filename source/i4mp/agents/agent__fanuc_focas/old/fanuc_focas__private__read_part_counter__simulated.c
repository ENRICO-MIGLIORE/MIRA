#include "fanuc_focas__private.h"


int fanuc_focas__private__read_part_counter__simulated (int md)
{

	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}


	ff->machine[md].part_counter_valid = 0;

	if (ff->machine[md].part_counter_simulated_valid != 1)
	{
		return -100;
	}

	ff->machine[md].part_counter = ff->machine[md].part_counter_simulated;
	sprintf(ff->machine[md].part_counter_utf_8, "%zu", ff->machine[md].part_counter);
	ff->machine[md].part_counter_utf_8_len = strlen(ff->machine[md].part_counter_utf_8);

	ff->machine[md].part_counter_valid = 1;

	return 0;

}