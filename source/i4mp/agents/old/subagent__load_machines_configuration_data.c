#include "subagent.h"


static int agents__load_entry__machine_section (void* subagent, const char* section_name, size_t section_name_len);

static int subagent__load_machine_id(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_name(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_networked(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_run_mode(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_server_ip_v4_address(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_server_ip_v4_port(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_server_user_name(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_server_password(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_client_private_key(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_client_certificate_file(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_server_part_counter_node_path(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_server_cycle_time_node_path(void* subagent, const char* data, size_t data_len);
static int subagent__load_machine_opc_server_part_program_name_node_path(void* subagent, const char* data, size_t data_len);



/*
 * name to callback function map
 */
static utils__sdb__value_callback_t names_values[] =
{

  {"ID",                                            subagent__load_machine_id                                        },
  {"NAME",                                          subagent__load_machine_name                                      },
  {"NETWORKED",                                     subagent__load_machine_networked                                 },
  {"RUN MODE",                                      subagent__load_machine_run_mode                                  },
  {"OPC SERVER IP-V4 ADDRESS",                      subagent__load_machine_opc_server_ip_v4_address                  },
  {"OPC SERVER IP-V4 PORT",                         subagent__load_machine_opc_server_ip_v4_port                     },
  {"OPC SERVER USER NAME",                          subagent__load_machine_opc_server_user_name                      },
  {"OPC SERVER PASSWORD",                           subagent__load_machine_opc_server_password                       },
  {"OPC SERVER PART COUNTER NODE PATH",             subagent__load_machine_opc_server_part_counter_node_path         },
  {"OPC SERVER CYCLE TIME NODE PATH",               subagent__load_machine_opc_server_cycle_time_node_path           },
  {"OPC SERVER PART PROGRAM NAME NODE PATH",        subagent__load_machine_opc_server_part_program_name_node_path    },
  {"OPC CLIENT PRIVATE KEY FILE",                   subagent__load_machine_opc_client_private_key                    },
  {"OPC CLIENT PRIVATE CERTIFICATE FILE",           subagent__load_machine_opc_client_certificate_file               }

};




/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */


int subagent__load_machines_configuration_data (subagent_t* subagent, int* number_of_machines)
{

	int rc;
	FILE* f;
	int i;
	int j;
	size_t record_number;
	size_t start_record;
	size_t machine_names_values_max;
	int done;
	size_t number_of_sections;
	size_t size;
	int end_of_file;
	const char* fn;
	utils__sdb__section_callback_t section_callback;
	int num_of_machines;


	fn = "agent__load_machines_configuration_data()";

	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "agent is null");
		return -100;
	}

	if (number_of_machines == NULL)
	{
		utils__printf__error(NULL, fn, -200, "number_of_machines is null");
		return -200;
	}

	f = fopen((const char*)subagent->config.file_name, "rb");
	if (f == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -200, "file %s not found", subagent->config.file_name);
		return -200;
	}
	fclose(f);


	number_of_sections = 0;
	rc = 0;
	end_of_file = 0;
	record_number = 0;


	
	/*
	 * count the number of sections, for example: [SIEMENS-OPEN62541 MACHINE]
	 */
	start_record = 1;

	//if (subagent->config.mode == SUBAGENT__FILE_CONFIG_MODE)
	if (1 == 1)
	{
		rc = utils__sdb__count_sections_from_file(&subagent->sdb, subagent->config.file_name, subagent->config.machine_section_name, start_record, &number_of_sections, &end_of_file);
		if (rc != 0)
		{		
			//utils__printf__error(&subagent->pf, fn, -1000, "utils__sdb__count_sections_from_file() returned %d", rc);
			return -1000;
		}
	}
	else
	{
		rc = utils__sdb__count_sections_from_buffer(&subagent->sdb, subagent->config.file_name, subagent->config.machine_section_name, start_record, &number_of_sections, &end_of_file);
		if (rc != 0)
		{			
			//utils__printf__error(&subagent->pf, fn, -1100, "utils__sdb__count_sections_from_buffer() returned %d", rc);
			return -1100;
		}
	}

	if (number_of_sections == 0)
	{		
		//utils__printf__error(&subagent->pf, fn, -1200, "can't find any [%s] sections in the configuration file or buffer", subagent->config.agent_machines_section_name);
		return -1200;
	}



	/*
	 * Allocate memory for the machines
	 */
	size = sizeof(subagent_machine_t) * number_of_sections;

	subagent->machine = (subagent_machine_t*) malloc(size);

	if (subagent->machine == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -1300, "delegate->machine - malloc() error");
		return -1300;
	}

	memset(subagent->machine, '\0', size);

	//subagent->number_of_machines = (int) number_of_sections;

	num_of_machines = (int) number_of_sections;
	subagent->machine_counter = -1;


	/*
	 * example: [SIEMENS-OPEN62541 MACHINE]
	 */
	memset(&section_callback, 0, sizeof(section_callback));

	section_callback.name = subagent->config.machine_section_name;
	section_callback.function = agents__load_entry__machine_section;
	machine_names_values_max = sizeof(names_values) / sizeof(utils__sdb__value_callback_t);


	done = 0;
	start_record = 1;
	do
	{
		//if (subagent->config.mode == SUBAGENT__FILE_CONFIG_MODE)
		if (1 == 1)
		{
			rc = utils__sdb__read_configuration_from_file((subagent_t *) subagent, &subagent->sdb, subagent->config.file_name, &section_callback, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		else
		{
			rc = utils__sdb__read_configuration_from_buffer((subagent_t*)subagent, &subagent->sdb, subagent->config.file_name, &section_callback, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		
		if (rc != 0)
		{
			if (end_of_file == 0)
			{
				//if (subagent->config.mode == SUBAGENT__FILE_CONFIG_MODE)
				if (1 == 1)
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

	}
	while (done == 0);


	//subagent->number_of_machines++;


	//if (subagent->number_of_machines != number_of_sections)
	//{		
	//	//utils__printf__error(&subagent->pf, fn, -2200, "delegate->number_of_machines = %d - number_of_sections = %d - they must be equal", subagent->number_of_machines, number_of_sections);
	//	return -2200;
	//}


	//if (subagent->number_of_machines > 1)
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
	//	for (i = 0; i < delegate->number_of_machines; i++)
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


	*number_of_machines = num_of_machines;

	return 0;
}
 

static int agents__load_entry__machine_section (void* subagent, const char* section_name, size_t section_name_len)
{

	const char* fn;
	subagent_t* sub;

	fn = "subagent__found_section()";

	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "subagent is null");
		return -100;
	}	

	sub = (subagent_t*) subagent;

	if (section_name == NULL)
	{
		utils__printf__error(&sub->pf, fn, -200, "section name is null");
		return -200;
	}

	if (section_name_len == 0)
	{
		utils__printf__error(&sub->pf, fn, -300, "section name len is zero");
		return -300;
	}

	if (sub->machine_counter == -1)
	{
		sub->machine_counter = 0;     /* first time */
	}
	else
	{
		sub->machine_counter++;
	}

	return 0;
}


static int subagent__load_machine_id (void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_id()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];


	/*
	 * id
	 */
	rc = utils__libc__write_int(&machine->config_2.id, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		utils__printf__error(&sub->pf, fn, -1000, "utils__libc__write_int() returned %d", rc);
		return -1000;
	}

	return 0;
}

static int subagent__load_machine_name(void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__write_entry__machine_name()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];
	

	/*
	 * name
	 */
	rc = utils__libc__write_string(machine->config_2.name, sizeof(machine->config_2.name), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2300, "name - utils__libc__write_string() returned %d", rc);
		return -2300;
	}


	return 0;
}

static int subagent__load_machine_networked(void* subagent, const char* data, size_t data_len)
{

	int rc;
	int tmp_int;
	const char* option_1;
	const char* option_2;
	size_t len_1;
	size_t len_2;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;

	fn = "subagent__load_machine_networked()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];


	/*
	 * networked
	 */
	option_1 = "NETWORKED";
	option_2 = "NOT NETWORKED";
	len_1 = strlen(option_1);
	len_2 = strlen(option_2);
	rc = utils__libc__write_option(&tmp_int, (const char*)tokens[0], tokens_len[0], option_1, len_1, option_2, len_2);
	if (rc != 0)
	{
		utils__printf__error(&sub->pf, fn, -1000, "utils__libc__write_option() returned %d", rc);
		return -1000;
	}

	if (tmp_int == 1)
	{
		machine->config_2.networked = 1;
	}
	else
	{
		machine->config_2.networked = 0;
	}


	return 0;


}

static int subagent__load_machine_run_mode(void* subagent, const char* data, size_t data_len)
{

	int rc;
	int tmp_int;
	const char* option_1;
	const char* option_2;
	size_t len_1;
	size_t len_2;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;

	fn = "subagent__load_machine_run_mode()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];


	option_1 = "RUN";
	option_2 = "SIMULATED";
	len_1 = strlen(option_1);
	len_2 = strlen(option_2);
	rc = utils__libc__write_option(&tmp_int, (const char*)tokens[1], tokens_len[1], option_1, len_1, option_2, len_2);
	if (rc != 0)
	{
		utils__printf__error(&sub->pf, fn, -1000, "utils__libc__write_option() returned %d", rc);
		return -1000;
	}

	if (tmp_int == 1)
	{
		machine->config_2.operating_mode = 1;
	}
	else
	{
		machine->config_2.operating_mode = 0;
	}


	return 0;


}


static int subagent__load_machine_opc_server_ip_v4_address (void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_server_ipv4_address()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];



	/*
	 * opc server ipv4 address
	 */
	rc = utils__libc__write_string(machine->config_2.opc_server_ipv4_address, sizeof(machine->config_2.opc_server_ipv4_address), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	return 0;
}


static int subagent__load_machine_opc_server_ip_v4_port(void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_server_ip_v4_port()";


	minimum_token_count = 4;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];



	rc = utils__libc__write_string(machine->config_2.opc_server_ipv4_port, sizeof(machine->config_2.opc_server_ipv4_port), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
		return -2200;
	}


	return 0;
}


static int subagent__load_machine_opc_server_user_name(void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_server_user_name()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];


	/*
	 * opc server user name
	 */
	rc = utils__libc__write_string(machine->config_2.opc_server_user_name, sizeof(machine->config_2.opc_server_user_name), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
		return -2300;
	}


	return 0;
}


static int subagent__load_machine_opc_server_password(void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_server_password()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];



	/*
	 * opc server password
	 */
	rc = utils__libc__write_string(machine->config_2.opc_server_password, sizeof(machine->config_2.opc_server_password), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;
}


static int subagent__load_machine_opc_client_private_key(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_client_private_key()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];



	/*
	 * opc server private key file
	 */
	rc = utils__libc__write_string(machine->config_2.opc_server_private_key_file, sizeof(machine->config_2.opc_server_private_key_file), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
		return -2200;
	}


	return 0;
}


static int subagent__load_machine_opc_client_certificate_file(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_client_certificate_file()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];



	/*
	 * opc server certificate file
	 */
	rc = utils__libc__write_string(machine->config_2.opc_server_certificate_file, sizeof(machine->config_2.opc_server_certificate_file), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	return 0;
}



static int subagent__load_machine_opc_server_part_counter_node_path(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_server_nodes_data()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];



	/*
	 * opc server part counter node path
	 */
	rc = utils__libc__write_string(machine->config_2.opc_server_part_counter_node_path, sizeof(machine->config_2.opc_server_part_counter_node_path), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}


	return 0;
}


static int subagent__load_machine_opc_server_cycle_time_node_path(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_server_nodes_data()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];





	/*
	 * opc server cycle time node path
	 */
	rc = utils__libc__write_string(machine->config_2.opc_server_cycle_time_node_path, sizeof(machine->config_2.opc_server_cycle_time_node_path), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
		return -2200;
	}




	return 0;
}



static int subagent__load_machine_opc_server_part_program_name_node_path(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent_machine_t* machine;


	fn = "subagent__load_machine_opc_server_nodes_data()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;
	i = sub->machine_counter;
	machine = &sub->machine[i];


	/*
	 * opc server part program name node path
	 */
	rc = utils__libc__write_string(machine->config_2.opc_server_part_program_name_node_path, sizeof(machine->config_2.opc_server_part_program_name_node_path), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&sub->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
		return -2300;
	}


	return 0;
}





//static int subagent__load_machine_opc_server_nodes_data(void* subagent, const char* data, size_t data_len)
//{
//	int rc;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* sub;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "subagent__load_machine_opc_server_nodes_data()";
//
//
//	minimum_token_count = 3;
//	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
//
//	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	sub = (subagent_t*)subagent;
//	i = sub->machine_counter;
//	machine = &sub->machine[i];
//
//
//
//	/*
//	 * opc server part counter node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_server_part_counter_node_path, sizeof(machine->config_2.opc_server_part_counter_node_path), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	/*
//	 * opc server cycle time node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_server_cycle_time_node_path, sizeof(machine->config_2.opc_server_cycle_time_node_path), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
//		return -2200;
//	}
//
//
//	/*
//	 * opc server part program name node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_server_part_program_name_node_path, sizeof(machine->config_2.opc_server_part_program_name_node_path), tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
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
//static int subagent__load_machine_plate_data (void* subagent, const char* data, size_t data_len)
//{
//
//	int rc;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* sub;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "subagent__load_machine_plate_data()";
//
//
//	minimum_token_count = 4;
//	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
//
//	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	sub = (subagent_t*)subagent;
//	i = sub->machine_counter;
//	machine = &sub->machine[i];
//
//
//	/*
//	 * manufacturer
//	 */
//	rc = utils__libc__write_string(machine->config_2.manufacturer, sizeof(machine->config_2.manufacturer) , tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		utils__printf__error(&sub->pf, fn, -1000, "utils__libc__write_string() returned %d", rc);
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
//		utils__printf__error(&sub->pf, fn, -2000, "utils__libc__write_string() returned %d", rc);
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
//		utils__printf__error(&sub->pf, fn, -3000, "utils__libc__write_string() returned %d", rc);
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
//		utils__printf__error(&sub->pf, fn, -4000, "utils__libc__write_string() returned %d", rc);
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
//static int subagent__load_machine_operating_mode_data (void* subagent, const char* data, size_t data_len)
//{
//
//	int rc;
//	int tmp_int;
//	const char* option_1;
//	const char* option_2;
//	size_t len_1;
//	size_t len_2;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* sub;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "subagent__load_machine_operating_mode_data()";
//
//
//	minimum_token_count = 3;
//	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
//
//	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	sub = (subagent_t*)subagent;
//	i = sub->machine_counter;
//	machine = &sub->machine[i];
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
//		utils__printf__error(&sub->pf, fn, -1000, "utils__libc__write_option() returned %d", rc);
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
//		utils__printf__error(&sub->pf, fn, -1000, "utils__libc__write_option() returned %d", rc);
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
//	//	utils__printf__error(&sub->pf, fn, -2000, "utils__libc__write_1_or_0() returned %d", rc);
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
//		utils__printf__error(&sub->pf, fn, -1000, "utils__libc__write_option() returned %d", rc);
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
//	//	utils__printf__error(&sub->pf, fn, -3000, "utils__libc__write_1_or_0() returned %d", rc);
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
//static int subagent__load_machine_geolocation_data(void* subagent, const char* data, size_t data_len)
//{
//
//	int rc;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* sub;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "subagent__load_machine_geolocation_data()";
//
//
//	minimum_token_count = 4;
//	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
//
//	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	sub = (subagent_t*)subagent;
//	i = sub->machine_counter;
//	machine = &sub->machine[i];
//
//
//	/*
//	 * organization
//	 */
//	rc = utils__libc__write_string(machine->config_2.organization, sizeof(machine->config_2.organization), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2000, "organization - utils__libc__write_string() returned %d", rc);
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
//		//utils__printf__error(&sub->pf, fn, -2100, "facility - utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	/*
//	 * department
//	 */
//	rc = utils__libc__write_string(machine->config_2.department, sizeof(machine->config_2.department), tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2200, "department - utils__libc__write_string() returned %d", rc);
//		return -2200;
//	}
//
//	/*
//	 * department location coordinates
//	 */
//	rc = utils__libc__write_string(machine->config_2.department_location_coordinates, sizeof(machine->config_2.department_location_coordinates), tokens[3], tokens_len[3]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2200, "department - utils__libc__write_string() returned %d", rc);
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
//static int subagent__load_machine_technical_data(void* subagent, const char* data, size_t data_len)
//{
//	int rc;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* sub;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "subagent__load_machine_technical_data()";
//
//
//	minimum_token_count = 2;
//	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
//
//	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	sub = (subagent_t*)subagent;
//	i = sub->machine_counter;
//	machine = &sub->machine[i];
//
//
//	/*
//	 * cnc
//	 */
//	rc = utils__libc__write_string(machine->config_2.cnc, sizeof(machine->config_2.cnc), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2000, "utils__libc__write_string() returned %d", rc);
//		return -2000;
//	}
//
//	/*
//	 * hmi
//	 */
//	rc = utils__libc__write_string(machine->config_2.hmi, sizeof(machine->config_2.hmi), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2100, "utils__libc__write_string() returned %d", rc);
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
//static int subagent__load_machine_feeder_data (void* subagent, const char* data, size_t data_len)
//{
//
//	int rc;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* sub;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "subagent__load_machine_feeder_data()";
//
//
//	minimum_token_count = 4;
//	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
//
//	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	sub = (subagent_t*)subagent;
//	i = sub->machine_counter;
//	machine = &sub->machine[i];
//
//
//
//	/*
//	 * feeder manufacturer
//	 */
//	rc = utils__libc__write_string(machine->config_2.feeder_manufacturer, sizeof(machine->config_2.feeder_manufacturer), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	/*
//	 * feeder model
//	 */
//	rc = utils__libc__write_string(machine->config_2.feeder_model, sizeof(machine->config_2.feeder_model), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
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
//		//utils__printf__error(&sub->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
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
//		//utils__printf__error(&sub->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
//		return -2400;
//	}
//
//
//	return 0;
//}
//
//



//
//static int subagent__load_machine_opc_server_nodes_data(void* subagent, const char* data, size_t data_len)
//{
//	int rc;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* sub;
//	const char* fn;
//	size_t i;
//	size_t minimum_token_count;
//	subagent_machine_t* machine;
//
//
//	fn = "subagent__load_machine_opc_server_nodes_data()";
//
//
//	minimum_token_count = 3;
//	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
//
//	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//	utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//
//	sub = (subagent_t*)subagent;
//	i = sub->machine_counter;
//	machine = &sub->machine[i];
//
//
//
//	/*
//	 * opc server part counter node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_server_part_counter_node_path, sizeof(machine->config_2.opc_server_part_counter_node_path), tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
//		return -2100;
//	}
//
//	/*
//	 * opc server cycle time node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_server_cycle_time_node_path, sizeof(machine->config_2.opc_server_cycle_time_node_path), tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
//		return -2200;
//	}
//
//
//	/*
//	 * opc server part program name node path
//	 */
//	rc = utils__libc__write_string(machine->config_2.opc_server_part_program_name_node_path, sizeof(machine->config_2.opc_server_part_program_name_node_path), tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&sub->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
//		return -2300;
//	}
//
//
//	return 0;
//}



//  
//
//  {"CONNECTION MONITOR DATA",                         subagent__load_connection_timeout_seconds                       },
//	{"CONNECTION TIMEOUT SECONDS",                      subagent__load_connection_timeout_seconds                       },
//	{"RECONNECTION ATTEMPTS TIME INTERVAL SECONDS",     subagent__load_reconnection_attempts_time_interval_seconds      },
//	{"MAX RECONNECTION ATTEMPTS",                       subagent__load_max_reconnection_attempts                        },
//	{"NO RESPONSE TIMEOUT SECONDS",                     subagent__load_no_response_timeout_seconds                      },
//
//
//  {"OPC SERVER CONNECTION DATA",                             subagent__load_machine_opc_connection_data                              },
//     {"OPC IP-V4 ADDRESS",                               subagent__load_machine_opc_ipv4_address                                 },
//     {"OPC IP-V4 PORT",                                  subagent__load_machine_opc_ipv4_port                                    },
//     {"OPC USER NAME",                                   subagent__load_machine_opc_user_name                                    },
//     {"OPC PASSWORD",                                    subagent__load_machine_opc_password                                     },
//     {"OPC CERTIFICATE FILE",                            subagent__load_machine_opc_certificate_file                             },
//     {"OPC PRIVATE KEY FILE",                            subagent__load_machine_opc_private_key_file                             },
//
//  {"OPC SERVER NODES DATA",                                            subagent__load_machine_opc_nodes_data                                   },
//     {"OPC PART COUNTER PATH",                           subagent__load_machine_opc_part_counter_path                            },
//     {"OPC CYCLE TIME PATH",                             subagent__load_machine_opc_cycle_time_path                              },
//     {"OPC PART PROGRAM NAME PATH",                      subagent__load_machine_opc_part_program_name_path                       },
//
//
// {"TCP SERVER CONNECTION DATA",                                subagent__load_connection_timeout_seconds                       },
//
//     {"TCP SERVER IP-V4 ADDRESS",                        subagent__load_tcp_server_ipv4_address                          },
//     {"TCP SERVER IP-V4 PORT",                           subagent__load_tcp_server_ipv4_port                             },
//     {"TCP CLIENT RECEIVE BUFFER SIZE",                  subagent__load_tcp_client_receive_buffer_size                   },
//     {"TCP CLIENT SEND STRING",                          subagent__load_tcp_client_send_string                           },
//     {"TCP CLIENT ENABLE PRINTF",                        subagent__load_tcp_enable_printf                                },
//
//
//  {"CYCLE TIME DATA FROM ",                           subagent__load_cycle_time_from_part_counter                     },
//  {"CYCLE TIME FROM PART COUNTER",                    subagent__load_cycle_time_from_part_counter                     },
//
//  {"PART PROGRAM NAME FILTER",                        subagent__load_part_program_name_filter                         }
//
//
//};




