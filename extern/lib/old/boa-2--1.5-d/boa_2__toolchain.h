#ifndef BOA_2__TOOLCHAIN__H
#define BOA_2__TOOLCHAIN__H

#include <winsock2.h>
#include <windows.h>

#pragma warning (disable : 4996)

typedef SOCKET      boa_2__socket_fd;
#define fd_zero     FD_ZERO 
#define fd_set      FD_SET
#define fd_isset    FD_ISSET

#define BOA_2__BACK_SLASH    "\\"


int boa_2__start_subsystem (char *error_message, size_t error_message_size);
int boa_2__stop_subsystem (void);
int boa2__is_send_buffer_empty (boa_2__socket_fd socket);
int boa_2__get_last_error (void);
void boa_2__task_1 (void);

#endif


