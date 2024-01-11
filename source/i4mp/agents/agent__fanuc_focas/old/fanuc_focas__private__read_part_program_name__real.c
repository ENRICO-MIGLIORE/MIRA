#include "fanuc_focas__private.h"


int fanuc_focas__private__read_part_program_name__real(int md)
{

	int rc;


	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}

	ff->machine[md].part_program_name_valid = 0;


	if (ff->machine[md].data_stream_valid != 1)
	{
		return -200;
	}

	rc = utils__xml__extract_inner_xml(ff->machine[md].receive_buffer, ff->machine[md].receive_buffer_len, "Program", 7, ff->machine[md].part_program_name_utf_8, sizeof(ff->machine[md].part_program_name_utf_8), &ff->machine[md].part_program_name_utf_8_len);
	if (rc != 0)
	{
		return -300;
	}

	ff->machine[md].part_program_name_valid = 1;

	return 0;

}