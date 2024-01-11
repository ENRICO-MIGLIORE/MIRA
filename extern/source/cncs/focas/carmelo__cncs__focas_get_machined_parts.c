#include "..\fggr.h"
#include <Fwlib32.h>




int fgg__cnc__focas_get_machined_parts (unsigned short fd, unsigned long *count)
{
	int rc;
	IODBPSD param ;

	rc = cnc_rdparam (fd, 6711, -1, 4+4*32, &param);  /* LEGGE IL NUMERO PART COUNT 6711*/
	//rc = cnc_rdparam (fd, 6712, -1, 4+4*32, &param);  


	*count = (unsigned long) param.u.ldata;

	return rc;
}

