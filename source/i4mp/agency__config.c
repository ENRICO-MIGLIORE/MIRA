#include <agent__fanuc_focas.h>

#include "agency_private.h"


extern int agent__siemens_open62541__platform__private__connect_to_machine(void* arg);
extern int agent__siemens_open62541__platform__private__read_machine_cycle_time(void* arg);
extern int agent__siemens_open62541__platform__private__read_machine_part_counter(void* arg);
extern int agent__siemens_open62541__platform__private__read_machine_part_program_name(void* arg);
extern int agent__siemens_open62541__platform__private__read_machine_status_run(void* arg);
extern int agent__siemens_open62541__platform__private__read_machine_status_alarm(void* arg);

extern int agent__fanuc_focas__connect_to_machine(void* arg);
extern int agent__fanuc_focas__read_machine_cycle_time(void* arg);
extern int agent__fanuc_focas__read_machine_part_counter(void* arg);
extern int agent__fanuc_focas__read_machine_part_program_name(void* arg);


extern int agent__okuma_okuma__platform__start(void* arg);
extern int agent__okuma_okuma__platform__private__stop(void* arg);
extern int agent__okuma_okuma__platform__private__connect_to_machine(void* arg);
extern int agent__okuma_okuma__platform__private__read_machine_cycle_time(void* arg);
extern int agent__okuma_okuma__platform__private__read_machine_part_counter(void* arg);
extern int agent__okuma_okuma__platform__private__read_machine_part_program_name(void* arg);

extern int  agent__okuma_okuma__platform__private__task__read_machine_data(void* arg);


typedef struct
{

	const char* name;
	const char* machine_section_name;

	agent__start_t start;
	agent__stop_t stop;
	agent__connect_to_machine_t connect_to_machine;
	agent__read_machine_data_t read_machine_part_counter;
	agent__read_machine_data_t read_machine_cycle_time;
	agent__read_machine_data_t read_machine_part_program_name;
	agent__read_machine_data_t read_machine_data_stream;

	//agent__disconnect_from_machine_t disconnect_from_machine;	

} agent___t;


static const agent___t agent__config[] = { {"SIEMENS-OPEN62541", 
                                            "MACHINE SIEMENS-OPEN62541",
	                                        NULL,
	                                        NULL,
	                                        agent__siemens_open62541__platform__private__connect_to_machine,
	                                        agent__siemens_open62541__platform__private__read_machine_part_counter,
	                                        agent__siemens_open62541__platform__private__read_machine_cycle_time,
	                                        agent__siemens_open62541__platform__private__read_machine_part_program_name,
	                                        NULL},
									       
	                                       {"FANUC-FOCAS",
	                                        "MACHINE FANUC-FOCAS",
											NULL,
											NULL,
									       agent__fanuc_focas__connect_to_machine,
									       agent__fanuc_focas__read_machine_part_counter,
									       agent__fanuc_focas__read_machine_cycle_time,
									       agent__fanuc_focas__read_machine_part_program_name,
                                           NULL},

										   {"OKUMA-OKUMA",
										    "MACHINE OKUMA-OKUMA",
											agent__okuma_okuma__platform__start,
											agent__okuma_okuma__platform__private__stop,
											agent__okuma_okuma__platform__private__connect_to_machine,
										    agent__okuma_okuma__platform__private__read_machine_part_counter,
										    agent__okuma_okuma__platform__private__read_machine_cycle_time,
										    agent__okuma_okuma__platform__private__read_machine_part_program_name,
                                            agent__okuma_okuma__platform__private__task__read_machine_data} };
//
//int agency__private__load_agents (agent___t** agent, int *number_of_agents)
//{
//
//	if (agent == NULL)
//	{
//		return -100;
//	}
//
//	if (number_of_agents == NULL)
//	{
//		return -200;
//	}
//
//	*agent = agent__config;
//	*number_of_agents = sizeof(agent__config) / sizeof(agent___t);
//
//	return 0;
//}
//



