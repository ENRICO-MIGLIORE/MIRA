#include <stdio.h>
#include <stddef.h>

/*
 *  this function works only if escape_sequence_len = 2 and if the escape sequence has 2 different characters
 * 
 *  example
 *  
 *  original buffer = "hi there ; how are you?"
 * 
 *  buffer escaped = "hi there !s how are you?"
 * 
 *  escape_sequence =  "!s"
 *  substitute_character = ';'
 * 
 *  buffer escaped = "hi there; how are you?"
 */


int utils__libc__unescape_buffer (char* buffer, size_t buffer_len, const char* escape_sequence, size_t escape_sequence_len, char substitute_character, size_t* buffer_new_len)
{
	int state;
	size_t i;
	size_t j;
	size_t len;
	int done;
	char c_retained;
	int c_retained_flag;

	if (buffer == NULL)
	{
		return -100;
	}

	if (escape_sequence == NULL)
	{
		return -200;
	}

	if (escape_sequence_len != 2)
	{
		return -300;
	}

	if (buffer_new_len == NULL)
	{
		return -400;
	}

	if (buffer_len == 0)
	{
		*buffer_new_len = 0;
		return 0;
	}

	if (buffer_len == 1)
	{
		*buffer_new_len = 1;
		return 0;
	}

	if (escape_sequence[0] == escape_sequence[1])
	{
		return -500;
	}


	c_retained = '\0';
	c_retained_flag = 0;
	len = 0;
	i = 0;
	j = 0;
	done = 0;
	state = 0;
	do
	{	

		switch (state)
		{

		case 0:
			if (buffer[i] == escape_sequence[0])
			{
				c_retained = escape_sequence[0];
				c_retained_flag = 1;
				state = 1;
				break;
			}

			buffer[j] = buffer[i];
			j++;
			if (j > buffer_len)
			{
				return -1000;
			}
			break;

		case 1:
			if (buffer[i] == escape_sequence[0])
			{
				buffer[j] = escape_sequence[0];
				j++;
				if (j > buffer_len)
				{
					return -2000;
				}
				c_retained_flag = 0; 
				state = 0;
				break;
			}

			if (buffer[i] == escape_sequence[1])
			{
				buffer[j] = substitute_character;  /* replace */
				j++;
				if (j > buffer_len)
				{
					return -3000;
				}
				c_retained_flag = 0;
				state = 0;
				break;
			}

			if (c_retained_flag != 1)
			{
				return -1200;         /* runtime check */
			}

			if (j > buffer_len + 1)
			{
				return -4000;
			}

			buffer[j] = c_retained;   /* false positive */
			j++;
			buffer[j] = buffer[i];
			j++;
			c_retained_flag = 0;
			state = 0;			
			break;

		default:
			return -5000;
			break;

		}

		i++;
		if (i >= buffer_len)
		{
			done = 1;
		}

	} 
	while (done == 0);


	if (c_retained_flag == 1)
	{
		if (j > buffer_len)
		{
			return -10000;
		}

		buffer[j] = c_retained;
		j++;
	}

	*buffer_new_len = j;

	return 0;
}



