#include "agency_private.h"


static int load_entry__machine_section(void* arg, const char* section_name, size_t section_name_len);
static int load_entry__id(void* arg, const char* data, size_t data_len);
static int load_entry__name(void* arg, const char* data, size_t data_len);
static int load_entry__networked(void* arg, const char* data, size_t data_len);
static int load_entry__run(void* arg, const char* data, size_t data_len);
static int load_entry__simulation(void* arg, const char* data, size_t data_len);
static int load_entry__enable_printf(void* p, const char* data, size_t data_len);

static int load_entry__opc_ua_server_ipv4_address(void* arg, const char* data, size_t data_len);
static int load_entry__opc_ua_server_ipv4_port(void* arg, const char* data, size_t data_len);
static int load_entry__opc_ua_server_user_name(void* arg, const char* data, size_t data_len);
static int load_entry__opc_ua_server_password(void* arg, const char* data, size_t data_len);
static int load_entry__opc_ua_server_node_id(void* arg, const char* data, size_t data_len);
static int load_entry__opc_ua_client_private_key(void* arg, const char* data, size_t data_len);
static int load_entry__opc_ua_client_certificate_file(void* arg, const char* data, size_t data_len);
static int load_entry__fanuc_tcp_server_ipv4_address(void* arg, const char* data, size_t data_len);
static int load_entry__fanuc_tcp_server_ipv4_port(void* arg, const char* data, size_t data_len);
static int load_entry__okuma_tcp_server_ipv4_address(void* arg, const char* data, size_t data_len);
static int load_entry__okuma_tcp_server_ipv4_port(void* arg, const char* data, size_t data_len);
static int load_entry__okuma_receive_buffer_size(void* arg, const char* data, size_t data_len);
static int load_entry__okuma_send_buffer_size(void* arg, const char* data, size_t data_len);
static int load_entry__okuma_http_request_string(void* arg, const char* data, size_t data_len);



static int load_entry__opc_ua_server_part_counter_node_path(void* ag, const char* data, size_t data_len); //carmelo
static int load_entry__opc_ua_server_cycle_time_node_path(void* ag, const char* data, size_t data_len);//carmelo
static int load_entry__opc_ua_server_part_program_name_node_path(void* ag, const char* data, size_t data_len);//carmelo
static int load_entry__opc_ua_server_machine_status_node_path(void* ag, const char* data, size_t data_len);//carmelo
static int load_entry__opc_ua_server_alarm_status_node_path(void* ag, const char* data, size_t data_len);//carmelo



/*
 * name to callback function map
 */
static utils__sdb__name_callback_t names_values[] =
{

  {"ID",                                            load_entry__id                               },
  {"NAME",                                          load_entry__name                             },  
  {"NETWORKED",                                             load_entry__networked                                },
  {"RUN",                                             load_entry__run                                },
  {"SIMULATION",                                             load_entry__simulation                                },
  {"ENABLE PRINTF",                                             load_entry__enable_printf                                },


	//{"ENABLE LOG FILE",                                           load_entry__enable_log_file                              },
	//{"LOG FILE",                                                  load_entry__log_file                                     },
	//{"MAX LOG FILE LINES PER MINUTE",                             load_entry__max_log_file_lines_per_minute                },
	//{"PROBABILITY OF SUCCESS OF EVENTS IN SIMULATION MODE",       load_entry__probability_of_success_in_simulation_mode    },
	//{"THREAD SLEEP TIME",                                         load_entry__thread_sleep_time                            }

  {"OPC-UA SERVER IP-V4 ADDRESS",                   load_entry__opc_ua_server_ipv4_address         },
  {"OPC-UA SERVER IP-V4 PORT",                      load_entry__opc_ua_server_ipv4_port            },
  {"OPC-UA SERVER USER NAME",                       load_entry__opc_ua_server_user_name             },
  {"OPC-UA SERVER PASSWORD",                        load_entry__opc_ua_server_password              },
  {"OPC-UA SERVER NODE ID",                         load_entry__opc_ua_server_node_id              },  //carmelo
  {"OPC-UA SERVER PART COUNTER NODE PATH",          load_entry__opc_ua_server_part_counter_node_path       },//carmelo
  {"OPC-UA SERVER CYCLE TIME NODE PATH",            load_entry__opc_ua_server_cycle_time_node_path        },//carmelo
  {"OPC-UA SERVER PART PROGRAM NAME NODE PATH",     load_entry__opc_ua_server_part_program_name_node_path    },//carmelo
  {"OPC-UA SERVER STATUS RUN NODE PATH",            load_entry__opc_ua_server_machine_status_node_path    },//carmelo
  {"OPC-UA SERVER STATUS ALARM NODE PATH",          load_entry__opc_ua_server_alarm_status_node_path    },//carmelo

  {"OPC-UA CLIENT PRIVATE KEY FILE",               load_entry__opc_ua_client_private_key           },
  {"OPC-UA CLIENT PRIVATE CERTIFICATE FILE",       load_entry__opc_ua_client_certificate_file      },

  {"FANUC-TCP SERVER IP-V4 ADDRESS",                load_entry__fanuc_tcp_server_ipv4_address      },
  {"FANUC-TCP SERVER IP-V4 PORT",                   load_entry__fanuc_tcp_server_ipv4_port        },

  {"OKUMA-TCP SERVER IP-V4 ADDRESS",                load_entry__okuma_tcp_server_ipv4_address      },
  {"OKUMA-TCP SERVER IP-V4 PORT",                   load_entry__okuma_tcp_server_ipv4_port        },
  {"OKUMA-TCP RECEIVE BUFFER SIZE",                   load_entry__okuma_receive_buffer_size        },
  {"OKUMA-TCP SEND BUFFER SIZE",                   load_entry__okuma_send_buffer_size        },
  {"OKUMA-TCP HTTP REQUEST STRING",                   load_entry__okuma_http_request_string        }




};