int agency__config (agency__config_t* config)
{
	 
	int rc;
	int i;
	int j;
	utils__printf__config_t pf_config;
	FILE* f;
	int number_of_agents;
	size_t size;
	const char* fn;
	//agent___t* agent;
	//agent___t* ag;

	agent__fanuc_focas__config_t fanuc_focas__config;



	fn = "agency__config()";


	if (agency == NULL)
	{
		//utils__printf__error(&agent_so->subagent.pf, fn, -100, "agent__siemens_open62541__private__check_config() returned %d", rc);
		return -100;
	}


	/*
	 * copy configuration data
	 */
	agency->config.file_name = config->file_name;
	agency->config.buffer = config->buffer;
	agency->config.buffer_len = config->buffer_len;

	//rc = agency__private__load_agents(&agent, &number_of_agents);
	//if (rc != 0)
	//{
	//	return -200;
	//}

#if enrico == 1

	number_of_agents = sizeof(agent__config) / sizeof(agent___t);

	size = sizeof(agent_t) * number_of_agents;
	agency->agent = (agent_t*)malloc(size);
	if (agency->agent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "malloc() error");
		return -200;
	}
	memset(agency->agent, '\0', size);


	agency->number_of_agents = number_of_agents;

	for (i = 0; i < agency->number_of_agents; i++)
	{
		agency->agent[i].name = agent__config[i].name;
		agency->agent[i].machine_section_name = agent__config[i].machine_section_name;
	}
	//ag = agent;
	//for (i = 0; i < agency->number_of_agents; i++)
	//{
	//	agency->agent[i].name = agent->name;
	//	agency->agent[i].machine_section_name = agent->machine_section_name;
	//	agent++;
	//}

	


	//rc = agent__siemens_open62541__private__check_config((void*)config);
	//if (rc != 0)
	//{
	//	utils__printf__error(&agent_so->subagent.pf, fn, -100, "agent__siemens_open62541__private__check_config() returned %d", rc);
	//	return -100;
	//}

#endif


	if (config->file_name != NULL)
	{
		f = fopen(config->file_name, "rb");
		if (f == NULL)
		{
			//utils__printf__error(&a->pf, fn, -200, "file %s not found", a->config.file_name);
			return -300;
		}
		fclose(f);
	}
	else if ((config->buffer != NULL) && (config->buffer_len > 0))
	{

	}
	else
	{
		return -400;
	}



	/*
	 * read configuration file
	 */
	rc = agency__read_configuration_file();

	if (rc != 0)
	{		
		utils__printf__error(&agency->pf, fn, -200, "agency__private__load_agency_configuration_data() returned error %d", rc);
		return -500;
	}


#if enrico == 1

	// All'atto della riconfigurazione della printf forzare ENABLE_TABLE_LAYOUT e ENABLE_AGENT_NAME_ON_OUPUT
	
    rc = agency__private__load_machines_configuration_data(agency);
	if (rc != 0)
	{
		utils__printf__error(&agency->pf, fn, -200, "agency__private__load_machines_configuration_data() returned error %d", rc);
		return -600;
	}


	for (i = 0; i < agency->number_of_agents; i++)
	{
		if (agency->agent[i].machine_index < 0)
		{
			agency->agent[i].number_of_machines = 0;
		}
		else
		{
			agency->agent[i].number_of_machines = agency->agent[i].machine_index + 1;
		}
	}

	//if (agent_so->number_of_machines == 0)
	//{
	//	utils__printf__warning(&agent_so->subagent.pf, fn, -200, "agent__load_agent_configuration_data() number_of_machines = 0");
	//}

	//	//if (agent_so->number_of_machines == 0)
	//{
	//	utils__printf__warning(&agent_so->subagent.pf, fn, -200, "agent__load_agent_configuration_data() number_of_machines = 0");
	//}

	//

	///*
	// * allocate 
	// */
	//size = sizeof(agent__siemens_open62541__machine_t) * agent_so->number_of_machines;

	//agent_so->machine = (agent__siemens_open62541__machine_t*) malloc(size);
	//if (agent_so->machine == NULL)
	//{
	//	utils__printf__error(NULL, fn, -100, "malloc() error");
	//	return -100;
	//}
	//memset(agent_so->machine, '\0', size);


