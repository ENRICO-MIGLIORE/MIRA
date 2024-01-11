#include "siemens_open62541__private.h"


int siemens_open62541__private__attach_stub_functions (void)
{
	int i;

	for (i = 0; i < so->machine_count; i++)
	{
		if (so->machine[i].config.simulation_mode == 1)
		{		
			so->machine[i].allocate_machine_resources = siemens_open62541__private__allocate_machines_resources__simulated;
			so->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__simulated;
			so->machine[i].reconnect_to_machine = siemens_open62541__private__disconnect_from_machine__simulated;
			so->machine[i].reconnect_to_machine = siemens_open62541__private__reconnect_to_machine__simulated;

			so->machine[i].read_machine_connection_status = siemens_open62541__private__read_connection_status__simulated;
			so->machine[i].read_machine_production_status = siemens_open62541__private__read_production_status__simulated;

			so->machine[i].read_part_counter = siemens_open62541__private__read_part_counter__simulated;
			so->machine[i].read_cycle_time = siemens_open62541__private__read_cycle_time__simulated;
			so->machine[i].read_part_program_name = siemens_open62541__private__read_part_program_name__simulated;

		}
		else
		{
			so->machine[i].allocate_machine_resources = siemens_open62541__private__allocate_machines_resources__real;
			so->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__real;
			so->machine[i].reconnect_to_machine = siemens_open62541__private__disconnect_from_machine__real;
			so->machine[i].reconnect_to_machine = siemens_open62541__private__reconnect_to_machine__real;

			so->machine[i].read_machine_connection_status = siemens_open62541__private__read_connection_status__real;
			so->machine[i].read_machine_production_status = siemens_open62541__private__read_production_status__real;
			so->machine[i].read_part_counter = siemens_open62541__private__read_part_counter__real;
			so->machine[i].read_cycle_time = siemens_open62541__private__read_cycle_time__real;
			so->machine[i].read_part_program_name = siemens_open62541__private__read_part_program_name__real;
		}
	}

	return 0;

}