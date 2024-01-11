#include "..\fggr.h"
#include <Fwlib32.h>
#include "carmelo__cncs.h"





unsigned long fgg__cnc__focas_is_connected (unsigned short fd)
{
	int rc;
	unsigned long state;

	rc = fgg__cnc__focas_get_status (fd, &state);

	if (rc != 0)
	{
		return 0; //non connessa
	}

	return 1; //connessa
}

