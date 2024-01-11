#include "okuma_mt__private.h"


int okuma_mt__private__read_part_program_name__simulated (int md)
{


	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}


	om->machine[md].part_program_name_valid = 0;


	if (om->machine[md].part_program_name_simulated_valid != 1)
	{
		return -100;
	}

	strcpy(om->machine[md].part_program_name, om->machine[md].part_program_name_simulated);
	strcpy(om->machine[md].part_program_name_utf_8, om->machine[md].part_program_name);
	om->machine[md].part_program_name_utf_8_len = strlen(om->machine[md].part_program_name_utf_8);

	om->machine[md].part_program_name_valid = 1;

	return 0;


}

