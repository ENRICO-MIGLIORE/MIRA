//#include "okuma_mt__private.h"
//#include <okuma_mt__platform__private.h>




int agent__siemens_open62541__platform__private__start (void)
{

#if 0
	WSADATA wsaData;
	int rc;
	size_t size;
	size_t len;
	size_t j;
	size_t k;
	int i;
	int done;
	int state;
	char* buffer;
	char* buffer_2;
	okuma_mt__platform__machine_t * platform__machine;

	/*
	 * initialize windows' winsock subsystem
	 */
	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc != 0)
	{
		/*
		 * printf("WSAStartup failed with error: %d\n", rc);
		 */
		return -100;
	}


	for (i = 0; i < om->machine_count; i++)
	{
		size = (sizeof(okuma_mt__platform__machine_t));

		platform__machine = (okuma_mt__platform__machine_t*) malloc(size);

		if (platform__machine == NULL)
		{
			return -(200 + (10 * i));
		}
		memset(platform__machine, '\0', size);

		size = om->machine[i].config.tcp_client_receive_buffer_size;


		/*
		 * double buffering due to threads' critical sections
		 */
		buffer = (char*)malloc(size);
		if (buffer == NULL)
		{
			return -(2000 + (10 * i));
		}
		om->machine[i].receive_buffer = buffer;
		om->machine[i].receive_buffer_size = size;
		om->machine[i].receive_buffer_len = 0;


		buffer_2 = (char*)malloc(size);
		if (buffer_2 == NULL)
		{
			return -(3000 + (10 * i));
		}
		om->machine[i].receive_buffer_2 = buffer_2;
		om->machine[i].receive_buffer_size_2 = size;
		om->machine[i].receive_buffer_len_2 = 0;


		/*
		 * Convert 2-byte string \r to 1-byte char '\r' and \n to '\n'
		 */
		len = strlen(om->machine[i].config.tcp_client_send_string) + 1;  /* +1 is needed because we copy the string terminator as well */

		done = 0;
		state = 0;
		j = 0;
		k = 0;
		do
		{
			switch (state)
			{

			case 0:
				if (om->machine[i].config.tcp_client_send_string[j] == '\\')
				{
					state = 1;
				}
				else
				{
					om->machine[i].config.tcp_client_send_string[k] = om->machine[i].config.tcp_client_send_string[j];
					k++;
				}
				break;

			case 1:
				if (om->machine[i].config.tcp_client_send_string[j] == 'r')
				{
					om->machine[i].config.tcp_client_send_string[k] = '\r';
					k++;
					state = 0;
				}
				else if (om->machine[i].config.tcp_client_send_string[j] == 'n')
				{
					om->machine[i].config.tcp_client_send_string[k] = '\n';
					k++;
					state = 0;
				}
				else
				{
					return -10000;
				}
				break;

			default:
				return -20000;
				break;

			}

			j++;
			if (j >= len)
			{
				done = 1;
			}

		} 
		while (done == 0);


		om->machine[i].send_buffer = om->machine[i].config.tcp_client_send_string;
		om->machine[i].send_buffer_len = strlen(om->machine[i].config.tcp_client_send_string);
	

		om->machine[i].platform = platform__machine;

	}

#endif	

	return 0;
}


