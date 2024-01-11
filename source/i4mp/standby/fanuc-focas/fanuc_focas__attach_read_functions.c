#include "fanuc_focas__private.h"



int fanuc_focas__attach_read_functions (void)
{
	size_t fd;


	for (fd = 0; fd < ff->machine_count; fd++)
	{
		if (ff->machine[fd].config.enable_simulation_mode == 0)
		{
			ff->machine[fd].connect_to_machine = fanuc_focas__connect_to_machine__real;
			ff->machine[fd].read_part_counter = fanuc_focas__read_part_counter__real;
			ff->machine[fd].read_cycle_time = fanuc_focas__read_cycle_time__real;			
		}
		else
		{
			ff->machine[fd].connect_to_machine = fanuc_focas__connect_to_machine__simulated;
			ff->machine[fd].read_part_counter = fanuc_focas__read_part_counter__simulated;
			ff->machine[fd].read_cycle_time = fanuc_focas__read_cycle_time__simulated;
		}
	}

	return 0;

}