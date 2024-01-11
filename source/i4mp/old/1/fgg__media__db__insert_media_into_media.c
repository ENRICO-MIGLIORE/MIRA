#include "fgg__media.h"


#if 0
int fgg__media__db__insert_media_into_media (size_t id, const fgg__buffer_t *value, size_t values_max)
{

	int rc;
	fgg__date_t date;
	fgg__time_t time;
	fgg__buffer_t file_name;
	fgg__buffer_t tmp_id_buffer;
	fgg__buffer_t name[FGG__CONFIG__DB_FIELDS_MAX];
	fgg__buffer_t local_value[FGG__CONFIG__DB_FIELDS_MAX];
	size_t i;
	size_t j;
	int tmp_id;

	values_max = values_max;

	/*
	* 1 - Get date and time
	*/
	rc = fgg__util__get_date(&date);
	rc |= fgg__util_get_time(&time);
	if (rc != 0)
	{
		return -10;
	}

	fgg__util__make_absolute_file_name (fgg__media->dir_path.data, "media",  file_name.data);

	rc = fgg__util_does_file_exist (file_name.data);
	if (rc != 0)
	{
		rc = fgg__util_create_empty_file (file_name.data);
		if (rc != 0)
		{
			return -20;
		}
	}

	fgg__media__fill_media_names (&name[0], 0);


	j = 0;

	/*
	* R-ID
	*/
	tmp_id = (int) id;
	tmp_id_buffer.len = sprintf (tmp_id_buffer.data, "%d", tmp_id);
	fgg__util__strcpy_buffer (&local_value[j], tmp_id_buffer.data);
	j++;

	/*
	* R-VERSION
	*/
	fgg__util__strcpy_buffer (&local_value[j], "1");
	j++;

	/*
	* R-ACTIVE
	*/
	fgg__util__strcpy_buffer (&local_value[j], "1");

	j++;

	/*
	* R-DATE
	*/
	fgg__util__strcpy_buffer (&local_value[j], date.iso_extended.data);
	j++;

	/*
	* R-TIME
	*/
	fgg__util__strcpy_buffer (&local_value[j], time.iso_extended.data);
	j++;

	/*
	* PK-ID
	*/
	fgg__util__strcpy_buffer (&local_value[j], tmp_id_buffer.data);

	j++;

	for (i = 0; i < (FGG__MEDIA__PAIRS_MAX_V1 - FGG__MEDIA__DEFAULT_VALUE_MAX); i++)
	{
		fgg__util__strcpy_buffer (&local_value[j], (char *) value[i].data);
	}

	rc = fgg__util__add_record (file_name.data, name, local_value, FGG__MEDIA__PAIRS_MAX_V1);
	if (rc != 0)
	{
		return -30;
	}			



	return 0;
}
#endif








