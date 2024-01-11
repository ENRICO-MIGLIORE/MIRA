#include "utils__sdb.h"


int utils__sdb__search_index_by_name (utils__sdb_t *sdb, const char *name, size_t name_len, size_t *index)
{
	size_t i;
	int rc;
	int exit;

	if (sdb == NULL)
	{
		return -10;
	}

	if (sdb->configured != 1)
	{
		return -20;
	}

	if (name == NULL)
	{
		return -30;
	}

	if (index == NULL)
	{
		return -40;
	}


	exit = 0;
	*index = 0;

	for (i = 0; (i < sdb->num_fields) && (exit == 0); i++)
	{
		if (sdb->name_len[i] == name_len)
		{
			rc = memcmp(sdb->name[i], name, sdb->name_len[i]);
			if (rc == 0)
			{
				*index = i;
				exit = 1;
			}
		}
	}

	if (exit == 0)
	{
		return -100;
	}

	return 0;
}
