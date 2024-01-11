#include <stdio.h>
#include <stddef.h>


int utils__utf_8__get_next_symbol (const void *buffer, size_t buffer_len, char **token, size_t *token_len)
{


	unsigned char *b;


	if (buffer == NULL)
	{
		return -10;
	}

	if (token == NULL)
	{
		return -20;
	}

	if (token_len == NULL)
	{
		return -30;
	}

	if (buffer_len == 0)
	{
		return -40;
	}


	b = (unsigned char *) buffer;

	if (b[0] < 0x80)
	{
		/*
		 * 0xxxxxxx
		 */
		*token_len = 1;
		*token = (char *) &b[0];
		return 0;
	}


	if (buffer_len >= 2)
	{
		if ((b[0] & 0xE0) == 0xC0) 
		{
			/* 
			* 110XXXXx 10xxxxxx
			*/
			if ((b[1] & 0xC0) != 0x80 ||
				(b[1] & 0xFE) == 0xC0)                        /* overlong? */
			{
				return -50;
			}

			*token_len = 2;
			*token = (char *) &b[0];
			return 0;
		} 
	}
	else
	{
		return -60;
	}

	if (buffer_len >= 3)
	{	
		if ((b[0] & 0xF0) == 0xE0) 
		{
			/* 
			 * 1110XXXX 10Xxxxxx 10xxxxxx
			 */
			if ((b[1] & 0xC0) != 0x80 || (b[2] & 0xC0) != 0x80 || (b[0] == 0xE0 && (b[1] & 0xE0) == 0x80) ||    /* overlong? */
				(b[0] == 0xED && (b[1] & 0xE0) == 0xA0) ||    /* surrogate? */
				(b[0] == 0xEF && b[1] == 0xBF &&
				(b[2] & 0xFE) == 0xBE))                      /* U+FFFE or U+FFFF? */
			{
				return -70;
			}

			*token_len = 3;
			*token = (char *) &b[0];
			return 0;
		}
	}
	else
	{
		return -80;
	}


	if (buffer_len >= 4)
	{	
		if ((b[0] & 0xF8) == 0xf0) 
		{
			/* 
			 * 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx 
			 */
			if ((b[1] & 0xC0) != 0x80 || (b[2] & 0xC0) != 0x80 || (b[3] & 0xC0) != 0x80 || 
				(b[0] == 0xF0 && (b[1] & 0xF0) == 0x80) || (b[0] == 0xF4 && b[1] > 0x8F) || b[0] > 0xF4) /* > U+10FFFF? */
			{
				return -90;
			}

			*token_len = 4;
			*token = (char *) &b[0];
			return 0;
		} 
	}
	else
	{
		return -100;
	}


	return -110;

}

