#include <stdio.h>
#include <stddef.h>


int utils__utf_8__get_symbol (const void *buffer, size_t buffer_len, size_t token_index, char **token, size_t *token_len)
{

	size_t i;
	size_t len;
	size_t token_count;
	int end;
	unsigned char *b;
	unsigned char *t;


	if (buffer == NULL)
	{
		return -10;
	}

	if (buffer_len == 0)
	{
		return -20;
	}

	if (token == NULL)
	{
		return -30;
	}

	if (token_len == NULL)
	{
		return -40;
	}


	b = (unsigned char *) buffer;


	t = (unsigned char *) NULL;
	token_count = 0;
	end = 0;
	len = 0;
	i = 0;

	do
	{
		if (b[i] < 0x80)
		{
			/*
			 * 0xxxxxxx
			 */
			t = &b[i];
			i++;
			len = 1;
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

				t = &b[i];
				i += 2;
				len = 2;
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

				t = &b[i];
				i += 3;
				len = 3;
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

				t = &b[i];
				i += 4;
				len = 4;
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
		

		if (token_count > token_index)
		{
			return -170;
		}

		if (token_count == token_index)
		{
			end = 1;
		}		
		else
		{
			token_count++;

			if (i >= buffer_len)
			{
				end = 2;
			}			
		}

		

	}
	while (end == 0);



	if (end == 2)
	{
		return -180;  /* token_count is less than token_index */
	}

	if (end != 1)
	{
		return -190;
	}


	if (t == NULL)
	{
		return -200;
	}

	*token = (char *) t;
	*token_len = len;
	
	return 0;

}


