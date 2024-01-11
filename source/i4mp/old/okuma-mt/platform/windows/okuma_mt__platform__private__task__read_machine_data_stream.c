#include "okuma_mt__private.h"

#include <okuma_mt__platform__private.h>


/*
 * Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
 */
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


static char* fn = "okuma_mt__platform__private__task__read_machine_data_stream()";


void okuma_mt__platform__private__task__read_machine_data_stream(void)
{

	int rc;
	int i;
	size_t len;
	size_t size;
	okuma_mt__platform__machine_t* machine;
	int done;
	int count;


	for (i = 0; i < om->machine_count; i++)
	{

		machine = (okuma_mt__platform__machine_t*)om->machine[i].platform;


		switch (om->machine[i].read_data_stream_task_state)
		{
		case 0:

			machine->socket = INVALID_SOCKET;
			machine->addrinfo_result = NULL;
			machine->addrinfo_ptr = NULL;

			ZeroMemory(&machine->addrinfo_hints, sizeof(machine->addrinfo_hints));
			machine->addrinfo_hints.ai_family = AF_UNSPEC;
			machine->addrinfo_hints.ai_socktype = SOCK_STREAM;
			machine->addrinfo_hints.ai_protocol = IPPROTO_TCP;

			/*
			 * resolve the server address and port
			 *
			 * example:  rc = getaddrinfo("192.168.1.242", 5000, &hints, &result);
			 */
			rc = getaddrinfo(om->machine[i].config.tcp_server_ipv4_address, om->machine[i].config.tcp_server_ipv4_port, &machine->addrinfo_hints, &machine->addrinfo_result);
			if (rc != 0)
			{
				machine->rc_getaddrinfo = rc;
				om->machine[i].read_data_stream_task_state = 1000;
			}
			else
			{
				om->machine[i].read_data_stream_task_state = 1;
			}
			break;

		case 1:

			om->machine[i].data_stream_valid = 0;

			/*
			 * Attempt to connect to an address until one succeeds
			 */
			done = 0;
			for (machine->addrinfo_ptr = machine->addrinfo_result; (machine->addrinfo_ptr != NULL) && (done == 0); machine->addrinfo_ptr = machine->addrinfo_ptr->ai_next)
			{
				/*
				 * create a socket for connecting to server
				 */
				machine->socket = socket(machine->addrinfo_ptr->ai_family, machine->addrinfo_ptr->ai_socktype, machine->addrinfo_ptr->ai_protocol);

				if (machine->socket == INVALID_SOCKET)
				{
					machine->rc_socket = WSAGetLastError();
					done = 1;
				}
				else
				{
					/*
					 * Connect to server
					 */
					rc = connect(machine->socket, machine->addrinfo_ptr->ai_addr, (int)machine->addrinfo_ptr->ai_addrlen);
					if (rc == SOCKET_ERROR)
					{
						closesocket(machine->socket);
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
				om->machine[i].read_data_stream_task_state = 1100;
				break;
			}

			if (done == 1)
			{
				/* freeaddrinfo(machine->addrinfo_result); */
				om->machine[i].read_data_stream_task_state = 1200;
				break;
			}


			rc = send(machine->socket, om->machine[i].send_buffer, (int)om->machine[i].send_buffer_len, 0);

			if (rc == SOCKET_ERROR)
			{
				//printf("send failed with error: %d\n", WSAGetLastError());
				machine->rc_send = WSAGetLastError();
				closesocket(machine->socket);
				//error = 1;
				om->machine[i].read_data_stream_task_state = 1300;
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
			size = om->machine[i].receive_buffer_size;
			done = 0;
			len = 0;
			do
			{
				/*
				 * if no error occurs, recv() returns the number of bytes received and the buffer pointed to by the buf parameter will contain this data received.
				 * if the connection has been gracefully closed, the return value is zero.
				 */
				count = recv(machine->socket, &om->machine[i].receive_buffer[len], (int)size, 0);
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
					om->machine[i].receive_buffer_len = len;
					done = 1;
				}
				else
				{
					printf("recv failed with error: %d\n", WSAGetLastError());
					machine->rc_recv = WSAGetLastError();
					done = 2;
				}

			} 
			while (done == 0);

			closesocket(machine->socket);

			if (done == 1)
			{
				//printf("%.*s", (int)om->machine[i].receive_buffer_len, om->machine[i].receive_buffer);
				om->machine[i].data_stream_valid = 1;
				om->machine[i].read_data_stream_task_state = 2;
			}
			else if (done == 2)
			{
				/*
				 * recv() error
				 */
				om->machine[i].read_data_stream_task_state = 300;
			}
			else
			{
				/*
				 * size error
				 */
				om->machine[i].read_data_stream_task_state = 300;
			}

		break;

		case 2:
			om->machine[i].read_data_stream_task_state = 1;
			break;


		case 1000:
			utils__printf__error(&om->pf, fn, -1000, "getaddrinfo() failed with error %d", fn, machine->rc_getaddrinfo);
			om->machine[i].read_data_stream_task_state = 1001;
			break;

		case 1001:
			om->machine[i].read_data_stream_task_state = 1001;   /* lingering */
			break;

		case 1010:
			utils__printf__error(&om->pf, fn, -1010, "socket() failed with error %d", fn, machine->rc_socket);
			om->machine[i].read_data_stream_task_state = 1011;
			break;

		case 1011:
			om->machine[i].read_data_stream_task_state = 1011;   /* lingering */
			break;

		case 1020:
			utils__printf__error(&om->pf, fn, -1020, "connect() failed - unable to connect to server", fn);
			om->machine[i].read_data_stream_task_state = 1021;
			break;

		case 1021:
			om->machine[i].read_data_stream_task_state = 1021;   /* lingering */
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

}


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