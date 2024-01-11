#include "fanuc_focas__private.h"


int fanuc_focas__read_part_counter__real (size_t machine_id)
{

	size_t fd;
	int rc;
	IODBPSD param;
	size_t part_counter;
	short number;
	short axis;
	short len;

	if (machine_id > ff->machine_count)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	fd = machine_id - 1;

	ff->machine[fd].part_counter_valid = 0;


	number = 6711;
	axis = -1;             /* -1 means all axes */
	len = 4 + 4 * 32;      /* data block length */

	//rc = cnc_rdparam((unsigned short) fd, 6711, -1, 4 + 4 * 32, &param);  /* LEGGE IL NUMERO PART COUNT 6711*/
	rc = cnc_rdparam(ff->machine[fd].handle, number, axis, len, &param);  /* LEGGE IL NUMERO PART COUNT 6711*/
	//rc = cnc_rdparam (fd, 6712, -1, 4+4*32, &param);  

	if (rc != 0)
	{
		return -300;
	}


	part_counter = (size_t) param.u.ldata;


	ff->machine[fd].part_counter = part_counter;
	sprintf(ff->machine[fd].part_counter_utf_8, "%zu", part_counter);
	ff->machine[fd].part_counter_utf_8_len = strlen(ff->machine[fd].part_counter_utf_8);
	ff->machine[fd].part_counter_valid = 1;

	return 0;


}



//int fgg__cnc__focas_get_machined_parts(unsigned short fd, unsigned long* count)
//{
//	int rc;
//	IODBPSD param;
//
//	rc = cnc_rdparam(fd, 6711, -1, 4 + 4 * 32, &param);  /* LEGGE IL NUMERO PART COUNT 6711*/
//	//rc = cnc_rdparam (fd, 6712, -1, 4+4*32, &param);  
//
//
//	*count = (unsigned long)param.u.ldata;
//
//	return rc;
//}
