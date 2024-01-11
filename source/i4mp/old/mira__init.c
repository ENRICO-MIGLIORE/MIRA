#include "mira__private.h"


mira__t* mira = NULL;

const char *mira_application_name = "MIRA 1.3.0";


int mira__init (void)
{

	int rc;
	size_t size;
	const char* fn;
	utils__printf__config_t pf_config;


	fn = "mira__init()";


	/*
	 * allocate the main structure
	 */
	size = sizeof(mira__t);
	mira = (mira__t*)malloc(size);
	if (mira == NULL)
	{		
		utils__printf__error(NULL, fn, -100, "malloc() error");
		return -100;
	}
	memset(mira, '\0', size);
	
	
	mira->application_name = mira_application_name;


	/*
	 * initialize the utils__printf subsystem
	 */
	rc = utils__printf__init(&mira->pf);
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -200, "utils__printf__init() error");
		return -200;
	}


	/*
	 * configure the utils__printf subsystem
	 */
	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = 1;
	pf_config.enable_log_file = 0;
	pf_config.log_file_name = "";
	pf_config.log_file_name_len = 0;
	pf_config.max_log_file_lines_per_minute = 120;
	pf_config.enable_table_layout_output = 1;
	pf_config.enable_application_name_on_output = 1;
	pf_config.application_name = mira->application_name;
	pf_config.application_name_len = strlen(mira->application_name);

	rc = utils__printf__config(&mira->pf, &pf_config);
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -300, "utils__printf__config() returned %d", rc);
		return -300;
	}


	mira->initialized = 1;


	return 0;
}