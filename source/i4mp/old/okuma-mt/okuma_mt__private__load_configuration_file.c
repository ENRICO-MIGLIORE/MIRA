#include "okuma_mt__private.h"


static char* fn = "okuma_mt__private__load_configuration_file()";


int okuma_mt__private__load_configuration_file (void)
{

	int rc;

	memset(&om->config, 0, sizeof(okuma_mt__config_t));


	/*
	 * read the configuration file and extract data for the application
	 */
	rc = okuma_mt__private__load_configuration_file__application();
	if (rc != 0)
	{
		printf("%s - error - okuma_mt__private__load_configuration_file__application() returned %d\n", fn, rc);
		return -100;
	}


	/*
	 * read the configuration file and extract data for the machines
	 */
	rc = okuma_mt__private__load_configuration_file__machines();
	if (rc != 0)
	{
		printf("%s - error - okuma_mt__private__load_configuration_file__machines() returned %d\n", fn, rc);
		return -200;
	}


	return 0;

}

