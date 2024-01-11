#include "users.h"


static char *fn = "users__index_file()";


int users__index_file (void)
{
	
	int rc;

	rc = utils__sdb__index_file(users->absolute_file_name, &users->record_count, users->sdb_file_index, FGGR__CONFIG__SDB_RECORDS_MAX);

	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -10, "utils__sdb__index_file() returned %d", rc);
		return -10;
	}

	return 0;
}


