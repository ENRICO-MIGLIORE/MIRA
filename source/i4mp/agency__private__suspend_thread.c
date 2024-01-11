#include "agency_private.h"


void agency__private__suspend_thread (machine_t* machine)
{

	if (machine == NULL)
	{
		return;
	}
	
	utils__platform__sleep(machine->thread_sleep_time);	

	machine->thread_ticks += machine->thread_sleep_time;

}