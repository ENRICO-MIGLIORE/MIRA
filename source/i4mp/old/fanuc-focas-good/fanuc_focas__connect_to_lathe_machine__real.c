#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;



static char* fn = "siemens_open62541__connect_to_machine__real";



int fanuc_focas__connect_to_lathe_machine__real (size_t machine_id)
{
	int rc;
	unsigned short focas_handle;
	unsigned long timeout;
	char ip_address[512];
	unsigned long cnc_tcp_port;
	char* ip;
	char ip_len;
	char* port;
	char port_len;

	size_t fd;


	if (machine_id > fanuc_focas->num_machines)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}
	
	fd = machine_id - 1;
	
	fanuc_focas->lathe_machine[fd].connected = 0;



	ip = "1923.168.1.1";
	ip_len = 4;
	port = "4844";
	port_len = 4;

	memcpy(ip_address, ip, ip_len);
	ip_address[ip_len] = '\0';

	utils__libc__atoul(port, port_len, &cnc_tcp_port);
	rc = 0;

	timeout = 3;

	rc = cnc_allclibhndl3((const char*)ip_address, (unsigned short)cnc_tcp_port, timeout, &focas_handle);

	if (rc == 0)
	{
		//*fd = focas_handle;
		return 0;
	}

	fanuc_focas->lathe_machine[fd].connected = 1;
	
	utils__printf__info(&fanuc_focas->lathe_machine[fd].pf, fn, 0, "machine %zu connected - communications enabled", machine_id);

	return -1000;

}

