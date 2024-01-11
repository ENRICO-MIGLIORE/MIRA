#include <pthread.h>

#include "agent__fanuc_focas__private.h"



int agent__fanuc_focas__start (void)
{

	int i;
	int rc;
	int done;
	size_t milliseconds;
	const char* fn;


	fn = "agent__fanuc_focas__start()";

	//for (i = 0; i < agency->agent[i].number_of_machines; i++)



	/*
	 * start one thread per machine
	 */

	for (i = 0; i < agent__fanuc_focas->number_of_machines; i++)
	{

		//agency->agent[i].machine[j].thread_mutex = PTHREAD_MUTEX_INITIALIZER;
		agent__fanuc_focas->machine[i].thread_mutex = PTHREAD_MUTEX_INITIALIZER;

		//rc = pthread_create(&agency->agent[i].machine[j].thread_id, NULL, agent__fanuc_focas__thread, (void*)&agency->agent[i].machine[j]);

		rc = pthread_create(&agent__fanuc_focas->machine[i].thread_id, NULL, agent__fanuc_focas__thread, (void*)&agent__fanuc_focas->machine[i]);

		if (rc != 0)
		{
			//utils__printf__error(&agency->pf, fn, -200, "pthread_create() returned %d - agent %s - machine id = %d", rc, agency->agent[i].machine[j].config_2.name, agency->agent[i].machine[j].config_2.id);
			return -200;
		}
	}


#if enrico == 1

		/*
		 * Wait for the thread to start
		 */
		done = 0;
		milliseconds = 100;
		do
		{
			utils__platform__sleep(milliseconds);

			//pthread_mutex_lock(&agency->agent[i].machine[j].thread_mutex);

			pthread_mutex_lock(&agent__fanuc_focas->machine[i].thread_mutex);

			if (agent__fanuc_focas->machine[i].thread_started == 1)
			{
				done = 1;
			}

			pthread_mutex_unlock(&agent__fanuc_focas->machine[i].thread_mutex);


		} while (done == 0);


		//agency->agent[i].machine[j].started = 1;

		agent__fanuc_focas->machine[i].started = 1;
	
#endif


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


