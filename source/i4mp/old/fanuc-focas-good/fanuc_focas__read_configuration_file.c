#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;


static int found_section_name (const char* section_name, size_t section_name_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_printf(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_max_log_file_lines_per_minute(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_square_brackets_output(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_section_name_output(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_section_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);

static int set_id(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_communications(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_opc_ipv4_address(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_opc_ipv4_port(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_opc_user_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_opc_password(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_opc_certificate_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_opc_private_key_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_opc_part_counter_node_path(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);




static utils__sdb__section_callback_t application_section;

static utils__sdb__name_value_callback_t application_names_values[] =  
{ 
  {"FANUC-FOCAS",     "ENABLE PRINTF",                     enable_printf,                      "enable_printf()",                        NULL,     0},
  {"FANUC-FOCAS",     "ENABLE LOG FILE",                   enable_log_file,                    "enable_log_file()",                      NULL,     0},
  {"FANUC-FOCAS",     "LOG FILE",                          set_log_file,                       "set_log_file()",                         NULL,     0},
  {"FANUC-FOCAS",     "MAX LOG FILE LINES PER MINUTE",     set_max_log_file_lines_per_minute,  "set_max_log_file_lines_per_minute()",    NULL,     0},
  {"FANUC-FOCAS",     "ENABLE SQUARE BRACKETS OUTPUT",     enable_square_brackets_output,      "enable_square_brackets_output()",        NULL,     0},
  {"FANUC-FOCAS",     "ENABLE SECTION NAME OUTPUT",        enable_section_name_output,         "enable_section_name_output()",           NULL,     0},
  {"FANUC-FOCAS",     "SECTION NAME",                      set_section_name,                   "set_section_name()",                     NULL,     0}
};




static utils__sdb__section_callback_t machines_section;

static utils__sdb__name_value_callback_t machines_names_values[] = 
{ 
  {"FANUC-FOCAS LATHE MACHINE",     "ENABLE PRINTF",                     enable_printf,                      "enable_printf()",                        NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "ENABLE LOG FILE",                   enable_log_file,                    "enable_log_file()",                      NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "LOG FILE",                          set_log_file,                       "set_log_file()",                         NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "MAX LOG FILE LINES PER MINUTE",     set_max_log_file_lines_per_minute,  "set_max_log_file_lines_per_minute()",    NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "ENABLE SQUARE BRACKETS OUTPUT",     enable_square_brackets_output,      "enable_square_brackets_output()",        NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "ENABLE SECTION NAME OUTPUT",        enable_section_name_output,         "enable_section_name_output()",           NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "SECTION NAME",                      set_section_name,                   "set_section_name()",                     NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "ID",                                set_id,                             "set_id()",                               NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "ENABLE COMMUNICATIONS",             enable_communications,              "enable_communications()",                NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "ENABLE SIMULATION MODE",            enable_simulation_mode,             "enable_simulation_mode()",               NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "OPC IP-V4 ADDRESS",                 set_opc_ipv4_address,               "set_opc_ipv4_address()",                 NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "OPC IP-V4 PORT",                    set_opc_ipv4_port,                  "set_opc_ipv4_port()",                    NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "OPC USER NAME",                     set_opc_user_name,                  "set_opc_user_name()",                    NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "OPC PASSWORD",                      set_opc_password,                   "set_opc_password()",                     NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "OPC CERTIFICATE FILE",              set_opc_certificate_file,           "set_opc_certificate_file()",             NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "OPC PRIVATE KEY FILE",              set_opc_private_key_file,           "set_opc_private_key_file()",             NULL,     0},
  {"FANUC-FOCAS LATHE MACHINE",     "OPC PART COUNTER NODE PATH",        set_opc_part_counter_node_path,     "set_opc_part_counter_node_path()",       NULL,     0}
};





static char* fn = "fanuc_focas__read_configuration_file()";


int fanuc_focas__read_configuration_file (int mode)
{

	int rc;
	size_t i;
	size_t record_number;
	size_t start_record;
	size_t names_values_max;
	int done;
	size_t num_sections;
	size_t size;


	if ((mode < 0) || (mode > 1))
	{
		return -10000;
	}

	if (mode == 0)
	{

		/*
		 * mode = 0 means that we look for the following section [FANUC-FOCAS] in the configuration file
		 */

		/*
		 * Null the config struct
		 */
		memset(&fanuc_focas->config, 0, sizeof(fanuc_focas__config_t));

		application_section.name = fanuc_focas->application_data.configuration_file_section_name;
		application_section.function = found_section_name;
		application_section.function_name = "found_section_name";
		application_section.error_buffer = fanuc_focas->error_buffer;
		application_section.error_buffer_size = sizeof(fanuc_focas->error_buffer);


		names_values_max = sizeof(application_names_values) / sizeof(utils__sdb__name_value_callback_t);
		for (i = 0; i < names_values_max; i++)
		{
			application_names_values[i].error_buffer = fanuc_focas->error_buffer;
			application_names_values[i].error_buffer_size = sizeof(fanuc_focas->error_buffer);
		}


		start_record = 1;
		rc = utils__sdb__read_configuration_file(&fanuc_focas->sdb,
			                                      fanuc_focas->application_data.fully_qualified_configuration_file_name,
			                                      &application_section,
			                                      application_names_values,
			                                      names_values_max,
			                                      start_record,
			                                      &record_number,
			                                      fanuc_focas->error_buffer,
			                                      sizeof(fanuc_focas->error_buffer));


		if (rc != 0)
		{			
			return -100;
		}


		return 0;
	}



	/*
	 * mode = 1 means that we look for the following section [FANUC-FOCAS LATHE MACHINE] in the configuration file
	 */


	/*
	 * Set section data of the machines: [FANUC-FOCAS LATHE MACHINE]
	 */
	machines_section.name = fanuc_focas->machines_data.configuration_file_section_name;
	machines_section.function = found_section_name;
	machines_section.function_name = "found_section_name";
	machines_section.error_buffer = fanuc_focas->error_buffer;
	machines_section.error_buffer_size = sizeof(fanuc_focas->error_buffer);


	start_record = 1;
	rc = utils__sdb__count_configuration_file_sections(&fanuc_focas->sdb,
		                                               fanuc_focas->machines_data.fully_qualified_configuration_file_name,
		                                               fanuc_focas->machines_data.configuration_file_section_name,
		                                               start_record,
		                                               &num_sections);
	if (rc != 0)
	{		
		return -200;
	}

	if (num_sections == 0)
	{
		return -300;
	}	




	/*
	 * Allocate memory for the Siemens machines
	 */
	size = sizeof(fanuc_focas__lathe_machine_t) * num_sections;
	fanuc_focas->lathe_machine = (fanuc_focas__lathe_machine_t*) malloc(size);
	if (fanuc_focas->lathe_machine == NULL)
	{
		printf("error in function %s - malloc() error\n", fn);
		return -400;
	}

	memset(fanuc_focas->lathe_machine, '\0', size);



	names_values_max = sizeof(machines_names_values) / sizeof(utils__sdb__name_value_callback_t);
	for (i = 0; i < names_values_max; i++)
	{
		machines_names_values[i].error_buffer = fanuc_focas->error_buffer;
		machines_names_values[i].error_buffer_size = sizeof(fanuc_focas->error_buffer);
	}

	fanuc_focas->num_machines = 0;
	fanuc_focas->machine_data_present_in_configuration_file = 1;

	done = 0;
	start_record = 1;
	do 
	{		

		rc = utils__sdb__read_configuration_file(&fanuc_focas->sdb,
			                                     fanuc_focas->machines_data.fully_qualified_configuration_file_name,
			                                     &machines_section,
			                                     machines_names_values,
			                                     names_values_max,
			                                     start_record,
			                                     &record_number,
			                                     fanuc_focas->error_buffer,
			                                     sizeof(fanuc_focas->error_buffer));

		if (rc != 0)
		{
			done = 1;
		}
		else
		{
			start_record = record_number + 1;			
		}

	} 
	while (done == 0);


	/*
	 * fanuc_focas->num_machines has benn used so far as an index from 0 to num_machines.  therefore it must be incremented by 1 to represent the actual number of machines
	 */

	fanuc_focas->num_machines++;

	for (i = 0; i < fanuc_focas->num_machines; i++)
	{
		sprintf(fanuc_focas->lathe_machine[i].name_and_index, "%s %zu", fanuc_focas->machines_data.name, i + 1);
		fanuc_focas->lathe_machine[i].name_and_index_len = strlen(fanuc_focas->lathe_machine[i].name_and_index);
	}

	return 0;


}




static int found_section_name (const char* section_name, size_t section_name_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	char dummy_value[8];
	size_t dummy_value_len;
	size_t dummy_value_len_max;
	size_t section_name_1_len;
	size_t section_name_2_len;

	strcpy(dummy_value, "dummy");
	dummy_value_len = strlen(dummy_value);
	dummy_value_len_max = dummy_value_len + 1;

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, dummy_value, dummy_value_len, dummy_value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	section_name_1_len = strlen(fanuc_focas->application_data.configuration_file_section_name);
	section_name_2_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   fanuc_focas->application_data.configuration_file_section_name, section_name_1_len, 
		                                   fanuc_focas->machines_data.configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		;
	}
	else if (rc_2 == 1)
	{
		if (fanuc_focas->machine_data_present_in_configuration_file == 1)
		{
			fanuc_focas->machine_data_present_in_configuration_file = 2;
		}
		else
		{
			fanuc_focas->num_machines++;
		}
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

static int enable_printf (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t section_name_1_len;
	size_t section_name_2_len;


	value_len_max = 8;   /* 8 characters max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	rc = utils__sdb__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);


	section_name_1_len = strlen(fanuc_focas->application_data.configuration_file_section_name);
	section_name_2_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   fanuc_focas->application_data.configuration_file_section_name, section_name_1_len,
		                                   fanuc_focas->machines_data.configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		fanuc_focas->config.enable_printf = rc;
	}
	else if (rc_2 == 1)
	{
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.enable_printf = rc;
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}

	return 0;
}

static int enable_log_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{


	int rc;
	int rc_2;
	size_t value_len_max;
	size_t section_name_1_len;
	size_t section_name_2_len;


	value_len_max = 8;   /* 8 characters max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	rc = utils__sdb__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);


	section_name_1_len = strlen(fanuc_focas->application_data.configuration_file_section_name);
	section_name_2_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   fanuc_focas->application_data.configuration_file_section_name, section_name_1_len,
		                                   fanuc_focas->machines_data.configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		fanuc_focas->config.enable_log_file = rc;
	}
	else if (rc_2 == 1)
	{
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.enable_log_file = rc;
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

static int set_log_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	char* fully_qualified_log_file_name;
	size_t* fully_qualified_log_file_name_len;
	size_t value_len_1_max;
	size_t value_len_2_max;
	size_t section_name_1_len;
	size_t section_name_2_len;

	value_len_1_max = sizeof(fanuc_focas->config.fully_qualified_log_file_name);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_1_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	value_len_2_max = sizeof(fanuc_focas->config.fully_qualified_log_file_name);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_2_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -200;
	}


	section_name_1_len = strlen(fanuc_focas->application_data.configuration_file_section_name);
	section_name_2_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   fanuc_focas->application_data.configuration_file_section_name, section_name_1_len,
		                                   fanuc_focas->machines_data.configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{		
		fully_qualified_log_file_name = fanuc_focas->config.fully_qualified_log_file_name;
		fully_qualified_log_file_name_len = &fanuc_focas->config.fully_qualified_log_file_name_len;
	}
	else if (rc_2 == 1)
	{
		fully_qualified_log_file_name = fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.fully_qualified_log_file_name;
		fully_qualified_log_file_name_len = &fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.fully_qualified_log_file_name_len;
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -300;
	}


	memcpy(fully_qualified_log_file_name, value, value_len);
	fully_qualified_log_file_name[value_len] = '\0';
	*fully_qualified_log_file_name_len = value_len;


	return 0;
}

static int set_max_log_file_lines_per_minute (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t section_name_1_len;
	size_t section_name_2_len;
	unsigned long max_log_file_lines_per_minute;
	unsigned long tmp;
	size_t value_len_max;


	value_len_max = 8;   /* 8 digits max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	/*
	 * Default value
	 */
	max_log_file_lines_per_minute = 30;

	rc = utils__libc__atoul(value, value_len, &tmp);
	if (rc == 0)
	{
		max_log_file_lines_per_minute = tmp;
	}

	section_name_1_len = strlen(fanuc_focas->application_data.configuration_file_section_name);
	section_name_2_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   fanuc_focas->application_data.configuration_file_section_name, section_name_1_len,
		                                   fanuc_focas->machines_data.configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		fanuc_focas->config.max_log_file_lines_per_minute = (size_t) max_log_file_lines_per_minute;		
	}
	else if (rc_2 == 1)
	{
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.max_log_file_lines_per_minute = (size_t) max_log_file_lines_per_minute;
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

static int enable_square_brackets_output (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t section_name_1_len;
	size_t section_name_2_len;


	value_len_max = 8;   /* 8 characters max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	rc = utils__sdb__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);


	section_name_1_len = strlen(fanuc_focas->application_data.configuration_file_section_name);
	section_name_2_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   fanuc_focas->application_data.configuration_file_section_name, section_name_1_len,
		                                   fanuc_focas->machines_data.configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		fanuc_focas->config.enable_square_brackets_output = rc;
	}
	else if (rc_2 == 1)
	{
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.enable_square_brackets_output = rc;
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

static int enable_section_name_output (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t section_name_1_len;
	size_t section_name_2_len;


	value_len_max = 8;   /* 8 characters max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	rc = utils__sdb__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);


	section_name_1_len = strlen(fanuc_focas->application_data.configuration_file_section_name);
	section_name_2_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   fanuc_focas->application_data.configuration_file_section_name, section_name_1_len,
		                                   fanuc_focas->machines_data.configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		fanuc_focas->config.enable_section_name_output = rc;
	}
	else if (rc_2 == 1)
	{
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.enable_section_name_output = rc;
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

static int set_section_name (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_1_max;
	size_t value_len_2_max;
	size_t section_name_1_len;
	size_t section_name_2_len;
	char* configuration_file_section_name;
	size_t* configuration_file_section_name_len;

	value_len_1_max = sizeof(fanuc_focas->config.configuration_file_section_name);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_1_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	value_len_2_max = sizeof(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.configuration_file_section_name);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_2_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -200;
	}


	section_name_1_len = strlen(fanuc_focas->application_data.configuration_file_section_name);
	section_name_2_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   fanuc_focas->application_data.configuration_file_section_name, section_name_1_len,
		                                   fanuc_focas->machines_data.configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		configuration_file_section_name = fanuc_focas->config.configuration_file_section_name;
		configuration_file_section_name_len = &fanuc_focas->config.configuration_file_section_name_len;
	}
	else if (rc_2 == 1)
	{
		configuration_file_section_name = fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.configuration_file_section_name;
		configuration_file_section_name_len = &fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.configuration_file_section_name_len;
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -300;
	}


	memcpy(configuration_file_section_name, value, value_len);
	configuration_file_section_name[value_len] = '\0';
	*configuration_file_section_name_len = value_len;


	return 0;
}

static int set_id(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{
	int rc;
	int rc_2;
	size_t sect_name_len;
	unsigned long tmp;
	size_t value_len_max;
	size_t id;


	value_len_max = 8;   /* 8 digits max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	rc = utils__libc__atoul(value, value_len, &tmp);
	if (rc == 0)
	{
		id = (size_t)tmp;
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__libc__atoul() returned %d\n", function_name, rc);
		return -200;
	}


	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.id = id;
	}

	return 0;
}

static int enable_communications (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;

	value_len_max = 8;   /* 8 characters max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	rc = utils__sdb__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);
	
	rc_2 = utils__sdb__cf__compare_sections_names (section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.enable_communications = rc;
	}

	return 0;

}




static int enable_simulation_mode (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;

	value_len_max = 8;   /* 8 characters max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	rc = utils__sdb__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.enable_simulation_mode = rc;
	}

	return 0;
}


static int set_opc_ipv4_address (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;

	value_len_max = sizeof(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_ipv4_address);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{		
		memcpy(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_ipv4_address, value, value_len);
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_ipv4_address[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

static int set_opc_ipv4_port(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;

	value_len_max = sizeof(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_ipv4_address);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		memcpy(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_ipv4_port, value, value_len);
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_ipv4_port[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

static int set_opc_user_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;

	value_len_max = sizeof(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_ipv4_address);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		memcpy(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_user_name, value, value_len);
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_user_name[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;

}

static int set_opc_password (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;

	value_len_max = sizeof(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_ipv4_address);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		memcpy(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_password, value, value_len);
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_password[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;

}


static int set_opc_certificate_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;

	value_len_max = sizeof(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_fully_qualified_certificate_file);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		memcpy(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_fully_qualified_certificate_file, value, value_len);
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_fully_qualified_certificate_file[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__compare_sections_names() returned %d\n", function_name, rc_2);
		return -200;
	}

	return 0;
}


static int set_opc_private_key_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;
	

	value_len_max = sizeof(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_fully_qualified_private_key_file);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		memcpy(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_fully_qualified_private_key_file, value, value_len);
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_fully_qualified_private_key_file[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__compare_sections_names() returned %d\n", function_name, rc_2);
		return -200;
	}

	return 0;
}


static int set_opc_part_counter_node_path(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;


	value_len_max = sizeof(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_part_counter_node_path);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(fanuc_focas->machines_data.configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, fanuc_focas->machines_data.configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		memcpy(fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_part_counter_node_path, value, value_len);
		fanuc_focas->lathe_machine[fanuc_focas->num_machines].config.opc_part_counter_node_path[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__compare_sections_names() returned %d\n", function_name, rc_2);
		return -200;
	}

	return 0;
}