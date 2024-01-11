#include "fanuc_focas__private.h"


static char *fn = "fanuc_focas__init()";


fanuc_focas_t* ff;


int fanuc_focas__init (int argc, char* argv[])
{
	int rc;
	char* configuration_file_name;
	size_t len;


	ff = (fanuc_focas_t*) malloc(sizeof(fanuc_focas_t));
	if (ff == NULL)
	{		
		printf("error in function %s - malloc() error\n", fn);
		return -100;
	}
	memset(ff, '\0', sizeof(fanuc_focas_t));



	/*
	 * Application data
	 */
	ff->application_name = "SIEMENS-OPEN62541";
	ff->application_version = fanuc_focas__get_version();
	sprintf(ff->application_name_and_version, "%s %s", ff->application_name, ff->application_version);
	ff->application_name_and_version_len = strlen(ff->application_name_and_version);
	ff->application_default_configuration_file_name = "fanuc_focas_conf.txt";
	ff->application_configuration_file_section_name = "FANUC-FOCAS";
	ff->application_configuration_file_section_name_len = strlen(ff->application_configuration_file_section_name);


	/*
	 * Machines data
	 */
	ff->machines_configuration_file_section_name = "FANUC-FOCAS LATHE MACHINE";
	ff->machines_configuration_file_section_name_len = strlen(ff->machines_configuration_file_section_name);




	configuration_file_name = "";

	if (argc == 1)
	{				
		configuration_file_name = ff->application_default_configuration_file_name;		
	}
	else if (argc == 2)
	{
		return -200;
	}
	else if (argc == 3)
	{

		rc = strcmp(argv[1], "-c");
		if (rc != 0)
		{
			return -300;
		}		
		configuration_file_name = argv[2];
	}
	else
	{
		return -400;
	}


	
	len = strlen(configuration_file_name);
	if (len >= sizeof(ff->application_fully_qualified_configuration_file_name))
	{
		printf("error in function %s - The configuration fully qualified file name is too long\n", fn);
		return -500;
	}

	memcpy(ff->application_fully_qualified_configuration_file_name, configuration_file_name, len);
	ff->application_fully_qualified_configuration_file_name[len] = '\0';


	return 0;
}