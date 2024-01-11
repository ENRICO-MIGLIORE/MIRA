#include "machine__star__h2__fanuc__focas.h"



int machine__star__h2__fanuc__focas__open (void)
{
	int found;
	size_t i;
	int fd;

	found = 0;

	for (i = 0; (i < 16) && (found == 0); i++)
	{
		if (machine__star__h2__fanuc__focas->fd[i] == -1)
		{
			machine__star__h2__fanuc__focas->fd[i] = i;
			fd = i;
			//memcpy (&fgg__focas->configuration_file[i], configuration_file, sizeof (fgg__focas_configuration_file_t));
			found = 1;
		}		
	}

	if (found == 0)
	{
		return -10;
	}


	return fd;
}


