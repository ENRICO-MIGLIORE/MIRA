#include "fanuc_focas__private.h"


static char* fn = "fanuc_focas__connect_to_machine__real";


int fanuc_focas__connect_to_machine__real (size_t machine_id)
{

	size_t fd;
	int error;
	int rc;
	unsigned short focas_handle;	
	char ipv4_address[64];	
	size_t ipv4_address_len;
	unsigned long ipv4_port;
	size_t ipv4_port_len;
	long timeout;


	if (machine_id > ff->machine_count)
	{
		return -100;
	}

	if (machine_id == 0)
	{
		return -200;
	}

	fd = machine_id - 1;

	ff->machine[fd].connected = 0;


	//ipv4 = "1923.168.1.75";
	//ip_len = 4;
	//ipv4_port = "8193";
	//port_len = 4;
	

	ipv4_address_len = strlen(ff->machine[fd].config.cnc_ipv4_address);
	if (ipv4_address_len >= sizeof(ipv4_address))
	{
		return -300;
	}
	strcpy(ipv4_address, ff->machine[fd].config.cnc_ipv4_address);
	

	ipv4_port_len = strlen(ff->machine[fd].config.cnc_ipv4_port);
	rc = utils__libc__atoul(ff->machine[fd].config.cnc_ipv4_port, ipv4_port_len, &ipv4_port);
	if (rc != 0)
	{
		return -400;
	}


	timeout = (long) ff->cnc_connection_attempt_timeout_seconds;

	rc = cnc_allclibhndl3((const char*)ipv4_address, (unsigned short)ipv4_port, timeout, &focas_handle);

	if (rc != 0)
	{
		error = -300;
		utils__printf__error(&ff->pf, fn, error, "cnc_allclibhndl3() returned %d", rc);
		return error;
	}


	ff->machine[fd].handle = focas_handle;
	ff->machine[fd].connected = 1;

	utils__printf__info(&ff->machine[fd].pf, fn, 0, "machine %zu connected", machine_id);

	return 0;
}



//int fanuc_focas__connect_to_lathe_machine__real(size_t machine_id)
//{
//	int rc;
//	unsigned short focas_handle;
//	unsigned long timeout;
//	char ip_address[512];
//	unsigned long cnc_tcp_port;
//	char* ip;
//	char ip_len;
//	char* port;
//	char port_len;
//	size_t fd;
//	int error;
//
//
//	if (machine_id > ff->num_machines)
//	{
//		return -100;
//	}
//
//	if (machine_id == 0)
//	{
//		return -200;
//	}
//
//	fd = machine_id - 1;
//
//	ff->machine[fd].connected = 0;
//
//
//
//	ip = "1923.168.1.1";
//	ip_len = 4;
//	port = "4844";
//	port_len = 4;
//
//	memcpy(ip_address, ip, ip_len);
//	ip_address[ip_len] = '\0';
//
//	utils__libc__atoul(port, port_len, &cnc_tcp_port);
//	rc = 0;
//
//
//	timeout = ff->cnc_connection_attempt_timeout_seconds;
//
//	rc = cnc_allclibhndl3((const char*)ip_address, (unsigned short)cnc_tcp_port, timeout, &focas_handle);
//
//	if (rc != 0)
//	{
//		error = -300;
//		utils__printf__error(&ff->pf, fn, error, "cnc_allclibhndl3() returned %d", rc);
//		return error;
//	}
//
//	ff->machine[fd].connected = 1;
//
//	utils__printf__info(&ff->machine[fd].pf, fn, 0, "machine %zu connected - communications enabled", machine_id);
//
//	return -1000;
//
//}