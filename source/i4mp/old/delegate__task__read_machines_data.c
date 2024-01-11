#include "delegate.h"


void delegate__private__task__read_machines_data (delegate_t* delegate)
{

	int i;

	for (i = 0; i < delegate->machine_count; i++)
	{

		/*
		 * production status
		 */
		if (delegate->machine[i].config_2.simulated == 1)
		{
			//(void)siemens_open62541__private__read_connection_status__simulated(i);

			//(void)siemens_open62541__private__read_production_status__simulated(i);

			//(void)siemens_open62541__private__read_alarm_status__simulated(i);

			//(void)siemens_open62541__private__read_part_counter__simulated(i);

			//(void)siemens_open62541__private__read_cycle_time__simulated(i);

			//(void)siemens_open62541__private__read_part_program_name__simulated(i);
		}
		else
		{
			//(void)siemens_open62541__private__read_connection_status__real(i);

			//(void)siemens_open62541__private__read_production_status__real(i);

			//(void)siemens_open62541__private__read_alarm_status__real(i);

			//(void)siemens_open62541__private__read_part_counter__real(i);

			//(void)siemens_open62541__private__read_cycle_time__real(i);

			//(void)siemens_open62541__private__read_part_program_name__real(i);

		}
	}

}


