#include "okuma_mt__private.h"
#include "okuma_mt.h"


static char *fn = "okuma_mt__init()";


okuma_mt_t* om;


int okuma_mt__init (int argc, char* argv[])
{
	int rc;
	char* agent_configuration_file_name;
	size_t len;
	utils__printf__config_t pf_config;


	if ((argc != 1) && (argc != 3))
	{
		printf("%s - error - argc must be 1 or 3\n", fn);
		return -100;
	}

	if (argc == 3)
	{
		rc = strcmp(argv[1], "-c");
		if (rc != 0)
		{
			printf("%s - error - argv[1] doesn't contain -c\n", fn);
			return -200;
		}
	}


	om = (okuma_mt_t*) malloc(sizeof(okuma_mt_t));
	if (om == NULL)
	{		
		printf("%s - error - malloc() error\n", fn);
		return -300;
	}
	memset(om, '\0', sizeof(okuma_mt_t));
	

	/*
	 * application data
	 */
	om->agent_name = "OKUMA-MT";
	om->agent_version = okuma_mt__get_application_version();
	sprintf(om->agent_name_and_version, "%s %s", om->agent_name, om->agent_version);
	om->agent_default_configuration_file_name = "okuma_tcp_conf.txt";
	om->agent_section_name = "OKUMA-MT";


	/*
	 * machines data
	 */
	om->machines_section_name = "OKUMA-MT MACHINE";



	/*
	 * config utils_printf subsystem
	 */
	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = 1;
	pf_config.enable_log_file = 1;
	pf_config.log_file_name = "";
	pf_config.log_file_name_len = 0;
	pf_config.max_log_file_lines_per_minute = 0;
	pf_config.enable_table_layout_output = 1;
	pf_config.enable_application_name_on_output = 1;
	pf_config.agent_name = om->agent_name_and_version;
	pf_config.application_name_len = strlen(om->agent_name_and_version);

	rc = utils__printf__config(&om->pf, &pf_config);
	if (rc != 0)
	{
		printf("%s - error - utils__printf__config() returned %d\n", fn, rc);
		return -400;
	}

	/*
	 * from now on we can use: utils__printf__info(), utils__printf__error(), and utils__printf__warning()
	 */
	agent_configuration_file_name = "";

	if (argc == 1)
	{
		agent_configuration_file_name = om->agent_default_configuration_file_name;
	}
	else
	{
		agent_configuration_file_name = argv[2];
	}

	
	len = strlen(agent_configuration_file_name);
	if (len >= sizeof(om->agent_configuration_file_name))
	{
		utils__printf__error(&om->pf, fn, -500, "the configuration file name is too long", fn);
		return -500;
	}

	memcpy(om->agent_configuration_file_name, agent_configuration_file_name, len);
	om->agent_configuration_file_name[len] = '\0';


	return 0;
}