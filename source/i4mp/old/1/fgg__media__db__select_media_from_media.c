#include "fgg__media.h"


#if 0
int fgg__media__db__select_media_from_media (size_t id, fgg__buffer_t *name, fgg__buffer_t *value, size_t pairs_max, size_t *pairs_read, int *active)
{
	int rc;
	fgg__buffer_t file_name;

	fgg__util__make_absolute_file_name (fgg__media->dir_path.data, "media", file_name.data);


	rc = fgg__util__get_record (file_name.data, id, name, value, pairs_max, pairs_read);
	if (rc != 0)
	{
		return -10;
	}


	rc = strcmp (name[2].data, "R-ACTIVE");
	if (rc == 0)
	{
		*active = 0;
		if (value[2].data[0] == '1')
		{
			*active = 1;
		}
	}


	return 0;
}



#endif