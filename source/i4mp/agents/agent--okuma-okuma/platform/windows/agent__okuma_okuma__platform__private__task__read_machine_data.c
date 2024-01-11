//#include "okuma_mt__private.h"


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>


/*
 * Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
 */
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <agency_private.h>


typedef struct
{
	SOCKET socket;
	struct addrinfo* addrinfo_result;
	struct addrinfo* addrinfo_ptr;
	struct addrinfo addrinfo_hints;

} okuma_okuma__platform__data_t;



static okuma_okuma__platform__data_t* data;

static int agent__okuma_okuma__platform__private__wsa_startup (void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/*Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h*/
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		printf("WSAStartup failed with error: %d\n", err);
		return -10;
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return -20;
	}
	else
	{ 
		printf("The Winsock 2.2 dll was found okay\n");


	/* The Winsock DLL is acceptable. Proceed to use it. */

	/* Add network programming using Winsock here */

	/* then call WSACleanup when done using the Winsock dll */


	}

	return 0;
}



     
int agent__okuma_okuma__platform__private__task__read_machine_data (void* arg)
{

	int rc;
	int i;
	size_t len;
	size_t size;
	int done;
	int count;
	const char* fn;
	machine_t* machine;

	fn = "agent__okuma_okuma__platform__private__task__read_machine_data()";

	if (arg == NULL)
	{
		return -1;
	}

	machine = (machine_t*)arg;

	if ((machine->config_2.networked == 0) || (machine->config_2.run == 0))
	{
		return -1;
	}


	if ((machine->config_2.run == 1) && (machine->config_2.simulation == 1))
	{
		return -1;
	}

	switch (machine->task_state)
	{

	case 0:
		size = sizeof(okuma_okuma__platform__data_t);

		machine->ext_void_pointer = malloc(size);
		if (machine->ext_void_pointer == NULL)
		{
			machine->task_state = 900;
			break;
		}

		rc = agent__okuma_okuma__platform__private__wsa_startup();
		if (rc != 0)
		{
			machine->task_state = 900;
			break;
		}



		//malloc del buffer di ricezione
		len = strlen(machine->config_2.okuma_tcp_receiver_buffer_size);
		rc = utils__libc__atost(machine->config_2.okuma_tcp_receiver_buffer_size, len, &size);
		if (rc != 0)
		{
			return 900;
		}

		machine->config_2.okuma_tcp_receive_buffer = (char*)malloc(size);
		if (machine->config_2.okuma_tcp_receive_buffer == NULL)
		{
			return 900;
		}

		//malloc del buffer di send
		len = strlen(machine->config_2.okuma_tcp_send_buffer_size);
		rc = utils__libc__atost(machine->config_2.okuma_tcp_send_buffer_size, len, &size);
		if (rc != 0)
		{
			return -400;
		}
		machine->config_2.okuma_tcp_send_buffer = (char*)malloc(size);
		if (machine->config_2.okuma_tcp_send_buffer == NULL)
		{
			return -500;
		}

		machine->task_state = 1;
		break;

	case 1:
		machine->task_state = 2;
		break;

	case 2:
		data = (okuma_okuma__platform__data_t*)machine->ext_void_pointer;

		data->socket = INVALID_SOCKET;
		data->addrinfo_result = NULL;
		data->addrinfo_ptr = NULL;

		ZeroMemory(&data->addrinfo_hints, sizeof(data->addrinfo_hints));
		data->addrinfo_hints.ai_family = AF_UNSPEC;
		data->addrinfo_hints.ai_socktype = SOCK_STREAM;
		data->addrinfo_hints.ai_protocol = IPPROTO_TCP;

		/*
		 * resolve the server address and port
		 *
		 * example:  rc = getaddrinfo("192.168.1.242", 5000, &hints, &result);
		 */
		rc = getaddrinfo(machine->config_2.okuma_tcp_server_ipv4_address, machine->config_2.okuma_tcp_server_ipv4_port, &data->addrinfo_hints, &data->addrinfo_result);
		if (rc != 0)
		{
			machine->task_state = 900;
			break;
		}


		machine->task_state = 3;
		break;
			
		case 3:
			data = (okuma_okuma__platform__data_t*)machine->ext_void_pointer;

			//machine->ext_data_stream_valid = 0;

			/*
			 * Attempt to connect to an address until one succeeds
			 */
			done = 0;
			for (data->addrinfo_ptr = data->addrinfo_result; (data->addrinfo_ptr != NULL) && (done == 0); data->addrinfo_ptr = data->addrinfo_ptr->ai_next)
			{
				/*
				 * create a socket for connecting to server
				 */
				data->socket = socket(data->addrinfo_ptr->ai_family, data->addrinfo_ptr->ai_socktype, data->addrinfo_ptr->ai_protocol);

				if (data->socket == INVALID_SOCKET)
				{
					//data->rc_socket = WSAGetLastError();
					done = 1;
				}
				else
				{
					/*
					 * Connect to server
					 */
					rc = connect(data->socket, data->addrinfo_ptr->ai_addr, (int)data->addrinfo_ptr->ai_addrlen);
					if (rc == SOCKET_ERROR)
					{
						closesocket(data->socket);
					}
					else
					{
						/* utils__printf__info(&om->pf, fn, 0, "agent connected to \"%s(%d)\" in run mode", om->machine[i].config.name, om->machine[i].config.id); */
						done = 2;  /* socket is connected*/
					}
				}
			}


			if (done == 0)
			{
				/* freeaddrinfo(machine->addrinfo_result); */
				machine->task_state = 1100;
				break;
			}

			if (done == 1)
			{
				/* freeaddrinfo(machine->addrinfo_result); */
				machine->task_state = 1200;
				break;
			}

			//GET /current HTTP/1.1\r\n\r\n
			//machine->ext_send_buffer_len = strlen("GET /current HTTP/1.1\r\n\r\n");  //GET /current HTTP/1.1\r\n\r\n
			//rc = send(data->socket, "GET /current HTTP/1.1\r\n\r\n", (int)machine->ext_send_buffer_len, 0);

			if (rc == SOCKET_ERROR)
			{
				//printf("send failed with error: %d\n", WSAGetLastError());
				//machine->rc_send = WSAGetLastError();
				closesocket(data->socket);
				//error = 1;
				machine->task_state = 1300;
				break;
			}




			/*
			 * Stackoverflow - Zan Lynx - Nov 12
			 *
			 * Big difference between shutdown and close on a socket is the behavior when the socket is shared by other processes.
			 * A shutdown() affects all copies of the socket while close() affects only the file descriptor in one process.
			 *
			 *
			 *   rc = shutdown(machine->socket, SD_SEND);
			 *   if (rc == SOCKET_ERROR)
			 *   {
			 *   	//printf("shutdown failed with error: %d\n", WSAGetLastError());
			 *   	closesocket(machine->socket);
			 *   	WSACleanup();
			 *   	om->machine[i].read_machine_data_stream_task_state = 1040;
			 *   	//return 1;
			 *   }
			 *   else
			 *   {
			 *
			 *   we use closesocket() instead of shutdown()
			 *
			 */


			 /*
			  * receive until the peer closes the connection
			  */
			//size = (size_t)machine->config_2.okuma_tcp_receiver_buffer_size;
			len = strlen(machine->config_2.okuma_tcp_receiver_buffer_size);
			rc = utils__libc__atost(machine->config_2.okuma_tcp_receiver_buffer_size, len, &size);
			if (rc != 0)
			{
				//error = 1;
				machine->task_state = 1300;
				break;
			}
			done = 0;
			len = 0;
			do
			{
				/*
				 * if no error occurs, recv() returns the number of bytes received and the buffer pointed to by the buf parameter will contain this data received.
				 * if the connection has been gracefully closed, the return value is zero.
				 */
				//count = recv(data->socket, &machine->ext_receive_buffer[len], (int)size, 0);

				count = 0;
				if (count > 0)
				{
					len += count;

					if (size >= count)
					{
						size -= count;
					}
					else
					{
						done = 3;
					}
				}
				else if (count == 0)
				{
					//machine->ext_receive_buffer_len = len;
					done = 1; //e' successo che sono entrato qui ma il buffer era vuoto
				}
				else
				{
					printf("recv failed with error: %d\n", WSAGetLastError());
					//machine->rc_recv = WSAGetLastError();
					done = 2;
				}

			} while (done == 0);

			closesocket(data->socket);

			if (done == 1)
			{
				//printf("%.*s", (int)om->machine[i].receive_buffer_len, om->machine[i].receive_buffer);
				//machine->ext_data_stream_valid = 1;
				machine->task_state = 4;
			}
			else if (done == 2)
			{
				/*
				 * recv() error
				 */
				machine->task_state = 4;
			}
			else
			{
				/*
				 * size error
				 */
				machine->task_state = 4;
			}

			break;

		case 4:
			machine->task_state = 3;
			break;


		case 1000:
			//utils__printf__error(&om->pf, fn, -1000, "getaddrinfo() failed with error %d", fn, machine->rc_getaddrinfo);
			machine->task_state = 1001;
			break;

		case 1001:
			machine->task_state = 1001;   /* lingering */
			break;

		case 1010:
			//utils__printf__error(&om->pf, fn, -1010, "socket() failed with error %d", fn, machine->rc_socket);
			machine->task_state = 1011;
			break;

		case 1011:
			machine->task_state = 1011;   /* lingering */
			break;

		case 1020:
			//utils__printf__error(&om->pf, fn, -1020, "connect() failed - unable to connect to server", fn);
			machine->task_state = 1021;
			break;

		case 1021:
			machine->task_state = 1021;   /* lingering */
			break;

		case 1100:
			break;

		case 1101:
			break;

		case 1200:
			break;

		case 1201:
			break;

		case 1300:
			break;

		case 1301:
			break;

		default:
			break;
		}



}

