#include "utils__sdb.h"


int utils__sdb__append_sdb (utils__sdb_t *sdb_1, const utils__sdb_t *sdb_2)
{

	size_t i;
	size_t offset;


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

	if (sdb_2->num_fields == 0)
	{
		return -50;
	}

	if ((sdb_1->buffer_len + sdb_2->buffer_len) > sdb_1->buffer_size)
	{
		return -60;
	}

	if ((sdb_1->num_fields + sdb_2->num_fields) > sdb_1->fields_max)
	{
		return -70;
	}
	
	

	/*
	 * Copy buffer
	 */
	memcpy(&sdb_1->buffer[sdb_1->buffer_len], &sdb_2->buffer[0], sdb_2->buffer_len);




	/*
	 * Copy fields
	 */
	offset = sdb_1->buffer_len;

	for (i = 0; i < sdb_2->num_fields; i++)
	{
		
		sdb_1->name[sdb_1->num_fields] = &sdb_1->buffer[offset];
		sdb_1->name_len[sdb_1->num_fields] = sdb_2->name_len[i];
	
		sdb_1->value[sdb_1->num_fields] = sdb_1->name[sdb_1->num_fields] + sdb_2->name_len[i];
		sdb_1->value_len[sdb_1->num_fields] = sdb_2->value_len[i];

		offset += sdb_2->name_len[i] + sdb_2->value_len[i];

		sdb_1->encoding[sdb_1->num_fields] = sdb_2->encoding[i];

		sdb_1->num_fields++;
	} 	

	sdb_1->buffer_len += sdb_2->buffer_len;
	

	return 0;

}

