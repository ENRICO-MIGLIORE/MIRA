#include "Fwlib64.h"

// #include <agency_private.h>

#include "agent__fanuc_focas__private.h"


int agent__fanuc_focas__read_machine_part_counter (fanuc_focas__machine_t *machine)
{
	
	short rc;
	short number;
	short axis;
	short len;
	const char* fn;
	unsigned short machine_handle;
	//machine_t* machine;
	IODBPSD param;
	

	fn = "agent__fanuc_focas__read_machine_part_counter()";


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

	machine->part_counter_valid = 0;   //ff->machine[md].part_counter_valid = 0;


	number = 6711;

	number = 6712;    /* https://en.industryarena.com/forum/fanuc-31i-parts-count--177281.html */

	number = 3011;  /* https://www.tornos.com/sites/tornos.com/files/data/Tips_and_tricks/IT/4_it_trucs_et_astuces_macro_b_ok.pdf  CNC time */


	number = 6750;  /* FANUC B-64730IT_01.pdf  */

	number = 6754;  /* FANUC B-64490EN_03 Parameter.pdf  */

	axis = -1;             /* -1 means all axes */
	len = 4 + 4 * 32;      /* data block length */

	//rc = cnc_rdparam((unsigned short) fd, 6711, -1, 4 + 4 * 32, &param);  /* LEGGE IL NUMERO PART COUNT 6711*/
	//rc = cnc_rdparam (fd, 6712, -1, 4+4*32, &param); 

	rc = cnc_rdparam(machine_handle, number, axis, len, &param);  /* LEGGE IL NUMERO PART COUNT 6711*/


	if (rc != EW_OK)
	{
		return -300;
	}


	machine->part_counter_native = (int)param.u.ldata;
	sprintf(machine->part_counter, "%d", machine->part_counter_native);
	machine->part_counter_valid = 1;

	return 0;

}

