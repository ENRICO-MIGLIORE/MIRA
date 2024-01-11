#include "fggr.h"
#include "fgg__po.h"
#include "fgg__resources.h"

/*
* This function returns the report of a odp request in the past
*/

/*
* The reading of this resource is atomic.
*/
static char *fn = "fgg__resources__fread__fd_46()";

//testata
unsigned long fgg__resources__fread__fd_46 (void *buffer, unsigned long buffer_size)
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

	if (&fgg__resources.data == NULL)
	{
		memcpy ((char *) buffer, "0", 1);

		fgg__resources.config.resource[46].eof = 1;
		fgg__resources.last_error_fd = 46;
		fgg__resources.last_error = -10;	
		utils__printf(UTILS__ERROR, fn, -10, "fgg__resources.data == NULL");
		return 1;
	}

	if (fgg__resources.data.pair_count != 2)
	{

		memcpy ((char *) buffer, "0", 1);

		fgg__resources.config.resource[46].eof = 1;
		fgg__resources.last_error_fd = 46;
		fgg__resources.last_error = -10;	
		utils__printf(UTILS__ERROR, fn, -10, "fgg__resources.data == NULL");
		return 1;
	}

	//1 - 2020
	p_2_len = fgg__resources.data.value_len[0];
	p = fgg__resources.data.value[0];
	p_2 = utils__libc__strnchr (fgg__resources.data.value[0], fgg__resources.data.value_len[0], '-');

	if (p_2 == NULL)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[46].eof = 1;
		fgg__resources.last_error_fd = 46;
		fgg__resources.last_error = -20;	
		utils__printf(UTILS__ERROR, fn, -20, "utils__libc__strnchr() returned NULL");
		return 1;
	}
	fgg__resources.data.value_len[0] = p_2 - p;

	rc = utils__libc__atoul(fgg__resources.data.value[0], fgg__resources.data.value_len[0], &pk_id);
	if (rc != 0)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[46].eof = 1;
		fgg__resources.last_error_fd = 46;
		fgg__resources.last_error = -30;	
		utils__printf(UTILS__ERROR, fn, -30, "utils__libc__atoul() returned %d", rc);
		return 1;
	}

	p_2++;
	p_2_len = p_2_len - fgg__resources.data.value_len[0] - 1;

	rc = utils__libc__atoul(p_2, p_2_len, &pk_year);
	if (rc != 0)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[46].eof = 1;
		fgg__resources.last_error_fd = 46;
		fgg__resources.last_error = -40;	
		utils__printf(UTILS__ERROR, fn, -40, "utils__libc__atoul() returned %d", rc);
		return 1;
	}

	rc = utils__libc__atoul(fgg__resources.data.value[1], fgg__resources.data.value_len[1], &lang);
	if (rc != 0)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[46].eof = 1;
		fgg__resources.last_error_fd = 46;
		fgg__resources.last_error = -30;	
		utils__printf(UTILS__ERROR, fn, -30, "utils__libc__atoul() returned %d", rc);
		return 1;
	}

	rc = fgg__po__sdb__select_po_from_po (pk_id, pk_year, &fgg__resources.data, &active, 1, lang);
	if (rc != 0)
	{
		memcpy ((char *) buffer, "0", 1);
		fgg__resources.config.resource[46].eof = 1;
		fgg__resources.last_error_fd = 46;
		fgg__resources.last_error = -50;	
		utils__printf(UTILS__ERROR, fn, -40, "fgg__po__db__select_job_from_jobs() returned %d - pk_id %d - pk_year %d", rc,pk_id, pk_year);
		return 1;
	}

	if (active == FGGR__RECORD_INACTIVE)
	{
		//lo invio lo stesso anche se inactive;
	}

	p = (char *) buffer;
	
	forbidden_charset = FGGR__BROWSER_FORBIDDEN_CHARSET_2;
	pair_count = 29;

	name = &fgg.javascript__field_names[0];
	name_len = &fgg.javascript__field_names_len[0];


	value[0] = fgg__resources.data.value[FGG__PO__FIELD__PK_ID];
	value[1] = fgg__resources.data.value[FGG__PO__FIELD__PK_YEAR];
	value[2] = fgg__resources.data.value[FGG__PO__FIELD__FK_CUSTOMERS__PK_ID];
	value[3] = fgg__resources.data.value[FGG__PO__FIELD__FK_FP__PK_ID];
	value[4] = fgg__resources.data.value[FGG__PO__FIELD__FK_RM__PK_ID];
	value[5] = fgg__resources.data.value[FGG__PO__FIELD__FK_MACHINE__PK_ID];
	value[6] = fgg__resources.data.value[FGG__PO__FIELD__FK_PROGRAMS__PK_ID];
	value[7] = fgg__resources.data.value[FGG__PO__FIELD__JOB_STATUS];
	value[8] = fgg__resources.data.value[FGG__PO__FIELD__CONNECTION_STATUS];
	value[9] = fgg__resources.data.value[FGG__PO__FIELD__PARTS_TO_PRODUCE];
	value[10] = fgg__resources.data.value[FGG__PO__FIELD__CYCLE_TIME];
	value[11] = fgg__resources.data.value[FGG__PO__FIELD__PART_LENGTH];
	value[12] = fgg__resources.data.value[FGG__PO__FIELD__RAW_PART_LENGTH];
	value[13] = fgg__resources.data.value[FGG__PO__FIELD__EXCERPT_LENGTH];
	value[14] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_1_BRAND];
	value[15] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_2_BRAND];
	value[16] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_3_BRAND];
	value[17] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_4_BRAND];
	value[18] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_5_BRAND];
	value[19] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_6_BRAND];
	value[20] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_7_BRAND];
	value[21] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_8_BRAND];
	value[22] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_9_BRAND];
	value[23] = fgg__resources.data.value[FGG__PO__FIELD__TOOL_10_BRAND];
	value[24] = fgg__resources.data.value[FGG__PO__FIELD__NOTE];
	value[25] = fgg__resources.data.value[FGG__PO__FIELD__CYCLE_TIME_READ_IN_MACHINE];
	value[26] = fgg__resources.data.value[FGG__PO__FIELD__INTERNAL_JOB_NUMBER];
	value[27] = fgg__resources.data.value[FGG__PO__FIELD__CUSTOMER_ORDER];
	value[28] = fgg__resources.data.value[FGG__PO__FIELD__CUSTOMER_JOB];
	value[29] = fgg__resources.data.value[FGG__PO__FIELD__CUSTOMER_ORDER_DATE];
	value[30] = fgg__resources.data.value[FGG__PO__FIELD__FK_RMW__PK_ID];


	value_len[0] = fgg__resources.data.value_len[FGG__PO__FIELD__PK_ID];
	value_len[1] = fgg__resources.data.value_len[FGG__PO__FIELD__PK_YEAR];
	value_len[2] = fgg__resources.data.value_len[FGG__PO__FIELD__FK_CUSTOMERS__PK_ID];
	value_len[3] = fgg__resources.data.value_len[FGG__PO__FIELD__FK_FP__PK_ID];
	value_len[4] = fgg__resources.data.value_len[FGG__PO__FIELD__FK_RM__PK_ID];
	value_len[5] = fgg__resources.data.value_len[FGG__PO__FIELD__FK_MACHINE__PK_ID];
	value_len[6] = fgg__resources.data.value_len[FGG__PO__FIELD__FK_PROGRAMS__PK_ID];
	value_len[7] = fgg__resources.data.value_len[FGG__PO__FIELD__JOB_STATUS];
	value_len[8] = fgg__resources.data.value_len[FGG__PO__FIELD__CONNECTION_STATUS];
	value_len[9] = fgg__resources.data.value_len[FGG__PO__FIELD__PARTS_TO_PRODUCE];
	value_len[10] = fgg__resources.data.value_len[FGG__PO__FIELD__CYCLE_TIME];
	value_len[11] = fgg__resources.data.value_len[FGG__PO__FIELD__PART_LENGTH];
	value_len[12] = fgg__resources.data.value_len[FGG__PO__FIELD__RAW_PART_LENGTH];
	value_len[13] = fgg__resources.data.value_len[FGG__PO__FIELD__EXCERPT_LENGTH];
	value_len[14] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_1_BRAND];
	value_len[15] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_2_BRAND];
	value_len[16] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_3_BRAND];
	value_len[17] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_4_BRAND];
	value_len[18] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_5_BRAND];
	value_len[19] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_6_BRAND];
	value_len[20] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_7_BRAND];
	value_len[21] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_8_BRAND];
	value_len[22] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_9_BRAND];
	value_len[23] = fgg__resources.data.value_len[FGG__PO__FIELD__TOOL_10_BRAND];
	value_len[24] = fgg__resources.data.value_len[FGG__PO__FIELD__NOTE];
	value_len[25] = fgg__resources.data.value_len[FGG__PO__FIELD__CYCLE_TIME_READ_IN_MACHINE];
	value_len[26] = fgg__resources.data.value_len[FGG__PO__FIELD__INTERNAL_JOB_NUMBER];
	value_len[27] = fgg__resources.data.value_len[FGG__PO__FIELD__CUSTOMER_ORDER];
	value_len[28] = fgg__resources.data.value_len[FGG__PO__FIELD__CUSTOMER_JOB];
	value_len[29] = fgg__resources.data.value_len[FGG__PO__FIELD__CUSTOMER_ORDER_DATE];
	value_len[30] = fgg__resources.data.value_len[FGG__PO__FIELD__FK_RMW__PK_ID];

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

	fgg__resources.config.resource[46].eof = 1;
	fgg__resources.last_error_fd = 0;
	fgg__resources.last_error = 0;


	return buffer_offset;


}
