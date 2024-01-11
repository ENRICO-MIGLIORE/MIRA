#include "..\fggr.h"
#include <Fwlib32.h>






int fgg__cnc__focas_connect (char* ip, char ip_len, char* port, char port_len, unsigned short *fd)
{
	int rc;
	unsigned short focas_handle;
	unsigned long timeout;
	char ip_address[512];
	unsigned long cnc_tcp_port;


	memcpy (ip_address, ip, ip_len);
	ip_address[ip_len] = '\0';

	utils__libc__atoul (port, port_len, &cnc_tcp_port);
	//util_atoul (port->data,port->len, &cnc_tcp_port);
	rc = 0;

	timeout = 3;

	rc = cnc_allclibhndl3 ((const char *) ip_address, (unsigned short) cnc_tcp_port, timeout, &focas_handle);



	if(rc == 0)
	{
		*fd = focas_handle;
	}
	

	return rc;

}


