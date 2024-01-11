#include "fanuc_focas__private.h"


int fanuc_focas__read_cycle_time__simulated (size_t machine_id)
{

	size_t buffer_new_len;	
	int r;
	int d;
	double cycle_time;
	double delta;
	int rc;
	size_t fd;

	rc = fanuc_focas__check_machine_id(machine_id);

	if (rc != 0)
	{
		return -100;
	}

	fd = machine_id - 1;

	ff->machine[fd].cycle_time_valid = 0;

	cycle_time = 10.0;


	r = rand();
	r = r % 100;

	if (r > 20)
	{

		d = rand();
		d = d % 10;

		delta = (double)d;
		delta /= 10;

		if (r % 2 == 0)
		{
			cycle_time += delta;
		}
		else
		{
			cycle_time -= delta;
		}



		/*
		 *   10.0 becomes 10
		 */
		ff->machine[fd].cycle_time = cycle_time;
		sprintf(ff->machine[fd].cycle_time_utf_8, "%f", cycle_time);
		ff->machine[fd].cycle_time_utf_8_len = strlen(ff->machine[fd].cycle_time_utf_8);

		rc = utils__libc__trim_string(ff->machine[fd].cycle_time_utf_8, ff->machine[fd].cycle_time_utf_8_len, &buffer_new_len, '0');
		if (rc != 0)
		{
			return -200;
		}

		if (buffer_new_len == 0)
		{
			return -300;
		}

		if (ff->machine[fd].cycle_time_utf_8[buffer_new_len - 1] == '.')
		{
			buffer_new_len--;
		}

		ff->machine[fd].cycle_time_utf_8[buffer_new_len] = '\0';
		ff->machine[fd].cycle_time_valid = 1;


		return 0;
	}


	return -1000;

}

