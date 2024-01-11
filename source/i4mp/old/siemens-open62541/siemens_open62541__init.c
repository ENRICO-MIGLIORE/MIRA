#include "siemens_open62541__private.h"
#include "siemens_open62541.h"


static char *fn = "siemens_open62541__init()";


siemens_open62541_private_t* so;


int siemens_open62541__init (void)
{
	int rc;
	utils__printf__config_t pf_config;


	so = (siemens_open62541_private_t*)malloc(sizeof(siemens_open62541_private_t));
	if (so == NULL)
	{
		printf("%s - error - malloc() error\n", fn);
		return -300;
	}
	memset(so, '\0', sizeof(siemens_open62541_private_t));


	/*
	 * agent data
	 */
	so->agent_name = "SIEMENS-OPEN62541";
	so->agent_version = siemens_open62541__get_application_version();
	sprintf(so->agent_name_and_version, "%s %s", so->agent_name, so->agent_version);
	so->agent_default_configuration_file_name = "siemens_open62541_conf.txt";
	so->agent_section_name = "SIEMENS-OPEN62541 AGENT";


	/*
	 * machines data
	 */
	so->machines_section_name = "SIEMENS-OPEN62541 MACHINE";



	/*
	 * init and config utils_printf subsystem
	 */
	rc = utils__printf__init(&so->pf);
	if (rc != 0)
	{
		printf("%s - error - utils__printf__init() returned %d\n", fn, rc);
		return -350;
	}


	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = 1;
	pf_config.enable_log_file = 0;
	pf_config.log_file_name = "";
	pf_config.log_file_name_len = 0;
	pf_config.max_log_file_lines_per_minute = 0;
	pf_config.enable_table_layout_output = 1;
	pf_config.enable_application_name_on_output = 1;
	pf_config.agent_name = so->agent_name_and_version;
	pf_config.application_name_len = strlen(so->agent_name_and_version);

	rc = utils__printf__config(&so->pf, &pf_config);
	if (rc != 0)
	{
		printf("%s - error - utils__printf__config() returned %d\n", fn, rc);
		return -400;
	}


	/* 
	 * from now on, we can use : utils__printf__info(), utils__printf__error(), and utils__printf__warning()
	 */


	return 0;
}