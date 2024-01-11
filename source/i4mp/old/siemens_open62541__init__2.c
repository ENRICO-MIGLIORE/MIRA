//#include "siemens_open62541__private.h"
#include "agent__2.h"


static char *fn = "machine__init__2()";


//siemens_open62541_t* so;


int machine__init__2 (machine__manufacturer__t* mm, int argc, char* argv[])
{
	int rc;
	char* configuration_file_name;
	size_t len;


	mm = (machine__manufacturer__t*) malloc(sizeof(machine__manufacturer__t));
	if (mm == NULL)
	{		
		printf("error in function %s - malloc() error\n", fn);
		return -100;
	}
	memset(mm, '\0', sizeof(machine__manufacturer__t));
	

	/*
	 * Application data
	 */
	mm->application_name = "SIEMENS-OPEN62541";
	mm->application_version = siemens_open62541__get_application_version();
	sprintf(mm->application_name_and_version, "%s %s", mm->application_name, mm->application_version);
	mm->default_configuration_file_name = "siemens_open62541_conf.txt";
	mm->application_section_name = "SIEMENS-OPEN62541";


	/*
	 * Machines data
	 */
	mm->machines_section_name = "SIEMENS-OPEN62541 MACHINE";


	configuration_file_name = "";

	if (argc == 1)
	{				
		configuration_file_name = mm->default_configuration_file_name;
	}
	else if (argc == 2)
	{
		return -400;
	}
	else if (argc == 3)
	{

		rc = strcmp(argv[1], "-c");
		if (rc != 0)
		{
			return -500;
		}		
		configuration_file_name = argv[2];
	}
	else
	{
		return -600;
	}

	
	len = strlen(configuration_file_name);
	if (len >= sizeof(mm->configuration_file_name))
	{
		printf("error in function %s - the configuration file name is too long", fn);
		return -700;
	}

	memcpy(mm->configuration_file_name, configuration_file_name, len);
	mm->configuration_file_name[len] = '\0';


	return 0;
}