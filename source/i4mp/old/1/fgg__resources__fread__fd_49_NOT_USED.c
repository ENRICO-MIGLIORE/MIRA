#include "fggr.h"
#include "fgg__resources.h"
#include "fgg__jo.h"

/*
* This function returns the first number available for a new job
*/

/*
* The reading of this resource is atomic.
*/
static char *fn = "fgg__resources__fread__fd_48()";

//testata

unsigned long fgg__resources__fread__fd_49 (void *buffer, unsigned long buffer_size)
{
	int rc;
	unsigned long year;
	unsigned long pk_id;
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


	p = (char *) buffer;
	buffer_offset = 0;
	buffer_new_size = buffer_size;


	if (buffer_size <= 32)
	{
		p[0] = '0';
		fgg__resources.config.resource[49].eof = 1;
		fgg__resources.last_error_fd = 49;
		fgg__resources.last_error = -10;	
		utils__printf(UTILS__ERROR, fn, -10, "buffer_size <= 32 - buffer_size %d", buffer_size);
		return 1;
	}


	rc = fgg__jo__make_new_jo_id_and_year (&year, &pk_id);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[49].eof = 1;
		fgg__resources.last_error_fd = 49;
		fgg__resources.last_error = -20;	
		utils__printf(UTILS__ERROR, fn, -50, "fgg__jo__make_new_jo_id_and_year() returned %d - year %d - pk_id %d", rc, year, pk_id);
		return 1;
	}

	tmp_value_len = sprintf(tmp_value, "%d-%d", pk_id, year);


	forbidden_charset = FGGR__BROWSER_FORBIDDEN_CHARSET_2;
	pair_count = 1;

	name = &fgg.javascript__field_names[0];
	name_len = &fgg.javascript__field_names_len[0];


	value[0] = tmp_value;
	value_len[0] = tmp_value_len;

	rc = utils__libc__build_url_buffer (&p[buffer_offset], buffer_new_size, &buffer_len, name, name_len, value, value_len, pair_count, (const char *) forbidden_charset);

	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[32].eof = 1;
		fgg__resources.last_error_fd = 32;
		fgg__resources.last_error = -30;
		utils__printf(UTILS__ERROR, fn, -30, "utils__libc__build_url_buffer() returned %d", rc);
		return 1;
	}

	buffer_offset += buffer_len;
	buffer_new_size -= buffer_len;


	fgg__resources.config.resource[49].eof = 1;
	fgg__resources.last_error_fd = 0;
	fgg__resources.last_error = 0;


	return buffer_offset;
}
