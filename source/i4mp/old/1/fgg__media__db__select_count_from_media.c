#include "fgg__media.h"

/*
* if option = 1, the INACTIVE jobs will be counted as ACTIVE
*/


#if 0
int fgg__media__db__select_count_from_media (size_t *count)
{		

	int rc;
	fgg__buffer_t file_name;


	fgg__util__make_absolute_file_name (fgg__media->dir_path.data, "media", file_name.data);


	rc = fgg__util__get_record_count (file_name.data, count);
	if (rc != 0)
	{
		return -10;
	}

	return 0;
}

#endif
