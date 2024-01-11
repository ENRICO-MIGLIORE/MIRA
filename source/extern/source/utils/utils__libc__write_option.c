#include <stdio.h>
#include <string.h>
#include <ctype.h>


int utils__libc__write_option (char* buffer, size_t buffer_size, const char* value, size_t value_len, const char* option_1, size_t option_1_len, const char* option_2, size_t option_2_len)
{

	size_t i;
	int rc;
	char o_1;
	char* op_1;
	char o_2;
	char* op_2;
	char v;
	char *vp;
	int done_1;
	int done_2;


	if (buffer == NULL)
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



	vp = (char*) value;
	done_1 = 0;
	done_2 = 0;
	
	if (value_len == option_1_len)
	{
		
		op_1 = (char*)option_1;

		for (i = 0; (i < value_len) && (done_1 == 0); i++)
		{

			v = (char)toupper((int)(*vp));

			o_1 = (char)toupper((int)(*op_1));

			if (v == o_1)
			{
				vp++;
				op_1++;
			}
			else
			{
				done_1 = 1;
			}
		}

		if (done_1 == 0)
		{
			done_1 = 2;
		}
	}

	if (value_len == option_2_len)
	{
		op_2 = (char*) option_2;

		for (i = 0; (i < value_len) && (done_2 == 0); i++)
		{

			v = (char)toupper((int)(*vp));

			o_2 = (char)toupper((int)(*op_2));

			if (v == o_2)
			{
				vp++;
				op_2++;
			}
			else
			{
				done_2 = 1;
			}
		}

		if (done_2 == 0)
		{
			done_2 = 2;
		}
	}


	rc = -5000;

	if (done_1 == 2)
	{
		if (buffer_size > option_1_len)
		{
			memcpy(buffer, option_1, option_1_len);
			buffer[option_1_len] = '\0';
			rc = 0;
		}
		else
		{
			rc = -6000;
		}		
	}
	else if (done_2 == 2)
	{
		if (buffer_size > option_2_len)
		{
			memcpy(buffer, option_2, option_2_len);
			buffer[option_2_len] = '\0';
			rc = 0;
		}
		else
		{
			rc = -7000;
		}
	}


	return rc;
}