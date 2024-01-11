#include "fanuc_focas__private.h"


int fanuc_focas__private__read_part_program_name__simulated (int md)
{


	if ((md < 0) || (md >= ff->machine_count))
	{
		return -1000;
	}


	ff->machine[md].part_program_name_valid = 0;


	if (ff->machine[md].part_program_name_simulated_valid != 1)
	{
		return -100;
	}

	strcpy(ff->machine[md].part_program_name, ff->machine[md].part_program_name_simulated);
	strcpy(ff->machine[md].part_program_name_utf_8, ff->machine[md].part_program_name);
	ff->machine[md].part_program_name_utf_8_len = strlen(ff->machine[md].part_program_name_utf_8);

	ff->machine[md].part_program_name_valid = 1;

	return 0;


}