/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */


int agency__private__load_machines_configuration_data (void)
{

	int rc;
	//FILE* f;
	int i;
	//int j;
	size_t record_number;
	size_t start_record;
	size_t names_values_max;
	int done;
	size_t number_of_sections;
	size_t size;
	int end_of_file;
	const char* fn;
	utils__sdb__section_callback_t section_callback;



	fn = "agency__load_machines_configuration_data()";

	//if (ag == NULL)
	//{
	//	utils__printf__error(NULL, fn, -100, "agents are null");
	//	return -100;
	//}



	number_of_sections = 0;
	rc = 0;
	end_of_file = 0;
	record_number = 0;


	
	/*
	 * count the number of machines for each agent
	 */
	start_record = 1;

	for (i = 0; i < agency->number_of_agents; i++)
	{
	
		if (agency->config.file_name != NULL)
		{			
			rc = utils__sdb__count_sections_from_file(&agency->sdb, agency->config.file_name, agency->agent[i].machine_section_name, start_record, &number_of_sections, &end_of_file);
			if (rc != 0)
			{
				//utils__printf__error(&subagent->pf, fn, -1000, "utils__sdb__count_sections_from_file() returned %d", rc);
				return -1000;
			}
		}
		else
		{
			rc = utils__sdb__count_sections_from_buffer(&agency->sdb, agency->config.file_name, agency->agent[i].machine_section_name, start_record, &number_of_sections, &end_of_file);
			if (rc != 0)
			{
				//utils__printf__error(&subagent->pf, fn, -1100, "utils__sdb__count_sections_from_buffer() returned %d", rc);
				return -1100;
			}
		}

		if (number_of_sections > 0)
		{
			/*
			 * Allocate memory for the machines
			 */
			size = sizeof(machine_t) * number_of_sections;

			agency->agent[i].machine = (machine_t*)malloc(size);
			if (agency->agent[i].machine == NULL)
			{
				//utils__printf__error(&subagent->pf, fn, -1100, "utils__sdb__count_sections_from_buffer() returned %d", rc);
				return -1100;
			}

			memset(agency->agent[i].machine, '\0', size);

			//agency->agent[i].machine_index = (int) number_of_sections;

			//utils__printf__error(&subagent->pf, fn, -1200, "can't find any [%s] sections in the configuration file or buffer", subagent->config.agent_machines_section_name);
		}
		else
		{
			//utils__printf__warning(&agency->pf, fn, -1200, "can't find any [%s] sections in the configuration file or buffer", agency->config.agent_machines_section_name);
		}

	}





	//if (agency->machine == NULL)
	//{
	//	//utils__printf__error(&subagent->pf, fn, -1300, "delegate->machine - malloc() error");
	//	return -1300;
	//}

	//memset(a->machine, '\0', size);



	//subagent->machine_index = (int) number_of_sections;

	names_values_max = sizeof(names_values) / sizeof(utils__sdb__name_callback_t);
	//num_of_machines = (int) number_of_sections;
	//a->machine_counter = -1;


	for (i = 0; i < agency->number_of_agents; i++)
	{

		agency->agent[i].machine_index = -1;

		/*
		 * example: [SIEMENS-OPEN62541 MACHINE]
		 */
		memset(&section_callback, 0, sizeof(section_callback));

		
		section_callback.name = agency->agent[i].machine_section_name;
		section_callback.function = load_entry__machine_section;
		


		done = 0;
		start_record = 1;
		do
		{

			if (agency->config.file_name != NULL)
			{
				rc = utils__sdb__read_configuration_from_file((void *)&agency->agent[i], &agency->sdb, agency->config.file_name, &section_callback, names_values, names_values_max, start_record, &record_number, &end_of_file);
			}
			else
			{
				rc = utils__sdb__read_configuration_from_buffer((void*)&agency->agent[i], &agency->sdb, agency->config.file_name, &section_callback, names_values, names_values_max, start_record, &record_number, &end_of_file);
			}

			if (rc != 0)
			{
				if (end_of_file == 0)
				{
					//if (subagent->config.mode == AGENCY__FILE_CONFIG_MODE)
					if (agency->config.file_name != NULL)
					{
						//utils__printf__error(&subagent->pf, fn, -2000, "utils__sdb__read_configuration_file() returned %d", rc);
						return -2000;
					}

					//utils__printf__error(&subagent->pf, fn, -2100, "utils__sdb__read_configuration_from_buffer() returned %d", rc);
					return -2100;
				}

				done = 1;
			}
			else if (end_of_file == 1)
			{
				done = 1;
			}
			else
			{
				start_record = record_number + 1;
			}

		} while (done == 0);


	}

#if 0
	//subagent->machine_index++;


	//if (subagent->machine_index != number_of_sections)
	//{		
	//	//utils__printf__error(&subagent->pf, fn, -2200, "delegate->machine_index = %d - number_of_sections = %d - they must be equal", subagent->machine_index, number_of_sections);
	//	return -2200;
	//}


	//if (subagent->machine_index > 1)
	if (num_of_machines > 1)
	{

		/*
		 * Check for duplicate machines' ID
		 */
		for (i = 0; i < num_of_machines; i++)
		{
			for (j = i + 1; j < num_of_machines; j++)
			{
				//if (subagent->machine[i].config_2.id == subagent->machine[j].config_2.id)
				{
					///utils__printf__error(&delegate->pf, fn_local, -1300, "Duplicate id found - id = %d - i = %d - j = %d", delegate->machine[i].config_2.id, i, j);
					///return -1300;
				}
			}
		}
	}


		/*
		 * Check for potential buffer overflow
		 */
	//	for (i = 0; i < delegate->machine_index; i++)
	//	{

	//		len = strlen(delegate->machine[i].config_2.part_program_name_in_simulation_mode);

	//		if (len > sizeof(delegate->machine[i].part_program_name_simulated))
	//		{
	//			printf("%s - error - len > delegate->machine[%d].part_program_name_utf_8_simulated\n", fn, delegate->machine[i].config_2.id);
	//			utils__printf__error(&delegate->pf, fn_local, -1400, "Duplicate id found - id = %d - i = %d - j = %d", delegate->machine[i].config_2.id, i, j);
	//			return -1400;
	//		}

	//		if (len > sizeof(delegate->machine[i].part_program_name_utf_8))
	//		{
	//			printf("%s - error - len > delegate->machine[%d].part_program_name_utf_8\n", fn, delegate->machine[i].config_2.id);
	//			return -700;
	//		}
	//	}
	//}



	for (i = 0; i < num_of_machines; i++)
	{
		//sprintf(subagent->machine[i].name_and_index, "%s %d", subagent->config.agent_machines_section_name, i + 1);
		//subagent->machine[i].name_and_index_len = strlen(subagent->machine_local[i].name_and_index);
	}



	/*
	 * initialize the utils__printf subsystem
	 */
	for (i = 0; i < num_of_machines; i++)
	{


		//rc = utils__printf__init(&subagent->machine[i].pf);
		//if (rc != 0)
		//{
		//	utils__printf__error(NULL, fn, -200, "utils__printf__init() error");
		//	return -200;
		//}


		///*
		// * configure the utils__printf subsystem
		// */
		//memset(&pf_config, 0, sizeof(pf_config));

		//pf_config.enable_printf = 1;
		//pf_config.enable_log_file = 0;
		//pf_config.log_file_name = "";
		//pf_config.log_file_name_len = 0;
		//pf_config.max_log_file_lines_per_minute = 120;
		//pf_config.enable_table_layout_output = 1;
		//pf_config.enable_application_name_on_output = 0;
		//pf_config.application_name = "";
		//pf_config.application_name_len = 0;

		//rc = utils__printf__config(&subagent->machine_local[i].pf, &pf_config);
		//if (rc != 0)
		//{
		//	utils__printf__error(NULL, fn, -300, "utils__printf__config() returned %d", rc);
		//	return -300;
		//}

	}


	*machine_index = num_of_machines;

#endif

	return 0;
}
 
