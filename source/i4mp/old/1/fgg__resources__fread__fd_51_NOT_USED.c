#include "fggr.h"
#include "fgg__resources.h"
#include "fgg__jo.h"

/*
* This function returns jobs list of one customer in one year
*/

/*
* The reading of this resource is atomic.
*/
static char *fn = "fgg__resources__fread__fd_51()";

//testata
unsigned long fgg__resources__fread__fd_51 (void *buffer, unsigned long buffer_size)
{
	int rc;
	unsigned long pk_year;
	unsigned long count;
	unsigned long i;
	int active;
	unsigned long customer;
	unsigned long customer_from_html;
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
	unsigned long lang;

	p = (char *) buffer;
	buffer_offset = 0;
	buffer_new_size = buffer_size;



	if (fgg__resources.data_3.pair_count != 3)
	{
		p[0] = '0';
		fgg__resources.config.resource[51].eof = 1;
		fgg__resources.last_error_fd = 51;
		fgg__resources.last_error = -10;	
		utils__printf(UTILS__ERROR, fn, -10, "fgg__resources.data_3.pair_count != 2 - fgg__resources.data_3.pair_count %d", fgg__resources.data_3.pair_count);
		return 1;
	}



	rc = utils__libc__atoul (fgg__resources.data_3.value[0], fgg__resources.data_3.value_len[0], &customer_from_html);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[51].eof = 1;
		fgg__resources.last_error_fd = 51;
		fgg__resources.last_error = -20;	
		utils__printf(UTILS__ERROR, fn, -20, "utils__libc__atoul() returned %d", rc);
		return 1;
	}


	rc = utils__libc__atoul (fgg__resources.data_3.value[1], fgg__resources.data_3.value_len[1], &pk_year);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[51].eof = 1;
		fgg__resources.last_error_fd = 51;
		fgg__resources.last_error = -30;	
		utils__printf(UTILS__ERROR, fn, -30, "utils__libc__atoul() returned %d", rc);
		return 1;
	}

	rc = utils__libc__atoul (fgg__resources.data_3.value[2], fgg__resources.data_3.value_len[2], &lang);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[51].eof = 1;
		fgg__resources.last_error_fd = 51;
		fgg__resources.last_error = -30;	
		utils__printf(UTILS__ERROR, fn, -30, "utils__libc__atoul() returned %d", rc);
		return 1;
	}


	rc = fgg__jo__sdb__select_count_from_jo  (pk_year, &count);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[51].eof = 1;
		fgg__resources.last_error_fd = 51;
		fgg__resources.last_error = -40;	
		utils__printf(UTILS__ERROR, fn, -40, "fgg__jo__db__select_count_from_commesse() returned %d - pk_year %d - count %d", rc, pk_year, count);
		return 1;
	}


	for (i = count; i > 0; i--)
	{
		rc = fgg__jo__sdb__select_jo_from_jo (i, pk_year, &fgg__resources.data, &active, 0, lang);
		if (rc != 0)
		{
			p[0] = '0';
			fgg__resources.config.resource[51].eof = 1;
			fgg__resources.last_error_fd = 51;
			fgg__resources.last_error = -50;	
			utils__printf(UTILS__ERROR, fn, -50, "fgg__jo__db__select_commessa_from_commesse() returned %d", rc);
			return 1;
		}

		rc = utils__libc__atoul (fgg__resources.data.value[FGG__JO__FIELD__PK_ID], fgg__resources.data.value_len[FGG__JO__FIELD__PK_ID], &customer);
		if (rc != 0)
		{
			p[0] = '0';
			fgg__resources.config.resource[51].eof = 1;
			fgg__resources.last_error_fd = 51;
			fgg__resources.last_error = -60;	
			utils__printf(UTILS__ERROR, fn, -60, "utils__libc__atoul() returned %d", rc);
			return 1;
		}

		if (customer == customer_from_html)
		{
			if (buffer_offset > 0)
			{			
				if (buffer_offset + 1 >= buffer_size)
				{
					p[0] = '0';
					fgg__resources.config.resource[51].eof = 1;
					fgg__resources.last_error_fd = 51;
					fgg__resources.last_error = -40;
					utils__printf(UTILS__ERROR, fn, -40, "buffer_offset + 1 >= buffer_size");
					return 1;
				}
				p[buffer_offset] = '*';
				buffer_offset++;
			}


			forbidden_charset = FGGR__BROWSER_FORBIDDEN_CHARSET_2;
			pair_count = 4;


			name = &fgg.javascript__field_names[0];
			name_len = &fgg.javascript__field_names_len[0];

			value[0] = fgg__resources.data.value[FGG__JO__FIELD__PK_ID];
			value[1] = fgg__resources.data.value[FGG__JO__FIELD__PK_YEAR];
			value[2] = fgg__resources.data.value[FGG__JO__FIELD__CUSTOMER_ORDER];
			value[3] = fgg__resources.data.value[FGG__JO__FIELD__CUSTOMER_ORDER_DATE];

			value_len[0] = fgg__resources.data.value_len[FGG__JO__FIELD__PK_ID];
			value_len[1] = fgg__resources.data.value_len[FGG__JO__FIELD__PK_YEAR];
			value_len[2] = fgg__resources.data.value_len[FGG__JO__FIELD__CUSTOMER_ORDER];
			value_len[3] = fgg__resources.data.value_len[FGG__JO__FIELD__CUSTOMER_ORDER_DATE];


			rc = utils__libc__build_url_buffer (&p[buffer_offset], buffer_new_size, &buffer_len, name, name_len, value, value_len, pair_count, (const char *) forbidden_charset);

			if (rc != 0)
			{
				p[0] = '0';
				fgg__resources.config.resource[51].eof = 1;
				fgg__resources.last_error_fd = 51;
				fgg__resources.last_error = -30;
				utils__printf(UTILS__ERROR, fn, -30, "utils__libc__build_url_buffer() returned %d", rc);
				return 1;
			}

			buffer_offset += buffer_len;
			buffer_new_size -= buffer_len;

		}
	}

	fgg__resources.config.resource[51].eof = 1;
	fgg__resources.last_error_fd = 0;
	fgg__resources.last_error = 0;


	return buffer_offset;

}
