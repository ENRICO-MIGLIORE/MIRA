#include <stdio.h>
#include <stddef.h>


/*
 *  buffer = "   CIAO      ERIKA   "
 *  buffer = "CIAO ERIKA"
 */

int utils__libc__compact_spaces (char *buffer, size_t buffer_len, size_t *trimmed_buffer_len)
{

	int state;
	int end;
	size_t i;
	size_t j;
	size_t consecutive_blank_space_count;

	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == 0)
	{
		*trimmed_buffer_len = 0;
		return 0;
	}

	if (trimmed_buffer_len == NULL)
	{
		return -200;
	}

	i = 0;
	j = 0;
	consecutive_blank_space_count = 0;
	end = 0;
	state = 0;
	do
	{
		/*
		 * TABS are converted into spaces
		 */
		if (buffer[i] == '\t')
		{
			buffer[i] = ' ';
		}

		switch (state)
		{

		case 0:
			/*
			 *  Skip leading spaces
			 */
			if (buffer[i] != ' ')
			{
				buffer[0] = buffer[i];
				j = 1;
				state = 1;
			}
			break;

		case 1:
			if (buffer[i] == ' ')
			{
				consecutive_blank_space_count++;
				if (consecutive_blank_space_count < 2)
				{
					buffer[j] = buffer[i];
					j++;
				}
			}
			else
			{
				buffer[j] = buffer[i];
				j++;
				consecutive_blank_space_count = 0;
			}
			break;


		default:
			return -1000;
			break;
		}


		i++;
		if (i >= buffer_len)
		{
			end = 1;
		}
	}
	while (end == 0);


	if (consecutive_blank_space_count >= 1)
	{
		if (j > 0)
		{
			j--;
		}
		else
		{
			return -30;
		}
	}

	*trimmed_buffer_len = j;

	return 0;

}
