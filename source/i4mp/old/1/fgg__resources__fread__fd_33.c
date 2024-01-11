#include "fggr.h"
#include "fgg__jobs.h"
#include "fgg__resources.h"

/*
* This function returns the open jobs list of one year
*/

/*
* The reading of this resource is atomic.
*/
static char *fn = "fgg__resources__fread__fd_33()";


unsigned long fgg__resources__fread__fd_33 (void *buffer, unsigned long buffer_size)
{
#if 0
	unsigned long count;
	int rc;
	unsigned long i;
	int active;
	unsigned long pk_year;
	unsigned long len;
	char *p;
	unsigned long room;



	p = (char*)buffer;
	room = 0;
	len = 0;

	if (fgg__resources.data_3.pair_count != 1)
	{
		p[0] = '0';
		fgg__resources.config.resource[33].eof = 1;
		fgg__resources.last_error_fd = 33;
		fgg__resources.last_error = -10;	
		fgg__printf(FGGR__ERROR, fn, -10, "fgg__resources.data_3.pair_count != 1 - fgg__resources.data_3.pair_count %d", fgg__resources.data_3.pair_count);
		return 1;
	}

	rc = utils__libc__atoul (fgg__resources.data_3.value[0], fgg__resources.data_3.value_len[0], &pk_year);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[33].eof = 1;
		fgg__resources.last_error_fd = 33;
		fgg__resources.last_error = -20;	
		fgg__printf(FGGR__ERROR, fn, -20, "utils__libc__atoul() returned %d", rc);
		return 1;
	}



	rc = fgg__jobs__sdb__select_count_from_jobs(pk_year, &count);
	if (rc != 0)
	{
		p[0] = '0';
		fgg__resources.config.resource[33].eof = 1;
		fgg__resources.last_error_fd = 33;
		fgg__resources.last_error = -30;	
		fgg__printf(FGGR__ERROR, fn, -30, "fgg__jobs__db__select_count_from_jobs() returned %d - pk_year %d - count %d", rc, pk_year, count);
		return 1;
	}


	for (i = 0; i < count; i++)
	{
		rc = fgg__jobs__sdb__select_job_from_jobs (i + 1, pk_year, &fgg__resources.data, &active, 1, "&*", 2);
		if (rc != 0)
		{
			p[0] = '0';
			fgg__resources.config.resource[33].eof = 1;
			fgg__resources.last_error_fd = 33;
			fgg__resources.last_error = -40;	
			fgg__printf(FGGR__ERROR, fn, -40, "fgg__jobs__db__select_job_from_jobs() returned %d", rc);
			return 1;
		}


		if (fgg__resources.data.value[FGG__JOBS__JOB_STATUS__V1][0] == '0') //se e' aperta la aggiungo
		{
			room += fgg__resources.data.value_len[FGG__JOBS__PK_ID__V1] +
				fgg__resources.data.value_len[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1] +
				fgg__resources.data.value_len[FGG__JOBS__FK_FP__PK_ID__V1] + 10;

			if (room >= buffer_size)
			{
				p[0] = '0';
				fgg__resources.config.resource[33].eof = 1;
				fgg__resources.last_error_fd = 33;
				fgg__resources.last_error = -50;	
				fgg__printf(FGGR__ERROR, fn, -50, "room >= buffer_size, room = %d", room);
				return 1;
			}

			if (len > 0)
			{
				memcpy(p, "&", 1); //aggiungo la & solo per i successivi dopo il primo
				p += 1;
				len += 1;
			}

			memcpy (p, fgg__resources.data.value[FGG__JOBS__PK_ID__V1], fgg__resources.data.value_len[FGG__JOBS__PK_ID__V1]);
			p += fgg__resources.data.value_len[FGG__JOBS__PK_ID__V1];
			len += fgg__resources.data.value_len[FGG__JOBS__PK_ID__V1];

			memcpy (p, "***", 3);
			p += 3;
			len += 3;

			memcpy (p, fgg__resources.data.value[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1], fgg__resources.data.value_len[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1]);
			p += fgg__resources.data.value_len[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1];
			len += fgg__resources.data.value_len[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1];

			memcpy (p, "***", 3);
			p += 3;
			len += 3;

			memcpy (p, fgg__resources.data.value[FGG__JOBS__FK_FP__PK_ID__V1], fgg__resources.data.value_len[FGG__JOBS__FK_FP__PK_ID__V1]);
			p += fgg__resources.data.value_len[FGG__JOBS__FK_FP__PK_ID__V1];
			len += fgg__resources.data.value_len[FGG__JOBS__FK_FP__PK_ID__V1];

		}
	}



	fgg__resources.config.resource[33].eof = 1;
	fgg__resources.last_error_fd = 0;
	fgg__resources.last_error = 0;


	return len;

#endif

	return 0;
}