#endif


	fanuc_focas__config.file_name = config->file_name;
	fanuc_focas__config.buffer = config->buffer;
	fanuc_focas__config. buffer_len = config->buffer_len;

	rc = agent__fanuc_focas__config (&fanuc_focas__config);

	/*
	 * copy agency's config data to all of the machines
	 */

#if enrico == 1

	for (i = 0; i < agency->number_of_agents; i++)
	{
		
		for (j = 0; j < agency->agent[i].number_of_machines; j++)
		{

			rc = utils__printf__init(&agency->agent[i].machine[j].pf);


			if (rc != 0)
			{
				utils__printf__error(&agency->pf, fn, -200, "utils__printf__init() returned error %d", rc);
				return -700;
			}

			memset(&pf_config, 0, sizeof(pf_config));

			pf_config.enable_printf = agency->pf.config.enable_printf;
			pf_config.enable_log_file = agency->pf.config.enable_log_file;
			pf_config.log_file_name = agency->pf.config.log_file_name;
			pf_config.log_file_name_len = strlen(agency->pf.config.log_file_name);
			pf_config.max_log_file_lines_per_minute = agency->pf.config.max_log_file_lines_per_minute;
			pf_config.enable_table_layout_output = agency->pf.config.enable_table_layout_output;
			pf_config.enable_application_name_on_output = agency->pf.config.enable_application_name_on_output;
			pf_config.application_name = agency->name;
			pf_config.application_name_len = strlen(agency->name);

			rc = utils__printf__config(&agency->agent[i].machine[j].pf, &pf_config);
			if (rc != 0)
			{
				utils__printf__error(NULL, fn, -300, "utils__printf__config() returned %d", rc);
				return -800;
			}

			strcpy(agency->agent[i].machine[j].config.agent_name, agency->agent[i].name);


			agency->agent[i].machine[j].config.connect_to_machine = agent__config[i].connect_to_machine;
			agency->agent[i].machine[j].config.read_machine_part_counter = agent__config[i].read_machine_part_counter;
			agency->agent[i].machine[j].config.read_machine_cycle_time = agent__config[i].read_machine_cycle_time;
			agency->agent[i].machine[j].config.read_machine_part_program_name = agent__config[i].read_machine_part_program_name;
			agency->agent[i].machine[j].config.read_machine_data_stream = agent__config[i].read_machine_data_stream;


		 //   agency->agent[i].machine[j].config.connect_to_machine = agent->connect_to_machine;
			//agency->agent[i].machine[j].config.read_machine_part_counter = agent->read_machine_part_counter;
			//agency->agent[i].machine[j].config.read_machine_cycle_time = agent->read_machine_cycle_time;
			//agency->agent[i].machine[j].config.read_machine_part_program_name = agent->read_machine_part_program_name;

			
		

			agency->agent[i].machine[j].thread_sleep_time = agency->config_2.thread_sleep_time * 1000;
			agency->agent[i].machine[j].thread_ticks = 0;
			agency->agent[i].machine[j].thread_stop_request = 0;
			agency->agent[i].machine[j].config_2.probability_of_success_of_events_in_simulation_mode = agency->config_2.probability_of_success_of_events_in_simulation_mode;
			agency->agent[i].machine[j].configured = 1;

		}


		if (agency->agent[i].number_of_machines > 0)
		{
			agency->agent[i].configured = 1;
		}

		/*agent++;*/
	}


#endif
	


