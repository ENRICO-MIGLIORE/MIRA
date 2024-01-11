#include "machine.h"


int delegate__private__read_cycle_time__simulated (subagent__machine_t * machine, int md)
{

	size_t buffer_new_len;	
	int rc;


	//if ((md < 0) || (md >= machine->machine_count))
	//{
	//	return -1000;
	//}


	//machine->machine_local[md].cycle_time_valid = 0;


	//if (machine->machine_local[md].cycle_time_simulated_valid != 1)
	//{
	//	return -100;
	//}

	//machine->machine_local[md].cycle_time = machine->machine_local[md].cycle_time_simulated;
	//sprintf(machine->machine_local[md].cycle_time_utf_8, "%f", machine->machine_local[md].cycle_time_simulated);
	//machine->machine_local[md].cycle_time_utf_8_len = strlen(machine->machine_local[md].cycle_time_utf_8);

	//rc = utils__libc__trim_string(machine->machine_local[md].cycle_time_utf_8, machine->machine_local[md].cycle_time_utf_8_len, &buffer_new_len, '0');
	//if (rc != 0)
	//{
	//	return -200;
	//}

	//if (buffer_new_len == 0)
	//{
	//	return -300;
	//}

	///*
	// *   transform 10.0 to 10
	// */
	//if (machine->machine_local[md].cycle_time_utf_8[buffer_new_len - 1] == '.')
	//{
	//	buffer_new_len--;
	//}

	//machine->machine_local[md].cycle_time_utf_8[buffer_new_len] = '\0';

	//machine->machine_local[md].cycle_time_utf_8_len = buffer_new_len;

	//machine->machine_local[md].cycle_time_valid = 1;


	return 0;


}

