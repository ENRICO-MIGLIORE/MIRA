#include <stdio.h>
#include <stddef.h>


int utils__libc__print_tokens (char** tokens, size_t* tokens_len, size_t token_count)
{

	size_t i;


	if (token_count == 0)
	{
		return -100;
	}

	if (tokens == NULL)
	{
		return -200;
	}

	if (tokens_len == NULL)
	{
		return -300;
	}

	for (i = 0; i < token_count; i++)
	{
		if (tokens[i] == NULL)
		{
			return -400;
		}
	}

	for (i = 0; i < token_count; i++)
	{		
		printf("\"%.*s\"\n", (int) tokens_len[i], tokens[i]);
	}

	return 0;

}


