#include "fggr.h"
#include "fgg__programs.h"



int fgg__programs__get_program_count (unsigned long *count)
{			
	int rc;
	fgg__buffer_t file_name;
	static char *fn = "fgg__programs__get_program_count()";

	rc = utils__platform__make_absolute_file_name (fgg__programs->dir_path.data, "\\", "fgg", "programs", "--", ".txt", file_name.data, sizeof(file_name.data), &file_name.len);
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -10, "utils__platform__make_absolute_file_name() returned %d", rc);
		return -10;
	}

	rc =  utils__sdb__index_file(file_name.data, count, fgg__programs->record_index, FGGR__CONFIG__SDB_RECORDS_MAX);
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__index_file() returned %d", rc);
		return -20;
	}


	return 0;
}

