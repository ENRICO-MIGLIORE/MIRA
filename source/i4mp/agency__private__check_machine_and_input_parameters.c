#include "agency_private.h"


int agency__private__check_machine_and_input_parameters (machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len)
{

	if (machine == NULL)
	{
		return -100;
	}

	if (machine->configured != 1)
	{
		return -200;
	}

	if (machine->started != 1)
	{
		return -300;
	}

	if (buffer == NULL)
	{
		return -400;
	}

	if (buffer_size < buffer_size_min)
	{
		return -500;
	}

	if (buffer_len == NULL)
	{
		return -600;
	}

	return 0;

}


//int subagent__check_subagent_and_input_parameters (subagent_t* subagent, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len)
//{
//
//	if (subagent == NULL)
//	{
//		return -100;
//	}
//
//	if (subagent->configured != 1)
//	{
//		return -200;
//	}
//
//	if (subagent->started != 1)
//	{
//		return -300;
//	}
//
//	if (buffer == NULL)
//	{
//		return -400;
//	}
//
//	if (buffer_size < buffer_size_min)
//	{
//		return -500;
//	}
//
//	if (buffer_len == NULL)
//	{
//		return -600;
//	}
//
//	return 0;
//
//}
//
//