static int load_entry__machine_section (void* arg, const char* section_name, size_t section_name_len)
{

	const char* fn;
	agent_t* agent;


	fn = "load_entry__machine_section()";

	agent = (agent_t*) arg;

	if ((agent == NULL) || (section_name == NULL) || (section_name_len == 0))
	{
		utils__printf__error(NULL, fn, -100, "a or section name are null pointers");
	}
		

	if (agent->machine_index == -1)
	{
		agent->machine_index = 0;     /* first time */
	}
	else
	{
		agent->machine_index++;
	}


	//if (agency->machine_counter == -1)
	//{
	//	agency->machine_counter = 0;     /* first time */
	//}
	//else
	//{
	//	agency->machine_counter++;
	//}

	return 0;
}

static int load_entry__id (void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__id()";

	agent = (agent_t*)arg;

	///*ag = (agency_t*) ag;*/
	//ag = (agent_t*) agent;

	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void *) agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	/*
	 * id
	 */
	rc = utils__libc__write_int(&machine->config_2.id, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1000, "utils__libc__write_int() returned %d", rc);
		return -1000;
	}

	return 0;
}

static int load_entry__name (void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__name()";


	agent = (agent_t*) arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void *) agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];

	/*
	 * name  
	 */
	rc = utils__libc__write_string(machine->config_2.name, sizeof(machine->config_2.name), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2300, "name - utils__libc__write_string() returned %d", rc);
		return -2300;
	}


	return 0;
}

static int load_entry__networked (void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__networked()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void *) agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	/*
	 * enable printf
	 */
	rc = utils__libc__write_1_or_0(&machine->config_2.networked, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1000, "enable printf - utils__libc__write_1_or_0() returned %d", rc);
		return -1000;
	}

	return 0;

}

static int load_entry__run (void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "agency__load_entry__run()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	/*
	 * run
	 */
	rc = utils__libc__write_1_or_0(&machine->config_2.run, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1000, "enable printf - utils__libc__write_1_or_0() returned %d", rc);
		return -1000;
	}


	return 0;
}

static int load_entry__simulation (void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__simulation()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	/*
	 * run
	 */
	rc = utils__libc__write_1_or_0(&machine->config_2.simulation, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1000, "enable printf - utils__libc__write_1_or_0() returned %d", rc);
		return -1000;
	}




	return 0;
}


