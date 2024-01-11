#include <stdio.h>
#include <stddef.h>

/*
 *  buffer = "&CIAO   ERIKA   &"
 *  buffer = "CIAO   ERIKA   "
 */

int utils__libc__count_trimmeable_characters (char *buffer, size_t buffer_len, size_t *trimmeable_space_count, char c)
{
	int state;
	int end;
	size_t i;
	size_t trailing_characters_count;
	size_t leading_characters_count;

	if (buffer == NULL)
	{
		return -100;
	}

	if (trimmeable_space_count == NULL)
	{
		return -200;
	}

	if (buffer_len == 0)
	{
		*trimmeable_space_count = 0;
		return 0;
	}

	leading_characters_count = 0;
	trailing_characters_count = 0;
	state = 0;
	i = 0;
	end = 0;
	
	/*
	 *  "     ABC    "
	 */
	do 
	{
		switch (state)
		{
		case 0:

			if (buffer[i] == c)
			{
				leading_characters_count++;
			}
			else
			{
				trailing_characters_count = 0;
				state = 1;
			}
			break;

		case 1:
			if (buffer[i] == c)
			{
				trailing_characters_count++;
			}
			else
			{
				trailing_characters_count = 0;
			}
			break;

		default:
			return -300;
			break;
		}


		i++;
		if (i >= buffer_len)
		{
			end = 1;
		}
	}
	while (end == 0);

	*trimmeable_space_count = trailing_characters_count + leading_characters_count;

	return 0;
}




