#include "utils__sdb.h"


#define UTILS__SDB__EORS__TWO_EMPTY_LINES              1
#define UTILS__SDB__EORS__SQUARE_BRACKETS              2


int utils__sdb__print_sdb (const utils__sdb_t* sdb)
{
	size_t i;
	size_t j;
	size_t len;
	unsigned char* name;
	unsigned char* value;

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


	printf("\n\n");
	printf("------------------------------------------------");
	printf("\n");

	if (sdb->section_name_len > 0)
	{
		printf("SECTION = [");
		for (j = 0; j < sdb->section_name_len; j++)
		{
			printf("%c", sdb->section_name[j]);
		}
		printf("]\n\n");
	}

	for (i = 0; i < sdb->num_fields; i++)
	{

		/*
		 * Name
		 */
		name = (unsigned char*)sdb->name[i];
		len = sdb->name_len[i];
		printf("\"");
		for (j = 0; j < len; j++)
		{
			printf("%c", name[j]);

		}
		printf("\"");


		if (sdb->num_fields >= 10)
		{
			if (i < 9)
			{
				printf("  = ");
			}
			else
			{
				printf(" = ");
			}
		}
		else
		{
			printf(" = ");
		}








		/*
		 * Value
		 */
		value = (unsigned char*)sdb->value[i];
		len = sdb->value_len[i];
		if (len == 0)
		{
			printf("(EMPTY STRING)");
		}
		else
		{
			printf("\"");

			for (j = 0; j < len; j++)
			{
				if (value[j] == '[')
				{
					printf("(SBO)");
				}
				else if (value[j] == ']')
				{
					printf("(SBC)");
				}
				else if (value[j] == '(')
				{
					printf("(RBO)");
				}
				else if (value[j] == ')')
				{
					printf("(RBC)");
				}
				else if ((value[j] >= ' ') && (value[j] <= '~'))
				{
					printf("%c", value[j]);
				}
				else if (value[j] == '\r')
				{
					printf("(CR)");
				}
				else if (value[j] == '\n')
				{
					printf("(LF)");
				}
				else if (value[j] == '\0')
				{
					printf("(NUL)");
				}
				else if (value[j] == '\t')
				{
					printf("(TAB)");
				}
				else if (value[j] == 0xE2)
				{
					if (j + 2 <= len)
					{
						if ((value[j + 1] == 0x82) && (value[j + 2] == 0xAC))
						{
							printf("(EURO)");
							j += 2;
						}
						else if ((value[j + 1] == 0x80) && (value[j + 2] == 0xA2))
						{
							printf("(BULLET)");
							j += 2;
						}
						else
						{
							printf("(%d)", value[j]);
						}
					}
					else
					{
						printf("(%d)", value[j]);
					}
				}
				else
				{
					printf("(%d)", value[j]);
				}
			}
			printf("\"");
		}


		printf("\n");

		if (sdb->encoding[i] == UTILS__SDB__ENCODING__UTF_8)
		{
			printf("Encoding = UTF-8");
		}
		else if (sdb->encoding[i] == UTILS__SDB__ENCODING__BINARY)
		{
			printf("Encoding = BINARY");
		}
		else if (sdb->encoding[i] == UTILS__SDB__ENCODING__CIPHERED)
		{
			printf("Encoding: CIPHERED");
		}
		else
		{
			return -100;
		}

		printf("\n\n");

	}


	printf("\n");
	printf("End of record signature = ");

	if (sdb->end_of_record_signature == UTILS__SDB__EORS__TWO_EMPTY_LINES)
	{
		printf("2 EMPTY LINES");
	}
	else if (sdb->end_of_record_signature == UTILS__SDB__EORS__SQUARE_BRACKETS)
	{
		printf("SQUARE BRACKETS");
	}
	else
	{
		printf("UNKNOWN");
	}
	printf("\n");


	printf("Comment lines = %d", (int)sdb->comment_lines);
	printf("\n");



	return 0;

}