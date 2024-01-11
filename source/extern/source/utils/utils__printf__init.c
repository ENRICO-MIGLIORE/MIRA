#include "utils__printf.h"


int utils__printf__init (utils__printf_t *pf)
{

	memset(pf, 0, sizeof(utils__printf_t));

	return 0;
}

