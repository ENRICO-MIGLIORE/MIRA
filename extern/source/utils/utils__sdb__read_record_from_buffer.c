#include "utils__utf_8.h"
#include "utils__percent_encoding.h"
#include "utils__sdb.h"


#define UTILS__SDB__EORS__TWO_EMPTY_LINES      1
#define UTILS__SDB__EORS__SQUARE_BRACKETS      2


#define UTF_8_BOM_SIZE                         3


#define START                                  0
#define START__COMMENT                        10
#define START__PARENT_NAME                    20
#define START__LF                             30
#define END_1                                100
#define END_2                                110
#define END_3                                120
#define COLLECT_NAME                         200
#define DETECT_ENCODING_1                    300
#define DETECT_ENCODING_2                    310
#define COLLECT_VALUE                        400
#define COLLECT_VALUE__LF                    410
#define COLLECT_VALUE__LINGER                420
#define FINALE                              1000


#define validate_char(c) 	((c >= 'A')  &  (c <= 'Z'))  |  ((c >= 'a')  &  (c <= 'z'))  |  ((c >= '0')  &  (c <= '9'))  |  ((c == '-')  |  (c == '_')  |  (c == '.')  |  (c == ':')  |  (c == '\''));


#define PREFIX__NOT_PRESENT                      0
#define PREFIX__NOT_PRESENT__AND__VALUE_EMPTY    1
#define PREFIX__DETECTED__EMPTY                  2
#define PREFIX__DETECTED__BINARY                 3
#define PREFIX__DETECTED__CIPHERED               4


/*
 * UTF-8
 *
 * Case 1:   file value = "CIAO"                             --->   sdb value = "CIAO"   +   sdb encoding = UTF-8
 * Case 2:   file value = ""                                 --->   sdb value = ""       +   sdb encoding = UTF-8
 * Case 3:   file value = "|empty|"                          --->   sdb value = ""       +   sdb encoding = UTF-8
 */

 /*
  * Binary
  *
  * Case 4:   file value = "|binary|%7C%0D"                  --->   sdb value = "|\r"   +   sdb encoding = BINARY
  */

  /*
   * Ciphered
   *
   * Case 5:   file value = "|ciphered|%7C%0D"                --->   sdb value = "|\r"   +  sdb encoding = CIPHERED
   */



