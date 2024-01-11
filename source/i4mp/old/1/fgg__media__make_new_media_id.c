#include "fgg__media.h"



#if 0
int fgg__media__make_new_media_id (size_t *pk_id)
{

	int rc;
	size_t record_count;	
	fgg__buffer_t file_name;

	fgg__util__make_absolute_file_name (fgg__media->dir_path.data, "media", file_name.data);

	rc = fgg__util_does_file_exist (file_name.data);
	if (rc != 0)
	{
		*pk_id = 1;
		return 0;
	}

	rc = fgg__util__get_record_count (file_name.data, &record_count);

	if (rc == 0)
	{
		*pk_id = record_count + 1;
		return 0;
	}

	return -10;

}
#endif