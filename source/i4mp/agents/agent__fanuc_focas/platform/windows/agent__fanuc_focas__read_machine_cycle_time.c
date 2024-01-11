#include "Fwlib64.h"

//#include <agency_private.h>

#include "agent__fanuc_focas__private.h"


int agent__fanuc_focas__read_machine_cycle_time (fanuc_focas__machine_t *machine)
{

	short rc;
	const char* fn;
	unsigned short machine_handle;
	short parameter_type;
	//machine_t* machine;
	IODBTIME cycle_time;
	IODBPSD seconds;
	IODBPSD minutes;

	

	fn = "agent__fanuc_focas__read_machine_cycle_time()";


	if (machine == NULL)
	{
		return -100;
	}

	//machine = (machine_t*) arg;

	if (machine->ext_unsigned_short_valid == 0)
	{
		return -100;
	}

	machine_handle = machine->ext_unsigned_short;


	machine->cycle_time_valid = 0;


	/*	 
	 *  0 :	Power on time
	 *	1 : Operating time
	 *	2 : Cutting time
	 *	3 : Cycle time
	 *	4 : Free purpose
     */
	parameter_type = 3;

	rc = cnc_rdtimer(machine_handle, parameter_type, &cycle_time);

	if (rc != EW_OK)
	{
		return -400;
	}

		
	rc = cnc_rdparam(machine_handle, 6757, 0, 8, &seconds);
	char* p;
	p = seconds.u.cdata;

	rc = cnc_rdparam(machine_handle, 6758, 0, 8, &minutes);

	char* q;
	q = minutes.u.ldata;

	machine->cycle_time_native = (double)(((double)cycle_time.minute) / 60.0);
	machine->cycle_time_native += (double)(((double)(cycle_time.msec)) * 1000);

	//machine->cycle_time_native = (double) (((double)cycle_time.minute) / 60.0);
	//machine->cycle_time_native += (double) (((double) (cycle_time.msec)) * 1000);


	sprintf(machine->cycle_time, "%.1f", machine->cycle_time_native);
	machine->cycle_time_valid = 1;


	return 0;

}