static int load_entry__enable_printf(void* p, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	agency_t* ag;
	const char* fn;
	size_t minimum_token_count;


	fn = "load_entry__enable_printf()";


	ag = (agency_t*)p;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)ag, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	/*
	 * enable printf
	 */
	rc = utils__libc__write_1_or_0(&agency->pf.config.enable_printf, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1000, "enable printf - utils__libc__write_1_or_0() returned %d", rc);
		return -1000;
	}



	return 0;
}




static int load_entry__opc_ua_server_ipv4_address(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__opc_ua_server_ipv4_address()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	/*
	 * opc server ip-v4 address
	 */
	rc = utils__libc__write_string(machine->config_2.opc_ua_server_ipv4_address, sizeof(machine->config_2.opc_ua_server_ipv4_address), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	//len = strlen(machine->config_2.fanuc_tcp_server_ipv4_port);
	//rc = utils__libc__validate_ipv4_address(machine->config_2.fanuc_tcp_server_ipv4_port, &len);
	//if (rc != 0)
	//{
	//	//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	//}

	return 0;
}

static int load_entry__opc_ua_server_ipv4_port(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__opc_ua_server_ipv4_port()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];



	rc = utils__libc__write_string(machine->config_2.opc_ua_server_ipv4_port, sizeof(machine->config_2.opc_ua_server_ipv4_port), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
		return -2200;
	}

	//len = strlen(machine->config_2.fanuc_tcp_server_ipv4_port);

	//rc = utils__libc__atoi(machine->config_2.fanuc_tcp_server_ipv4_port, len, &port);
	//if (rc != 0)
	//{
	//	//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	//}
	//else if ((port < 0) || (port >= 0xFFFF))
	//{

	//	//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	//}

	return 0;
}

static int load_entry__opc_ua_server_user_name(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__opc_ua_server_user_name()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	/*
	 * opc server user name
	 */
	rc = utils__libc__write_string(machine->config_2.opc_ua_server_user_name, sizeof(machine->config_2.opc_ua_server_user_name), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
		return -2300;
	}


	return 0;
}

static int load_entry__opc_ua_server_password(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__opc_ua_server_ipv4_address()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];



	/*
	 * opc server password
	 */
	rc = utils__libc__write_string(machine->config_2.opc_ua_server_password, sizeof(machine->config_2.opc_ua_server_password), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;
}




static int load_entry__opc_ua_server_node_id(void* arg, const char* data, size_t data_len)//carmelo
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;
	char tmp_buff[1024];
	size_t len;

	fn = "load_entry__opc_ua_server_node_id()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	/////
	/*
	 * opc server node id
	 */
	rc = utils__libc__write_string(tmp_buff, sizeof(tmp_buff), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	len = strlen(tmp_buff);

    rc = utils__libc__atoi(tmp_buff, len, &machine->config_2.opc_ua_server_node_id);
	if (rc != 0)
	{
		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
		return -2500;
	}
	

	return 0;
}

static int load_entry__opc_ua_client_private_key(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__opc_ua_client_private_key()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];



	/*
	 * opc server private key file
	 */
	rc = utils__libc__write_string(machine->config_2.opc_ua_client_private_key_file, sizeof(machine->config_2.opc_ua_client_private_key_file), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
		return -2200;
	}


	return 0;
}

static int load_entry__opc_ua_client_certificate_file(void* arg, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__opc_ua_client_certificate_file()";


	agent = (agent_t*) arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];



	/*
	 * opc server certificate file
	 */
	rc = utils__libc__write_string(machine->config_2.opc_ua_client_certificate_file, sizeof(machine->config_2.opc_ua_client_certificate_file), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	return 0;
}