#if 0

void agent__okuma_okuma__platform__private__task__read_machine_data_lasciato_da_enrico (void* arg)
{

	int rc;
	int i;
	size_t len;
	size_t size;
	int done;
	int count;
	const char* fn;
	machine_t* machine;

	fn = "agent__okuma_okuma__platform__private__task__read_machine_data()";

	if (arg == NULL)
	{
		return;
	}

	machine = (machine_t*) arg;

	if ((machine->config_2.networked == 0) || (machine->config_2.run == 0))
	{
		return;
	}

	if ((machine->config_2.run == 1) && (machine->config_2.simulation == 1))
	{
		return;
	}

	switch (machine->task_state)
	{

	    case 0:
			//client = UA_Client_new();
			size = sizeof(okuma_okuma__platform__data_t);

			machine->ext_void_pointer = malloc(size);
			if (machine->ext_void_pointer == NULL)
			{
				machine->task_state = 900;
				break;
			}

			machine->task_state = 1;
		break;

		case 1:
			machine->task_state = 2;
			break;

	    case 2:
		    data->socket = INVALID_SOCKET;
		    data->addrinfo_result = NULL;
		    data->addrinfo_ptr = NULL;
		    
		    ZeroMemory(&data->addrinfo_hints, sizeof(data->addrinfo_hints));
		    data->addrinfo_hints.ai_family = AF_UNSPEC;
		    data->addrinfo_hints.ai_socktype = SOCK_STREAM;
		    data->addrinfo_hints.ai_protocol = IPPROTO_TCP;

		    /*
		     * resolve the server address and port
		     *
		     * example:  rc = getaddrinfo("192.168.1.242", 5000, &hints, &result);
		     */
		    rc = getaddrinfo(machine->config_2.okuma_tcp_server_ipv4_address, machine->config_2.okuma_tcp_server_ipv4_port, &data->addrinfo_hints, &data->addrinfo_result);
		    if (rc != 0)
		    {
		    	machine->task_state = 900;
		    	break;
		    }
	

		    machine->task_state = 3;
		break;



	}

	//for (i = 0; i < om->machine_count; i++)
	for (i = 0; i < 10; i++)
	{

		/*data = (okuma_mt__data_t*) om->machine[i].platform;
		statistics = (okuma_mt__statistics_t*) &om->machine[i].statistics;*/

		//if (om->machine[i].config.simulated == 1)
		//{
		//	continue;
		//}

		//switch (om->machine[i].read_data_stream_task_state)
		switch (1)
		{
		case 0:

			data->socket = INVALID_SOCKET;
			data->addrinfo_result = NULL;
			data->addrinfo_ptr = NULL;

			ZeroMemory(&data->addrinfo_hints, sizeof(data->addrinfo_hints));
			data->addrinfo_hints.ai_family = AF_UNSPEC;
			data->addrinfo_hints.ai_socktype = SOCK_STREAM;
			data->addrinfo_hints.ai_protocol = IPPROTO_TCP;

			/*
			 * resolve the server address and port
			 *
			 * example:  rc = getaddrinfo("192.168.1.242", 5000, &hints, &result);
			 */
			rc = getaddrinfo(om->machine[i].config.tcp_server_ipv4_address, om->machine[i].config.tcp_server_ipv4_port, &data->addrinfo_hints, &data->addrinfo_result);
			if (rc != 0)
			{
				//statistics->getaddrinfo_error++;
				om->machine[i].read_data_stream_task_state = 1000;				
			}
			else
			{
				//statistics->getaddrinfo_ok++;
				om->machine[i].read_data_stream_task_state = 1;
			}
			break;

		case 3:

			/*
			 * Attempt to connect to an address until one succeeds
			 */
			done = 0;
			for (data->addrinfo_ptr = data->addrinfo_result; (data->addrinfo_ptr != NULL) && (done == 0); data->addrinfo_ptr = data->addrinfo_ptr->ai_next)
			{
				/*
				 * create a socket for connecting to server
				 */
				data->socket = socket(data->addrinfo_ptr->ai_family, data->addrinfo_ptr->ai_socktype, data->addrinfo_ptr->ai_protocol);

				if (data->socket == INVALID_SOCKET)
				{
					//if (om->machine[i].config.tcp_client_enable_printf)
					{
						//utils__printf__error(&om->pf, fn, -100, "machine id %d - socket() returned INVALID_SOCKET", om->machine[i].config.id);
					}

					//data->rc_socket = WSAGetLastError();
					done = 1;
				}
				else
				{
					/*
					 * Connect to server
					 */
					rc = connect(data->socket, data->addrinfo_ptr->ai_addr, (int)data->addrinfo_ptr->ai_addrlen);
					if (rc == SOCKET_ERROR)
					{
						//if (om->machine[i].config.tcp_client_enable_printf)
						{
							//utils__printf__error(&om->pf, fn, -200, "machine id %d - connect() returned SOCKET_ERROR", om->machine[i].config.id);
						}

						//statistics->connect_error++;
						closesocket(data->socket);
					}
					else
					{						
						if (om->machine[i].config.tcp_client_enable_printf)
						{
							utils__printf__info(&om->pf, fn, 0, "machine id %d - connect() returned OK", om->machine[i].config.id);
						}

						/* utils__printf__info(&om->pf, fn, 0, "agent connected to \"%s(%d)\" in run mode", om->machine[i].config.name, om->machine[i].config.id); */
						//statistics->connect_ok++;
						done = 2;  /* socket is connected*/
					}
				}
			}


			if (done == 0)
			{
				/* freeaddrinfo(data->addrinfo_result); */
				om->machine[i].read_data_stream_task_state = 1100;
				break;
			}

			if (done == 1)
			{
				/* freeaddrinfo(data->addrinfo_result); */
				om->machine[i].read_data_stream_task_state = 1200;
				break;
			}


			rc = send(data->socket, om->machine[i].send_buffer, (int)om->machine[i].send_buffer_len, 0);

			if (rc == SOCKET_ERROR)
			{
				//utils__printf__error("send failed with error: %d\n", WSAGetLastError());

				//machine->config_2.
				if (om->machine[i].config.tcp_client_enable_printf)
				{
					utils__printf__error(&om->pf, fn, -300, "machine id %d - send() returned SOCKET_ERROR", om->machine[i].config.id);
				}
				
				//data->rc_send = WSAGetLastError();
				closesocket(data->socket);

				//statistics->send_error++;

				om->machine[i].read_data_stream_task_state = 1300;
				break;
			}

			//statistics->send_ok++;


			/*
			 * Stackoverflow - Zan Lynx - Nov 12
			 *
			 * Big difference between shutdown and close on a socket is the behavior when the socket is shared by other processes.
			 * A shutdown() affects all copies of the socket while close() affects only the file descriptor in one process.
			 *
			 *
			 *   rc = shutdown(data->socket, SD_SEND);
			 *   if (rc == SOCKET_ERROR)
			 *   {
			 *   	//utils__printf__error("shutdown failed with error: %d\n", WSAGetLastError());
			 *   	closesocket(data->socket);
			 *   	WSACleanup();
			 *   	om->machine[i].read_machine_data_stream_task_state = 1040;
			 *   	//return 1;
			 *   }
			 *   else
			 *   {
			 *
			 *   we use closesocket() instead of shutdown()
			 *
			 */


			 /*
			  * receive until the peer closes the connection
			  */


			om->machine[i].receive_buffer_len_2 = 0;
			size = om->machine[i].receive_buffer_size_2;
			len = 0;
			done = 0;


			do
			{
				/*
				 * if no error occurs, recv() returns the number of bytes received and the buffer pointed to by the buf parameter will contain this data received.
				 * if the connection has been gracefully closed, the return value is zero.
				 */
				count = recv(data->socket, &om->machine[i].receive_buffer_2[len], (int) size, 0);
				if (count > 0)
				{
					len += count;

					if (size >= count)
					{
						size -= count;
					}
					else
					{
						done = 3;
					}

					statistics->recv_ok++;
				}
				else if (count == 0)
				{
					om->machine[i].receive_buffer_len_2 = len;
					done = 1;

					statistics->recv_ok++;
				}
				else
				{

					//utils__printf__error("recv failed with error: %d\n", WSAGetLastError());
					//data->rc_recv = WSAGetLastError();
					statistics->recv_error++;
					done = 2;					
				}

			} 
			while (done == 0);


			closesocket(data->socket);


		//	if (done == 1)
		//	{
		//		//utils__printf__error("%.*s", (int)om->machine[i].receive_buffer_len, om->machine[i].receive_buffer);

		//		if (om->machine[i].config.tcp_client_enable_printf)
		//		{
		//			utils__printf__info(&om->pf, fn, 0, "machine id %d - recv() completed without errors", om->machine[i].config.id);
		//		}

		//		pthread_mutex_lock(&om->thread_mutex);                               /* enter critical section */

		//		memcpy(om->machine[i].receive_buffer, om->machine[i].receive_buffer_2, om->machine[i].receive_buffer_len_2);
		//		om->machine[i].receive_buffer_len = om->machine[i].receive_buffer_len_2;
		//		om->machine[i].data_stream_valid = 1;

		//		(void) okuma_mt__private__read_part_counter__real(i);

		//		(void) okuma_mt__private__read_alarm_status__real(i);

		//		(void) okuma_mt__private__read_production_status__real(i);

		//		(void) okuma_mt__private__read_part_program_name__real(i);

		//		(void) okuma_mt__private__read_connection_status__real(i);

		//		pthread_mutex_unlock(&om->thread_mutex);                              /* exit critical section */

		//		om->machine[i].read_data_stream_task_state = 1;
		//	}
		//	else if (done == 2)
		//	{
		//		/*
		//		 * recv() error
		//		 */
		//		if (om->machine[i].config.tcp_client_enable_printf)
		//		{
		//			utils__printf__error(&om->pf, fn, -400, "machine id %d - recv() returned ERROR", om->machine[i].config.id);
		//		}

		//		pthread_mutex_lock(&om->thread_mutex);
		//		om->machine[i].data_stream_valid = 0;
		//		pthread_mutex_unlock(&om->thread_mutex);

		//		om->machine[i].read_data_stream_task_state = 300;
		//	}
		//	else
		//	{
		//		/*
		//		 * size error
		//		 */
		//		if (om->machine[i].config.tcp_client_enable_printf)
		//		{
		//			utils__printf__error(&om->pf, fn, -400, "machine id %d - recv() is ok but receive_buffer_size is too small", om->machine[i].config.id);
		//		}

		//		pthread_mutex_lock(&om->thread_mutex);
		//		om->machine[i].data_stream_valid = 0;
		//		pthread_mutex_unlock(&om->thread_mutex);

		//		om->machine[i].read_data_stream_task_state = 400;
		//	}

		//break;


		//case 300:
		//	om->machine[i].read_data_stream_task_state = 1;
		//	break;

		//case 400:
		//	om->machine[i].read_data_stream_task_state = 1;
		//	break;

		//case 1000:
		//	//utils__printf__error(&om->pf, fn, -1000, "getaddrinfo() failed with error %d", fn, data->rc_getaddrinfo);
		//	om->machine[i].read_data_stream_task_state = 1001;
		//	break;

		//case 1001:
		//	om->machine[i].read_data_stream_task_state = 1001;   /* lingering */
		//	break;

		//case 1010:
		//	//utils__printf__error(&om->pf, fn, -1010, "socket() failed with error %d", fn, data->rc_socket);
		//	om->machine[i].read_data_stream_task_state = 1011;
		//	break;

		//case 1011:
		//	om->machine[i].read_data_stream_task_state = 1011;   /* lingering */
		//	break;

		//case 1020:
		//	utils__printf__error(&om->pf, fn, -1020, "connect() failed - unable to connect to server", fn);
		//	om->machine[i].read_data_stream_task_state = 1021;
		//	break;

		//case 1021:
		//	om->machine[i].read_data_stream_task_state = 1021;   /* lingering */
		//	break;


		// 
		// 
		// 
		// 
		case 900:
			break;

		default:
			break;
	}

//}

}


#endif

#if 0



#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>



// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")




#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "5000"

int __cdecl tcp_client(void)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	char* sendbuf = "GET /current HTTP/1.1\r\n\r\n";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;



	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("192.168.1.242", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// Receive until the peer closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			//printf("%s", recvbuf);
			parser_string(recvbuf, (unsigned long)iResult);

		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}


#endif