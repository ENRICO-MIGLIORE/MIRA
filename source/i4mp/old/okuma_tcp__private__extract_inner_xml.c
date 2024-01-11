#include "okuma_mt__private.h"



int okuma_mt__private__extract_inner_xml (const char* xml_document, size_t xml_document_len,  const char* name, size_t name_len, char *value, size_t value_size, size_t* value_len)
{
	size_t i;
	size_t j;
	size_t k;
	int done;
	int state;


	if (xml_document == NULL)
	{
		return -100;
	}

	if (xml_document_len == 0)
	{
		return -200;
	}

	if (name == NULL)
	{
		return -300;
	}

	if (name_len == 0)
	{
		return -400;
	}

	if (value == NULL)
	{
		return -500;
	}

	if (value_size == 0)
	{
		return -600;
	}

	if (value_len == NULL)
	{
		return -700;
	}

	
	i = 0;
	j = 0;
	k = 0;
	done = 0;
	state = 0;
	do
	{
		switch (state)
		{
		    case 0:
			if (xml_document[i] == '<')
			{
				state = 1;
			}
		    break;

			case 1:
				if (xml_document[i] == name[j])
				{
					j++;
					if (j >= name_len)
					{
						state = 2;
					}
				}
				else
				{
					j = 0;
					state = 0;
				}
			break;

			case 2:
				if (xml_document[i] == ' ')
				{
					state = 3;
				}
				else
				{
					j = 0;
					state = 0;
				}
				break;

			case 3:
				if (xml_document[i] == '>')
				{
					k = 0;
					state = 4;
				}
			break;

			case 4:
				if (xml_document[i] == '<')
				{
					/* 
					 * if (k + 1 > value_size) allows us to safely terminate value 
					 */
					value[k] = '\0';
					j = 0;
					state = 5;
				}
				else
				{
					value[k] = xml_document[i];
					k++;
					if (k + 1 > value_size)
					{
						return -2000;
					}
				}
			break;

			case 5:
				if (xml_document[i] == '/')
				{
					state = 6;
				}
				else
				{
					return -3000;
				}
				break;


			case 6:
				if (xml_document[i] == name[j])
				{
					j++;
					if (j >= name_len)
					{
						state = 7;
					}
				}
				else
				{
					return -4000;
				}
				break;

			case 7:
				if (xml_document[i] == '>')
				{
					done = 1;
				}
				else
				{
					return -5000;
				}
				break;

			default:
				return -6000;
				break;

		}

		if (done == 0)
		{
			i++;
			if (i >= xml_document_len)
			{
				done = 2;
			}
		}

	}
	while (done == 0);


	if (done != 1)
	{
		return -10000;
	}

	*value_len = k;

	return 0;
}