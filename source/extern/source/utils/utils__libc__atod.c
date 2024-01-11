#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <errno.h>


/*
 * we use atof() under the hood
 * 
 * atof() errors from ibm site:
 * 
 * if the atof() conversion cannot be performed, a value of 0 is returned, and the errno global variable is set to indicate the error.
 *
 * if the atof() conversion causes an overflow (that is, the value is outside the range of representable values), +/- HUGE_VAL is returned
 * with the sign indicating the direction of the overflow, and the errno global variable is set to ERANGE. 
 * 
 * 
 * valid floating point arguments for atof():   [whitespace] [- | +] [digits] [.digits] [ {e | E }[- | +]digits]
 * 
 */

int utils__libc__atod (const char *buffer, size_t buffer_len, double *number)
{

	double d;
	size_t i;
	char buf[64];
	int state;



	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == 0)
	{
		return -200;
	}

	if (number == NULL)
	{
		return -300;
	}

	if (buffer_len + 1 > sizeof(buf))
	{
		return -400;
	}

	//state = 0;
	//for (i = 0; i < buffer_len; i++)
	//{
	//	switch (state)
	//	{
	//	case 0:
	//		if (buffer[i] == ' ')
	//		{
	//			;
	//		}
	//		else if ((buffer[i] == '+') || (buffer[i] == '-'))
	//		{
	//			state = 1;
	//		}
	//		else if ((buffer[i] >= '0') && (buffer[i] <= '9'))
	//		{
	//			state = 1;
	//		}
	//		else if (buffer[i] == '.')
	//		{
	//			state = 2;
	//		}
	//		else
	//		{
	//			return -500;
	//		}
	//		break;

	//	case 1:
	//		if ((buffer[i] >= '0') && (buffer[i] <= '9'))
	//		{
	//			;
	//		}
	//		else if (buffer[i] == '.')
	//		{
	//			state = 2;
	//		}
	//		break;

	//	case 2:
	//		if ((buffer[i] >= '0') && (buffer[i] <= '9'))
	//		{
	//			;
	//		}
	//		else if ((buffer[i] == 'e') || (buffer[i] == 'E'))
	//		{
	//			state = 3;
	//		}
	//		break;

	//	case 3:
	//		if ((buffer[i] == '+') || (buffer[i] == '-'))
	//		{
	//			;
	//		}
	//		else if ((buffer[i] >= '0') && (buffer[i] <= '9'))
	//		{
	//			state = 1;
	//		}
	//		break;
	//	}
	//}

	memcpy(buf, buffer, buffer_len);
	buf[buffer_len] = '\0';

	//strcpy(buf, "UNAVAILABLE");
	

	d = atof(buf);

	if (errno == ERANGE)
	{
		return -700;
	}


	*number = d;

	return 0;

}
