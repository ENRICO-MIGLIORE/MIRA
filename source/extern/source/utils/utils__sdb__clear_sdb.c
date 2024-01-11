#include "utils__sdb.h"


int utils__sdb__clear_sdb (utils__sdb_t *sdb)
{
	size_t i;
	

	if (sdb == NULL)
	{
		return -10;
	}

	if (sdb->configured != 1)
	{
		return -20;
	}

	for (i = 0; i < sdb->fields_max; i++)
	{
		sdb->encoding[i] = 0;
	}


	sdb->buffer_len = 0;
	sdb->num_fields = 0;
	sdb->section_name_len = 0;

	sdb->end_of_record_signature = -1;
	sdb->comment_lines = 0;

	return 0;
}


