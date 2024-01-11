#include "..\fggr.h"
#include "carmelo__cncs.h"


int carmelo__cncs__db__select_count_from_cncs(unsigned long *count)
{		

	int rc;
	fgg__buffer_t file_name;
	static char *fn = "carmelo__cncs__db__select_count_from_cncs()";


	
	rc = utils__platform__make_absolute_file_name(carmelo__cncs->dir_path.data, "carmelo", "cncs", "--", ".txt", file_name.data, sizeof(file_name.data), &file_name.len);
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -10, "utils__platform__make_absolute_file_name() returned %d", rc);
		return -10;
	}

	/*rc = utils__sdb__get_record_count_from_file (file_name.data, count);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -20, "utils__sdb__get_record_count_from_file() returned %d", rc);
		return -20;
	}*/
	
	rc =  utils__sdb__index_file(file_name.data, count, carmelo__cncs->record_index, FGGR__CONFIG__SDB_RECORDS_MAX);
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__index_file() returned %d", rc);
		return -20;
	}

	return 0;
}


