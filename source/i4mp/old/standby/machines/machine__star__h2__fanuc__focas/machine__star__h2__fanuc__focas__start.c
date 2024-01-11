#include "machine__star__h2__fanuc__focas.h"


int machine__star__h2__fanuc__focas__start (int fd)
{
	machine__star__h2__fanuc__focas->start[fd] = 1;

	return 0;
}
