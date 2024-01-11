#include "fgg__suppliers__private.h"
#include "fgg__suppliers.h"

static char *fn = "fgg__suppliers__db__select_count_from_suppliers()";


int fgg__suppliers__sdb__select_count_from_suppliers(unsigned long *count)
{		
	*count = fgg__suppliers->record_count;

	return 0;
}
