#include "machines__private.h"
#include "machines.h"


static char *fn = "machines__sdb__index_file()";

/*
int machines__sdb__index_file (void)
{
	
	int rc;
	unsigned char buffer[FGG__CONFIG__STACK_BUFFER_SIZE];

	rc = utils__sdb__index_file (machines->absolute_file_name, buffer, sizeof(buffer), &machines->record_count, machines->sdb_file_index, FGG__CONFIG__SDB_RECORDS_MAX, SDB__EOR__TILDE);

	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -10, "utils__sdb__index_file() returned %d", rc);
		return -10;
	}

	return 0;
}


*/