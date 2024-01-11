#include "Fwlib32.h"

//#include <agency_private.h>

#include "agent__fanuc_focas__private.h"


int agent__fanuc_focas__connect_to_machine (fanuc_focas__machine_t* machine)
{

	short rc;
	unsigned short machine_handle;
	unsigned long timeout;
	const char* ipv4_address;
	unsigned short ipv4_port;
	const char* fn;
	size_t len;
	int n;
	//fanuc_focas__machine_t* machine;


	fn = "agent__fanuc_focas__connect_to_machine()";


	if (machine == NULL)
	{
		return -100;
	}

	//machine = (fanuc_focas__machine_t *) arg;

	machine->ext_unsigned_short_valid = 0;

	timeout = 3;


#if enrico == 1

	ipv4_address = machine->config_2.fanuc_tcp_server_ipv4_address;
	
	len = strlen(machine->config_2.fanuc_tcp_server_ipv4_port);
	rc = utils__libc__atoi((const char*)machine->config_2.fanuc_tcp_server_ipv4_port, len, &n);

	if (rc != 0)
	{
		return -200;
	}

	if ((n < 0) || (n > 0xFFFF))
	{
		return -300;
	}

	ipv4_port = (unsigned short)n;
	


	rc = cnc_allclibhndl3(ipv4_address, ipv4_port, timeout, &machine_handle);

	if (rc != EW_OK)
	{
		return -200;
	}


	machine->ext_unsigned_short = machine_handle;
	machine->ext_unsigned_short_valid = 1;

#endif
	return 0;

}

