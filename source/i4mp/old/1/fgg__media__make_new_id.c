#include "fgg__media.h"
#if 0

int fgg__media__make_new_part_id (size_t *pk_id)
{

	int rc;
	size_t record_count;	
	fgg__buffer_t file_name;
	fgg__date_t date;


	rc = fgg__util__get_date (&date);
	if (rc != 0)
	{
		return -10;
	}


	fgg__util__make_absolute_file_name_with_year (fgg__media->dir_path.data, "media", date.year_integer, file_name.data);


	rc = fgg__util__get_record_count (file_name.data, &record_count);
	if (rc == -20)
	{
		*pk_id = 1;
		return 0;
	}
	else if (rc != 0)
	{
		return -13;
	}

	*pk_id = record_count + 1;

	return 0;
}


#endif
