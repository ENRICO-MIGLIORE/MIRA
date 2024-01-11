#include "fanuc_focas__private.h"
#include "fanuc_focas.h"


static char *fn = "fanuc_focas__init()";


fanuc_focas__application_t* ff = NULL;


int fanuc_focas__init (void)
{
	int rc;
	utils__printf__config_t pf_config;


	ff = (fanuc_focas__application_t*)malloc(sizeof(fanuc_focas__application_t));
	if (ff == NULL)
	{
		printf("%s - error - malloc() error\n", fn);
		return -100;
	}
	memset(ff, '\0', sizeof(fanuc_focas__application_t));


	/*
	 * agent data
	 */
	ff->application_name = "FANUC-FOCAS";
	ff->agent_version = fanuc_focas__get_application_version();
	sprintf(ff->agent_name_and_version, "%s %s", ff->application_name, ff->agent_version);
	ff->agent_default_configuration_file_name = "okuma_mt_conf.txt";
	ff->agent_section_name = "FANUC-FOCAS AGENT";


	/*
	 * machines data
	 */
	ff->machines_section_name = "FANUC-FOCAS MACHINE";



	/*
	 * init and config utils_printf subsystem
	 */
	rc = utils__printf__init(&ff->pf);
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
	pf_config.application_name = ff->agent_name_and_version;
	pf_config.application_name_len = strlen(ff->agent_name_and_version);

	rc = utils__printf__config(&ff->pf, &pf_config);
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

