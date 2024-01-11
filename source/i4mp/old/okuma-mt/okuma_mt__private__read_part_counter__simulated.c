#include "okuma_mt__private.h"


int okuma_mt__private__read_part_counter__simulated (int md)
{

	long c;
	size_t part_counter_real;


	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}
	

	//om->machine[md].part_counter_valid = 0;

	//if (om->machine[md].part_counter_simulated_valid != 1)
	//{
	//	return -100;
	//}

	//om->machine[md].part_counter = om->machine[md].part_counter_simulated;
	//sprintf(om->machine[md].part_counter_utf_8, "%zu", om->machine[md].part_counter);
	//om->machine[md].part_counter_utf_8_len = strlen(om->machine[md].part_counter_utf_8);

	//om->machine[md].part_counter_valid = 1;




	if (om->machine[md].data_stream_valid == 1)
	{

		c = 100;

		part_counter_real = (size_t) c;

		om->machine[md].part_counter = part_counter_real;
		sprintf(om->machine[md].part_counter_utf_8, "%zu", part_counter_real);
		om->machine[md].part_counter_utf_8_len = strlen(om->machine[md].part_counter_utf_8);
		om->machine[md].part_counter_valid = 1;

		return 0;
	}


	return 0;

}


int okuma_mt__private__get_inner_xml (const char* xml_document, size_t xml_document_len,  const char* name, size_t name_size, char *value, size_t value_size, size_t* value_size_len)
{
	size_t i;
	size_t j;
	size_t k;
	size_t r;
	int done;
	int state;

	
	i = 0;
	j = 0;
	k = 0;
	r = 0;
	done = 0;
	state = 0;
	do
	{
		switch (state)
		{
		    case 0:
			if (xml_document[i] == '<')
			{
				state = 0;
			}
		    break;

			case 1:
				if (xml_document[i] == name[j])
				{
					k++;
					if (k >= xml_document_len)
					{
						state = 2;
					}
				}
				else
				{
					k = 0;
					state = 0;
				}
			break;

			case 2:
				if (xml_document[i] == ' ')
				{
					state = 3;
				}
				else if (xml_document[i] == '>')
				{
					r = 0;
					state = 5;
				}
				else
				{
					k = 0;
					state = 0;
				}
				break;

			case 3:
				if (xml_document[i] == '>')
				{
					state = 4;
				}
				else
				{
					k = 0;
					state = 0;
				}
			break;

			case 4:
				if (xml_document[i] == '>')
				{
					r = 0;
					state = 5;
				}
				else
				{
					k = 0;
					state = 0;
				}
			break;

			case 5:
				if (xml_document[i] == '<')
				{
					state = 6;
				}
				else
				{
					value[r] = xml_document[i];
					r++;
				}
				break;

			case 6:
				if (xml_document[i] == '/')
				{
					state = 7;
				}
				else
				{
					k = 0;
					state = 0;
				}
				break;

			case 7:
				if (xml_document[i] == '/')
				{
					state = 6;
				}
				else
				{
					value[r] = xml_document[i];
					r++;
				}
				break;

		}

		i++;
		if (i >= xml_document_len)
		{
			done = 2;
		}
	}
	while (done == 0);


	if (done == 1)
	{

	}

	return 0;
}