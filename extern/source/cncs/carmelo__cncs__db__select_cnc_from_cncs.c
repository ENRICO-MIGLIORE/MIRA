#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/plugin/securitypolicy.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/plugin/securitypolicy_default.h>
#include <open62541/plugin/common.h>


#include "..\fggr.h"
#include "carmelo__cncs.h"

static char *fn = "carmelo__cncs__db__select_customer_from_customers()";


int carmelo__cncs__db__select_cnc_from_cncs (unsigned long id, utils__sdb_t *data, int *active, const char *ascii_7_bit_characters_to_escape, unsigned long ascii_7_bit_characters_to_escape_len, unsigned long lang)
{

	int rc;
	fgg__buffer_t file_name;
	/*unsigned char buffer[FGGR__CONFIG__STACK_BUFFER_SIZE];*/
	unsigned long record_count;

	unsigned long language_iso_639_1_code_len;
	char language_iso_639_1_code[UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	language_iso_639_1_code[0] = 'i';
	language_iso_639_1_code[1] = 't';
	language_iso_639_1_code_len = 2;
	

	
	rc = utils__platform__make_absolute_file_name(carmelo__cncs->dir_path.data, "carmelo", "cncs", "--", ".txt", file_name.data, sizeof(file_name.data), &file_name.len);
	
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -10, "utils__platform__make_absolute_file_name() returned %d", rc);
		return -10;
	}


	/*rc = utils__sdb__read_record_from_file (file_name.data, id, data, 0, ascii_7_bit_characters_to_escape, ascii_7_bit_characters_to_escape_len);
	if (rc != 0)
	{
	utils__printf(FGGR__ERROR, fn, -20, "utils__platform__make_absolute_file_name() returned %d- id = %d", rc, id);
	return -20;
	}*/

	
	rc = utils__sdb__index_file (file_name.data, &record_count, carmelo__cncs->record_index, FGGR__CONFIG__SDB_RECORDS_MAX);
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__index_file() returned %d", rc);
		return -20;
	}

	if(id > 0)
	{
      
		rc = utils__sdb__read_record_from_file(data, file_name.data, 1, carmelo__cncs->record_index[id - 1], language_iso_639_1_code, language_iso_639_1_code_len);
		//rc = utils__sdb__read_record_using_index (data, file_name.data, buffer, sizeof(buffer), carmelo__cncs->record_index[id - 1], SDB__EOR__TILDE, lang);
		if (rc != 0)
		{
			utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__read_record_from_file() returned %d", rc);
			return -30;
		}
	}
	else
	{
		rc = utils__sdb__read_record_from_file(data, file_name.data, 1, carmelo__cncs->record_index[id], language_iso_639_1_code, language_iso_639_1_code_len);
		if (rc != 0)
		{
			utils__printf__error(&fggr->pf, fn, -30, "utils__sdb__read_record_from_file() returned %d", rc);
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
		utils__printf__error(&fggr->pf, fn, -20, "memcmp() returned %d", rc);
		return -20;
	}


	return 0;
}




