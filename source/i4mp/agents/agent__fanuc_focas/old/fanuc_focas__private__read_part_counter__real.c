#include "fanuc_focas__private.h"


int fanuc_focas__private__read_part_counter__real (int md)
{

	
	IODBPSD param;
	int rc;
	//size_t part_counter;
	short number;
	short axis;
	short len;

	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}


	ff->machine[md].part_counter_valid = 0;


	number = 6711;
	axis = -1;             /* -1 means all axes */
	len = 4 + 4 * 32;      /* data block length */

	//rc = cnc_rdparam((unsigned short) fd, 6711, -1, 4 + 4 * 32, &param);  /* LEGGE IL NUMERO PART COUNT 6711*/
	//rc = cnc_rdparam (fd, 6712, -1, 4+4*32, &param); 

	rc = cnc_rdparam(ff->machine[md].handle, number, axis, len, &param);  /* LEGGE IL NUMERO PART COUNT 6711*/
	 

	if (rc != 0)
	{
		return -300;
	}

	//part_counter = (size_t) param.u.ldata;

	ff->machine[md].part_counter = (size_t)param.u.ldata;

	ff->machine[md].part_counter_valid = 1;

	return 0;

}


int fanuc_focas__private__read_part_counter__real__old (int md)
{

	int rc;
	size_t number;

	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}

	ff->machine[md].part_counter_valid = 0;


	if (ff->machine[md].data_stream_valid != 1)
	{
		return -200;
	}
	
	rc = utils__xml__extract_inner_xml(ff->machine[md].receive_buffer, ff->machine[md].receive_buffer_len, "PartCount", 9, ff->machine[md].part_counter_utf_8, sizeof(ff->machine[md].part_counter_utf_8), &ff->machine[md].part_counter_utf_8_len);
	if (rc != 0)
	{
		return -300;
	}
	
	rc = utils__libc__atost((const char*)ff->machine[md].part_counter_utf_8, ff->machine[md].part_counter_utf_8_len, &number);	
	if (rc != 0)
	{
		return -400;
	}


	ff->machine[md].part_counter = number;

	ff->machine[md].part_counter_valid = 1;

	return 0;



	

}
