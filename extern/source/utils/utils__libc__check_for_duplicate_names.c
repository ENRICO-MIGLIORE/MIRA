#include "utils__libc.h"


int utils__libc__check_for_duplicate_names (const char **names, const size_t *names_len, size_t names_count)
{

	size_t start_j;
	int rc;
	size_t i;
	size_t j;

	if (names == NULL)
	{
		return -10;
	}

	if (names_len == NULL)
	{
		return -20;
	}

	if (names_count == 0)
	{
		return -30;
	}

	if (names_count > 1)
	{		
		/*
		 * All names must appear just once
		 */

		start_j = 1;

		for (i = 0; i < names_count; i++)
		{
			for (j = start_j; j < names_count; j++)
			{			
				if (names_len[i] ==  names_len[j])
				{
					if (names[i] == NULL)
					{
						return -40;
					}

					if (names[j] == NULL)
					{
						return -50;
					}

					rc = memcmp(names[i], names[j], names_len[i]);
					if (rc == 0)
					{
						return -60;
					}
				}
			}
			start_j++;
		}
	}

	return 0;
}


