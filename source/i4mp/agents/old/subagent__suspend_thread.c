#include "subagent.h"


void subagent__suspend_thread (subagent_machine_t* machine,  size_t milliseconds)
{

	if (machine == NULL)
	{
		return;
	}
	
	utils__platform__sleep(milliseconds);

	machine->thread_ticks += milliseconds;

}