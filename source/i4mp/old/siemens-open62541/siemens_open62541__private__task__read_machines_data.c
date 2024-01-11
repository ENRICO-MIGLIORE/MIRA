#include "siemens_open62541__private.h"


void siemens_open62541__private__task__read_machines_data (void)
{

	int i;

	for (i = 0; i < so->machine_count; i++)
	{
		(void) siemens_open62541__private__read_connection_status(i);

		(void) siemens_open62541__private__read_production_status(i);

		(void) siemens_open62541__private__read_part_counter(i);
			   
		(void) siemens_open62541__private__read_cycle_time(i);
			   
		(void) siemens_open62541__private__read_part_program_name(i);
	}

}


