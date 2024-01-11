#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;
extern int fanuc_focas__connect_to_lathe_machine__real(size_t machine_id);
extern int fanuc_focas__connect_to_lathe_machine__simulated(size_t machine_id);
extern int fanuc_focas__read_part_counter__real (size_t machine_id);
extern int fanuc_focas__read_part_counter__simulated (size_t machine_id);
extern int fanuc_focas__read_cycle_time__real(size_t machine_id);
extern int fanuc_focas__read_cycle_time__simulated(size_t machine_id);


static char *fn = "fanuc_focas__attach_functions()";


int fanuc_focas__attach_functions (void)
{
	size_t fd;


	for (fd = 0; fd < fanuc_focas->num_machines; fd++)
	{

		///*
		// * Connect functions
		// */
		//if (fanuc_focas->lathe_machine[fd].config.enable_simulation_mode == 0)
		//{
		//	fanuc_focas->lathe_machine[fd].connect_to_lathe_machine = fanuc_focas__connect_to_lathe_machine__real;
		//}
		//else
		//{
		//	fanuc_focas->lathe_machine[fd].connect_to_lathe_machine = fanuc_focas__connect_to_lathe_machine__simulated;
		//}


		///*
		// * Part counter functions
		// */
		//if (fanuc_focas->lathe_machine[fd].config.enable_simulation_mode == 0)
		//{
		//	fanuc_focas->lathe_machine[fd].read_part_counter_node = fanuc_focas__read_part_counter__real;
		//}
		//else
		//{
		//	fanuc_focas->lathe_machine[fd].read_part_counter_node = fanuc_focas__read_part_counter__simulated;
		//}

		///*
		// * Cycle time functions
		// */
		//if (fanuc_focas->lathe_machine[fd].config.enable_simulation_mode == 0)
		//{
		//	fanuc_focas->lathe_machine[fd].read_cycle_time_node = fanuc_focas__read_cycle_time__real;
		//}
		//else
		//{
		//	fanuc_focas->lathe_machine[fd].read_cycle_time_node = fanuc_focas__read_cycle_time__simulated;
		//}
	}

	return 0;

}
