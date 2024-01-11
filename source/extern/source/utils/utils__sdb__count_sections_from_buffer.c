#include <stddef.h>
#include <string.h>


#include <utils__sdb.h>


int utils__sdb__count_sections_from_buffer (utils__sdb_t* sdb, const char* file_name, const char* section_name, size_t start_record, size_t* section_count, int* end_of_file)
{

	int rc;
	size_t record_index;
	size_t file_offset;
	int done;
	size_t section_name_len;
	size_t n;


	if (sdb == NULL)
	{
		return -100;
	}

	if (sdb->configured != 1)
	{
		return -200;
	}

	if (file_name == NULL)
	{
		return -300;
	}

	if (section_name == NULL)
	{
		return -400;
	}

	if (section_count == NULL)
	{
		return -500;
	}

	section_name_len = strlen(section_name);

	if (section_name_len > UTILS__SDB__SECTION_NAME_SIZE)
	{
		return -600;
	}

	if (end_of_file == NULL)
	{
		return -700;
	}

	/*
	 * Loooking for [SECTION NAME]
	 */
	record_index = start_record;
	file_offset = 0;
	done = 0;
	n = 0;
	do
	{

		rc = utils__sdb__read_record_from_file(sdb, file_name, record_index, file_offset, end_of_file);
		if (rc != 0)
		{
			if (*end_of_file == 0)
			{
				return -800;
			}

			done = 1;
		}
		else if (*end_of_file == 1)
		{
			if (section_name_len == sdb->section_name_len)
			{
				rc = memcmp(sdb->section_name, section_name, section_name_len);

				if (rc == 0)
				{
					n++;
				}
			}
			record_index++;

			done = 1;
		}
		else
		{
			/* utils__sdb__print_sdb(sdb); */

			if (section_name_len == sdb->section_name_len)
			{
				rc = memcmp(sdb->section_name, section_name, section_name_len);

				if (rc == 0)
				{
					n++;
				}
			}
			record_index++;
		}
	}
	while (done == 0);


	*section_count = n;

	return 0;

}
