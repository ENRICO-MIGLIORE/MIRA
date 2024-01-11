#include "fggr.h"
#include "fgg__po.h"
#include "fgg__resources.h"

/*
* This function returns the complete jobs (close e open) list of one year
*/

/*
* The reading of this resource is atomic.
*/
static char *fn = "fgg__resources__fread__fd_29()";

unsigned long fgg__resources__fread__fd_29 (void *buffer, unsigned long buffer_size)
{

	unsigned long count;
	int rc;
	unsigned long i;
	int active;
	unsigned long pk_year;
	double job_completion;
	unsigned long pieces_machined;
	unsigned long len;
	char *p;
	unsigned long buffer_len;
	unsigned long buffer_offset;
	unsigned long buffer_new_size;
	char **name;
	unsigned long *name_len;
	char *value[FGG__CONFIG__SDB_FIELDS_MAX];
	unsigned long value_len[FGG__CONFIG__SDB_FIELDS_MAX];
	unsigned long pair_count;
	char *forbidden_charset;
	char tmp_value[64];
	unsigned long tmp_value_len;
	char tmp_value_2[64];
	unsigned long tmp_value_len_2;
	unsigned long lang;


	p = (char *) buffer;
	buffer_offset = 0;
	buffer_new_size = buffer_size;

	if (fgg__resources.data_3.pair_count != 2)
	{
		p[0] = '0';
		fgg__resources.config.resource[29].eof = 1;
		fgg__resources.last_error_fd = 29;
		fgg__resources.last_error = -10;	
		utils__printf(UTILS__ERROR, fn, -10, "fgg__resources.data_3.pair_count != 1 - fgg__resources.data_3.pair_count %d", fgg__resources.data_3.pair_count);
		return 1;
	}


	rc = utils__libc__atoul (fgg__resources.data_3.value[0], fgg__resources.data_3.value_len[0], &pk_year);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[29].eof = 1;
		fgg__resources.last_error_fd = 29;
		fgg__resources.last_error = -20;	
		utils__printf(UTILS__ERROR, fn, -20, "utils__libc__atoul() returned %d", rc);
		return 1;
	}

	rc = utils__libc__atoul (fgg__resources.data_3.value[1], fgg__resources.data_3.value_len[1], &lang);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[29].eof = 1;
		fgg__resources.last_error_fd = 29;
		fgg__resources.last_error = -20;	
		utils__printf(UTILS__ERROR, fn, -20, "utils__libc__atoul() returned %d", rc);
		return 1;
	}



	rc = fgg__po__sdb__select_count_from_po (pk_year, &count);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[29].eof = 1;
		fgg__resources.last_error_fd = 29;
		fgg__resources.last_error = -30;	
		utils__printf(UTILS__ERROR, fn, -30, "fgg__po__db__select_count_from_jobs() returned %d - pk_year %d - count %d", rc, pk_year, count);
		return 1;
	}

		for (i = 0; i < count; i++)
		{
		rc = fgg__po__sdb__select_po_from_po (i + 1, pk_year, &fgg__resources.data, &active, 1, lang);
		if (rc != 0)
		{
			p[0] = '0';
			fgg__resources.config.resource[29].eof = 1;
			fgg__resources.last_error_fd = 29;
			fgg__resources.last_error = -40;	
			utils__printf(UTILS__ERROR, fn, -40, "fgg__po__db__select_job_from_jobs() returned %d", rc);
			return 1;
		}

		if (active == FGGR__RECORD_INACTIVE)
		{
			continue;
		}

		rc = fgg__po__sdb__select_po_completion_from_po(i + 1, pk_year, &job_completion, &pieces_machined, lang);
		if (rc != 0)
		{
			p[0] = '0';
			fgg__resources.config.resource[29].eof = 1;
			fgg__resources.last_error_fd = 29;
			fgg__resources.last_error = -50;	
			utils__printf(UTILS__ERROR, fn, -50, "fgg__po__db__select_job_completion_from_jobs() returned %d", rc);
			return 1;
		}

		forbidden_charset = FGGR__BROWSER_FORBIDDEN_CHARSET_2;
		pair_count = 7;

		name = &fgg.javascript__field_names[0];
		name_len = &fgg.javascript__field_names_len[0];

		tmp_value_len = sprintf(tmp_value, "%d", pieces_machined);
		tmp_value_len_2 = sprintf(tmp_value_2, "%.1f %%",job_completion);

		value[0] = fgg__resources.data.value[FGG__PO__FIELD__PK_ID];
		value[1] = fgg__resources.data.value[FGG__PO__FIELD__FK_FP__PK_ID];
		value[2] = fgg__resources.data.value[FGG__PO__FIELD__FK_CUSTOMERS__PK_ID];
		value[3] = fgg__resources.data.value[FGG__PO__FIELD__PARTS_TO_PRODUCE];
		value[4] = tmp_value;
		value[5] = tmp_value_2;
		value[6] = fgg__resources.data.value[FGG__PO__FIELD__INTERNAL_JOB_NUMBER];

		value_len[0] = fgg__resources.data.value_len[FGG__PO__FIELD__PK_ID];
		value_len[1] = fgg__resources.data.value_len[FGG__PO__FIELD__FK_FP__PK_ID];
		value_len[2] = fgg__resources.data.value_len[FGG__PO__FIELD__FK_CUSTOMERS__PK_ID];
		value_len[3] = fgg__resources.data.value_len[FGG__PO__FIELD__PARTS_TO_PRODUCE];
		value_len[4] = tmp_value_len;
		value_len[5] = tmp_value_len_2;
		value_len[6] = fgg__resources.data.value_len[FGG__PO__FIELD__INTERNAL_JOB_NUMBER];

		rc = utils__libc__build_url_buffer (&p[buffer_offset], buffer_new_size, &buffer_len, name, name_len, value, value_len, pair_count, (const char *) forbidden_charset);
		
		if (rc != 0)
		{
			p[0] = '0';
			fgg__resources.config.resource[29].eof = 1;
			fgg__resources.last_error_fd = 29;
			fgg__resources.last_error = -30;
			utils__printf(UTILS__ERROR, fn, -30, "utils__libc__build_url_buffer() returned %d", rc);
			return 1;
		}

		buffer_offset += buffer_len;
		buffer_new_size -= buffer_len;

		if ((i + 1) < count)
		{			
			if (buffer_offset + 1 >= buffer_size)
			{
				p[0] = '0';
				fgg__resources.config.resource[29].eof = 1;
				fgg__resources.last_error_fd = 29;
				fgg__resources.last_error = -40;
				utils__printf(UTILS__ERROR, fn, -40, "buffer_offset + 1 >= buffer_size");
				return 1;
			}
			p[buffer_offset] = '*';
			buffer_offset++;
		}

	}


	fgg__resources.config.resource[29].eof = 1;
	fgg__resources.last_error_fd = 0;
	fgg__resources.last_error = 0;


	return buffer_offset;

}
