#include "utils__libc.h"
#include "utils__utf_8.h"
#include "utils__sdb.h"


/*
 * sdb ORIGINAL ==>  nome1ENRICOnome2ERIKAnome3CARMELOnome4MIMMO
 *
 * sdb TMP      ==>   nome1ENRICOnome2LAMPUGNANInome3CARMELOnome4MIMMO
 *
 * sdb ORIGINAL ==>  nome1   ENRICO    nome2     ERIKA       nome3    CARMELO    LUMPAGNANI                         nome1ENRICOnome2ERIKAnome3CARMELO    ==>MODIFICATO    nome1ENRICOnome2ERIKAnome3CARMELOLUMPAGNANI
 *                   name[0] value[0]  name[1]   xxxxxx    name[2]  value[2]      value[1]
 */


int utils__sdb__replace_value_in_position (utils__sdb_t *sdb, const char *value, size_t value_len, size_t value_index, int encoding)
{
	int rc;
	size_t total;
	size_t buffer_new_len;

	if (sdb == NULL)
	{
		return -10;
	}

	if (sdb->configured != 1)
	{
		return -20;
	}

	if (value == NULL)
	{
		return -30;
	}

	if (sdb->num_fields >= sdb->fields_max)
	{
		return -60;
	}

	if (value_index >= sdb->num_fields)
	{
		return -70;
	}

	if ((encoding < UTILS__SDB__ENCODING__UTF_8) || (encoding > UTILS__SDB__ENCODING__CIPHERED))
	{
		return -80;
	}

	if (sdb->buffer_len > sdb->buffer_size)
	{
		return -90;
	}

	total = sdb->buffer_len + value_len;

	if (total > sdb->buffer_size)
	{
		return -100;
	}


	switch (encoding)
	{

	case UTILS__SDB__ENCODING__UTF_8:
		rc = utils__utf_8__validate_data (value, value_len);
		if (rc != 0)
		{
			return -200;
		}
		break;

	case UTILS__SDB__ENCODING__BINARY:
		break;

	case UTILS__SDB__ENCODING__CIPHERED:
		break;

	default:
		return -210;
		break;

	}

	sdb->encoding[value_index] = encoding;
	//code_offset = value_index << 1;

	//if (language_iso_639_1_code_len == 0)
	//{
	//	sdb->language_iso_639_1_buffer[code_offset] = '\0';
	//	sdb->language_iso_639_1_buffer[code_offset + 1] = '\0';
	//}
	//else
	//{		
	//	sdb->language_iso_639_1_buffer[code_offset] = language_iso_639_1_code[0];
	//	sdb->language_iso_639_1_buffer[code_offset + 1] = language_iso_639_1_code[1];
	//}



	/*
	 * Write the value
	 */	
	if (value_len == 0)
	{
		sdb->value[value_index] = (char *) "";
		sdb->value_len[value_index] = 0;	
		sdb->encoding[value_index] = UTILS__SDB__ENCODING__UTF_8;
	}
	else
	{
		memcpy(&sdb->buffer[sdb->buffer_len], value, value_len);
		sdb->value[value_index] = &sdb->buffer[sdb->buffer_len];
		sdb->buffer_len += value_len;
		sdb->value_len[value_index] = value_len;

		if (encoding == UTILS__SDB__ENCODING__UTF_8)
		{
			/*
			 * Remove all leading and trailing spaces from the name
			 */
			rc = utils__libc__trim_string (sdb->value[value_index], sdb->value_len[value_index], &buffer_new_len, ' ');
			if (rc != 0)
			{
				return -240;
			}
			

			sdb->buffer_len -= (sdb->value_len[value_index] - buffer_new_len);
			sdb->value_len[value_index] = buffer_new_len;
		}
	}
	

	return 0;
}




