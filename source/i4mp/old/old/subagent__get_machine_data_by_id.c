#include "subagent.h"


//int subagent__get_machine_data (machine_t* machine, char *data, size_t data_len, int data_valid, char* buffer, size_t buffer_size, size_t* buffer_len)
//{
//
//	size_t buffer_size_min;
//	int rc;
//
//	buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE_256;
//
//	rc = subagent__check_machine_and_input_parameters(machine, buffer, buffer_size, buffer_size_min, buffer_len);
//
//	if ((rc == 0) && (data_valid == 1))
//	{		
//		strcpy(buffer, data);
//		*buffer_len = data_len;
//	}
//	else 
//	{
//		buffer[0] = '-';    /* data not available */
//		buffer[1] = '\0';
//		*buffer_len = 1;
//	}
//
//	return 0;
//}
//
//

int subagent__get_machine_data_by_id (machine_t* machine, int data_id, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;
	int flag;

	flag = 0;

	buffer_size_min = SUBAGENT__CONFIG__BUFFER_SIZE_256;

	rc = subagent__check_machine_and_input_parameters(machine, buffer, buffer_size, buffer_size_min, buffer_len);

	switch (data_id)	
	{
	    case SUBAGENT__CYCLE_TIME:
		if ((rc == 0) && (machine->cycle_time_valid == 1))
		{
			strcpy(buffer, machine->cycle_time);
			*buffer_len = machine->cycle_time_len;
			flag = 1;
		}
		break;
	}


	if (flag == 0)
	{
		buffer[0] = '-';    /* data not available */
		buffer[1] = '\0';
		*buffer_len = 1;
	}


	return 0;
}
