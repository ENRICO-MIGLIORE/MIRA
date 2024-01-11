#include "okuma_mt__private.h"


int okuma_mt__private__read_part_counter__real (int md)
{

	int rc;
	double number;

	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}

	om->machine[md].part_counter_valid = 0;


	if (om->machine[md].data_stream_valid != 1)
	{
		return -200;
	}
	
	rc = utils__xml__extract_inner_xml(om->machine[md].receive_buffer, om->machine[md].receive_buffer_len, "PartCount", 9, om->machine[md].part_counter_utf_8, sizeof(om->machine[md].part_counter_utf_8), &om->machine[md].part_counter_utf_8_len);
	if (rc != 0)
	{
		return -300;
	}


	rc = utils__libc__atod((const char*)om->machine[md].part_counter_utf_8, om->machine[md].part_counter_utf_8_len, &number);
	if (rc != 0)
	{
		return -400;
	}

	if (number < 0)
	{
		return -500;
	}

	om->machine[md].part_counter = (size_t) number;

	om->machine[md].part_counter_valid = 1;

	return 0;



	

}
