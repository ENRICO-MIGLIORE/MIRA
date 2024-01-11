#ifndef OKUMA_MT__PLATFORM__PRIVATE_H
#define OKUMA_MT__PLATFORM__PRIVATE_H


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>


typedef struct
{
	SOCKET socket;
	struct addrinfo* addrinfo_result;
	struct addrinfo* addrinfo_ptr;
	struct addrinfo addrinfo_hints;

} okuma_mt__platform__machine_t;


int okuma_mt__platform__private__start(void);
int okuma_mt__platform__private__stop(void);
void okuma_mt__platform__private__task__read_machine_data_stream (void);



#endif