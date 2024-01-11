#include "fgg__users.h"
#include "fgg__customers.h"
#include "fgg__fp.h"
#include "fgg__programs.h"
#include "fgg__rm.h"
#include "fgg__jobs.h"



int fgg__jobs__db__select_job_from_jobs_c_old (size_t pk_id, size_t year, fgg__buffer_t *name, fgg__buffer_t *value, size_t pairs_max, size_t *pairs_read, int *active, int present)
{
	int rc;
	size_t i;
	size_t j;
	size_t k;
	int end;
	size_t record_count;
	size_t record_version;
	fgg__buffer_t log_file_name;
	fgg__buffer_t file_name;
	fgg__buffer_t tmp_name[FGG__CONFIG__DB_FIELDS_MAX];
	fgg__buffer_t tmp_value[FGG__CONFIG__DB_FIELDS_MAX];
	size_t tmp_pairs_read;
	int tmp_active;
	fgg__buffer_t tmp_buf;
	size_t tmp_id;
	fgg__buffer_t tmp_log_name[FGG__CONFIG__DB_FIELDS_MAX];
	fgg__buffer_t tmp_log_value[FGG__CONFIG__DB_FIELDS_MAX];
	size_t tmp_log_pairs_read;
	size_t updated[FGG__CONFIG__DB_FIELDS_MAX];
	fgg__buffer_t *p_value;
	size_t versions[2];
	int tmp_int;


	if (pairs_max < fgg__jobs->fields_max)
	{
		return -10;
	}


	fgg__util__make_absolute_file_name_with_year (fgg__jobs->dir_path.data, "jobs", year, file_name.data);

	fgg__util__write_default_values (&value[0], pairs_max);

	/*
	* Read and overwrite the default values
	*/
	rc = fgg__util__get_record_c (file_name.data, pk_id, name, value, pairs_max, pairs_read);
	if (rc != 0)
	{
		return -11;
	}

	if (value[FGG__JOBS__R_ACTIVE].data[0] == '1')
	{
		*active = 1;
	}
	else
	{
		*active = 0; //devo tornare non devo espandere un bel nulla. torno gli stessi valori che ho letto da file
		return 0;
	}


	//versions[0] = FGG__JOBS__PAIRS_MAX_V1;
	//versions[1] = FGG__JOBS__PAIRS_MAX_V2;

	versions[0] = FGG__JOBS__PAIRS_MAX_V1;

	rc = fgg__util__check_record_integrity (name, fgg__jobs->field_names, *pairs_read, &value[1], &record_version, &versions[0], sizeof (versions) / sizeof (size_t), 1);
	if (rc != 0)
	{
		return -12;
	}


	/*
	* FK-USERS--PK-ID
	*/
	i = FGG__COMMON__RECORD__PRIVATE_FIELDS + 2;

	if (present == 1)
	{
		tmp_int = atoi(value[i].data);
		if (tmp_int >= 0)
		{
			tmp_id = (size_t) tmp_int;
		}
		else
		{
			return -20;
		}

		/*
		* The users' table doesn't have foreign keys
		*/ 
		rc = fgg__users__db__select_user_from_users_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active);
		if (rc != 0)
		{
			return -21;
		}

		rc = fgg__users__present_user (1, tmp_value, tmp_pairs_read, &tmp_buf);
		if (rc != 0)
		{
			//fgg__fpw_im->error = -21;
			//fgg__log__write (FGG__LOG__ERROR, "FGG", "%d - fgg__fpw_im__db__select_inventory_movement_from_rmw_im - %d", fgg__fpw_im->error, fgg__system.svn_version);
			return -22;
		}

		(void) fgg__util__strcpy_buffer (&value[i], tmp_buf.data);

	}
	i++;

	/*
	* FK-CUSTOMERS--PK-ID
	*/
	if (present == 1)
	{
		tmp_int = atoi(value[i].data);
		if (tmp_int >= 0)
		{
			tmp_id = (size_t) tmp_int;
		}
		else
		{
			return -30;
		}

		rc = fgg__customers__db__select_customer_from_customers_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active);
		if (rc != 0)
		{				
			return -31;
		}

		fgg__customers__present_customer (1, tmp_value, tmp_pairs_read, &tmp_buf);
		(void) fgg__util__strcpy_buffer (&value[i], tmp_buf.data);

	}

	i++;


	/*
	* FK-FP--PK-ID
	*/
	if (present == 1)
	{
		tmp_int = atoi(value[i].data);
		if (tmp_int >= 0)
		{
			tmp_id = (size_t) tmp_int;
		}
		else
		{
			return -40;
		}


		rc = fgg__fp__db__select_fp_from_fp_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active, 1);
		if (rc != 0)
		{				
			return -41;
		}

		rc = fgg__fp__present_fp (1, tmp_value, tmp_pairs_read, &tmp_buf);
		if (rc != 0)
		{				
			return -42;
		}
		(void) fgg__util__strcpy_buffer (&value[i], tmp_buf.data);
	}
	i++;

	/*
	* FK-RM--PK-ID
	*/
	if (present == 1)
	{
		tmp_int = atoi(value[i].data);
		if (tmp_int >= 0)
		{
			tmp_id = (size_t) tmp_int;
		}
		else
		{
			return -50;
		}


		rc = fgg__rm__db__select_rm_from_rm_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active);
		if (rc != 0)
		{				
			return -51;
		}

		fgg__rm__present_rm (1, tmp_value, tmp_pairs_read, &tmp_buf);
		(void) fgg__util__strcpy_buffer (&value[i], tmp_buf.data);
	}
	i++;

	/*
	* FK-MACHINE--PK-ID
	*/
	i++;


	/*
	* FK-PROGRAMS--PK-ID
	*/
	if (value[i].data[0] != '-')
	{
		if (present == 1)
		{
			tmp_int = atoi(value[i].data);
			if (tmp_int >= 0)
			{
				tmp_id = (size_t) tmp_int;
			}
			else
			{
				return -60;
			}


			rc = fgg__programs__select_program_from_programs_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active);
			if (rc != 0)
			{
				return -61;
			}

			fgg__programs__present_program (1, tmp_value, tmp_pairs_read, &tmp_buf);
			(void) fgg__util__strcpy_buffer (&value[i], tmp_buf.data);
		}
	}



	fgg__util__make_file_and_dir_log_names_with_year (fgg__jobs->dir_path.data, pk_id, year, "jobs", log_file_name.data);


	//rc = fgg__util__get_record_count (log_file_name.data, &record_count);
	rc = fgg__util__get_record_count_c(log_file_name.data, &record_count);
	if (rc != 0)
	{				
		return -70;
	}

	memset (updated, 0, sizeof(updated));


	/*
	* When reading the log file, we start from the last record up to the first
	*/
	for (i = record_count; i > 0; i--)
	{

		rc = fgg__util__get_record_c (log_file_name.data, i, tmp_log_name, tmp_log_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_log_pairs_read);
		if (rc != 0)
		{
			return -80;
		}

		rc = fgg__util__check_record_integrity (tmp_log_name, fgg__jobs->field_names, tmp_log_pairs_read, &tmp_log_value[1], &record_version, &versions[0], sizeof (versions) / sizeof (size_t), 0);
		if (rc != 0)
		{
			return -81;
		}

		for (j = FGG__COMMON__RECORD__PRIVATE_FIELDS; j < tmp_log_pairs_read; j++)
		{

			/*
			* skip: R-ID, R-VERSION, R-ACTIVE, R-DATE, R-TIME, PK-ID, PK-YEAR
			*/
			p_value = value + (FGG__COMMON__RECORD__PRIVATE_FIELDS + 2);

			/*
			* FK-USERS--PK-ID
			*/
			if (memcmp (tmp_log_name[j].data, fgg__jobs->field_names[FGG__JOBS__FK_USERS__PK_ID__V1].data, fgg__jobs->field_names[FGG__JOBS__FK_USERS__PK_ID__V1].len)== 0)
			{
				if (updated[FGG__JOBS__FK_USERS__PK_ID__V1] == 0)
				{
					if (present == 1)
					{
						tmp_int = atoi(tmp_log_value[j].data);
						if (tmp_int >= 0)
						{
							tmp_id = (size_t) tmp_int;
						}
						else
						{
							return -90;
						}

						rc = fgg__users__db__select_user_from_users_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active);
						if (rc != 0)
						{
							return -91;
						}

						rc = fgg__users__present_user (1, tmp_value, tmp_pairs_read, &tmp_buf);
						if (rc != 0)
						{
							//fgg__fpw_im->error = -21;
							//fgg__log__write (FGG__LOG__ERROR, "FGG", "%d - fgg__fpw_im__db__select_inventory_movement_from_rmw_im - %d", fgg__fpw_im->error, fgg__system.svn_version);
							return -92;
						}

						(void) fgg__util__strcpy_buffer (p_value, tmp_buf.data);

					}
					else
					{
						(void) fgg__util__strcpy_buffer (p_value, tmp_log_value[j].data);
					}

					updated[FGG__JOBS__FK_USERS__PK_ID__V1] = 1;
				}
				continue;
			}

			p_value++;

			/*
			* FK-CUSTOMERS--PK-ID
			*/
			if (memcmp (tmp_log_name[j].data, fgg__jobs->field_names[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1].data, fgg__jobs->field_names[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1].len)== 0)
			{
				if (updated[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1] == 0)
				{
					//tmp_log_value[j].data[tmp_log_value[j].len] = '\0';

					tmp_int = atoi(tmp_log_value[j].data);
					if (tmp_int >= 0)
					{
						tmp_id = (size_t) tmp_int;
					}
					else
					{
						return -100;
					}



					rc = fgg__customers__db__select_customer_from_customers_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active);
					if (rc != 0)
					{				
						return -101;
					}

					fgg__customers__present_customer (1, tmp_value, tmp_pairs_read, &tmp_buf);
					(void) fgg__util__strcpy_buffer (p_value, tmp_buf.data);
					updated[FGG__JOBS__FK_CUSTOMERS__PK_ID__V1] = 1;
				}
				continue;
			}

			p_value++;

			/*
			* FK-F--PK-ID
			*/
			if (memcmp (tmp_log_name[j].data, fgg__jobs->field_names[FGG__JOBS__FK_FP__PK_ID__V1].data, fgg__jobs->field_names[FGG__JOBS__FK_FP__PK_ID__V1].len) == 0)
			{
				if (updated[FGG__JOBS__FK_FP__PK_ID__V1] == 0)
				{
					//tmp_log_value[j].data[tmp_log_value[j].len] = '\0';

					tmp_int = atoi(tmp_log_value[j].data);
					if (tmp_int >= 0)
					{
						tmp_id = (size_t) tmp_int;
					}
					else
					{
						return -110;
					}


					rc = fgg__fp__db__select_fp_from_fp_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active, 1);
					if (rc != 0)
					{				
						return -111;
					}

					rc = fgg__fp__present_fp (1, tmp_value, tmp_pairs_read, &tmp_buf);
					if (rc != 0)
					{				
						return -112;
					}

					(void) fgg__util__strcpy_buffer (p_value, tmp_buf.data);
					updated[FGG__JOBS__FK_FP__PK_ID__V1] = 1;

				}
				continue;
			}

			p_value++;

			/*
			* FK-RM--PK-ID
			*/
			if (memcmp (tmp_log_name[j].data, fgg__jobs->field_names[FGG__JOBS__FK_RM__PK_ID__V1].data, fgg__jobs->field_names[FGG__JOBS__FK_RM__PK_ID__V1].len) == 0)
			{
				if (updated[FGG__JOBS__FK_RM__PK_ID__V1] == 0)
				{
					//tmp_log_value[j].data[tmp_log_value[j].len] = '\0';

					tmp_int = atoi(tmp_log_value[j].data);
					if (tmp_int >= 0)
					{
						tmp_id = (size_t) tmp_int;
					}
					else
					{
						return -120;
					}


					rc = fgg__rm__db__select_rm_from_rm_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active);
					if (rc != 0)
					{				
						return -121;
					}

					fgg__rm__present_rm (1, tmp_value, tmp_pairs_read, &tmp_buf);
					(void) fgg__util__strcpy_buffer (p_value, tmp_buf.data);
					updated[FGG__JOBS__FK_RM__PK_ID__V1] = 1;
				}
				continue;
			}


			p_value++;

			/*
			* FK-MACHINE--PK-ID
			*/
			p_value++;

			/*
			* FK-PROGRAMS--PK-ID
			*/
			if (memcmp (tmp_log_name[j].data, fgg__jobs->field_names[FGG__JOBS__FK_PROGRAMS__PK_ID__V1].data, fgg__jobs->field_names[FGG__JOBS__FK_PROGRAMS__PK_ID__V1].len) == 0)
			{
				if (updated[FGG__JOBS__FK_PROGRAMS__PK_ID__V1] == 0)
				{
					//tmp_log_value[j].data[tmp_log_value[j].len] = '\0';

					tmp_int = atoi(tmp_log_value[j].data);
					if (tmp_int >= 0)
					{
						tmp_id = (size_t) tmp_int;
					}
					else
					{
						return -140;
					}


					rc = fgg__programs__select_program_from_programs_c (tmp_id, tmp_name, tmp_value, FGG__CONFIG__DB_FIELDS_MAX, &tmp_pairs_read, &tmp_active);
					if (rc != 0)
					{
						return -141;
					}

					fgg__programs__present_program (1, tmp_value, tmp_pairs_read, &tmp_buf);
					(void) fgg__util__strcpy_buffer (p_value, tmp_buf.data);
					updated[FGG__JOBS__FK_PROGRAMS__PK_ID__V1] = 1;

				}
				continue;
			}

			p_value++;

			end = 0;

			for (k = FGG__JOBS__CONNECTION_STATUS__V1; (k < fgg__jobs->fields_max) && (end == 0); k++)
			{
				
				if (memcmp (tmp_log_name[j].data, fgg__jobs->field_names[k].data, fgg__jobs->field_names[k].len) == 0)
				{
					if (updated[k] == 0)
					{
						(void) fgg__util__strcpy_buffer (p_value, tmp_log_value[j].data);
						updated[k] = 1;
					}
					end = 1;
				}
		
				if (end == 0)
				{
					p_value++;
				}				
			}
		}
	}
	return 0;
}






