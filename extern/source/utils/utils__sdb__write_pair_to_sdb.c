#include "utils__libc.h"
#include "utils__utf_8.h"
#include "utils__sdb.h"


/*
 * When encoding is UTF-8, all leading and trailing spaces in names and values are removed. Multiple spaces inside names and values are preserved.
 */



int utils__sdb__write_pair_to_sdb (utils__sdb_t* sdb, const char* name, size_t name_len, const char* value, size_t value_len, int encoding)
{
	int rc;
	size_t room;
	size_t buffer_new_len;	


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

	if (value == NULL)
	{
		return -40;
	}

	if (name_len == 0)
	{
		return -50;
	}

	if (sdb->num_fields >= sdb->fields_max)
	{
		return -60;
	}

	if (sdb->buffer_len > sdb->buffer_size)
	{
		return -70;
	}


	/*
	 * We want a safety room of 16 bytes for all write operations
	 */
	room = sdb->buffer_size - sdb->buffer_len + 16;
	if (name_len + value_len > room)
	{
		return -90;
	}

	if ((encoding != UTILS__SDB__ENCODING__UTF_8) && (encoding != UTILS__SDB__ENCODING__BINARY) && (encoding != UTILS__SDB__ENCODING__CIPHERED))
	{
		return -100;
	}

	//if (language_iso_639_1_code == NULL)
	//{
	//	return -110;
	//}

	//
	//if (language_iso_639_1_code_len == 0)
	//{
	//	;
	//}
	//else if (language_iso_639_1_code_len == UTILS__LANGUAGE_ISO_639_1__CODE_LEN)
	//{
	//	rc = utils__language_iso_639_1__validate_code(language_iso_639_1_code, language_iso_639_1_code_len);
	//	if (rc != 0)
	//	{
	//		return -120;
	//	}
	//}
	//else
	//{
	//	return -130;
	//}



 	rc = utils__sdb__validate_name (name, name_len);
	if (rc != 0)
	{
		return -200;
	}

	memcpy(&sdb->buffer[sdb->buffer_len], name, name_len);
	sdb->name[sdb->num_fields] = &sdb->buffer[sdb->buffer_len];
	sdb->buffer_len += name_len;
	sdb->name_len[sdb->num_fields] = name_len;


	/*
	 * Remove all leading and trailing spaces from the name. 
	 */
	rc = utils__libc__trim_string (sdb->name[sdb->num_fields], sdb->name_len[sdb->num_fields], &buffer_new_len, ' ');
	if (rc != 0)
	{
		return -210;
	}
	 

	if (buffer_new_len > sdb->name_len[sdb->num_fields])
	{
		return -220;
	}

    /*
	 * Sanity check before updating sdb->buffer_len
	 */
	if (sdb->buffer_len + buffer_new_len < sdb->name_len[sdb->num_fields])
	{
		return -230;
	}

    /*
	 * Update sdb->buffer_len and sdb->name_len
	 */
	sdb->buffer_len -= (sdb->name_len[sdb->num_fields] - buffer_new_len);
	sdb->name_len[sdb->num_fields] = buffer_new_len;


	/*
	 * Write the value
	 */	
	if (value_len == 0)
	{
		sdb->value[sdb->num_fields] = (char *) "";
		sdb->value_len[sdb->num_fields] = 0;
		sdb->encoding[sdb->num_fields] = UTILS__SDB__ENCODING__UTF_8;		
	}
	else
	{
		memcpy(&sdb->buffer[sdb->buffer_len], value, value_len);
		sdb->value[sdb->num_fields] = &sdb->buffer[sdb->buffer_len];
		sdb->buffer_len += value_len;
		sdb->value_len[sdb->num_fields] = value_len;

		sdb->encoding[sdb->num_fields] = encoding;

		if (encoding == UTILS__SDB__ENCODING__UTF_8)
		{
			
	        /*
	         * Validate UTF-8 data
	         */
			rc = utils__utf_8__validate_data (value, value_len);
			if (rc != 0)
			{
				return -300;
			}

			/*
			 * Remove all leading and trailing spaces from value
			 */
			rc = utils__libc__trim_string (sdb->value[sdb->num_fields], sdb->value_len[sdb->num_fields], &buffer_new_len, ' ');
			if (rc != 0)
			{
				return -310;
			}

			/*
			 * Sanity check before updating sdb->buffer_len
			 */
			if (buffer_new_len > sdb->value_len[sdb->num_fields])
			{
				return -320;
			}

			/*
			 * Sanity check before updating sdb->buffer_len
			 */
			if (sdb->buffer_len + buffer_new_len < sdb->value_len[sdb->num_fields])
			{
				return -330;
			}

			sdb->buffer_len -= (sdb->value_len[sdb->num_fields] - buffer_new_len);
			sdb->value_len[sdb->num_fields] = buffer_new_len;
		}
	}

	/*code_offset = sdb->num_fields << 1;*/

	//if (language_iso_639_1_code_len == 0)
	//{
	//	sdb->language_iso_639_1_buffer[code_offset] = '\0';
	//	sdb->language_iso_639_1_buffer[code_offset + 1] = '\0';
	//}
	//else
	//{
	//	sdb->language_iso_639_1_buffer[code_offset] = language_iso_639_1_code[0];
	//	sdb->language_iso_639_1_buffer[code_offset + 1] = language_iso_639_1_code[1];     /* language is specified */
	//}

	
	sdb->num_fields++;

	return 0;
}






