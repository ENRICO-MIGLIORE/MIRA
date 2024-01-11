#include "fgg__suppliers__private.h"
#include "fgg__suppliers.h"

static char *fn = "fgg__suppliers__db__select_supplier_from_suppliers()";


int fgg__suppliers__sdb__select_supplier_from_suppliers(unsigned long pk_id, utils__sdb_t *sdb, int *active)
{
	int rc;
	unsigned char buffer[FGG__CONFIG__STACK_BUFFER_SIZE];


	if (pk_id == 0)
	{
		fgg__printf(FGGR__ERROR, fn, -10, "pk_id = 0");
		return -10;
	}


	if (pk_id > fgg__suppliers->record_count)
	{
		fgg__printf(FGGR__ERROR, fn, -20, "pk_id > fgg__fiscal_data->record_count - pk_id = %d", pk_id);
		return -20;
	}


	rc = utils__sdb__read_record_using_index (sdb, fgg__suppliers->absolute_file_name, buffer, sizeof(buffer), fgg__suppliers->sdb_file_index[pk_id - 1], SDB__EOR__TILDE);
	if (rc != 0)
	{
		fgg__printf(FGGR__ERROR, fn, -20, "utils__sdb__read_record_using_index() returned %d", rc);
		return -30;
	}



	rc = memcmp (sdb->name[FGGR__PRIVATE_FIELD__ACTIVE], fgg.reserved__field_names[FGGR__PRIVATE_FIELD__ACTIVE], fgg.reserved_field_names_len[FGGR__PRIVATE_FIELD__ACTIVE]);
	if (rc == 0)
	{
		*active = 0;
		if (sdb->value[FGGR__PRIVATE_FIELD__ACTIVE][0] == FGGR__PRIVATE_FIELD__VALUE__ACTIVE)
		{
			*active = 1;
		}
	}
	else
	{
		fgg__printf(FGGR__ERROR, fn, -30, "memcmp() returned %d", rc);
		return -30;
	}


	return 0;
}





