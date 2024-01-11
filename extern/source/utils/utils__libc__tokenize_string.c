#include <stdio.h>
#include <string.h>
#include <stddef.h>


 /*
  *
  *   intput:
  * 
  *       buffer = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao";
  *	      
  *       seps = "+", "@@@"
  *       
  *
  *
  * 
  *   output:
  * 
  *       token_count = 4
  *       
  *       tokens[0] = "CIAO "
  *       tokens[1] = " com"
  *       tokens[2] = "e stai * io bene "
  *       tokens[3] = " grazie  ciao ?? ciao"
  *       
  *       tokens_len[0] = 4
  *       tokens_len[1] = 4
  *       tokens_len[2] = 17
  *       tokens_len[3] = 21
  *
  */


/*
 * 
 *  buffer = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao ";
 *	buffer = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +";
 *	buffer = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A";
 *	buffer = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A ";
 *	buffer = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@@";
 *	buffer = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@";
 *	buffer = "@@CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@";
 *	buffer = "++CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @";
 *	buffer = "+@+CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @+";
 *	buffer = "@@+@+++CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @++";
 *  buffer_2 = "@@";
 *	buffer_2 = "";
 *	buffer_2 = "+";
 *	buffer_2 = "++";
 *	buffer_2 = "+A+";
 *  buffer_2 = "+@@@++@@@+++@@@"; 
 *	buffer_len = strlen(buffer_2);
 *	seps_len[0] = strlen(seps[0]);
 *	seps_len[1] = strlen(seps[1]);
 *	seps_count = sizeof(seps) / sizeof(char*);
 *	tokens_max = sizeof(tokens) / sizeof(char*);
 */

int utils__libc__tokenize_string (const char* buffer, size_t buffer_len, const char** seps, size_t* seps_len, size_t seps_count, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count)
{


	size_t i;
	size_t j;
	int token_len;
	int chunk_len;
	size_t chunk_len_2;
	size_t token_cnt;
	char* b;
	int found;
	int rc;
	int done;
	int flag;

	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == 0)
	{
		tokens[0] = "";
		tokens_len[0] = 0;
		*token_count = 1;
		return 0;
	}

	if (seps_count == 0)
	{
		return -300;
	}

	if (seps_len == NULL)
	{
		return -400;
	}

	if (tokens_max == 0)
	{
		return -500;
	}

	if (tokens == NULL)
	{
		return -600;
	}

	if (tokens_len == NULL)
	{
		return -700;
	}

	if (token_count == NULL)
	{
		return -800;
	}


	flag = 0;
	token_cnt = 0;
	b = (char *) &buffer[0];
	done = 0;
	i = 0;

	do
	{

		found = 0;

		for (j = 0; (j < seps_count) && (found == 0); j++)
		{

			if (seps_len[j] == 0)
			{
				continue;
			}

			if (seps[j] == NULL)
			{
				continue;
			}

			if (buffer_len - i >= seps_len[j])
			{			
				
				rc = memcmp(&buffer[i], seps[j], seps_len[j]);

				if (rc == 0)
				{
					token_len = (int)(&buffer[i] - b);

					if (token_len < 0)
					{
						return -100;
					}

					if (token_len > 0)
					{
						if (token_cnt > tokens_max)
						{
							return -200;
						}

						tokens[token_cnt] = b;
						tokens_len[token_cnt] = (size_t)token_len;
						token_cnt++;

						b = (char*)(&buffer[i] + seps_len[j]);

						i += seps_len[j];
						if (i >= buffer_len)
						{
							done = 1;
						}
						
						flag = 1;
						found = 1;
					}
					else
					{
						b = (char*)(&buffer[i] + seps_len[j]);

						i += seps_len[j];
						if (i >= buffer_len)
						{
							done = 1;
						}

						flag = 1;
					}									
				}
			}
		}

		if (flag == 0)
		{
			if (done == 0)
			{
				i++;
				if (i >= buffer_len)
				{
					done = 2;
				}
			}
		}
		else
		{
			flag = 0;
		}
	} 
	while (done == 0);



	/*
	 * last token
	 */
	chunk_len = (int) (b - &buffer[0]);
	if (chunk_len < 0)
	{
		return -300;
	}

	chunk_len_2 = (size_t)chunk_len;
	if (chunk_len_2 < buffer_len)
	{
		if (token_cnt > tokens_max)
		{
			return -400;
		}

		tokens[token_cnt] = b;
		tokens_len[token_cnt] = buffer_len - chunk_len_2;
		token_cnt++;
	}


	*token_count = token_cnt;

	return 0;


}





