#include <agent__fanuc_focas.h>

#include "agency_private.h"


static const char* agency_name = "AGENCY";
static const char* agency_version = "1.1";


agency_t* agency = NULL;


int agency__init (void)
{

	int rc;
	int i;
	const char* fn;
	utils__printf__config_t pf_config;
	utils__sdb__config_t sdb_config;
	size_t size;
	int number_of_agents;


	fn = "agency__init()";



	/*
	 * allocate the structure
	 */
	agency = (agency_t*) malloc(sizeof(agency_t));
	if (agency == NULL)
	{
		utils__printf__error(NULL, fn, -100, "malloc() error");
		return -100;
	}
	memset(agency, '\0', sizeof(agency_t));

	agency->name = agency_name;
	agency->version = agency_version;


#if 0
	number_of_agents =  sizeof(i4_agents_name) / sizeof(const char*);
	
	size = sizeof(i4_agent_t) * number_of_agents;
	i4_agency->agent = (i4_agent_t*)malloc(size);
	if (i4_agency->agent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "malloc() error");
		return -100;
	}
	memset(i4_agency->agent, '\0', size);


	i4_agency->number_of_agents = number_of_agents;
	
	for (i = 0; i < i4_agency->number_of_agents; i++)
	{
		i4_agency->agent[i].name = i4_agents_name[i];
		i4_agency->agent[i].machine_section_name = i4_agents_machine_section_name[i];		
	}


