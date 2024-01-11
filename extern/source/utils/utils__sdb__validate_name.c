#include "utils__sdb.h"


int utils__sdb__validate_name (const char *name, size_t name_len)
{
	size_t i;
	size_t blank_space_count;
	int valid;


	if (name == NULL)
	{
		return -10;
	}

	if (name_len == 0)
	{
		return -20;
	}


	blank_space_count = 0;

	for (i = 0; i < name_len; i++)
	{
		valid = ((name[i] >= 'A')  &  (name[i] <= 'Z')) |
			    ((name[i] >= 'a')  &  (name[i] <= 'z')) |
			    ((name[i] >= '0')  &  (name[i] <= '9')) |
			    ((name[i] == '-')  |  (name[i] == '_')  |  (name[i] == '.')  |  (name[i] == ':')  |  (name[i] == '\'')  |  (name[i] == ' '));

		if (valid == 0)
		{
			return -40;
		}

		if (name[i] == ' ')
		{
			blank_space_count++;
		}
	}

	/*
	 * A name can't be made of all white spaces
	 */
	if (blank_space_count == name_len)
	{
		return -50;
	}

	return 0;
}