static int load_entry__fanuc_tcp_server_ipv4_address(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	size_t len;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__fanuc_tcp_server_ipv4_address()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	rc = utils__libc__write_string(machine->config_2.fanuc_tcp_server_ipv4_address, sizeof(machine->config_2.fanuc_tcp_server_ipv4_address), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	len = strlen(machine->config_2.fanuc_tcp_server_ipv4_address);
	rc = utils__libc__validate_ipv4_address(machine->config_2.fanuc_tcp_server_ipv4_address, &len);
	if (rc != 0)
	{
		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	}

	return 0;
}

static int load_entry__fanuc_tcp_server_ipv4_port(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	size_t len;
	int port;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__fanuc_tcp_server_ipv4_port()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	rc = utils__libc__write_string(machine->config_2.fanuc_tcp_server_ipv4_port, sizeof(machine->config_2.fanuc_tcp_server_ipv4_port), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	len = strlen(machine->config_2.fanuc_tcp_server_ipv4_port);

	rc = utils__libc__atoi(machine->config_2.fanuc_tcp_server_ipv4_port, len, &port);
	if (rc != 0)
	{
		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	}
	else if ((port < 0) || (port >= 0xFFFF))
	{

		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	}

	return 0;
}

static int load_entry__okuma_tcp_server_ipv4_address(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	size_t len;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__okuma_tcp_server_ipv4_address()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	rc = utils__libc__write_string(machine->config_2.okuma_tcp_server_ipv4_address, sizeof(machine->config_2.okuma_tcp_server_ipv4_address), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	len = strlen(machine->config_2.okuma_tcp_server_ipv4_address);
	rc = utils__libc__validate_ipv4_address(machine->config_2.okuma_tcp_server_ipv4_address, &len);
	if (rc != 0)
	{
		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	}

	return 0;
}

static int load_entry__okuma_tcp_server_ipv4_port(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	size_t len;
	int port;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__okuma_tcp_server_ipv4_port()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	rc = utils__libc__write_string(machine->config_2.okuma_tcp_server_ipv4_port, sizeof(machine->config_2.okuma_tcp_server_ipv4_port), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	len = strlen(machine->config_2.okuma_tcp_server_ipv4_port);

	rc = utils__libc__atoi(machine->config_2.okuma_tcp_server_ipv4_port, len, &port);
	if (rc != 0)
	{
		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	}
	else if ((port < 0) || (port >= 0xFFFF))
	{

		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	}

	return 0;
}


static int load_entry__okuma_receive_buffer_size(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	size_t len;
	int buffer_receive_size;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__okuma_receive_buffer_size()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	rc = utils__libc__write_string(machine->config_2.okuma_tcp_receiver_buffer_size, sizeof(machine->config_2.okuma_tcp_receiver_buffer_size), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	len = strlen(machine->config_2.okuma_tcp_receiver_buffer_size);

	rc = utils__libc__atoi(machine->config_2.okuma_tcp_receiver_buffer_size, len, &buffer_receive_size);

	if (buffer_receive_size <= 0)
	{

		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	}

	return 0;
	

}



static int load_entry__okuma_http_request_string(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__okuma_send_buffer_size()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	rc = utils__libc__write_string(machine->config_2.okuma_tcp_http_request_string, sizeof(machine->config_2.okuma_tcp_http_request_string), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	return 0;
}

static int load_entry__okuma_send_buffer_size(void* arg, const char* data, size_t data_len)
{

	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	size_t len;
	int buffer_send_size;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__okuma_send_buffer_size()";


	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];


	rc = utils__libc__write_string(machine->config_2.okuma_tcp_send_buffer_size, sizeof(machine->config_2.okuma_tcp_send_buffer_size), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	len = strlen(machine->config_2.okuma_tcp_send_buffer_size);

	rc = utils__libc__atoi(machine->config_2.okuma_tcp_send_buffer_size, len, &buffer_send_size);

	if (buffer_send_size <= 0)
	{

		//utils__printf__warning(&agency->pf, fn, -2100, "invalid ip-v4 address %d", rc);
	}

	return 0;
}




static int load_entry__opc_ua_server_part_counter_node_path(void* arg, const char* data, size_t data_len)
{


	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t minimum_token_count;
	agent_t* agent;
	machine_t* machine;


	fn = "load_entry__opc_ua_part_counter_node_path()";

	agent = (agent_t*)arg;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	machine = &agent->machine[agent->machine_index];

	/*
	 * opc_ua_server_part_counter_node_path
	 */
	rc = utils__libc__write_string(machine->config_2.opc_ua_server_part_counter_node_path, sizeof(machine->config_2.opc_ua_server_part_counter_node_path), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;

}

static int load_entry__opc_ua_server_cycle_time_node_path (void* arg, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t i;
	size_t minimum_token_count;

	agent_t* agent;
	machine_t* machine;


	agent = (agent_t*) arg;

	fn = "load_entry__opc_ua_server_cycle_time_node_path()";


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	machine = &agent->machine[agent->machine_index];


	/*
	 * opc server cycle time node path
	 */


	rc = utils__libc__write_string(machine->config_2.opc_ua_server_cycle_time_node_path, sizeof(machine->config_2.opc_ua_server_cycle_time_node_path), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;

}

static int load_entry__opc_ua_server_part_program_name_node_path(void* arg, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t i;
	size_t minimum_token_count;

	agent_t* agent;
	machine_t* machine;


	agent = (agent_t*)arg;

	fn = "load_entry__opc_ua_server_part_program_name_node_path()";


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	machine = &agent->machine[agent->machine_index];


	/*
	 * opc server cycle time node path
	 */


	rc = utils__libc__write_string(machine->config_2.opc_ua_server_part_program_name_node_path, sizeof(machine->config_2.opc_ua_server_part_program_name_node_path), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;
}

static int load_entry__opc_ua_server_machine_status_node_path(void* arg, const char* data, size_t data_len) //carmelo
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t i;
	size_t minimum_token_count;

	agent_t* agent;
	machine_t* machine;


	agent = (agent_t*)arg;

	fn = "load_entry__opc_ua_server_machine_status_node_path()";


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	machine = &agent->machine[agent->machine_index];


	/*
	 * opc server cycle time node path
	 */


	rc = utils__libc__write_string(machine->config_2.opc_ua_server_machine_status_node_path, sizeof(machine->config_2.opc_ua_server_machine_status_node_path), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;
}


static int load_entry__opc_ua_server_alarm_status_node_path(void* arg, const char* data, size_t data_len) //carmelo
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	size_t i;
	size_t minimum_token_count;

	agent_t* agent;
	machine_t* machine;


	agent = (agent_t*)arg;

	fn = "load_entry__opc_ua_serveralarm_status_node_path()";


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*)agent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	machine = &agent->machine[agent->machine_index];


	/*
	 * opc server cycle time node path
	 */


	rc = utils__libc__write_string(machine->config_2.opc_ua_server_alarm_status_node_path, sizeof(machine->config_2.opc_ua_server_alarm_status_node_path), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;
}


//static int agency__load_machine_opc_server_nodes_data(void* ag, const char* data, size_t data_len)
//{
//	int rc;
//	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	agency_t* ag;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "agency__load_machine_opc_server_nodes_data()";
//
//
//	minimum_token_count = 3;
//	tokens_max = AGENCY__CONFIG__TOKENS_MAX;
//
//	rc = agency__private__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	ag = (agency_t*) a;
//	i = agency->machine_counter;
//	machine = &agency->machine[i];
//
//
//
//	/*
//	 * opc server part counter node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_ua_server_part_counter_node_path, sizeof(machine->config_2.opc_ua_server_part_counter_node_path), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	/*
//	 * opc server cycle time node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_ua_server_cycle_time_node_path, sizeof(machine->config_2.opc_ua_server_cycle_time_node_path), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
//		return -2200;
//	}
//
//
//	/*
//	 * opc server part program name node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_ua_server_part_program_name_node_path, sizeof(machine->config_2.opc_ua_server_part_program_name_node_path), tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
//		return -2300;
//	}
//
//
//	return 0;
//}






//
//
///*
//
//
///*
// * example of config file entry:
// *
// * MACHINE PLATE DATA = UTIMAC; SCN32HT; 1234; 2018
// *
// * tokens[0] = UTIMAC                      (MANUFACTURER)
// * tokens[1] = SCN32HT                     (MODEL)
// * tokens[2] = 1234                        (SERIAL NUMBER)
// * tokens[3] = 2018                        (MANUFACTURE YEAR)
// *
// */
//static int agency__load_machine_plate_data (void* ag, const char* data, size_t data_len)
//{
//
//	int rc;
//	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	agency_t* ag;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "agency__load_machine_plate_data()";
//
//
//	minimum_token_count = 4;
//	tokens_max = AGENCY__CONFIG__TOKENS_MAX;
//
//	rc = agency__private__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	ag = (agency_t*) a;
//	i = agency->machine_counter;
//	machine = &agency->machine[i];
//
//
//	/*
//	 * manufacturer
//	 */
//	rc = utils__libc__write_string(machine->config_2.manufacturer, sizeof(machine->config_2.manufacturer) , tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		utils__printf__error(&agency->pf, fn, -1000, "utils__libc__write_string() returned %d", rc);
//		return -1000;
//	}
//
//
//	/*
//	 * model
//	 */
//	rc = utils__libc__write_string(machine->config_2.model, sizeof(machine->config_2.model), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		utils__printf__error(&agency->pf, fn, -2000, "utils__libc__write_string() returned %d", rc);
//		return -2000;
//	}
//
//
//	/*
//	 * serial number
//	 */
//	rc = utils__libc__write_string(machine->config_2.serial_number, sizeof(machine->config_2.serial_number), tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		utils__printf__error(&agency->pf, fn, -3000, "utils__libc__write_string() returned %d", rc);
//		return -3000;
//	}
//
//
//	/*
//	 * manufacture year
//	 */
//	rc = utils__libc__write_string(machine->config_2.manufacture_year, sizeof(machine->config_2.manufacture_year), tokens[3], tokens_len[3]);
//	if (rc != 0)
//	{
//		utils__printf__error(&agency->pf, fn, -4000, "utils__libc__write_string() returned %d", rc);
//		return -4000;
//	}
//
//
//	return 0;
//}
//
///*
// * example of config file entry:
// * 
// * MACHINE OPERATING MODE DATA = NETWORKED; RUN; ACTIVE
// * 
// * tokens[0] = NETWORKED
// * tokens[1] = RUN
// * tokens[2] = ACTIVE
// * 
// */
//static int agency__load_machine_operating_mode_data (void* ag, const char* data, size_t data_len)
//{
//
//	int rc;
//	int tmp_int;
//	const char* option_1;
//	const char* option_2;
//	size_t len_1;
//	size_t len_2;
//	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	agency_t* ag;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "agency__load_machine_operating_mode_data()";
//
//
//	minimum_token_count = 3;
//	tokens_max = AGENCY__CONFIG__TOKENS_MAX;
//
//	rc = agency__private__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	ag = (agency_t*) a;
//	i = agency->machine_counter;
//	machine = &agency->machine[i];
//
//
//	/*
//	 * networked
//	 */	
//	option_1 = "NETWORKED";
//	option_2 = "NOT NETWORKED";
//	len_1 = strlen(option_1);
//	len_2 = strlen(option_2);
//	rc = utils__libc__write_option(&tmp_int, (const char*)tokens[0], tokens_len[0], option_1, len_1, option_2, len_2);
//	if (rc != 0)
//	{
//		utils__printf__error(&agency->pf, fn, -1000, "utils__libc__write_option() returned %d", rc);
//		return -1000;
//	}
//
//	if (tmp_int == 1)
//	{
//		machine->config_2.networked = 1;
//	}
//	else
//	{
//		machine->config_2.networked = 0;
//	}
//
//	/*
//	 * operating_mode
//	 */
//	option_1 = "RUN";
//	option_2 = "SIMULATED";
//	len_1 = strlen(option_1);
//	len_2 = strlen(option_2);
//	rc = utils__libc__write_option(&tmp_int, (const char*) tokens[1], tokens_len[1], option_1, len_1, option_2, len_2);
//	if (rc != 0)
//	{
//		utils__printf__error(&agency->pf, fn, -1000, "utils__libc__write_option() returned %d", rc);
//		return -1000;
//	}
//
//	if (tmp_int == 1)
//	{
//		machine->config_2.operating_mode = 1;
//	}
//	else
//	{
//		machine->config_2.operating_mode = 0;
//	}
//
//
//
//	//rc = utils__libc__write_1_or_0(&machine->config_2.operating_mode, tokens[1], tokens_len[1]);
//	//if (rc != 0)
//	//{
//	//	utils__printf__error(&agency->pf, fn, -2000, "utils__libc__write_1_or_0() returned %d", rc);
//	//	return -2000;
//	//}
//
//
//	/*
//	 * active
//	 */
//	option_1 = "ACTIVE";
//	option_2 = "NOT ACTIVE";
//	len_1 = strlen(option_1);
//	len_2 = strlen(option_2);
//	rc = utils__libc__write_option(&tmp_int, (const char*) tokens[2], tokens_len[2], option_1, len_1, option_2, len_2);
//	if (rc != 0)
//	{
//		utils__printf__error(&agency->pf, fn, -1000, "utils__libc__write_option() returned %d", rc);
//		return -1000;
//	}
//
//	if (tmp_int == 1)
//	{
//		machine->config_2.active = 1;
//	}
//	else
//	{
//		machine->config_2.active = 0;
//	}
//
//	//rc = utils__libc__write_1_or_0(&machine->config_2.active, tokens[2], tokens_len[2]);
//	//if (rc != 0)
//	//{
//	//	utils__printf__error(&agency->pf, fn, -3000, "utils__libc__write_1_or_0() returned %d", rc);
//	//	return -3000;
//	//}
//
//
//	return 0;
//
//}
//
///*
// * example of config file entry:
// *
// * MACHINE GEOLOCATION DATA = FATTI MECCANICA srl; FINOTTO; LEFT 2; SCY45HT-2018
// *
// * tokens[0] = FATTI MECCANICA srl        (ORGANIZATION)
// * tokens[1] = FINOTTO                    (FACILITY)
// * tokens[2] = PRODUCTION                 (DEPARTMENT)
// * tokens[3] = LEFT 2                     (DEPARTMENT LOCATION COORDINATES)
// * tokens[4] = SCY45HT-2018               (NAME)
// *
// */
//static int agency__load_machine_geolocation_data(void* ag, const char* data, size_t data_len)
//{
//
//	int rc;
//	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	agency_t* ag;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "agency__load_machine_geolocation_data()";
//
//
//	minimum_token_count = 4;
//	tokens_max = AGENCY__CONFIG__TOKENS_MAX;
//
//	rc = agency__private__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	ag = (agency_t*) a;
//	i = agency->machine_counter;
//	machine = &agency->machine[i];
//
//
//	/*
//	 * organization
//	 */
//	rc = utils__libc__write_string(machine->config_2.organization, sizeof(machine->config_2.organization), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2000, "organization - utils__libc__write_string() returned %d", rc);
//		return -2000;
//	}
//
//
//	/*
//	 * facility
//	 */
//	rc = utils__libc__write_string(machine->config_2.facility, sizeof(machine->config_2.facility), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2100, "facility - utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	/*
//	 * department
//	 */
//	rc = utils__libc__write_string(machine->config_2.department, sizeof(machine->config_2.department), tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2200, "department - utils__libc__write_string() returned %d", rc);
//		return -2200;
//	}
//
//	/*
//	 * department location coordinates
//	 */
//	rc = utils__libc__write_string(machine->config_2.department_location_coordinates, sizeof(machine->config_2.department_location_coordinates), tokens[3], tokens_len[3]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2200, "department - utils__libc__write_string() returned %d", rc);
//		return -2200;
//	}
//
//
//	return 0;
//}
//
///*
// * example of config file entry:
// *
// * MACHINE TECHNICAL DATA = -; ESA AUTOMATION VT550
// *
// * tokens[0] = -                                  (CNC NAME)
// * tokens[1] = ESA AUTOMATION VT550               (HMI)
// *
// */
//static int agency__load_machine_technical_data(void* ag, const char* data, size_t data_len)
//{
//	int rc;
//	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	agency_t* ag;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "agency__load_machine_technical_data()";
//
//
//	minimum_token_count = 2;
//	tokens_max = AGENCY__CONFIG__TOKENS_MAX;
//
//	rc = agency__private__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	ag = (agency_t*) a;
//	i = agency->machine_counter;
//	machine = &agency->machine[i];
//
//
//	/*
//	 * cnc
//	 */
//	rc = utils__libc__write_string(machine->config_2.cnc, sizeof(machine->config_2.cnc), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2000, "utils__libc__write_string() returned %d", rc);
//		return -2000;
//	}
//
//	/*
//	 * hmi
//	 */
//	rc = utils__libc__write_string(machine->config_2.hmi, sizeof(machine->config_2.hmi), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2100, "utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	
//	return 0;
//}
//
///*
// * examples of config file entry: 
// *
// * 
// * MACHINE FEEDER DATA = FUMAGALLI; A!s13-41; 1234; 2017
// *
// * tokens[0] = FUMAGALLI              (MANUFACTURER)
// * tokens[1] = A;13-41                (MODEL)   (note that !s will be converted to ;)
// * tokens[2] = 1234                   (SERIAL NUMBER)
// * tokens[3] = 2017                   (MANUFACTURE YEAR)
// *
// * 
// * MACHINE FEEDER DATA = -;-;-;-
// *
// * tokens[0] = -                      (MANUFACTURER)
// * tokens[1] = -                      (MODEL)
// * tokens[2] = -                      (SERIAL NUMBER)
// * tokens[3] = -                      (MANUFACTURE YEAR)
// * 
// */
//static int agency__load_machine_feeder_data (void* ag, const char* data, size_t data_len)
//{
//
//	int rc;
//	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	agency_t* ag;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "agency__load_machine_feeder_data()";
//
//
//	minimum_token_count = 4;
//	tokens_max = AGENCY__CONFIG__TOKENS_MAX;
//
//	rc = agency__private__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	ag = (agency_t*) a;
//	i = agency->machine_counter;
//	machine = &agency->machine[i];
//
//
//
//	/*
//	 * feeder manufacturer
//	 */
//	rc = utils__libc__write_string(machine->config_2.feeder_manufacturer, sizeof(machine->config_2.feeder_manufacturer), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	/*
//	 * feeder model
//	 */
//	rc = utils__libc__write_string(machine->config_2.feeder_model, sizeof(machine->config_2.feeder_model), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
//		return -2200;
//	}
//
//
//	/*
//	 * feeder serial number
//	 */
//	rc = utils__libc__write_string(machine->config_2.feeder_serial_number, sizeof(machine->config_2.feeder_serial_number), tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
//		return -2300;
//	}
//
//
//	/*
//	 * feeder manufacture year
//	 */
//	rc = utils__libc__write_string(machine->config_2.feeder_manufacture_year, sizeof(machine->config_2.feeder_manufacture_year), tokens[3], tokens_len[3]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
//		return -2400;
//	}
//
//
//	return 0;
//}
//
//



//
//static int agency__load_machine_opc_server_nodes_data(void* ag, const char* data, size_t data_len)
//{
//	int rc;
//	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	agency_t* ag;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "agency__load_machine_opc_server_nodes_data()";
//
//
//	minimum_token_count = 3;
//	tokens_max = AGENCY__CONFIG__TOKENS_MAX;
//
//	rc = agency__private__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	ag = (agency_t*) a;
//	i = agency->machine_counter;
//	machine = &agency->machine[i];
//
//
//
//	/*
//	 * opc server part counter node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_ua_server_part_counter_node_path, sizeof(machine->config_2.opc_ua_server_part_counter_node_path), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	/*
//	 * opc server cycle time node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_ua_server_cycle_time_node_path, sizeof(machine->config_2.opc_ua_server_cycle_time_node_path), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
//		return -2200;
//	}
//
//
//	/*
//	 * opc server part program name node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_ua_server_part_program_name_node_path, sizeof(machine->config_2.opc_ua_server_part_program_name_node_path), tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&agency->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
//		return -2300;
//	}
//
//
//	return 0;
//}



//  
//
//  {"CONNECTION MONITOR DATA",                         agency__load_connection_timeout_seconds                       },
//	{"CONNECTION TIMEOUT SECONDS",                      agency__load_connection_timeout_seconds                       },
//	{"RECONNECTION ATTEMPTS TIME INTERVAL SECONDS",     agency__load_reconnection_attempts_time_interval_seconds      },
//	{"MAX RECONNECTION ATTEMPTS",                       agency__load_max_reconnection_attempts                        },
//	{"NO RESPONSE TIMEOUT SECONDS",                     agency__load_no_response_timeout_seconds                      },
//
//
//  {"OPC-UA SERVER CONNECTION DATA",                             agency__load_machine_opc_connection_data                              },
//     {"OPC IP-V4 ADDRESS",                               agency__load_machine_opc_ipv4_address                                 },
//     {"OPC IP-V4 PORT",                                  agency__load_machine_opc_ipv4_port                                    },
//     {"OPC USER NAME",                                   agency__load_machine_opc_user_name                                    },
//     {"OPC PASSWORD",                                    agency__load_machine_opc_password                                     },
//     {"OPC CERTIFICATE FILE",                            agency__load_machine_opc_certificate_file                             },
//     {"OPC PRIVATE KEY FILE",                            agency__load_machine_opc_private_key_file                             },
//
//  {"OPC-UA SERVER NODES DATA",                                            agency__load_machine_opc_nodes_data                                   },
//     {"OPC PART COUNTER PATH",                           agency__load_machine_opc_part_counter_path                            },
//     {"OPC CYCLE TIME PATH",                             agency__load_machine_opc_cycle_time_path                              },
//     {"OPC PART PROGRAM NAME PATH",                      agency__load_machine_opc_part_program_name_path                       },
//
//
// {"TCP SERVER CONNECTION DATA",                                agency__load_connection_timeout_seconds                       },
//
//     {"TCP SERVER IP-V4 ADDRESS",                        agency__load_tcp_server_ipv4_address                          },
//     {"TCP SERVER IP-V4 PORT",                           agency__load_tcp_server_ipv4_port                             },
//     {"TCP CLIENT RECEIVE BUFFER SIZE",                  agency__load_tcp_client_receive_buffer_size                   },
//     {"TCP CLIENT SEND STRING",                          agency__load_tcp_client_send_string                           },
//     {"TCP CLIENT ENABLE PRINTF",                        agency__load_tcp_enable_printf                                },
//
//
//  {"CYCLE TIME DATA FROM ",                           agency__load_cycle_time_from_part_counter                     },
//  {"CYCLE TIME FROM PART COUNTER",                    agency__load_cycle_time_from_part_counter                     },
//
//  {"PART PROGRAM NAME FILTER",                        agency__load_part_program_name_filter                         }
//
//
//};





