#include "utils__utf_8.h"
#include "utils__sdb.h"


/* 
 * BUFFER_SIZE_MIN must be greater strlen("|ciphered|%FF")
 */
#define UTILS__SDB__WRITE__BUFFER_SIZE        64 


static const unsigned char utils__sdb__write_sdb_to_file__lookup_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};


int utils__sdb__write_record_to_file (const char *file_name, const utils__sdb_t *sdb)
{
	FILE *f;
	size_t i;
	size_t j;
	unsigned char buffer[UTILS__SDB__WRITE__BUFFER_SIZE];  			
	size_t buffer_len;
	unsigned char *v;
	unsigned char low;
	unsigned char high;	
	int rc;
	int encode;
	//size_t code_len;
	//size_t code_offset;
	size_t room;


	if (file_name == NULL)
	{
		return -10;
	}

	if (sdb == NULL)
	{
		return -20;
	}

	if (sdb->configured != 1)
	{
		return -30;
	}

	if (sdb->num_fields == 0)
	{
		return -40;
	}

	if (sdb->num_fields >= sdb->fields_max)
	{
		return -50;
	}


	f = fopen(file_name, "rb");

	if (f == NULL)
	{
		f = fopen(file_name, "wb");
		if (f == NULL)
		{
			return -300;
		}		
	}

	fclose(f);
	

	f = fopen(file_name, "ab");

	if (f == NULL)
	{
		return -300;
	}	



	fwrite("\r\n\r\n", 1, 4, f);


	buffer_len = 0;

	for (i = 0; i < sdb->num_fields; i++)
	{


		//code_len = 0;
		//code_offset = i << 1;

		rc = utils__sdb__validate_name (sdb->name[i], sdb->name_len[i]);
		if (rc != 0)
		{
			return -200;
		}

		/*
		 * All name value pairs must have the encoding flag set
		 */
		if ((sdb->encoding[i] != UTILS__SDB__ENCODING__UTF_8) && (sdb->encoding[i] != UTILS__SDB__ENCODING__BINARY) && (sdb->encoding[i] != UTILS__SDB__ENCODING__CIPHERED))
		{
			return -210;
		}




		if (sdb->encoding[i] == UTILS__SDB__ENCODING__UTF_8)
		{

			/*
			 * When UTF_8__ENCODING is set, sdb->value[i] must contain a valid UTF-8 sequence
			 */
			rc = utils__utf_8__validate_data (sdb->value[i], sdb->value_len[i]);
			if (rc != 0)
			{
				return -220;
			}
			
			
			//if ((sdb->language_iso_639_1_buffer[code_offset] == '\0') && (sdb->language_iso_639_1_buffer[code_offset + 1] == '\0'))
			//{
			//	;
			//}
			//else
			//{				
			//	code_len = UTILS__LANGUAGE_ISO_639_1__CODE_LEN;

			//	rc = utils__language_iso_639_1__validate_code (&sdb->language_iso_639_1_buffer[code_offset], code_len);
			//	if (rc != 0)
			//	{
			//		return -240;
			//	}				
			//}
		}


		/*
		* Write the name
		*/
		fwrite(sdb->name[i], 1, sdb->name_len[i], f);

		fwrite(" = ", 1, 3, f);

		v = (unsigned char *) sdb->value[i];

		/*
		 * Write the value
		 */
		if (sdb->value_len[i] == 0)
		{			
			/*
			 * We convert empty values in "|empty|"
			 */
			if (sdb->encoding[i] == UTILS__SDB__ENCODING__UTF_8)
			{
				/*if (code_len != 0)
				{
					buffer[buffer_len] = '|';
					buffer_len++;
					buffer[buffer_len] = sdb->language_iso_639_1_buffer[code_offset];
					buffer_len++;
					buffer[buffer_len] = sdb->language_iso_639_1_buffer[code_offset + 1];
					buffer_len++;
					buffer[buffer_len] = '|';
					buffer_len++;
				}*/
				//else
				//{				
				buffer[buffer_len] = '|';
				buffer_len++;
				buffer[buffer_len] = 'e';
				buffer_len++;
				buffer[buffer_len] = 'm';
				buffer_len++;
				buffer[buffer_len] = 'p';
				buffer_len++;
				buffer[buffer_len] = 't';
				buffer_len++;
				buffer[buffer_len] = 'y';
				buffer_len++;
				buffer[buffer_len] = '|';
				buffer_len++;
				//}
			}
			else
			{
				return -310;
			}
		}
		else
		{ 


			/*
			 *  "VALUE"
			 */
			for (j = 0; j < sdb->value_len[i]; j++)
			{
				if (j == 0)
				{
				    if (sdb->encoding[i] == UTILS__SDB__ENCODING__UTF_8)
				    {												
						;
				    }
					else if (sdb->encoding[i] == UTILS__SDB__ENCODING__BINARY)
					{
						buffer[buffer_len] = '|';
						buffer_len++;
						buffer[buffer_len] = 'b';
						buffer_len++;
						buffer[buffer_len] = 'i';
						buffer_len++;
						buffer[buffer_len] = 'n';
						buffer_len++;
						buffer[buffer_len] = 'a';
						buffer_len++;
						buffer[buffer_len] = 'r';
						buffer_len++;
						buffer[buffer_len] = 'y';
						buffer_len++;
						buffer[buffer_len] = '|';
						buffer_len++;
					}
					else if (sdb->encoding[i] == UTILS__SDB__ENCODING__CIPHERED)
					{
						buffer[buffer_len] = '|';
						buffer_len++;
						buffer[buffer_len] = 'c';
						buffer_len++;
						buffer[buffer_len] = 'i';
						buffer_len++;
						buffer[buffer_len] = 'p';
						buffer_len++;
						buffer[buffer_len] = 'h';
						buffer_len++;
						buffer[buffer_len] = 'e';
						buffer_len++;
						buffer[buffer_len] = 'r';
						buffer_len++;
						buffer[buffer_len] = 'e';
						buffer_len++;
						buffer[buffer_len] = 'd';
						buffer_len++;
						buffer[buffer_len] = '|';
						buffer_len++;
					}
				}


				/*
				 * We have two reserved characters: | and %
				 */
				if (v[j] == '|')
				{				
					buffer[buffer_len] = '%';
					buffer[buffer_len + 1] = '7';
					buffer[buffer_len + 2] = 'C';
					buffer_len += 3;
				}
				else if (v[j] == '%')
				{				
					buffer[buffer_len] = '%';
					buffer[buffer_len + 1] = '2';
					buffer[buffer_len + 2] = '5';
					buffer_len += 3;
				}
				else if (v[j] == '~')
				{				
					buffer[buffer_len] = '%';
					buffer[buffer_len + 1] = '7';
					buffer[buffer_len + 2] = 'E';
					buffer_len += 3;
				}
				else
				{
					encode = 0;  

					if (sdb->encoding[i] == UTILS__SDB__ENCODING__UTF_8)
					{
						if (((v[j] >= '\0') && (v[j] < ' ')) || (v[j] == 127))
						{
							encode = 1;                /* Encode non-printeable ASCII 7-bit symbols */
						}
					}
					else if ((sdb->encoding[i] == UTILS__SDB__ENCODING__BINARY) || (sdb->encoding[i] == UTILS__SDB__ENCODING__CIPHERED))		
					{
						if (((v[j] >= '\0') && (v[j] <= ' ')) || (v[j] >= 127))
						{
							encode = 1;                /* Encode non-printeable ASCII 8-bit symbols */
						}
					}


					if (encode == 1)
					{
						/*
						*
						*   %hl    %00  %01   %02  %0F ...  %1F  ...  %FF
						*
						*     h   l
						*   0000 0000
						*   0000 0001
						*   0000 0010
						*   0000 0011
						*   0000 0100
						*
						*   0000 1111
						*
						*   0010 0000
						*/					
						buffer[buffer_len] = '%';

						high = (unsigned char) (v[j] >> 4);
						high = (unsigned char) (high & 0x0F);
						buffer[buffer_len + 1] = utils__sdb__write_sdb_to_file__lookup_table[high];

						low = (unsigned char) (v[j] & 0x0F);
						buffer[buffer_len + 2] = utils__sdb__write_sdb_to_file__lookup_table[low];

						buffer_len += 3;
					}
					else
					{
						buffer[buffer_len] = v[j];
						buffer_len++;
					}
				}


				/*
				 * max len = 13 and we have it when buffer[] contains:  |ciphered|%FF
				 */
				fwrite(buffer, 1, buffer_len, f);
				buffer_len = 0;

				room = 20;
				if (buffer_len + room >= sizeof(buffer))
				{
					fwrite(buffer, 1, buffer_len, f);
					buffer_len = 0;
				}
			}
		}


		if (buffer_len > 0)
		{
			fwrite(buffer, 1, buffer_len, f);
			buffer_len = 0;			
		}

		
		/* 
		 * Add new line after a pair
		 */
		fwrite("\r\n", 1, 2, f);

	}


	/*
	 * Write the end of record signature
	 */
	fwrite("\r\n\r\n", 1, 4, f);

	fclose(f);

	return 0;

}




