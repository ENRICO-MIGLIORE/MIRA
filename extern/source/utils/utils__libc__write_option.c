#include "utils__libc.h"


int utils__libc__write_option (int* data, const char* value, size_t value_len, const char* option_1, size_t option_1_len, const char* option_2, size_t option_2_len)
{

	size_t i;
	char ch_opt;
	char* opt;
	char ch_val;
	char *val;
	int done;


	if (data == NULL)
	{
		return -100;
	}

	if (value == NULL)
	{
		return -200;
	}

	if (option_1 == NULL)
	{
		return -300;
	}

	if (option_2 == NULL)
	{
		return -400;
	}

	if (value_len == 0)
	{
		return -500;
	}	

	if (option_1_len == 0)
	{
		return -600;
	}

	if (option_2_len == 0)
	{
		return -700;
	}


	val = (char*) value;

	
	
	if (value_len == option_1_len)
	{
		done = 0;
		
		opt = (char*) option_1;

		for (i = 0; (i < value_len) && (done == 0); i++)
		{

			ch_val = (char)toupper((int)(*val));

			ch_opt = (char)toupper((int)(*opt));

			if (ch_val == ch_opt)
			{
				val++;
				opt++;
			}
			else
			{
				done = 1;
			}
		}

		if (done == 0)
		{
			*data = 1;
			return 0;
		}
	}


	

	if (value_len == option_2_len)
	{
		done = 0;

		opt = (char*) option_2;

		for (i = 0; (i < value_len) && (done == 0); i++)
		{

			ch_val = (char)toupper((int)(*val));

			ch_opt = (char)toupper((int)(*opt));

			if (ch_val == ch_opt)
			{
				val++;
				opt++;
			}
			else
			{
				done = 1;
			}
		}

		if (done == 0)
		{
			*data = 2;
			return 0;
		}
	}


	return -1000;
}