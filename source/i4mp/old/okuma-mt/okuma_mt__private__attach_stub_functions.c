#include "okuma_mt__private.h"


int okuma_mt__private__attach_stub_functions (void)
{
	int i;

	for (i = 0; i < om->machine_count; i++)
	{
		if (om->machine[i].config.simulation_mode == 1)
		{		
			om->machine[i].allocate_machine_resources = okuma_mt__private__allocate_machines_resources__simulated;
			om->machine[i].connect_to_machine = okuma_mt__private__connect_to_machine__simulated;
			om->machine[i].reconnect_to_machine = okuma_mt__private__disconnect_from_machine__simulated;
			om->machine[i].reconnect_to_machine = okuma_mt__private__reconnect_to_machine__simulated;

			om->machine[i].read_machine_connection_status = okuma_mt__private__read_connection_status__simulated;
			om->machine[i].read_machine_production_status = okuma_mt__private__read_production_status__simulated;

			om->machine[i].read_part_counter = okuma_mt__private__read_part_counter__simulated;
			om->machine[i].read_cycle_time = okuma_mt__private__read_cycle_time__simulated;
			om->machine[i].read_part_program_name = okuma_mt__private__read_part_program_name__simulated;

		}
		else
		{
			om->machine[i].allocate_machine_resources = okuma_mt__private__allocate_machines_resources__real;
			om->machine[i].connect_to_machine = okuma_mt__private__connect_to_machine__real;
			om->machine[i].reconnect_to_machine = okuma_mt__private__disconnect_from_machine__real;
			om->machine[i].reconnect_to_machine = okuma_mt__private__reconnect_to_machine__real;

			om->machine[i].read_machine_connection_status = okuma_mt__private__read_connection_status__real;
			om->machine[i].read_machine_production_status = okuma_mt__private__read_production_status__real;
			om->machine[i].read_part_counter = okuma_mt__private__read_part_counter__real;
			om->machine[i].read_cycle_time = okuma_mt__private__read_cycle_time__real;
			om->machine[i].read_part_program_name = okuma_mt__private__read_part_program_name__real;
		}
	}

	return 0;

}