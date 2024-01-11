#include "fgg__rmw.h"


int fgg__rmw__get_warehouse_count (size_t *count)
{
	int rc;
	size_t record_count;
	fgg__buffer_t file_name;
	

	fgg__util__make_absolute_file_name (fgg__rmw->dir_path.data, "rmw", file_name.data);
	
	rc = fgg__util__get_record_count (file_name.data, &record_count);
	if (rc < 0)
	{
		return -10;
	}

	*count = record_count;


	return 0;
}


