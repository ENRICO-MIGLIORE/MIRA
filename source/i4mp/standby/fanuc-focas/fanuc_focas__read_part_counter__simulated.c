#include "fanuc_focas__private.h"



int fanuc_focas__read_part_counter__simulated (size_t machine_id)
{

	size_t fd;
	int r;
	static size_t part_counter = 100;    /* one static variable for all the machines */


	if (machine_id > ff->machine_count)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	fd = machine_id - 1;

	ff->machine[fd].part_counter_valid = 0;

	part_counter++;

	r = rand();      /* Returns a pseudo-random integer between 0 and RAND_MAX */
	r = r % 100;


	if (r > 20)
	{
		ff->machine[fd].part_counter = part_counter;
		sprintf(ff->machine[fd].part_counter_utf_8, "%zu", part_counter);
		ff->machine[fd].part_counter_utf_8_len = strlen(ff->machine[fd].part_counter_utf_8);
		ff->machine[fd].part_counter_valid = 1;
		return 0;
	}


	return -1000;

}