#endif

	


	/*
	 * initialize the utils__printf subsystem
	 */
	rc = utils__printf__init(&agency->pf);
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
	pf_config.application_name = agency_name;
	pf_config.application_name_len = strlen(agency_name);

	rc = utils__printf__config(&agency->pf, &pf_config);
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -300, "utils__printf__config() returned %d", rc);
		return -300;
	}


	(void) utils__sdb__init(&agency->sdb);

	memset(&sdb_config, 0, sizeof(sdb_config));

	sdb_config.buffer = agency->sdb_buffer;
	sdb_config.buffer_size = sizeof(agency->sdb_buffer);
	sdb_config.name = agency->sdb_name;
	sdb_config.name_len = agency->sdb_name_len;
	sdb_config.value = agency->sdb_value;
	sdb_config.value_len = agency->sdb_value_len;
	sdb_config.encoding = agency->sdb_encoding;
	sdb_config.fields_max = AGENCY__CONFIG__SDB_FIELDS_MAX;

	rc = utils__sdb__config(&agency->sdb, &sdb_config);
	if (rc != 0)
	{
		utils__printf__error(&agency->pf, fn, -500, "utils__sdb__config() returned %d", rc);
		return -500;
	}




	rc = agent__fanuc_focas__init();
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -200, "agent__fanuc_focas__init() error");
		return -200;
	}


	return 0;

	/*
	 * 
	 */
	//agent_so->machine = (subagent_machine_t*)malloc(sizeof(subagent_machine_t));
	//if (agent_so->machine == NULL)
	//{
	//	utils__printf__error(NULL, fn, -200, "machine malloc() error");
	//	return -200;
	//}


	///*
	// * call subagent's init function
	// */
	//rc = machine__init(agent_so->machine);
	//if (rc != 0)
	//{
	//	utils__printf__error(NULL, fn, -300, "machine__init() returned %d", rc);
	//	return -300;
	//}





	//memset(subagent, '\0', sizeof(subagent_t));


	
	//subagent->name = SIEMENS_OPEN62541__AGENT__NAME;
	//subagent->version = siemens_open62541__get_application_version();
	//sprintf(subagent->name_and_version, "%s %s", subagent->name, subagent->version);
	//subagent->default_configuration_file_name = SIEMENS_OPEN62541__AGENT__DEFAULT_CONFIGURATION_FILE_NAME;	
	//subagent->section_name = SIEMENS_OPEN62541__AGENT__SECTION_NAME;
	//subagent->machines_section_name = SIEMENS_OPEN62541__AGENT__MACHINE_SECTION_NAME;

	//subagent->connect_to_machine = siemens_open62541__private__connect_to_machine__real;
	//subagent->disconnect_from_machine = agent__siemens_open62541__private__disconnect_from_machine__real;

	//subagent->read_part_counter = agent__siemens_open62541__private__read_part_counter__real;
	//subagent->read_cycle_time = agent__siemens_open62541__private__read_cycle_time__real;
	//subagent->read_part_program_name = agent__siemens_open62541__private__read_part_program_name__real;
	//	

	//so_2->delegate = subagent;

	//rc = agency__init(so_2->delegate);



	///*
	//	 * subagent 0:  SIEMENS-OPEN62541
	//	 */
	//subagent[agent_count].name = "SIEMENS-OPEN62541";

	//subagent[agent_count].init = siemens_open62541__init;
	//subagent[agent_count].config = siemens_open62541__config;
	//subagent[agent_count].start = agent__siemens_open62541__start;

	//subagent[agent_count].get_machine_count = siemens_open62541__get_machine_count;

	//subagent[agent_count].get_id = agent__siemens_open62541__get_machine_id;
	//subagent[agent_count].get_type = siemens_open62541__get_type;
	//subagent[agent_count].get_manufacturer = agent__siemens_open62541__get_machine_manufacturer;
	//subagent[agent_count].get_model = agent__siemens_open62541__get_machine_model;
	//subagent[agent_count].get_machine_serial_number = agent__siemens_open62541__get_machine_serial_number;
	//subagent[agent_count].get_name = agent__siemens_open62541__get_machine_name;
	//subagent[agent_count].get_facility = agent__siemens_open62541__get_machine_facility;
	//subagent[agent_count].get_department = agent__siemens_open62541__get_machine_department;
	//subagent[agent_count].get_cnc_name = agent__siemens_open62541__get_machine_cnc_name;

	//subagent[agent_count].get_machine_alarm_status = siemens_open62541__get_alarm_status;
	//subagent[agent_count].get_machine_networked_status = agent__siemens_open62541__get_machine_networked_status;
	//subagent[agent_count].get_machine_run_mode_status = agent__siemens_open62541__get_machine_run_mode_status;
	//subagent[agent_count].get_machine_connection_status = agent__siemens_open62541__get_machine_connection_status;
	//subagent[agent_count].get_machine_active_status = agent__siemens_open62541__get_machine_active_status;
	//subagent[agent_count].get_machine_production_status = agent__siemens_open62541__get_machine_production_status;
	//subagent[agent_count].get_part_counter = agent__siemens_open62541__get_machine_part_counter;
	//subagent[agent_count].get_cycle_time = agent__siemens_open62541__get_machine_cycle_time;
	//subagent[agent_count].get_part_program_name = agent__siemens_open62541__get_machine_part_program_name;

	//agent_count++;

	//if (agent_count > number_of_agents)
	//{
	//	printf("%s - error - agent_count %d > number_of_agents %d\n", fn, agent_count, number_of_agents);
	//	return -50;
	//}


	//so_2 = (siemens_open62541_2_t*)malloc(sizeof(siemens_open62541_2_t));
	//if (so_2 == NULL)
	//{
	//	printf("%s - error - malloc() error\n", fn);
	//	return -100;
	//}
	//memset(so_2, '\0', sizeof(siemens_open62541_2_t));

	//subagent = (subagent_t*) malloc(sizeof(subagent_t));
	//if (subagent == NULL)
	//{
	//	printf("%s - error - malloc() error\n", fn);
	//	return -100;
	//}
	//memset(subagent, '\0', sizeof(subagent_t));

	//subagent->application_name = "SIEMENS-OPEN62541";
	//subagent->agent_version = siemens_open62541__get_application_version();
	//sprintf(subagent->agent_name_and_version, "%s %s", subagent->application_name, subagent->agent_version);
	//subagent->agent_default_configuration_file_name = "siemens_open62541_conf.txt";
	//subagent->agent_section_name = "SIEMENS-OPEN62541 AGENT";

	//subagent->machines_section_name = "SIEMENS-OPEN62541 MACHINE";


	//rc = agency__init(subagent);


	//so_2->delegate = subagent;


	/////*
	//// * init and config utils_printf subsystem
	//// */
	////rc = utils__printf__init(&subagent->pf);
	////if (rc != 0)
	////{
	////	printf("%s - error - utils__printf__init() returned %d\n", fn, rc);
	////	return -200;
	////}


	////memset(&pf_config, 0, sizeof(pf_config));

	////pf_config.enable_printf = 1;
	////pf_config.enable_log_file = 0;
	////pf_config.log_file_name = "";
	////pf_config.log_file_name_len = 0;
	////pf_config.max_log_file_lines_per_minute = 0;
	////pf_config.enable_table_layout_output = 1;
	////pf_config.enable_application_name_on_output = 1;
	////pf_config.application_name = subagent->agent_name_and_version;
	////pf_config.application_name_len = strlen(subagent->agent_name_and_version);

	////rc = utils__printf__config(&subagent->pf, &pf_config);
	////if (rc != 0)
	////{
	////	printf("%s - error - utils__printf__config() returned %d\n", fn, rc);
	////	return -300;
	////}


	/////*
	//// * from now on, we can use : utils__printf__info(), utils__printf__error(), and utils__printf__warning()
	//// */


	return 0;
}



//siemens_open62541__application_t* so = NULL;

#if 0
int siemens_open62541__init__good (void)
{
	int rc;
	utils__printf__config_t pf_config;

	siemens_open62541__init_2();


	so = (siemens_open62541__application_t*)malloc(sizeof(siemens_open62541__application_t));
	if (so == NULL)
	{
		printf("%s - error - malloc() error\n", fn);
		return -100;
	}
	memset(so, '\0', sizeof(siemens_open62541__application_t));


	/*
	 * subagent data
	 */
	so->application_name = "SIEMENS-OPEN62541";
	so->agent_version = siemens_open62541__get_application_version();
	sprintf(so->agent_name_and_version, "%s %s", so->application_name, so->agent_version);
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
	pf_config.application_name = so->agent_name_and_version;
	pf_config.application_name_len = strlen(so->agent_name_and_version);

	rc = utils__printf__config(&so->pf, &pf_config);
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
#endif