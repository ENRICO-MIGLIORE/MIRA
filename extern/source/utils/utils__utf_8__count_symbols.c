#include <stdio.h>
#include <stddef.h>


int utils__utf_8__count_symbols (const void *buffer, size_t buffer_len, size_t *token_count)
{

	unsigned char *b;
	int end;
	size_t i;
	size_t count;

	if (buffer == NULL)
	{
		return -10;
	}

	if (buffer_len == 0)
	{
		return -20;
	}

	if (token_count == NULL)
	{
		return -30;
	}



	b = (unsigned char *) buffer;

	count = 0;
	end = 0;
	i = 0;

	do
	{
		if (b[i] < 0x80)
		{
			/*
			 * 0xxxxxxx
			 */
			i++;
		}
		else if ((b[i] & 0xE0) == 0xC0) 
		{
			if (i + 1 < buffer_len)
			{
				/* 
				 * 110XXXXx 10xxxxxx
				 */
				if ((b[i + 1] & 0xC0) != 0x80 ||
					(b[1] & 0xFE) == 0xC0)                        /* overlong? */
				{
					return -100;
				}
				else
				{
					i += 2;
				}
			}
			else
			{
				return -110;
			}
		} 
		else if ((b[i] & 0xF0) == 0xE0) 
		{
			if (i + 2 < buffer_len)
			{
				/* 
				 * 1110XXXX 10Xxxxxx 10xxxxxx
				 */
				if ((b[i + 1] & 0xC0) != 0x80 || (b[i + 2] & 0xC0) != 0x80 || (b[i] == 0xE0 && (b[i + 1] & 0xE0) == 0x80) ||    /* overlong? */
					(b[i] == 0xED && (b[i + 1] & 0xE0) == 0xA0) ||    /* surrogate? */
					(b[i] == 0xEF && b[i + 1] == 0xBF &&
					(b[i + 2] & 0xFE) == 0xBE))                      /* U+FFFE or U+FFFF? */
				{
					return -120;
				}
				else
				{
					i += 3;
				}
			}
			else
			{
				return -130;
			}
		} 
		else if ((b[i] & 0xF8) == 0xf0) 
		{
			if (i + 3 < buffer_len)
			{
				/* 
				 * 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx 
				 */
				if ((b[i + 1] & 0xC0) != 0x80 || (b[i + 2] & 0xC0) != 0x80 || (b[i + 3] & 0xC0) != 0x80 || 
					(b[i] == 0xF0 && (b[i + 1] & 0xF0) == 0x80) || (b[i] == 0xF4 && b[i + 1] > 0x8F) || b[i] > 0xF4) /* > U+10FFFF? */
				{
					return -140;
				}
				else
				{
					i += 4;
				}
			}
			else
			{
				return -150;
			}
		} 
		else
		{
			return -160;
		}

		count++;
		if (i >= buffer_len)
		{
			end = 1;
		}

	}
	while (end == 0);

	*token_count = count;

	return 0;

}



