#include "fanuc_focas__private.h"


void fanuc_focas__private__task__read_machines_data(void)
{

	int i;

	for (i = 0; i < ff->machine_count; i++)
	{

		/*
		 * production status
		 */
		if (ff->machine[i].config.simulated == 1)
		{
			(void) fanuc_focas__private__read_connection_status__simulated(i);

			(void) fanuc_focas__private__read_production_status__simulated(i);

			(void) fanuc_focas__private__read_alarm_status__simulated(i);

			(void) fanuc_focas__private__read_part_counter__simulated(i);

			(void) fanuc_focas__private__read_cycle_time__simulated(i);

			(void) fanuc_focas__private__read_part_program_name__simulated(i);
		}
		else
		{
			(void)fanuc_focas__private__read_connection_status__real(i);

			(void)fanuc_focas__private__read_production_status__real(i);

			(void)fanuc_focas__private__read_alarm_status__real(i);

			(void)fanuc_focas__private__read_part_counter__real(i);

			(void)fanuc_focas__private__read_cycle_time__real(i);

			(void)fanuc_focas__private__read_part_program_name__real(i);
		
		}
	}

}