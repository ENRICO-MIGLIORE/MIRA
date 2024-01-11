#include "fanuc_focas__private.h"


static int found_section_name (const char* section_name, size_t section_name_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_printf(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_max_log_file_lines_per_minute(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_square_brackets_output(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_section_name_output(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_section_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_thread_sleep_time_seconds (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_cnc_connection_attempt_timeout_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);


static int set_id(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_communications(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_cnc_ipv4_address(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_cnc_ipv4_port(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);


static utils__cf__section_callback_t application_section;

static utils__cf__name_value_callback_t application_names_values[] =  
{ 
  {"FANUC_FOCAS",     "ENABLE PRINTF",                               enable_printf,                                "enable_printf()",                                 NULL,     0},
  {"FANUC_FOCAS",     "ENABLE LOG FILE",                             enable_log_file,                              "enable_log_file()",                               NULL,     0},
  {"FANUC_FOCAS",     "LOG FILE",                                    set_log_file,                                 "set_log_file()",                                  NULL,     0},
  {"FANUC_FOCAS",     "MAX LOG FILE LINES PER MINUTE",               set_max_log_file_lines_per_minute,            "set_max_log_file_lines_per_minute()",             NULL,     0},
  {"FANUC_FOCAS",     "ENABLE SQUARE BRACKETS OUTPUT",               enable_square_brackets_output,                "enable_square_brackets_output()",                 NULL,     0},
  {"FANUC_FOCAS",     "ENABLE SECTION NAME OUTPUT",                  enable_section_name_output,                   "enable_section_name_output()",                    NULL,     0},
  {"FANUC_FOCAS",     "SECTION NAME",                                set_section_name,                             "set_section_name()",                              NULL,     0},
  {"FANUC_FOCAS",     "THREAD SLEEP TIME SECONDS",                   set_thread_sleep_time_seconds,                "set_thread_sleep_time_seconds()",                 NULL,     0},
  {"FANUC_FOCAS",     "CNC CONNECTION ATTEMPT TIME OUT SECONDS",     set_cnc_connection_attempt_timeout_seconds,   "set_cnc_connection_attempt_timeout_seconds()",    NULL,     0}
};


static utils__sdb__section_callback_t machines_section;

static utils__sdb__name_value_callback_t machines_names_values[] = 
{ 
  {"FANUC_FOCAS LATHE MACHINE",     "ENABLE PRINTF",                                     enable_printf,                                        "enable_printf()",                                        NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "ENABLE LOG FILE",                                   enable_log_file,                                      "enable_log_file()",                                      NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "LOG FILE",                                          set_log_file,                                         "set_log_file()",                                         NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "MAX LOG FILE LINES PER MINUTE",                     set_max_log_file_lines_per_minute,                    "set_max_log_file_lines_per_minute()",                    NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "ENABLE SQUARE BRACKETS OUTPUT",                     enable_square_brackets_output,                        "enable_square_brackets_output()",                        NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "ENABLE SECTION NAME OUTPUT",                        enable_section_name_output,                           "enable_section_name_output()",                           NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "SECTION NAME",                                      set_section_name,                                     "set_section_name()",                                     NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "ID",                                                set_id,                                               "set_id()",                                               NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "ENABLE COMMUNICATIONS",                             enable_communications,                                "enable_communications()",                                NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "ENABLE SIMULATION MODE",                            enable_simulation_mode,                               "enable_simulation_mode()",                               NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "CNC IP-V4 ADDRESS",                                 set_cnc_ipv4_address,                                 "set_cnc_ipv4_address()",                                 NULL,     0},
  {"FANUC_FOCAS LATHE MACHINE",     "CNC IP-V4 PORT",                                    set_cnc_ipv4_port,                                    "set_cnc_ipv4_port()",                                    NULL,     0},
  
};





static char* fn = "fanuc_focas__process_configuration_file()";


int fanuc_focas__process_configuration_file (void)
{

	int rc;
	size_t i;
	size_t record_number;
	size_t start_record;
	size_t names_values_max;
	int done;
	size_t num_sections;
	size_t size;


	/*
	 * Null the config struct
	 */
	memset(&ff->config, 0, sizeof(fanuc_focas__config_t));


	/*
	 * Set section data of the application: [FANUC_FOCAS]
	 */
	application_section.name = ff->application_configuration_file_section_name;
	application_section.function = found_section_name;
	application_section.function_name = "found_section_name";
	application_section.error_buffer = ff->error_buffer;
	application_section.error_buffer_size = sizeof(ff->error_buffer);

	names_values_max = sizeof(application_names_values) / sizeof(utils__sdb__name_value_callback_t);
	for (i = 0; i < names_values_max; i++)
	{
		application_names_values[i].error_buffer = ff->error_buffer;
		application_names_values[i].error_buffer_size = sizeof(ff->error_buffer);
	}


	/*
	 * Look for section: [FANUC_FOCAS]
	 */
	start_record = 1;
	rc = utils__cf__read_configuration_file(&ff->sdb,
		                                         ff->application_fully_qualified_configuration_file_name,
		                                         &application_section,
		                                         application_names_values,
		                                         names_values_max,
		                                         start_record,
		                                         &record_number,
		                                         ff->error_buffer,
		                                         sizeof(ff->error_buffer));

	
	if (rc != 0)
	{
		printf("%s", ff->error_buffer);
		return -200;
	}


	/*
	 * Count the number of sections: [FANUC_FOCAS LATHE MACHINE]
	 */
	start_record = 1;
	rc = utils__sdb__cf__count_sections(&ff->sdb,
		                                ff->application_fully_qualified_configuration_file_name,
		                                ff->machines_configuration_file_section_name,
		                                start_record,
		                                &num_sections);
	if (rc != 0)
	{
		printf("error in function %s - utils__sdb__count_configuration_file_sections() error\n", fn);
		return -100;
	}

	if (num_sections == 0)
	{
		printf("error in function %s - There aren't [%s] sections in the configuration file\n", fn, machines_section.name);
		return -100;
	}


	/*
	 * Allocate memory for the Siemens machines
	 */
	size = sizeof (fanuc_focas__lathe_machine_t) * num_sections;

	ff->machine = (fanuc_focas__lathe_machine_t*) malloc(size);

	if (ff->machine == NULL)
	{
		printf("error in function %s - malloc() error\n", fn);
		return -100;
	}

	memset(ff->machine, '\0', size);




	/*
	 * Set section data of the machines: [FANUC_FOCAS LATHE MACHINE]
	 */
	machines_section.name = ff->machines_configuration_file_section_name;
	machines_section.function = found_section_name;
	machines_section.function_name = "found_section_name";
	machines_section.error_buffer = ff->error_buffer;
	machines_section.error_buffer_size = sizeof(ff->error_buffer);


	names_values_max = sizeof(machines_names_values) / sizeof(utils__sdb__name_value_callback_t);
	for (i = 0; i < names_values_max; i++)
	{
		machines_names_values[i].error_buffer = ff->error_buffer;
		machines_names_values[i].error_buffer_size = sizeof(ff->error_buffer);
	}

	ff->machine_count = 0;
	ff->machine_flag = 1;

	done = 0;
	start_record = 1;
	do 
	{		

		rc = utils__cf__read_configuration_file(&ff->sdb,
			                                         ff->application_fully_qualified_configuration_file_name,
			                                         &machines_section,
			                                         machines_names_values,
			                                         names_values_max,
			                                         start_record,
			                                         &record_number,
			                                         ff->error_buffer,
			                                         sizeof(ff->error_buffer));

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
	 * It's been used as an index from 0 to num_machines and therefore it must be incremented by 1 to represent the actual number of machines
	 */


	ff->machine_count++;

	for (i = 0; i < ff->machine_count; i++)
	{		
		//sprintf(ff->machine[i].name_and_index, "%s %zu", ff->machines_name, i + 1);
		sprintf(ff->machine[i].name_and_index, "%s %zu", ff->machines_configuration_file_section_name, i + 1);
		ff->machine[i].name_and_index_len = strlen(ff->machine[i].name_and_index);
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


	section_name_1_len = strlen(ff->application_configuration_file_section_name);
	section_name_2_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                       ff->application_configuration_file_section_name, section_name_1_len, 
		                                       ff->machines_configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		;
	}
	else if (rc_2 == 1)
	{
		if (ff->machine_flag == 1)
		{
			ff->machine_flag = 2;
		}
		else
		{
			ff->machine_count++;
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



	//config = (fanuc_focas__lathe_machine_config_t*) ff->machine->config;

	value_len_max = 8;   /* 8 characters max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	rc = utils__sdb__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);


	section_name_1_len = strlen(ff->application_configuration_file_section_name);
	section_name_2_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   ff->application_configuration_file_section_name, section_name_1_len,
		                                   ff->machines_configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		ff->config.enable_printf = rc;
	}
	else if (rc_2 == 1)
	{		
		ff->machine[ff->machine_count].config.enable_printf = rc;		
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


	section_name_1_len = strlen(ff->application_configuration_file_section_name);
	section_name_2_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   ff->application_configuration_file_section_name, section_name_1_len,
		                                   ff->machines_configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		ff->config.enable_log_file = rc;
	}
	else if (rc_2 == 1)
	{
		ff->machine[ff->machine_count].config.enable_log_file = rc;
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


	value_len_1_max = sizeof(ff->config.fully_qualified_log_file_name);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_1_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	value_len_2_max = sizeof(ff->config.fully_qualified_log_file_name);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_2_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -200;
	}


	section_name_1_len = strlen(ff->application_configuration_file_section_name);
	section_name_2_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   ff->application_configuration_file_section_name, section_name_1_len,
		                                   ff->machines_configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{		
		fully_qualified_log_file_name = ff->config.fully_qualified_log_file_name;
		fully_qualified_log_file_name_len = &ff->config.fully_qualified_log_file_name_len;
	}
	else if (rc_2 == 1)
	{
		fully_qualified_log_file_name = ff->machine[ff->machine_count].config.fully_qualified_log_file_name;
		fully_qualified_log_file_name_len = &ff->machine[ff->machine_count].config.fully_qualified_log_file_name_len;

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

	section_name_1_len = strlen(ff->application_configuration_file_section_name);
	section_name_2_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   ff->application_configuration_file_section_name, section_name_1_len,
		                                   ff->machines_configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		ff->config.max_log_file_lines_per_minute = (size_t) max_log_file_lines_per_minute;		
	}
	else if (rc_2 == 1)
	{
		ff->machine[ff->machine_count].config.max_log_file_lines_per_minute = (size_t) max_log_file_lines_per_minute;
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


	section_name_1_len = strlen(ff->application_configuration_file_section_name);
	section_name_2_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   ff->application_configuration_file_section_name, section_name_1_len,
		                                   ff->machines_configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		ff->config.enable_square_brackets_output = rc;
	}
	else if (rc_2 == 1)
	{
		ff->machine[ff->machine_count].config.enable_square_brackets_output = rc;
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


	section_name_1_len = strlen(ff->application_configuration_file_section_name);
	section_name_2_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   ff->application_configuration_file_section_name, section_name_1_len,
		                                   ff->machines_configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		ff->config.enable_section_name_output = rc;
	}
	else if (rc_2 == 1)
	{
		ff->machine[ff->machine_count].config.enable_section_name_output = rc;
		
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


	value_len_1_max = sizeof(ff->config.configuration_file_section_name);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_1_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	value_len_2_max = sizeof(ff->machine[ff->machine_count].config.configuration_file_section_name);
	

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_2_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -200;
	}


	section_name_1_len = strlen(ff->application_configuration_file_section_name);
	section_name_2_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__select_section_name(section_name, section_name_len,
		                                   ff->application_configuration_file_section_name, section_name_1_len,
		                                   ff->machines_configuration_file_section_name, section_name_2_len);

	if (rc_2 == 0)
	{
		configuration_file_section_name = ff->config.configuration_file_section_name;
		configuration_file_section_name_len = &ff->config.configuration_file_section_name_len;
	}
	else if (rc_2 == 1)
	{
		configuration_file_section_name = ff->machine[ff->machine_count].config.configuration_file_section_name;
		configuration_file_section_name_len = &ff->machine[ff->machine_count].config.configuration_file_section_name_len;
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



static int set_thread_sleep_time_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	unsigned long tmp;
	size_t value_len_max;

	value_len_max = 8;   /* 8 digits max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	rc = utils__libc__atoul(value, value_len, &tmp);
	if (rc != 0)
	{
		//sprintf(error_buffer, "error in function %s() - utils__sdb__cf__compare_sections_names() returned %d\n", function_name, rc_2);
		return -200;
	}

	if (tmp == 0)
	{
		//sprintf(error_buffer, "error in function %s() - utils__sdb__cf__compare_sections_names() returned %d\n", function_name, rc_2);
		return -300;
	}

	/*
	 * No need to lock the thread because it hasn't started yet
	 */
	ff->pthread_sleep_time_seconds = (size_t) tmp;


	return 0;
}




static int set_cnc_connection_attempt_timeout_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{


	int rc;
	unsigned long tmp;
	size_t value_len_max;

	value_len_max = 8;   /* 8 digits max */

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	rc = utils__libc__atoul(value, value_len, &tmp);
	if (rc != 0)
	{
		//sprintf(error_buffer, "error in function %s() - utils__sdb__cf__compare_sections_names() returned %d\n", function_name, rc_2);
		return -200;
	}

	if (tmp == 0)
	{
		tmp = (unsigned long) ff->cnc_connection_attempt_timeout_seconds;
	}

	/*
	 * No need to lock the thread because it hasn't started yet
	 */
	ff->cnc_connection_attempt_timeout_seconds = (size_t) tmp;


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


	sect_name_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, ff->machines_configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		ff->machine[ff->machine_count].config.id = id;		
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

	sect_name_len = strlen(ff->machines_configuration_file_section_name);
	
	rc_2 = utils__sdb__cf__compare_sections_names (section_name, section_name_len, ff->machines_configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		ff->machine[ff->machine_count].config.enable_communications = rc;
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

	sect_name_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, ff->machines_configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		ff->machine[ff->machine_count].config.enable_simulation_mode = rc;
	}

	return 0;
}

static int set_cnc_ipv4_address (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;


	value_len_max = sizeof(ff->machine[ff->machine_count].config.cnc_ipv4_address);


	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, ff->machines_configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{		
		memcpy(ff->machine[ff->machine_count].config.cnc_ipv4_address, value, value_len);
		ff->machine[ff->machine_count].config.cnc_ipv4_address[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

static int set_cnc_ipv4_port(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	int rc_2;
	size_t value_len_max;
	size_t sect_name_len;

	value_len_max = sizeof(ff->machine[ff->machine_count].config.cnc_ipv4_address);

	rc = utils__sdb__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(ff->machines_configuration_file_section_name);

	rc_2 = utils__sdb__cf__compare_sections_names(section_name, section_name_len, ff->machines_configuration_file_section_name, sect_name_len);

	if (rc_2 == 0)
	{
		memcpy(ff->machine[ff->machine_count].config.cnc_ipv4_port, value, value_len);
		ff->machine[ff->machine_count].config.cnc_ipv4_port[value_len] = '\0';
	}
	else
	{
		sprintf(error_buffer, "error in function %s() - utils__sdb__cf__select_section_name() returned %d\n", function_name, rc_2);
		return -200;
	}


	return 0;
}

