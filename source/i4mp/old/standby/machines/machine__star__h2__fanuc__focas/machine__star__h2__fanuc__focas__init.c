#include "machine__star__h2__fanuc__focas.h"


machine__star__h2__fanuc__focas_t *machine__star__h2__fanuc__focas;

int machine__star__h2__fanuc__focas__init (void)
{
	size_t i;

	machine__star__h2__fanuc__focas = (machine__star__h2__fanuc__focas_t *) malloc (sizeof(machine__star__h2__fanuc__focas_t));

	if (machine__star__h2__fanuc__focas == NULL)
	{
		return -10;
	}

	memset (machine__star__h2__fanuc__focas, '\0', (sizeof(machine__star__h2__fanuc__focas_t)));

	for (i = 0; i < 16; i++)
	{
		machine__star__h2__fanuc__focas->fd[i] = -1; 
	}

	return 0;
}
