#include "okuma_mt__private.h"
#include "okuma_mt.h"


static char *fn = "okuma_mt__init()";


okuma_mt__application_t* om = NULL;


int okuma_mt__init (void)
{
	int rc;
	utils__printf__config_t pf_config;


	om = (okuma_mt__application_t*)malloc(sizeof(okuma_mt__application_t));
	if (om == NULL)
	{
		printf("%s - error - malloc() error\n", fn);
		return -100;
	}
	memset(om, '\0', sizeof(okuma_mt__application_t));


	/*
	 * agent data
	 */
	om->application_name = "OKUMA-MT";
	om->agent_version = okuma_mt__get_application_version();
	sprintf(om->agent_name_and_version, "%s %s", om->application_name, om->agent_version);
	om->agent_default_configuration_file_name = "okuma_mt_conf.txt";
	om->agent_section_name = "OKUMA-MT AGENT";


	/*
	 * machines data
	 */
	om->machines_section_name = "OKUMA-MT MACHINE";



	/*
	 * init and config utils_printf subsystem
	 */
	rc = utils__printf__init(&om->pf);
	if (rc != 0)
	{
		printf("%s - error - utils__printf__init() returned %d\n", fn, rc);
		return -200;
	}


	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = 1;
	pf_config.enable_log_file = 0;
	pf_config.log_file_name = "";
	pf_config.log_file_name_len = 0;
	pf_config.max_log_file_lines_per_minute = 0;
	pf_config.enable_table_layout_output = 1;
	pf_config.enable_application_name_on_output = 1;
	pf_config.application_name = om->agent_name_and_version;
	pf_config.application_name_len = strlen(om->agent_name_and_version);

	rc = utils__printf__config(&om->pf, &pf_config);
	if (rc != 0)
	{
		printf("%s - error - utils__printf__config() returned %d\n", fn, rc);
		return -300;
	}


	/*
	 * from now on, we can use : utils__printf__info(), utils__printf__error(), and utils__printf__warning()
	 */


	return 0;
}

