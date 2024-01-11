#include "okuma_mt__private.h"


int okuma_mt__private__read_part_counter__real (int md)
{

	int rc;
	size_t part_counter;
	size_t len;
	char* p;

	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}

	om->machine[md].part_counter_valid = 0;


	if (om->machine[md].data_stream_valid != 1)
	{
		return -200;
	}
	

	p = "PartCount";
	len = strlen(p);
	
	rc = utils__xml__extract_inner_xml(om->machine[md].receive_buffer, om->machine[md].receive_buffer_len, p, len, om->machine[md].part_counter_utf_8, sizeof(om->machine[md].part_counter_utf_8), &om->machine[md].part_counter_utf_8_len);
	if (rc != 0)
	{
		return -300;
	}
	
	rc = utils__libc__atost((const char*)om->machine[md].part_counter_utf_8, om->machine[md].part_counter_utf_8_len, &part_counter);	
	if (rc != 0)
	{
		return -400;
	}

	om->machine[md].part_counter = part_counter;
	om->machine[md].part_counter_valid = 1;

	return 0;

}
