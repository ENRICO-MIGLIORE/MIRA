#include "fggr.h"
#include "fgg__programs.h"


static char *fn = "fgg__programs__select_program_from_programs()";


int fgg__programs__select_program_from_programs(unsigned long pk_id, utils__sdb_t *data, int* active, const char *ascii_7_bit_characters_to_escape, unsigned long ascii_7_bit_characters_to_escape_len, unsigned long lang)
{
	int rc;
	fgg__buffer_t file_name;
	unsigned char buffer[FGGR__CONFIG__STACK_BUFFER_SIZE];
	unsigned long record_count;
	char language_iso_639_1_code[UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	language_iso_639_1_code[0] = 'i';
	language_iso_639_1_code[1] = 't';

	rc = utils__platform__make_absolute_file_name (fgg__programs->dir_path.data, "\\", "fgg", "programs", "--", ".txt", file_name.data, sizeof(file_name.data), &file_name.len);
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -10, "utils__platform__make_absolute_file_name() returned %d", rc);
		return -10;
	}

	/*rc = utils__sdb__read_sdb_from_file (file_name.data, pk_id, data, 0, ascii_7_bit_characters_to_escape, ascii_7_bit_characters_to_escape_len);
	if (rc != 0)
	{
	utils__printf(FGGR__ERROR, fn, -20, "utils__sdb__read_sdb_from_file() returned %d - pk_id %d", rc, pk_id);
	return -20;
	}*/


	rc =  utils__sdb__index_file(file_name.data, &record_count, fgg__programs->record_index, FGGR__CONFIG__SDB_RECORDS_MAX);
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__index_file() returned %d", rc);
		return -20;
	}

	if (pk_id > 0)
	{
		rc = utils__sdb__read_sdb_from_file(data, file_name.data, 1, fgg__programs->record_index[pk_id - 1], language_iso_639_1_code);
		if (rc != 0)
		{
			utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__read_record_using_index() returned %d", rc);
			return -30;
		}
	}
	else
	{
		rc = utils__sdb__read_sdb_from_file(data, file_name.data, 1, fgg__programs->record_index[pk_id], language_iso_639_1_code);
		if (rc != 0)
		{
			utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__read_record_using_index() returned %d", rc);
			return -30;
		}
	}

	rc = memcmp(data->name[2], "R-ACTIVE", 8);
	if (rc == 0)
	{
		*active = 0;
		if (data->value[2][0] == '1')
		{
			*active = 1;
		}
	}
	else
	{
		utils__printf__error(&fggr->pf, fn, -30, "memcmp() returned %d", rc);
		return -30;
	}


	return 0;
}



