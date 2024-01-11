#include <windows.h>

#include <stddef.h>


void utils__platform__sleep (size_t milliseconds)
{
	DWORD millis;

	millis = (DWORD) milliseconds;

	Sleep(millis);

}

