#include "utils__libc.h"
#include "utils__percent_encoding.h"
#include "utils__utf_8.h"
#include "utils__sdb.h"





/*
 * This function converts an x www form urlencoded buffer to an sdb: n1=value 1&n2=value 2&N3=IT
 *
 * All names must be compliant to sdb names
 *
 */

/*
 * All leading and trailing spaces in the names and in the values are removed. Multiple spaces inside the value are preserved.
 */


/*
 * RFC 3986 states:
 *
 * Reserved (must arrive encoded)
 *
 *  ':' 	   '/' 	  '?'  	 '#' 	'[' 	']' 	'@' 	'!' 	'$' 	'&' 	"'" 	'(' 	')' 	'*' 	'+' 	',' 	';' 	'=' 	'%' 	' '
 *  %3A     %2F 	  %3F 	 %23 	%5B 	%5D 	%40 	%21 	%24 	%26 	%27 	%28 	%29 	%2A 	%2B 	%2C 	%3B 	%3D 	%25 	%20  or  +
 *
 *
 *
 *
 * Unreserved (must arrive unencoded)
 *
 *
 *  'a', 'b', ...'z'        'A', 'B',...'Z'        '0', '1',   ,'9'    '-'  '.'  '_'   '~'
 *
 *
 * Other characters must be percent encoded
 *
 *  0x00, 0x01, 0x
 *
 */


#define UTILS__SDB__WRITE__URLENCODED_DATA_RESERVED_CHARACTERS   17


static char utils__sdb__write_urlencoded_data_to_sdb__reserved_characters[UTILS__SDB__WRITE__URLENCODED_DATA_RESERVED_CHARACTERS] = {':', '/', '?', '#', '[', ']', '@', '!', '$', '\'', '(', ')', '*', '+', ',', ';', ' '};


#define NAME_START__STATE            0
#define COLLECT_NAME__STATE          1
#define VALUE_START__STATE           2
#define COLLECT_VALUE__STATE         3


