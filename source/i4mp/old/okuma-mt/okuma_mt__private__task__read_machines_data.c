#include "okuma_mt__private.h"


void okuma_mt__private__task__read_machines_data (void)
{

	int i;



	for (i = 0; i < om->machine_count; i++)
	{
		(void) okuma_mt__private__read_connection_status(i);

		(void) okuma_mt__private__read_production_status(i);

		(void) okuma_mt__private__read_part_counter(i);
			   
		(void) okuma_mt__private__read_cycle_time(i);
			   
		(void) okuma_mt__private__read_part_program_name(i);
	}

}
