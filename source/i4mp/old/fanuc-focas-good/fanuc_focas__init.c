#include "fanuc_focas.h"


static char *fn = "fanuc_focas__init()";


fanuc_focas_t *fanuc_focas;


int fanuc_focas__init (int argc, char* argv[])
{
	int rc;
	char* application_configuration_file_name;	
	char* machines_configuration_file_name;
	size_t len;


	fanuc_focas = (fanuc_focas_t*) malloc(sizeof(fanuc_focas_t));
	if (fanuc_focas == NULL)
	{		
		printf("error in function %s - malloc() error\n", fn);
		return -100;
	}
	memset(fanuc_focas, '\0', sizeof(fanuc_focas_t));


	/*
	 * Application data
	 */
	fanuc_focas->application_data.name = "FANUC-FOCAS";
	fanuc_focas->application_data.version = fanuc_focas__get_application_version();
	sprintf(fanuc_focas->application_data.name_and_version, "%s %s", fanuc_focas->application_data.name, fanuc_focas->application_data.version);
	fanuc_focas->application_data.name_and_version_len = strlen(fanuc_focas->application_data.name_and_version);
	fanuc_focas->application_data.default_configuration_file_name = "fanuc_focas_conf.txt";
	fanuc_focas->application_data.configuration_file_section_name = "FANUC-FOCAS";
	fanuc_focas->application_data.configuration_file_section_name_len = strlen(fanuc_focas->application_data.configuration_file_section_name);


	/*
	 * Machines data
	 */
	fanuc_focas->machines_data.name = "FANUC-FOCAS LATHE MACHINE";
	fanuc_focas->machines_data.name_len = strlen(fanuc_focas->machines_data.name);
	fanuc_focas->machines_data.default_configuration_file_name = "fanuc_focas_conf.txt";
	fanuc_focas->machines_data.configuration_file_section_name = "FANUC-FOCAS LATHE MACHINE";
	fanuc_focas->machines_data.configuration_file_section_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);




	/*
	 * Application and machines configuration file name from the command line
	 */

	application_configuration_file_name = "";
	machines_configuration_file_name = "";

	if (argc == 1)
	{				
		application_configuration_file_name = fanuc_focas->application_data.default_configuration_file_name;
		machines_configuration_file_name = fanuc_focas->machines_data.default_configuration_file_name;
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
		application_configuration_file_name = argv[2];
		machines_configuration_file_name = argv[2];
	}
	else
	{
		return -400;
	}


	
	len = strlen(application_configuration_file_name);
	if (len >= sizeof(fanuc_focas->application_data.fully_qualified_configuration_file_name))
	{
		printf("error in function %s - The configuration fully qualified file name is too long\n", fn);
		return -500;
	}
	memcpy(fanuc_focas->application_data.fully_qualified_configuration_file_name, application_configuration_file_name, len);
	fanuc_focas->application_data.fully_qualified_configuration_file_name[len] = '\0';


	len = strlen(machines_configuration_file_name);
	if (len >= sizeof(fanuc_focas->machines_data.fully_qualified_configuration_file_name))
	{
		printf("error in function %s - The configuration fully qualified file name is too long\n", fn);
		return -700;
	}	
	memcpy(fanuc_focas->machines_data.fully_qualified_configuration_file_name, machines_configuration_file_name, len);
	fanuc_focas->machines_data.fully_qualified_configuration_file_name[len] = '\0';


	return 0;
}

