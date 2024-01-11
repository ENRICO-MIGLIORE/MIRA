#include "fggr.h"
#include "fgg__rmw_ie.h"
#include "fgg__resources.h"

/*
* This function returns the specific weight of one rm           ===> get_specific_weight?22
*/

/*
* The reading of this resource is atomic.
*/
static char *fn = "fgg__resources__fread__fd_14()";


//INTESTABILE non e' piu' chiamata in js
unsigned long fgg__resources__fread__fd_14 (void *buffer, unsigned long buffer_size)
{

	int rc;
	double weight;
	unsigned long pk_id;
	unsigned long number;
	unsigned long date_year;
	unsigned long date_month;
	unsigned long date_day;
	char *p;
	unsigned long len;
	unsigned long lang;

	p = (char *) buffer;
	len = 0;


	if (fgg__resources.data_3.pair_count != 2)
	{
		p[0] = '0';
		fgg__resources.config.resource[14].eof = 1;
		fgg__resources.last_error_fd = 14;
		fgg__resources.last_error = -10;	
		return 1;
	}


	/*
	 * double numbers when printed on a buffer span at most 16 or 17 bytes
	 */
	if (buffer_size <= 32)
	{
		p[0] = '0';
		fgg__resources.config.resource[14].eof = 1;
		fgg__resources.last_error_fd = 14;
		fgg__resources.last_error = -20;	
		return 1;
	}

	rc = utils__time__get_integer_date (&number, &date_year, &date_month, &date_day);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[14].eof = 1;
		fgg__resources.last_error_fd = 14;
		fgg__resources.last_error = -30;	
		return 1;
	}


	rc = utils__libc__atoul (fgg__resources.data_3.value[0], fgg__resources.data_3.value_len[0], &pk_id);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[14].eof = 1;
		fgg__resources.last_error_fd = 14;
		fgg__resources.last_error = -40;	
		return 1;
	}


	rc = utils__libc__atoul (fgg__resources.data_3.value[1], fgg__resources.data_3.value_len[1], &lang);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[14].eof = 1;
		fgg__resources.last_error_fd = 14;
		fgg__resources.last_error = -40;	
		return 1;
	}

	rc = fgg__rmw_ie__procedure_2__calculate_inventory (pk_id, date_year, &weight, lang);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[14].eof = 1;
		fgg__resources.last_error_fd = 14;
		fgg__resources.last_error = -50;	
		return 1;
	}


	len = (unsigned long) sprintf(p, "%.2f", weight);


	fgg__resources.config.resource[14].eof = 1;
	fgg__resources.last_error_fd = 0;
	fgg__resources.last_error = 0;


	return len;
}
