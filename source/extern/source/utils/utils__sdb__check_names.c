#include "utils__sdb.h"


/*
 *
 *     sdb         names      names        names     names           names          names      names         names
 *
 *   "NAME_1"     "NAME_1"    "NAME_2"    "NAME_1"   "NAME_2"        "NAME_1"      "NAME_1"    "NAME_3"      "NAME_2"
 *   "NAME_2"     "NAME_2"    "NAME_4"    "NAME_2"   "NAME_1"    	 "NAME_2"	   "NAME_2"	   "NAME_4"	   	 "NAME_5"
 *   "NAME_3"     "NAME_3"    "NAME_1"								 "NAME_2"	   "NAME_5"	   "NAME_1"
 *   "NAME_4"     "NAME_4"    "NAME_3"                               "NAME_4"	   "NAME_3"	   "NAME_4"
 *                                                                   "NAME_5"	   "NAME_4"	   "NAME_2"
 *
 *
 *                return 0     return 1   return 2    return 3       return 4      return 5	  return 6     	return -80
 */


int utils__sdb__check_names (const utils__sdb_t *sdb, const char **names, const size_t *names_len, size_t names_count, size_t *names_index)
{
	int rc;
	int flag;
	size_t i;
	size_t j;
	size_t start_j;
	size_t valid_out_of_sequence;
	size_t valid_in_sequence;


	if (sdb == NULL)
	{
		return -10;
	}

	if (sdb->configured != 1)
	{
		return -20;
	}

	if (sdb->num_fields == 0)
	{
		return -30;
	}

	if (names == NULL)
	{
		return -40;
	}

	if (names_len == NULL)
	{
		return -50;
	}

	if (names_count == 0)
	{
		return -60;
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
					rc = memcmp(names[i], names[j], names_len[i]);
					if (rc == 0)
					{
						return -70;
					}
				}
			}
			start_j++;
		}
	}


	valid_out_of_sequence = 0;
	valid_in_sequence = 0;

	for (i = 0; i < names_count; i++)
	{
		flag = 0;

		for (j = 0; (j < sdb->num_fields) && (flag == 0); j++)
		{
			if (sdb->name_len[j] == names_len[i])
			{
				rc = memcmp(sdb->name[j], names[i], names_len[i]);
				if (rc == 0)
				{
					if (i == j)
					{
						valid_in_sequence++;
					}
					else
					{
						valid_out_of_sequence++;
					}

					names_index[i] = j;
					flag = 1;
				}
			}
		}
	}


	if (names_count == sdb->num_fields)
	{
		if (valid_in_sequence == names_count)
		{
			return 0;
		}
		else if (valid_out_of_sequence + valid_in_sequence == sdb->num_fields)
		{
			return 1;
		}
	}
	else if (names_count < sdb->num_fields)
	{
		if (valid_in_sequence == names_count)
		{
			return 2;
		}
		else if ((valid_out_of_sequence + valid_in_sequence) == names_count)
		{
			return 3;
		}
	}
	else
	{
		if (valid_in_sequence == sdb->num_fields)
		{
			return 4;
		}
		else if ((valid_out_of_sequence + valid_in_sequence) == sdb->num_fields)
		{
			return 5;
		}

	}

	return -80;


}