int utils__sdb__write_urlencoded_data_to_sdb (utils__sdb_t *sdb, const char *buffer, size_t buffer_len)
{
	int rc;
	int state;
	int end;
	unsigned char c;
	size_t i;
	unsigned char *buf;
	size_t room;
	int c_retained_flag;
	unsigned char c_retained;
	size_t buffer_new_len;
	//size_t code_offset;
	//unsigned char code[UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	if (sdb == NULL)
	{
		return -10;
	}

	if (sdb->configured != 1)
	{
		return -20;
	}

	if (buffer == NULL)
	{
		return -30;
	}

	if (buffer_len == 0)
	{
		return -40;
	}


	buf = (unsigned char *) buffer;


	//if (language_iso_639_1_code_len == 0)
	//{
	//	code[0] = '\0';
	//	code[1] = '\0';
	//}
	//else if (language_iso_639_1_code_len == UTILS__LANGUAGE_ISO_639_1__CODE_LEN)
	//{
	//	rc = utils__language_iso_639_1__validate_code(language_iso_639_1_code, language_iso_639_1_code_len);
	//	if (rc != 0)
	//	{
	//		return -50;
	//	}

	//	code[0] = language_iso_639_1_code[0];
	//	code[1] = language_iso_639_1_code[0];
	//}
	//else
	//{
	//	return -60;
	//}



	sdb->buffer_len = 0;
	sdb->num_fields = 0;

	c_retained = 0x00;	
	c_retained_flag = 0;
	state = 0;
	end = 0;
	i = 0;

	do 
	{
		if (c_retained_flag == 1)
		{
			c = c_retained;					
		}
		else
		{		
			c = buf[i];
		}


		switch (state)
		{

		case NAME_START__STATE:
			if (c == '=') 
			{
				return -100;   /* A name can't start by '='   */
			}

			if (c == '&')
			{
				return -110;   /* A name can't start by '&'   */
			}

			sdb->buffer[sdb->buffer_len] = c;
			sdb->name[sdb->num_fields] = &sdb->buffer[sdb->buffer_len];
			sdb->name_len[sdb->num_fields] = 1;
			sdb->buffer_len++;
			state = COLLECT_NAME__STATE;
			break;

		case COLLECT_NAME__STATE:
			if (c == '=')
			{

				rc = utils__percent_encoding__decode_data_strict (sdb->name[sdb->num_fields], sdb->name_len[sdb->num_fields], &buffer_new_len);
				if (rc != 0)
				{
					return -140;
				}

				sdb->buffer_len -= (sdb->name_len[sdb->num_fields] - buffer_new_len);
				sdb->name_len[sdb->num_fields] = buffer_new_len;

				/*
				 * Remove all leading and trailing spaces
				 */
				rc = utils__libc__trim_string (sdb->name[sdb->num_fields], sdb->name_len[sdb->num_fields], &buffer_new_len, ' ');
				if (rc != 0)
				{
					return -150;
				}
				 
				sdb->buffer_len -= (sdb->name_len[sdb->num_fields] - buffer_new_len);
				sdb->name_len[sdb->num_fields] = buffer_new_len;
			
				rc = utils__sdb__validate_name (sdb->name[sdb->num_fields], sdb->name_len[sdb->num_fields]);
				if (rc != 0)
				{
					return -160;
				}

				state = VALUE_START__STATE;
				break;
			}

			if (c == '&')
			{
				return -150;
			}

			sdb->buffer[sdb->buffer_len] = c;
			sdb->name_len[sdb->num_fields]++;
			sdb->buffer_len++;
			break;

		case VALUE_START__STATE:
			if (c == '=')
			{
				return -170;
			}

			if (c == '&')
			{
				sdb->value[sdb->num_fields] = "";
				sdb->value_len[sdb->num_fields] = 0;
				sdb->encoding[sdb->num_fields] = UTILS__SDB__ENCODING__UTF_8;

				//code_offset = sdb->num_fields << 1;

				//sdb->language_iso_639_1_buffer[code_offset] = code[0];
				//sdb->language_iso_639_1_buffer[code_offset + 1] = code[0];

				sdb->num_fields++;
				state = NAME_START__STATE;
				break;
			}


			sdb->buffer[sdb->buffer_len] = c;
			sdb->value[sdb->num_fields] = &sdb->buffer[sdb->buffer_len];
			sdb->value_len[sdb->num_fields] = 1;
			sdb->buffer_len++;
			state = COLLECT_VALUE__STATE;
			break;

		case COLLECT_VALUE__STATE:
			if (c == '=')
			{
				return -180;
			}

			if (c == '&')
			{

				rc = utils__percent_encoding__decode_data_strict (sdb->value[sdb->num_fields], sdb->value_len[sdb->num_fields], &buffer_new_len);
				if (rc != 0)
				{
					return -190;
				}

				sdb->buffer_len -= (sdb->value_len[sdb->num_fields] - buffer_new_len);
				sdb->value_len[sdb->num_fields] = buffer_new_len;


				/*
				 * Remove all leading and trailing spaces
				 */
				rc = utils__libc__trim_string (sdb->value[sdb->num_fields], sdb->value_len[sdb->num_fields], &buffer_new_len, ' ');
				if (rc != 0)
				{
					return -200;
				}
				 
				sdb->buffer_len -= (sdb->value_len[sdb->num_fields] - buffer_new_len);
				sdb->value_len[sdb->num_fields] = buffer_new_len;


				rc = utils__utf_8__validate_data(sdb->value[sdb->num_fields], sdb->value_len[sdb->num_fields]);
				if (rc == 0)
				{
					sdb->encoding[sdb->num_fields] = UTILS__SDB__ENCODING__UTF_8;					
				}
				else
				{
					sdb->encoding[sdb->num_fields] = UTILS__SDB__ENCODING__BINARY;
				}


				//code_offset = sdb->num_fields << 1;

				//sdb->language_iso_639_1_buffer[code_offset] = code[0];
				//sdb->language_iso_639_1_buffer[code_offset + 1] = code[0];

				sdb->num_fields++;
				state = NAME_START__STATE;
				break;
			}

			sdb->buffer[sdb->buffer_len] = c;
			sdb->value_len[sdb->num_fields]++;
			sdb->buffer_len++;
			break;

		default:
			return -1000;
			break;

		}


		room = 16;
		if (sdb->buffer_len + room > sdb->buffer_size)
		{
			return -210;
		}

		i++;

		if (i >= buffer_len)
		{
			if (c_retained_flag == 0)
			{
				i--;
				c_retained = '&';
				c_retained_flag = 1;			
			}
			else
			{
				end = 1;
			}

		}
	}
	while (end == 0);

	return 0;

}










