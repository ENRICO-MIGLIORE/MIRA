#include "utils__sdb.h"


int utils__sdb__compare_two_sdbs (const utils__sdb_t *sdb_1, const utils__sdb_t *sdb_2, int mode)
{
	int rc;
	size_t i;
	
	
	/*
	 * Sanity check
	 */
	if (sdb_1 == NULL)
	{
		return -10;
	}

	if (sdb_2 == NULL)
	{
		return -20;
	}

	if (sdb_1->configured != 1)
	{
		return -30;
	}

	if (sdb_2->configured != 1)
	{
		return -40;
	}

	if (sdb_1->num_fields != sdb_2->num_fields)
	{
		return -50;
	}

	if (sdb_1->buffer_len != sdb_2->buffer_len)
	{
		return -60;
	}

	rc = memcmp(sdb_1->buffer, sdb_2->buffer, sdb_1->buffer_len);
	if (rc != 0)
	{
		return -70;
	}


	if (mode == 1)
	{
	
		if (sdb_1->section_name_len != sdb_2->section_name_len)
		{
			return -80;
		}

		if (sdb_1->section_name_len > 0)
		{
			rc = memcmp(sdb_1->section_name, sdb_2->section_name, sdb_1->section_name_len);
			if (rc != 0)
			{
				return -90;
			}
		}
	}

	for (i = 0; i < sdb_1->num_fields; i++)
	{
		if (sdb_1->name_len[i] != sdb_2->name_len[i])
		{
			return -200;
		}

		if (sdb_1->value_len[i] != sdb_2->value_len[i])
		{
			return -210;
		}

		rc = memcmp(sdb_1->name[i], sdb_2->name[i], sdb_2->name_len[i]);
	    if (rc != 0)
	    {
			return -220;
	    }

		rc = memcmp(sdb_1->value[i], sdb_2->value[i], sdb_2->value_len[i]);
	    if (rc != 0)
	    {
			return -230;
	    }

		if (sdb_1->encoding[i] != sdb_2->encoding[i])
		{
			return -240;
		}

		//code_offset = i << 1;

		//if ((sdb_1->value_len[i] != 0) && (sdb_1->encoding[i] == UTILS__SDB__ENCODING__UTF_8))
		//{
		//	if ((sdb_1->language_iso_639_1_buffer[code_offset] != sdb_2->language_iso_639_1_buffer[code_offset]) ||
		//		(sdb_1->language_iso_639_1_buffer[code_offset + 1] != sdb_2->language_iso_639_1_buffer[code_offset + 1]))
		//	{
		//		return -250;
		//	}
		//}
		

	}

	return 0;

}