int utils__sdb__read_record_from_buffer(utils__sdb_t* sdb, const char* file_name, size_t record_number, size_t record_index, int* end_of_file)
{
	FILE* f;
	int rc;
	int state;
	size_t k;
	int done;
	int utf_8;
	size_t bytes_read;
	size_t residual_size;
	size_t new_len;
	int valid;
	unsigned char buffer_local[1024];
	char prefix[16];    /* sizeof(prefix) must be greater than strlen("ciphered") */
	size_t i;
	int end;
	int end_internal;
	size_t offset;
	unsigned char c;
	unsigned char c_retained;
	int c_retained_flag;
	int record_started;
	size_t record_count;
	size_t prefix_len;
	size_t prefix_count;
	int prefix_type;
	int parent_name_flag;
	const char* dummy_end_of_file;
	int coming_from_linger;
	int end_of_file_reached;
	size_t crlf_count;
	int square_bracket_pending;
	int finale_pending;



	rc = utils__sdb__clear_sdb(sdb);
	if (rc != 0)
	{
		return -10;
	}

	if (record_number == 0)
	{
		return -20;
	}

	if (end_of_file == NULL)
	{
		return -30;
	}

	if (file_name == NULL)
	{
		return -40;
	}

	f = fopen((const char*)file_name, "rb");
	if (f == NULL)
	{
		return -50;
	}



	c = 0x00;             /* keep the compiler happy */
	c_retained = 0x00;	  /* keep the compiler happy */
	c_retained_flag = 0;
	square_bracket_pending = 0;
	finale_pending = 0;
	end_of_file_reached = 0;
	dummy_end_of_file = "\r\n\r\n\r\n";
	coming_from_linger = 0;
	parent_name_flag = 0;
	prefix_type = PREFIX__NOT_PRESENT;
	prefix_count = 0;
	prefix_len = 0;
	record_count = 0;
	record_started = 0;
	crlf_count = 0;
	*end_of_file = 0;

	bytes_read = 0;

	offset = 0;
	end = 0;
	state = START;

	if (record_index > 0)
	{
		fseek(f, (long)record_index, SEEK_SET);
		record_number = 1;
	}
	else
	{
		bytes_read = fread(buffer_local, 1, UTF_8_BOM_SIZE, f);

		if (bytes_read != UTF_8_BOM_SIZE)
		{
			fclose(f);
			return -80;
		}

		if ((buffer_local[0] == 0xEF) && (buffer_local[1] == 0xBB) && (buffer_local[2] == 0xBF))
		{
			;
		}
		else
		{
			offset = 3;
		}
	}


	do
	{

		end_internal = 0;

		bytes_read = 0;

		if (end_of_file_reached == 0)
		{

			residual_size = sizeof(buffer_local) - offset;

			bytes_read = fread((char*)&buffer_local[offset], 1, residual_size, f);

			if (offset > 0)
			{
				bytes_read += offset;
				offset = 0;
			}
		}

		if (bytes_read == 0)
		{

			end_of_file_reached = 1;
			*end_of_file = 1;

			if (record_count == record_number - 1)
			{
				parent_name_flag = 0;
				crlf_count++;
				if (crlf_count <= 6)
				{
					c_retained_flag = 1;
					c_retained = dummy_end_of_file[crlf_count - 1];
				}
				else
				{
					fclose(f);       /* error: record_count greater than record_number */
					return -200;
				}
			}
			else
			{

				if (record_count < record_number)
				{
					fclose(f);        /* error: File doesn't have enough records error */
					return -210;
				}

				if (record_count > record_number)
				{
					fclose(f);       /* error: record_count greater than record_number */
					return -220;
				}

				/*
				 * Unexpected error
				 */
				fclose(f);
				return -230;
			}
		}

		i = 0;

		do
		{
			if (c_retained_flag == 1)
			{
				c_retained_flag = 0;
				c = c_retained;
			}
			else
			{
				c = buffer_local[i];
			}



			switch (state)
			{

			case START:

				if (c == ' ')
				{
					break;
				}

				if (c == '#')
				{
					sdb->comment_lines++;
					state = START__COMMENT;
					break;
				}

				if (record_started == 0)
				{

					if (c == '\r')
					{
						state = START__LF;
						break;
					}

					if (c == '\n')
					{
						c_retained = c;
						c_retained_flag = 1;
						state = START__LF;
						break;
					}

					if (c == '[')
					{
						parent_name_flag = 0;
						sdb->section_name_len = 0;
						state = START__PARENT_NAME;
						break;
					}

					record_started = 1;

				}
				else
				{
					if (c == '\r')
					{
						state = END_1;
						break;
					}

					if (c == '\n')
					{
						c_retained = c;
						c_retained_flag = 1;
						state = END_1;
						break;
					}

					if (c == '[')
					{
						c_retained = c;
						c_retained_flag = 1;
						square_bracket_pending = 1;
						sdb->end_of_record_signature = UTILS__SDB__EORS__SQUARE_BRACKETS;
						state = FINALE;
						break;
					}
				}

				valid = validate_char(c);
				if (valid == 0)
				{
					fclose(f);
					return -300;
				}

				sdb->name[sdb->num_fields] = &sdb->buffer[sdb->buffer_len];
				sdb->name_len[sdb->num_fields] = 1;
				sdb->value_len[sdb->num_fields] = 0;

				sdb->buffer[sdb->buffer_len] = c;
				sdb->buffer_len++;

				state = COLLECT_NAME;
				break;

			case START__COMMENT:
				if (c == '\r')
				{
					state = START__LF;
					break;
				}

				if (c == '\n')
				{
					c_retained = c;
					c_retained_flag = 1;
					state = START__LF;
					break;
				}
				break;

			case START__PARENT_NAME:
				if (c == ']')
				{
					if (sdb->section_name_len == 0)
					{
						fclose(f);
						return -400;
					}


					/*
					 * Remove all trailing white spaces
					 */

					done = 0;
					while ((sdb->section_name_len > 0) && (done == 0))
					{
						if (sdb->section_name[sdb->section_name_len - 1] == ' ')
						{
							sdb->section_name_len--;
						}
						else
						{
							done = 1;
						}
					}

					parent_name_flag = 1;
					coming_from_linger = 0;
					state = START;
					break;
				}

				if (c == ' ')
				{
					if (sdb->section_name_len == 0)
					{
						break;  /* skip leading white spaces */
					}
				}
				else
				{
					valid = validate_char(c);
					if (valid == 0)
					{
						fclose(f);
						return -500;
					}
				}

				sdb->section_name[sdb->section_name_len] = c;
				sdb->section_name_len++;
				if (sdb->section_name_len >= UTILS__SDB__SECTION_NAME_SIZE)
				{
					fclose(f);   /* Overflow error */
					return -510;
				}
				break;

			case START__LF:
				if (c != '\n')
				{
					fclose(f);
					return -520;
				}

				coming_from_linger = 0;
				state = START;
				break;

			case END_1:
				if (c != '\n')
				{
					fclose(f);
					return -600;
				}
				state = END_2;
				break;

			case END_2:

				if (parent_name_flag == 1)
				{
					c_retained = c;
					c_retained_flag = 1;
					coming_from_linger = 0;
					state = START;
					break;
				}


				if (c == '\r')
				{
					state = END_3;
					break;
				}

				if (c == '\n')
				{
					c_retained = c;
					c_retained_flag = 1;
					state = END_3;
					break;
				}

				if (c == ' ')
				{
					break;
				}


				c_retained = c;
				c_retained_flag = 1;

				coming_from_linger = 0;
				state = START;
				break;

			case END_3:
				if (c != '\n')
				{
					fclose(f);
					return -700;
				}

				c_retained = c;
				c_retained_flag = 1;

				finale_pending = 1;

				sdb->end_of_record_signature = UTILS__SDB__EORS__TWO_EMPTY_LINES;
				state = FINALE;
				break;

			case COLLECT_NAME:
				if (c == '=')
				{

					/*
					 * Remove all trailing white spaces
					 */
					done = 0;
					while ((sdb->name_len[sdb->num_fields] > 0) && (sdb->buffer_len > 0) && (done == 0))
					{
						if (sdb->buffer[sdb->buffer_len - 1] == ' ')
						{
							sdb->buffer_len--;
							sdb->name_len[sdb->num_fields]--;
						}
						else
						{
							done = 1;
						}
					}

					sdb->value[sdb->num_fields] = (char*)"";
					sdb->value_len[sdb->num_fields] = 0;
					sdb->encoding[sdb->num_fields] = UTILS__SDB__ENCODING__UTF_8;

					prefix_type = PREFIX__NOT_PRESENT;
					state = DETECT_ENCODING_1;
					break;
				}

				if (c != ' ')
				{
					valid = validate_char(c);
					if (valid == 0)
					{
						fclose(f);
						return -800;
					}
				}

				sdb->name_len[sdb->num_fields]++;
				sdb->buffer[sdb->buffer_len] = c;
				sdb->buffer_len++;
				break;

			case DETECT_ENCODING_1:
				if (c == '\r')
				{
					prefix_type = PREFIX__NOT_PRESENT__AND__VALUE_EMPTY;
					state = COLLECT_VALUE__LF;
					break;
				}

				if (c == '\n')
				{
					c_retained = c;
					c_retained_flag = 1;
					prefix_type = PREFIX__NOT_PRESENT__AND__VALUE_EMPTY;
					state = COLLECT_VALUE__LF;
					break;
				}

				if (c == '|')
				{
					prefix_len = 0;
					prefix_count = 0;
					state = DETECT_ENCODING_2;
					break;
				}

				if (c == ' ')
				{
					break;
				}

				sdb->value[sdb->num_fields] = &sdb->buffer[sdb->buffer_len];
				sdb->value_len[sdb->num_fields] = 1;
				sdb->buffer[sdb->buffer_len] = c;
				sdb->buffer_len++;

				state = COLLECT_VALUE;
				break;

			case DETECT_ENCODING_2:

				prefix_count++;
				if (prefix_count >= sizeof(prefix))
				{
					fclose(f);     /* prefix_count overflow */
					return -900;
				}

				if (c != '|')
				{
					prefix[prefix_len] = (char)tolower(c);
					prefix_len++;
					if (prefix_len >= sizeof(prefix))
					{
						fclose(f);
						return -910;	/* prefix_len overflow */
					}
					break;
				}


				if ((prefix_len > 2) && (coming_from_linger == 1))
				{
					fclose(f);
					return -930; /*carmelo bug */
				}

				if (prefix_len == 5)
				{
					rc = memcmp(prefix, "empty", 5);
					if (rc == 0)
					{
						prefix_type = PREFIX__DETECTED__EMPTY;
						state = COLLECT_VALUE;
						break;
					}
				}

				if (prefix_len == 6)
				{
					rc = memcmp(prefix, "binary", 6);
					if (rc == 0)
					{
						sdb->encoding[sdb->num_fields] = UTILS__SDB__ENCODING__BINARY;
						prefix_type = PREFIX__DETECTED__BINARY;
						state = COLLECT_VALUE;
						break;
					}
				}

				if (prefix_len == 8)
				{
					rc = memcmp(prefix, "ciphered", 8);
					if (rc == 0)
					{
						sdb->encoding[sdb->num_fields] = UTILS__SDB__ENCODING__CIPHERED;
						prefix_type = PREFIX__DETECTED__CIPHERED;
						state = COLLECT_VALUE;
						break;
					}
				}

				fclose(f);
				return -1010;

				break;

			case COLLECT_VALUE:
				if (c == '\r')
				{
					state = COLLECT_VALUE__LF;
					break;
				}

				if (c == '\n')
				{
					c_retained = c;
					c_retained_flag = 1;
					state = COLLECT_VALUE__LF;
					break;
				}

				if (prefix_type == PREFIX__DETECTED__EMPTY)
				{
					break;  /* Wait for the end of line */
				}

				if ((prefix_type == PREFIX__DETECTED__BINARY) && (sdb->value_len[sdb->num_fields] == 0))
				{
					if (c == ' ')
					{
						break;   /* skip leading white spaces */
					}

					sdb->value[sdb->num_fields] = &sdb->buffer[sdb->buffer_len];
				}

				if ((prefix_type == PREFIX__DETECTED__CIPHERED) && (sdb->value_len[sdb->num_fields] == 0))
				{
					if (c == ' ')
					{
						break;   /* skip leading white spaces */
					}
					sdb->value[sdb->num_fields] = &sdb->buffer[sdb->buffer_len];
				}


				if (c == '|')
				{
					fclose(f);
					return -1020;
				}

				sdb->value_len[sdb->num_fields]++;
				sdb->buffer[sdb->buffer_len] = c;
				sdb->buffer_len++;
				break;



			case COLLECT_VALUE__LF:
				if (c != '\n')
				{
					fclose(f);
					return -1100;
				}

				if ((prefix_type == PREFIX__NOT_PRESENT__AND__VALUE_EMPTY) || (prefix_type == PREFIX__DETECTED__EMPTY))
				{
					sdb->num_fields++;
					coming_from_linger = 0;
					state = START;
					break;
				}


				utf_8 = 0;

				if (prefix_type == PREFIX__NOT_PRESENT)
				{
					utf_8 = 1;
				}
				else if ((prefix_type == PREFIX__DETECTED__BINARY) || (prefix_type == PREFIX__DETECTED__CIPHERED))
				{
					;
				}
				else
				{
					fclose(f);
					return -1110;
				}


				/* Remove all trailing white spaces */

				done = 0;
				while ((sdb->value_len[sdb->num_fields] > 0) && (sdb->buffer_len > 0) && (done == 0))
				{
					if (sdb->buffer[sdb->buffer_len - 1] == ' ')
					{
						sdb->buffer_len--;
						sdb->value_len[sdb->num_fields]--;
					}
					else
					{
						done = 1;
					}
				}


				/*
				 *  If the function "utils__percent_encoding__decode__data()" returns 0, than "new_len" is surely smaller than or equal to "sdb->value_len[sdb->num_fields]"
				 */
				rc = utils__percent_encoding__decode__data(sdb->value[sdb->num_fields], sdb->value_len[sdb->num_fields], &new_len);
				if (rc != 0)
				{
					fclose(f);
					return -1120;
				}


				/*
				 * Sanity check: sdb->buffer_len must be greater than (sdb->value_len[sdb->num_fields] - new_len)
				 */
				if (new_len < sdb->value_len[sdb->num_fields])
				{
					if (sdb->buffer_len < (sdb->value_len[sdb->num_fields] - new_len))
					{
						fclose(f);
						return -1130;
					}

					sdb->buffer_len -= (sdb->value_len[sdb->num_fields] - new_len);
					sdb->value_len[sdb->num_fields] = new_len;
				}

				if (utf_8 == 1)
				{
					rc = utils__utf_8__validate_data(sdb->value[sdb->num_fields], sdb->value_len[sdb->num_fields]);
					if (rc != 0)
					{
						fclose(f);
						return -1140;
					}
				}


				sdb->num_fields++;

				coming_from_linger = 0;
				state = START;
				break;


			case COLLECT_VALUE__LINGER:
				if (c == '\r')
				{
					state = COLLECT_VALUE__LF;
					break;
				}

				if (c == '\n')
				{
					c_retained = c;
					c_retained_flag = 1;
					state = COLLECT_VALUE__LF;
					break;
				}
				break;


			case FINALE:
				record_count++;

				if (record_count > record_number)
				{
					fclose(f);
					return -1300;
				}

				if (record_count == record_number)
				{
					end = 1;
					break;
				}


				for (k = 0; k < sdb->fields_max; k++)
				{
					sdb->encoding[k] = 0;
				}
				sdb->buffer_len = 0;
				sdb->num_fields = 0;
				sdb->section_name_len = 0;
				sdb->end_of_record_signature = 0;


				c = 0x00;             /* keep the compiler happy */
				c_retained = 0x00;	  /* keep the compiler happy */
				c_retained_flag = 0;
				coming_from_linger = 0;
				parent_name_flag = 0;
				prefix_type = PREFIX__NOT_PRESENT;
				prefix_count = 0;
				prefix_len = 0;
				record_started = 0;

				if (finale_pending == 1)
				{
					finale_pending = 0;
				}
				else if (square_bracket_pending == 1)
				{
					square_bracket_pending = 0;
					c_retained = '[';
					c_retained_flag = 1;
				}

				state = START;
				break;

			default:
				fclose(f);
				return -3000;
				break;
			}


			if (end == 0)
			{
				/*
				 * We want a safety room of 16 bytes
				 */
				if (sdb->buffer_len + 16 > sdb->buffer_size)
				{
					fclose(f);
					return -4000;
				}

				if (c_retained_flag == 0)
				{

					i++;
					if (i >= bytes_read)
					{
						end_internal = 1;
					}
				}
			}
			else
			{
				end_internal = 1;
			}
		} while (end_internal == 0);

	} while (end == 0);


	fclose(f);



	return 0;

}