#if 0
	for (i = 0; i < agent_so->number_of_machines; i++)
	{
		agent_so->subagent.machine[i].config.connect_to_machine = agent__siemens_open62541__connect_to_machine;
		agent_so->subagent.machine[i].config.md = (int) i;


		/*
		 * just for debugging
		 */
		

		//agent_so->subagent.machine[i].config_2.probability_of_success_of_events_in_simulation_mode = agent_so->subagent.config_2.probability_of_success_of_events_in_simulation_mode;


		rc = utils__printf__init(&agent_so->subagent.machine[i].pf);

		if (rc != 0)
		{
			utils__printf__error(&agent_so->subagent.pf, fn, -200, "utils__printf__init() returned error %d", rc);
			return -1100;
		}


		pf_config.enable_printf = agent_so->subagent.pf.config.enable_printf;
		pf_config.enable_log_file = agent_so->subagent.pf.config.enable_log_file;
		pf_config.log_file_name = agent_so->subagent.pf.config.log_file_name;
		pf_config.log_file_name_len = strlen(agent_so->subagent.pf.config.log_file_name);
		pf_config.max_log_file_lines_per_minute = agent_so->subagent.pf.config.max_log_file_lines_per_minute;
		pf_config.enable_table_layout_output = agent_so->subagent.pf.config.enable_table_layout_output;
		pf_config.enable_application_name_on_output = agent_so->subagent.pf.config.enable_application_name_on_output;
		pf_config.application_name = agent_so->application_name;
		pf_config.application_name_len = strlen(agent_so->application_name);

		rc = utils__printf__config(&agent_so->subagent.machine[i].pf, &pf_config);

		if (rc != 0)
		{
			utils__printf__error(&agent_so->subagent.pf, fn, -200, "utils__printf__config() returned error %d", rc);
			return -1100;
		}


		agent_so->subagent.machine[i].config.read_part_counter = agent__siemens_open62541__read_machine_part_counter;
		agent_so->subagent.machine[i].config.read_cycle_time = agent__siemens_open62541__read_machine_cycle_time;
		agent_so->subagent.machine[i].config.read_part_program_name = agent__siemens_open62541__read_machine_part_program_name;

		agent_so->subagent.machine[i].configured = 1;

	}
	

	agent_so->configured = 1;
