#include "fggr.h"
#include "fgg__resources.h"
#include "fgg__jo.h"

/*
* This function returns all raws of one job
*/

/*
* The reading of this resource is atomic.
*/
static char *fn = "fgg__resources__fread__fd_53()";

//testata
unsigned long fgg__resources__fread__fd_53 (void *buffer, unsigned long buffer_size)
{
	int rc;
	int active;
	unsigned long pk_year;
	unsigned long pk_id;
	char *p;
	char *p_2;
	unsigned long p_2_len;
	char **name;
	unsigned long *name_len;
	char *value[FGG__CONFIG__SDB_FIELDS_MAX];
	unsigned long value_len[FGG__CONFIG__SDB_FIELDS_MAX];
	unsigned long pair_count;
	char *forbidden_charset;
	unsigned long buffer_len;
	unsigned long buffer_offset;
	unsigned long buffer_new_size;
	unsigned long lang;


	buffer_offset = 0;
	buffer_new_size = buffer_size;


	if (fgg__resources.data_3.pair_count != 2)
	{
		p[0] = '0';
		fgg__resources.config.resource[53].eof = 1;
		fgg__resources.last_error_fd = 53;
		fgg__resources.last_error = -10;	
		utils__printf(UTILS__ERROR, fn, -10, "fgg__resources.data_3.pair_count != 1 - fgg__resources.data_3.pair_count %d", fgg__resources.data_3.pair_count);
		return 1;
	}


	p_2_len = fgg__resources.data_3.value_len[0];
	p = fgg__resources.data_3.value[0];
	p_2 = utils__libc__strnchr (fgg__resources.data_3.value[0], fgg__resources.data_3.value_len[0], '-');

	if (p_2 == NULL)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[48].eof = 1;
		fgg__resources.last_error_fd = 48;
		fgg__resources.last_error = -20;	
		utils__printf(UTILS__ERROR, fn, -20, "utils__libc__strnchr() returned NULL");
		return 1;
	}
	fgg__resources.data_3.value_len[0] = p_2 - p; 

	rc = utils__libc__atoul(fgg__resources.data_3.value[0], fgg__resources.data_3.value_len[0], &pk_id);
	if (rc != 0)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[48].eof = 1;
		fgg__resources.last_error_fd = 48;
		fgg__resources.last_error = -30;	
		utils__printf(UTILS__ERROR, fn, -30, "utils__libc__atoul() returned %d", rc);
		return 1;
	}

	p_2++;


	p_2_len = p_2_len - fgg__resources.data_3.value_len[0] - 1;
	rc = utils__libc__atoul(p_2, p_2_len, &pk_year);
	if (rc != 0)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[48].eof = 1;
		fgg__resources.last_error_fd = 48;
		fgg__resources.last_error = -40;	
		utils__printf(UTILS__ERROR, fn, -40, "utils__libc__atoul() returned %d", rc);
		return 1;
	}

	p = (char *) buffer;

	rc = utils__libc__atoul(fgg__resources.data_3.value[1], fgg__resources.data_3.value_len[1], &lang);
	if (rc != 0)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[48].eof = 1;
		fgg__resources.last_error_fd = 48;
		fgg__resources.last_error = -30;	
		utils__printf(UTILS__ERROR, fn, -30, "utils__libc__atoul() returned %d", rc);
		return 1;
	}


	rc = fgg__jo__sdb__select_jo_from_jo (pk_id, pk_year, &fgg__resources.data, &active, 1, lang);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[53].eof = 1;
		fgg__resources.last_error_fd = 53;
		fgg__resources.last_error = -50;	
		utils__printf(UTILS__ERROR, fn, -50, "fgg__jo__db__select_commessa_from_commesse() returned %d - pk_id %d - pk_year %d", rc, pk_id, pk_year);
		return 1;
	}

	if (active == FGGR__RECORD_INACTIVE)
	{
		//lo invio lo stesso anche se inactive;
	}

	forbidden_charset = FGGR__BROWSER_FORBIDDEN_CHARSET_2;
	pair_count = 16;

	name = &fgg.javascript__field_names[0];
	name_len = &fgg.javascript__field_names_len[0];
/*	value[0] = fgg__resources.data.value[FGG__JO__FIELD__ROW_1];
	value[1] = fgg__resources.data.value[FGG__JO__FIELD__ROW_2];
	value[2] = fgg__resources.data.value[FGG__JO__FIELD__ROW_3];
	value[3] = fgg__resources.data.value[FGG__JO__FIELD__ROW_4];
	value[4] = fgg__resources.data.value[FGG__JO__FIELD__ROW_5];
	value[5] = fgg__resources.data.value[FGG__JO__FIELD__ROW_6];
	value[6] = fgg__resources.data.value[FGG__JO__FIELD__ROW_7];
	value[7] = fgg__resources.data.value[FGG__JO__FIELD__ROW_8];
	value[8] = fgg__resources.data.value[FGG__JO__FIELD__ROW_9];
	value[9] = fgg__resources.data.value[FGG__JO__FIELD__ROW_10];
	value[10] = fgg__resources.data.value[FGG__JO__FIELD__ROW_11];
	value[11] = fgg__resources.data.value[FGG__JO__FIELD__ROW_12];
	value[12] = fgg__resources.data.value[FGG__JO__FIELD__ROW_13];
	value[13] = fgg__resources.data.value[FGG__JO__FIELD__ROW_14];
	value[14] = fgg__resources.data.value[FGG__JO__FIELD__ROW_15];
	value[15] = fgg__resources.data.value[FGG__JO__FIELD__ROW_16];

	value_len[0] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_1];
	value_len[1] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_2];
	value_len[2] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_3];
	value_len[3] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_4];
	value_len[4] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_5];
	value_len[5] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_6];
	value_len[6] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_7];
	value_len[7] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_8];
	value_len[8] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_9];
	value_len[9] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_10];
	value_len[10] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_11];
	value_len[11] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_12];
	value_len[12] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_13];
	value_len[13] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_14];
	value_len[14] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_15];
	value_len[15] = fgg__resources.data.value_len[FGG__JO__FIELD__ROW_16];
	*/
	rc = utils__libc__build_url_buffer (&p[buffer_offset], buffer_new_size, &buffer_len, name, name_len, value, value_len, pair_count, (const char *) forbidden_charset);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[35].eof = 1;
		fgg__resources.last_error_fd = 35;
		fgg__resources.last_error = -30;
		utils__printf(UTILS__ERROR, fn, -30, "utils__libc__build_url_buffer() returned %d", rc);
		return 1;
	}

	buffer_offset += buffer_len;
	buffer_new_size -= buffer_len;


	fgg__resources.config.resource[53].eof = 1;
	fgg__resources.last_error_fd = 0;
	fgg__resources.last_error = 0;


	return buffer_offset;

}
