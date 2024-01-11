#include "machine.h"


int machine__exit (subagent__machine_t* machine_local)
{
	int rc;
	utils__printf__config_t pf_config;
	const char* fn;


	fn = "machine__exit()";


	//so = (siemens_open62541__application_t*)malloc(sizeof(siemens_open62541__application_t));
	//if (so == NULL)
	//{
	//	printf("%s - error - malloc() error\n", fn);
	//	return -100;
	//}
	//memset(so, '\0', sizeof(siemens_open62541__application_t));


	///*
	// * delegate data
	// */
	//delegate->application_name = "SIEMENS-OPEN62541";
	//delegate->agent_version = siemens_open62541__get_application_version();
	//sprintf(delegate->agent_name_and_version, "%s %s", delegate->application_name, delegate->agent_version);
	//delegate->agent_default_configuration_file_name = "siemens_open62541_conf.txt";
	//delegate->agent_section_name = "SIEMENS-OPEN62541 AGENT";


	///*
	// * machines data
	// */
	//delegate->machines_section_name = "SIEMENS-OPEN62541 MACHINE";



	///*
	// * init and config utils_printf subsystem
	// */
	//rc = utils__printf__init(&machine->pf);
	//if (rc != 0)
	//{
	//	printf("%s - error - utils__printf__init() returned %d\n", fn, rc);
	//	return -200;
	//}


	//memset(&pf_config, 0, sizeof(pf_config));

	//pf_config.enable_printf = 1;
	//pf_config.enable_log_file = 0;
	//pf_config.log_file_name = "";
	//pf_config.log_file_name_len = 0;
	//pf_config.max_log_file_lines_per_minute = 0;
	//pf_config.enable_table_layout_output = 1;
	//pf_config.enable_application_name_on_output = 1;
	//pf_config.application_name = machine->config.agent_name_and_version;
	//pf_config.application_name_len = strlen(machine->config.agent_name_and_version);

	//rc = utils__printf__config(&machine->pf, &pf_config);
	//if (rc != 0)
	//{
	//	printf("%s - error - utils__printf__config() returned %d\n", fn, rc);
	//	return -300;
	//}


	/*
	 * from now on, we can use : utils__printf__info(), utils__printf__error(), and utils__printf__warning()
	 */


	return 0;
}