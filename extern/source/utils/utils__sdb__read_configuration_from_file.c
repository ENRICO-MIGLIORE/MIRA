#include "utils__sdb.h"
 

int utils__sdb__read_configuration_from_file (void *p, utils__sdb_t* sdb, const char* file_name, utils__sdb__section_callback_t* section, utils__sdb__name_callback_t* names_values, size_t names_values_max, size_t start_record, size_t *record_number, int* end_of_file)
{

	int rc;
	size_t i;
	size_t j;
	size_t record_index;
	size_t file_offset;
	int done;
	size_t section_name_len;


	if (sdb == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -100");
		return -100;
	}

	if (sdb->configured != 1)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -200");
		return -200;
	}

	if (file_name == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -300");
		return -300;
	}

	if (section == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -400");
		return -400;
	}

	if (section->function == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -500");
		return -500;
	}

	if (section->name == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -600");
		return -600;
	}

	if (names_values == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -700");
		return -700;
	}
	
	if (names_values_max == 0)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -800");
		return -800;
	}

	if (end_of_file == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -900");
		return -900;
	}

	if (p == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -1000");
		return -1000;
	}

	
	for (i = 0; i < names_values_max; i++)
	{
		if (names_values[i].function == NULL)
		{
			printf("-1000 - utils__sdb__read_configuration_from_file() returned -1100");
			return -900;
		}

		if (names_values[i].name == NULL)
		{
			printf("-1000 - utils__sdb__read_configuration_from_file() returned -1200");
			return -1000;
		}
	}


	if (record_number == NULL)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -1300");
		return -1200;
	}


	section_name_len = strlen(section->name);

	if (section_name_len > UTILS__SDB__SECTION_NAME_SIZE)
	{
		printf("-1000 - utils__sdb__read_configuration_from_file() returned -1400");
		return -1300;
	}


	/*
	 * Loooking for [SECTION NAME]
	 */
	record_index = start_record;
	file_offset = 0;
	done = 0;
	do
	{
		
		rc = utils__sdb__read_record_from_file(sdb, file_name, record_index, file_offset, end_of_file);
		if (rc != 0)
		{
			done = -1;
		}
		else
		{
			/* utils__sdb__print_sdb(sdb); */
						
			if (section_name_len == sdb->section_name_len)
			{
				rc = memcmp(sdb->section_name, section->name, section_name_len);

				if (rc == 0)
				{
					done = 1;
				}
				else
				{
					record_index++;
				}
			}
			else
			{
				record_index++;
			}
		}
	} 
	while (done == 0);

	if (done != 1)
	{		
		return -1400;
	}


	/*
	 * Call section function
	 */	
	rc = section->function(p, section->name, section_name_len);
	if (rc != 0)
	{
		return -1500;
	}

	/*
	 * Parse all fields of the record
	 */
	for (i = 0; i < sdb->num_fields; i++)
	{
		for (j = 0; j < names_values_max; j++)
		{
			if (sdb->name_len[i] != strlen(names_values[j].name))
			{
				continue;
			}

			rc = memcmp(sdb->name[i], names_values[j].name, sdb->name_len[i]);
			if (rc != 0)
			{
				continue;
			}

			/*
			 * call the name-value function
			 */
			rc = names_values[j].function(p, sdb->value[i], sdb->value_len[i]);

			if (rc != 0)
			{
				return -1600;
			}
		}
	}


	*record_number = record_index;

	return 0;

}