#endif



	///*
	// * srand() must be called once per thread
	// */
	//t = time(NULL);
	//if (t < 0)
	//{
	//	seed = 100;
	//}
	//else
	//{
	//	seed = (unsigned int)t;
	//}
	//srand(seed);



	//utils__printf__error(&agency->pf, fn, -200, "agents__load_machines_configuration_data() returned error %d", rc);



	agency->configured = 1;

	return 0;

	//so->agent_configuration_file_name[0] = '\0';

	//if (conf->mode == 0)
	//{

	//	len = strlen(conf->file_name);

	//	if (len >= sizeof(so->agent_configuration_file_name))
	//	{
	//		utils__printf__error(&so->pf, fn, -200, "the configuration file name is too long", fn);
	//		return -200;
	//	}

	//	memcpy(so->agent_configuration_file_name, conf->file_name, len);
	//	so->agent_configuration_file_name[len] = '\0';
	//}
	//else if (conf->mode == 1)
	//{
	//	;
	//}
	//else if (conf->mode == 2)
	//{
	//	len = strlen(so->agent_default_configuration_file_name);

	//	if (len >= sizeof(so->agent_configuration_file_name))
	//	{
	//		utils__printf__error(&so->pf, fn, -200, "the default configuration file name is too long", fn);
	//		return -300;
	//	}

	//	memcpy(so->agent_configuration_file_name, so->agent_default_configuration_file_name, len);
	//	so->agent_configuration_file_name[len] = '\0';
	//}
	//else
	//{
	//	utils__printf__error(&so->pf, fn, -300, "mode must be: 0, 1, or 2", fn);
	//	return -400;
	//}

	//so->config_mode = conf->mode;


	


	//for (i = 0; i < so->number_of_machines; i++)
	//{
	//	if (so->machine[i].conf.operating_mode == 1)
	//	{

	//		so->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__simulated;
	//		so->machine[i].disconnect_from_machine = agent__siemens_open62541__private__disconnect_from_machine__simulated;

	//		so->machine[i].read_connection_status = agent__siemens_open62541__private__read_connection_status__simulated;
	//		so->machine[i].read_production_status = agent__siemens_open62541__private__read_production_status__simulated;
	//		so->machine[i].read_alarm_status = agent__siemens_open62541__private__read_alarm_status__simulated;

	//		so->machine[i].read_part_counter = agent__siemens_open62541__private__read_part_counter__simulated;
	//		so->machine[i].read_cycle_time = agent__siemens_open62541__private__read_cycle_time__simulated;
	//		so->machine[i].read_part_program_name = agent__siemens_open62541__private__read_part_program_name__simulated;


	//	}
	//	else
	//	{

	//		so->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__real;
	//		so->machine[i].disconnect_from_machine = agent__siemens_open62541__private__disconnect_from_machine__real;

	//		so->machine[i].read_connection_status = agent__siemens_open62541__private__read_connection_status__real;
	//		so->machine[i].read_production_status = agent__siemens_open62541__private__read_production_status__real;
	//		so->machine[i].read_alarm_status = agent__siemens_open62541__private__read_alarm_status__real;

	//		so->machine[i].read_part_counter = agent__siemens_open62541__private__read_part_counter__real;
	//		so->machine[i].read_cycle_time = agent__siemens_open62541__private__read_cycle_time__real;
	//		so->machine[i].read_part_program_name = agent__siemens_open62541__private__read_part_program_name__real;

	//	}
	//}


	//for (i = 0; i < so->number_of_machines; i++)
	//{
	//	so->machine[i].connection_status = 0;
	//	so->machine[i].part_counter_simulated = so->machine[i].conf.part_counter_initial_value_in_simulation_mode;
	//	so->machine[i].cycle_time_simulated = so->machine[i].conf.average_cycle_time_in_simulation_mode_seconds;
	//}


	//so->configured = 1;


	return 0;
}







