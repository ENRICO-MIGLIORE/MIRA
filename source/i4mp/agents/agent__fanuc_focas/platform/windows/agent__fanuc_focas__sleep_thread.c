 #include "agent__fanuc_focas__private.h"


void agent__fanuc_focas__sleep_thread (fanuc_focas__machine_t *machine)
{

	if (machine == NULL)
	{
		return;
	}
	
	utils__platform__sleep(machine->thread_sleep_time);	

	machine->thread_ticks += machine->thread_sleep_time;

}