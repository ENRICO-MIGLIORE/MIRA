#include <stdio.h>
#include <string.h>
#include <stddef.h>


/*
 * This function removes all leading and trailing spaces from a set of tokens by shifting the tokens' pointer and by trimming their length
 *
 *
 * 	char* tokens[16];
 *	size_t tokens_len[16];
 *	size_t tokens_max;
 *
 *
 *
 * 	tokens[0] = " ABC ";
 *	tokens_len[0] = strlen(tokens[0]);
 *
 *	tokens[1] = " EFG";
 *	tokens_len[1] = strlen(tokens[1]);
 *
 *	tokens[2] = "HIL ";
 *	tokens_len[2] = strlen(tokens[2]);
 *
 *	tokens[3] = " ";
 *	tokens_len[3] = strlen(tokens[3]);
 *
 *  tokens[4] = " Z";
 *	tokens_len[4] = strlen(tokens[4]);
 *
 *	tokens[5] = " Hello World! ";
 *	tokens_len[5] = strlen(tokens[5]);
 *
 *	tokens[6] = "";
 *	tokens_len[6] = strlen(tokens[6]);
 *
 *  tokens_max = 7;
 *  rc = utils__libc__trim_tokens(tokens, tokens_len, tokens_max, ' ');
 *
 */

int utils__libc__trim_tokens (char** tokens, size_t* tokens_len, size_t tokens_max, char c)
{


	size_t i;
	size_t j;
	size_t k;
	size_t r;
	size_t s;
	int done;
	char* token;
	char* token_start;
	size_t token_len;

	if (tokens_max == 0)
	{
		return 0;
	}

	if (tokens == NULL)
	{
		return -200;
	}

	if (tokens_len == NULL)
	{
		return -300;
	}


	for (i = 0; i < tokens_max; i++)
	{

		token = tokens[i];
		token_len = tokens_len[i];

		if (token_len > 0)
		{
			
			token_start = NULL;
			r = 0;
			done = 0;
			for (j = 0; (j < token_len) && (done == 0); j++)
			{
				if (token[j] != c)
				{
					token_start = &token[j];
					done = 1;
				}
				else
				{
					r++;
				}
			}

			if (token_start == NULL)
			{
				tokens_len[i] = 0;
			}
			else
			{
				s = 0;
				done = 0;
				for (k = token_len - 1; (k > 0) && (done == 0); k--)
				{
					if (token[k] != c)
					{
						done = 1;
					}
					else
					{
						s++;
					}
				}

				if (token_len < r + s)
				{
					return -1000;
				}

				tokens[i] = token_start;
				tokens_len[i] = token_len - r - s;
			}
		}
	}

	return 0;

}

//int utils__libc__trim_tokens (char** tokens, size_t* tokens_len, size_t tokens_max, char c)
//{
//
//
//	size_t i;
//	size_t j;
//	size_t len;	
//	int done;
//	int state;
//	char* token;
//	char* token_start;
//	size_t token_len;
//
//	if (tokens_max == 0)
//	{
//		return -100;
//	}
//
//	if (tokens == NULL)
//	{
//		return -200;
//	}
//
//	if (tokens_len == NULL)
//	{
//		return -300;
//	}
//
//
//	for (i = 0; i < tokens_max; i++)
//	{
//
//		token = tokens[i];
//		len = tokens_len[i];
//		token_len = 0;
//		token_start = NULL;
//		done = 0;
//		state = 0;
//
//		for (j = 0; (j < len) && (done == 0); j++)
//		{
//			switch (state)
//			{
//
//			case 0:
//				if (token[j] != c)
//				{
//					token_start = &token[j];
//					token_len = 1;
//					state = 1;
//				}
//				break;
//
//			case 1:
//				if (token[j] == c)
//				{
//					done = 1;
//				}
//				else
//				{
//					token_len++;
//				}
//				break;
//
//			default:
//				return -5000;
//				break;
//
//			}
//		}
//
//		if (token_len == 0)
//		{
//			tokens_len[i] = tokens[i];
//		}
//		else
//		{
//			tokens[i] = token_start;			
//		}
//
//		tokens_len[i] = token_len;
//	}
//
//	return 0;
//
//}
//
//