#if 0
int siemens_open62541__config (siemens_open62541__config_t* config)
{

	int rc;
	int i;
	size_t len;
	utils__sdb__config_t sdb_config;
	utils__printf__config_t pf_config;


	if (config == NULL)
	{
		return -100;
	}

	so->agent_configuration_file_name[0] = '\0';

	if (config->mode == 0)
	{

		len = strlen(config->file_name);

		if (len >= sizeof(so->agent_configuration_file_name))
		{
			utils__printf__error(&so->pf, fn, -200, "the configuration file name is too long", fn);
			return -200;
		}

		memcpy(so->agent_configuration_file_name, config->file_name, len);
		so->agent_configuration_file_name[len] = '\0';
	}
	else if (config->mode == 1)
	{
		;
	}
	else if (config->mode == 2)
	{
		len = strlen(so->agent_default_configuration_file_name);

		if (len >= sizeof(so->agent_configuration_file_name))
		{
			utils__printf__error(&so->pf, fn, -200, "the default configuration file name is too long", fn);
			return -300;
		}

		memcpy(so->agent_configuration_file_name, so->agent_default_configuration_file_name, len);
		so->agent_configuration_file_name[len] = '\0';
	}
	else
	{
		utils__printf__error(&so->pf, fn, -300, "mode must be: 0, 1, or 2", fn);
		return -400;
	}

	so->config_mode = config->mode;


	(void)utils__sdb__init(&so->sdb);

	memset(&sdb_config, 0, sizeof(sdb_config));

	sdb_config.buffer = so->sdb_buffer;
	sdb_config.buffer_size = sizeof(so->sdb_buffer);
	sdb_config.name = so->sdb_name;
	sdb_config.name_len = so->sdb_name_len;
	sdb_config.value = so->sdb_value;
	sdb_config.value_len = so->sdb_value_len;
	sdb_config.encoding = so->sdb_encoding;
	sdb_config.fields_max = SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX;

	rc = utils__sdb__config(&so->sdb, &sdb_config);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -100, "utils__sdb__config() returned %d", fn, rc);
		return -500;
	}


	/*
	 * null the configuration structure
	 */
	memset(&so->config, 0, sizeof(siemens_open62541__secondary_config_t));

	/*
	 * read the configuration file or buffer and extract data for the subagent
	 */
	rc = siemens_open62541__private__load_application_configuration();
	if (rc != 0)
	{
		printf("%s - error - siemens_open62541__private__load_application_configuration() returned %d\n", fn, rc);
		return -1000;
	}


	/*
	 * read the configuration file or buffer and extract data for the machines
	 */
	rc = siemens_open62541__private__load_machines_configuration();
	if (rc != 0)
	{
		printf("%s - error - siemens_open62541__private__load_machines_configuration() returned %d\n", fn, rc);
		return -1100;
	}



	/*
	 * reconfigure the printf subsystem with user's data contained in the configuration file
	 */
	rc = utils__printf__init(&so->pf);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -300, "utils__printf__init() returned %d", fn, rc);
		return -1200;
	}


	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = so->config.enable_printf;
	pf_config.enable_log_file = so->config.enable_log_file;
	pf_config.log_file_name = so->config.log_file_name;
	pf_config.log_file_name_len = strlen(so->config.log_file_name);
	pf_config.max_log_file_lines_per_minute = so->config.max_log_file_lines_per_minute;
	pf_config.enable_table_layout_output = so->config.enable_table_layout_output;
	pf_config.enable_application_name_on_output = so->config.enable_application_name_on_output;
	pf_config.application_name = so->agent_name_and_version;
	pf_config.application_name_len = strlen(so->agent_name_and_version);


	rc = utils__printf__config(&so->pf, &pf_config);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -400, "utils__printf__config() returned %d", fn, rc);
		return -1300;
	}


	for (i = 0; i < so->machine_count; i++)
	{
		if (so->machine[i].config.simulated == 1)
		{

			so->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__simulated;
			so->machine[i].disconnect_from_machine = siemens_open62541__private__disconnect_from_machine__simulated;

			so->machine[i].read_connection_status = siemens_open62541__private__read_connection_status__simulated;
			so->machine[i].read_production_status = siemens_open62541__private__read_production_status__simulated;
			so->machine[i].read_alarm_status = siemens_open62541__private__read_alarm_status__simulated;

			so->machine[i].read_part_counter = siemens_open62541__private__read_part_counter__simulated;
			so->machine[i].read_cycle_time = siemens_open62541__private__read_cycle_time__simulated;
			so->machine[i].read_part_program_name = siemens_open62541__private__read_part_program_name__simulated;


		}
		else
		{

			so->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__real;
			so->machine[i].disconnect_from_machine = siemens_open62541__private__disconnect_from_machine__real;

			so->machine[i].read_connection_status = siemens_open62541__private__read_connection_status__real;
			so->machine[i].read_production_status = siemens_open62541__private__read_production_status__real;
			so->machine[i].read_alarm_status = siemens_open62541__private__read_alarm_status__real;

			so->machine[i].read_part_counter = siemens_open62541__private__read_part_counter__real;
			so->machine[i].read_cycle_time = siemens_open62541__private__read_cycle_time__real;
			so->machine[i].read_part_program_name = siemens_open62541__private__read_part_program_name__real;

		}
	}


	for (i = 0; i < so->machine_count; i++)
	{
		so->machine[i].connection_status = 0;
		so->machine[i].part_counter_simulated = so->machine[i].config.part_counter_initial_value_in_simulation_mode;
		so->machine[i].cycle_time_simulated = so->machine[i].config.average_cycle_time_in_simulation_mode_seconds;
	}


	so->configured = 1;


	return 0;
}
#endif