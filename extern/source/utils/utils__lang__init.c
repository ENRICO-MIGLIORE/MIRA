#include "utils__lang.h"
#include "utils__lang__private.h"


utils__lang__t lang;


int utils__lang__init (void)
{
	memset(&lang, 0 , sizeof(utils__lang__t));

	return 0;
}
