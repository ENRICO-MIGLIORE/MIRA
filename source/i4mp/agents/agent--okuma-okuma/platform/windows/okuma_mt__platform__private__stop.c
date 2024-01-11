#include <okuma_mt__platform__private.h>


int okuma_mt__platform__private__stop(void)
{

	WSACleanup();

	return 0;
}
