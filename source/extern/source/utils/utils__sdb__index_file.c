#include "utils__sdb.h"


#define UTF_8_BOM_SIZE                         3


#define START                                  0
#define START__COMMENT                        10
#define START__PARENT_NAME                    20
#define START__LF                             30
#define END_1                                100
#define END_2                                110
#define END_3                                120
#define COLLECT_NAME                         200
#define DETECT_ENCODING_1                    300
#define DETECT_ENCODING_2                    310
#define COLLECT_VALUE                        400
#define COLLECT_VALUE__LF                    410
#define COLLECT_VALUE__LINGER                420
#define DETECT_LANGUAGE__LINGER              500
#define DETECT_LANGUAGE__LINGER__LF          510
#define FINALE                              1000


                           
int utils__sdb__index_file (const char *file_name, size_t *record_count, size_t *record_index, size_t record_index_max)
{
	FILE *f;
	int state;	
    size_t bytes_read;
	size_t residual_size;
	unsigned char buffer_local[1024];   /* sizeof(buffer_local) must be greater than 16 */
	size_t i;
	int end;
	int end_internal;
	size_t offset;
	unsigned char c;
	unsigned char c_retained;
	int c_retained_flag;
	int record_started;
	size_t rec_count;
	const char *dummy_end_of_file;
	int parent_name_flag;
	int end_of_file_reached;
	size_t crlf_count;
	
	int square_bracket_pending;	
	int finale_pending;
	size_t parsed_byte;
	


	
	if (file_name == NULL)
	{
		return -30;
	}

	

	f = fopen ((const char *) file_name, "rb");
	if (f == NULL)
	{
		return -70;
	}

	
	c = 0x00;             /* keep the compiler happy */
	c_retained = 0x00;	  /* keep the compiler happy */
	c_retained_flag = 0;
	square_bracket_pending = 0;
	finale_pending = 0;	
	end_of_file_reached = 0;
	parent_name_flag = 0;
	dummy_end_of_file = "\r\n\r\n\r\n";
	rec_count = 0;
	record_started = 0;
	crlf_count = 0;

	offset = 0;
	end = 0;
	state = START;

	
	bytes_read = fread(buffer_local, 1, UTF_8_BOM_SIZE, f);
	
	if (bytes_read != UTF_8_BOM_SIZE)
	{
		fclose(f);
		return -80;
	}

	if ((buffer_local[0] == 0xEF) && (buffer_local[1] == 0xBB) && (buffer_local[2] == 0xBF))
	{
		parsed_byte = UTF_8_BOM_SIZE;
	}
	else
	{
		offset = 3;
		parsed_byte = 0;
	}
	

	/*
	 * Optimization: we subtract 1 in order not to do this operation at every loop cycle:  parsed_byte - 1
	 */
	
	 

	do 
	{

		end_internal = 0;


		if (end_of_file_reached == 0)
		{
					
			residual_size = sizeof(buffer_local) - offset;

			bytes_read = fread((char *) &buffer_local[offset], 1, residual_size, f);

			if (offset > 0)
			{
				bytes_read += offset;
				offset = 0;
			}
		}

		if (bytes_read == 0)
		{

			end_of_file_reached = 1;

			//if (rec_count == record_number - 1)
			//{				
				parent_name_flag = 0;
				crlf_count++;
				if (crlf_count <= 6)
				{
					c_retained_flag = 1;
					c_retained = dummy_end_of_file[crlf_count - 1];
				}
				else
				{
					if (state == START)
					{
						end = 1;
						 continue;
						 
					}
					else
					{
					    fclose(f);       
					    return -200;
					}
				}
			//}
			
		}

		i = 0;

		do
		{
			if (c_retained_flag == 1)
			{
				c_retained_flag = 0;
				c = c_retained;					
			}
			else
			{		
				c = buffer_local[i];
				parsed_byte++;
			}



			switch (state)
			{

			case START:

				if (c == ' ')
				{		
					break;   
				}

				if (c == '#')
				{
					
					state = START__COMMENT;
					break;
				}

				if (record_started == 0)
				{
				
					if (c == '\r')
					{
						state = START__LF;
						break;
					}

					if (c == '\n')
					{
						c_retained = c;
						c_retained_flag = 1;
						state = START__LF;
						break;
					}

					if (c == '[')
					{						
						parent_name_flag = 0;
						
						state = START__PARENT_NAME;
						break;
					}

					record_started = 1;					
					record_index[rec_count] = parsed_byte - 1;
				}
				else
				{
				    if (c == '\r')
					{
						state = END_1;
						break;
					}

					if (c == '\n')
					{
						c_retained = c;
						c_retained_flag = 1;
						state = END_1;
						break;
					}

					if (c == '[')
					{
						c_retained = c;
						c_retained_flag = 1;
						square_bracket_pending = 1;
						
						state = FINALE;
						break;
					}
				}

			    if (rec_count > record_index_max)
				{
					fclose(f);
					return -210;
				}

				
			

				state = COLLECT_NAME;
				break;

			case START__COMMENT:
				if (c == '\r')
				{
					state = START__LF;
					break;
				}

				if (c == '\n')
				{
					c_retained = c;
					c_retained_flag = 1;
					state = START__LF;
					break;
				}
				break;

			case START__PARENT_NAME:
				if (c == ']')
				{			
					parent_name_flag = 1;
					state = START;
				}

				
				break;

			case START__LF:
				if (c != '\n')
				{					
					fclose(f);
					return -520;
				}

				state = START;
				break;

			case END_1:
				if (c != '\n')
				{					
					fclose(f);
					return -600;
				}
				state = END_2;
				break;

			case END_2:

		
				if (parent_name_flag == 1)
				{
					c_retained = c;
					c_retained_flag = 1;
					state = START;
					break;
				}


				if (c == '\r')
				{
					state = END_3;
					break;
				}

				if (c == '\n')
				{
					c_retained = c;
					c_retained_flag = 1;
					state = END_3;
					break;
				}

				if (c == ' ')
				{
					break; //carmelo
				}


				c_retained = c;
				c_retained_flag = 1;

				state = START;
				break;

			case END_3:
				if (c != '\n')
				{					
					fclose(f);
					return -700;
				}

				c_retained = c;
				c_retained_flag = 1;

				finale_pending = 1;

				state = FINALE;
				break;

			case COLLECT_NAME:
				if (c == '=')
				{				
					state = COLLECT_VALUE;
				}				
				break;

			case COLLECT_VALUE:
				if (c == '\r')
				{
					state = COLLECT_VALUE__LF;
					break;
				}

				if (c == '\n')
				{
					c_retained = c;
					c_retained_flag = 1;
					state = COLLECT_VALUE__LF;
					break;
				}
		
				break;

			case COLLECT_VALUE__LF:
				if (c != '\n')
				{					
					fclose(f);
					return -1100;
				}
				
				state = START;
				break;

			case FINALE:
				rec_count++;

				if (rec_count > record_index_max)
				{
					fclose(f);
					return -1300;
				}

				if (rec_count == record_index_max)
				{
					end = 1;
					break;
				}

				c = 0x00;             /* keep the compiler happy */
				c_retained = 0x00;	  /* keep the compiler happy */
				c_retained_flag = 0;		
				parent_name_flag = 0;
					
				record_started = 0;			

				if (finale_pending == 1)
				{
					finale_pending = 0;
				}
				else if (square_bracket_pending == 1)
				{
					square_bracket_pending = 0;
					c_retained = '[';
					c_retained_flag = 1;
				}

				state = START;	
				break;

			default:
				fclose(f);
				return -5000;
				break;
			}


			if (end == 0)
			{
			

				if (c_retained_flag == 0)
				{
					
					i++;
					if (i >= bytes_read)
					{
						end_internal = 1;
					}
				}
			}
			else
			{
				end_internal = 1;
			}
		}
		while (end_internal == 0);

	}
	while (end == 0);

	fclose(f);

	*record_count = rec_count;

	return 0;

}











