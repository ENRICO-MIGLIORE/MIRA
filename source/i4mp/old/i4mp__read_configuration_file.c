#include "mira__private.h"


static int found_section_name(const char* section_name, size_t section_name_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_printf(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_max_log_file_lines_per_minute (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_square_brackets_output (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int enable_section_name_output (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);
static int set_section_name (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size);


static utils__cf__section_callback_t application_section;


static utils__cf__name_value_callback_t application_names_values[] =
{
  {"I4MP",     "ENABLE PRINTF",                     enable_printf,                      "enable_printf()",                        NULL,     0},
  {"I4MP",     "ENABLE LOG FILE",                   enable_log_file,                    "enable_log_file()",                      NULL,     0},
  {"I4MP",     "LOG FILE",                          set_log_file,                       "set_log_file()",                         NULL,     0},
  {"I4MP",     "MAX LOG FILE LINES PER MINUTE",     set_max_log_file_lines_per_minute,  "set_max_log_file_lines_per_minute()",    NULL,     0},
  {"I4MP",     "ENABLE SQUARE BRACKETS OUTPUT",     enable_square_brackets_output,      "enable_square_brackets_output()",        NULL,     0},
  {"I4MP",     "ENABLE SECTION NAME OUTPUT",        enable_section_name_output,         "enable_section_name_output()",           NULL,     0},
  {"I4MP",     "SECTION NAME",                      set_section_name,                   "set_section_name()",                     NULL,     0}
};


static char* fn = "i4mp__read_configuration_file()";


int i4mp__read_configuration_file (void)
{

	int rc;
	size_t i;
	size_t record_number;
	size_t start_record;
	size_t names_values_max;


	/*
	 * Null the config struct
	 */
	memset(&i4mp->config, 0, sizeof(i4lmp__config_t));


	/*
	 * Set section data of the application: [I4MP]
	 */
	application_section.name = i4mp->application_configuration_file_section_name;
	application_section.function = found_section_name;
	application_section.function_name = "found_section_name()";
	application_section.error_buffer = i4mp->error_buffer;
	application_section.error_buffer_size = sizeof(i4mp->error_buffer);


	names_values_max = sizeof(application_names_values) / sizeof(utils__cf__name_value_callback_t);
	for (i = 0; i < names_values_max; i++)
	{
		application_names_values[i].error_buffer = i4mp->error_buffer;
		application_names_values[i].error_buffer_size = sizeof(i4mp->error_buffer);
	}


	/*utils__sdb__clear_sdb(&i4lmp->sdb);*/


	start_record = 1;
	rc = utils__cf__read_configuration_file(&i4mp->sdb,
		                                    i4mp->application_fully_qualified_configuration_file_name,
		                                    &application_section,
		                                    application_names_values,
		                                    names_values_max,
		                                    start_record,
		                                    &record_number,
		                                    i4mp->error_buffer,
		                                    sizeof(i4mp->error_buffer));



	if (rc != 0)
	{
		printf("%s", i4mp->error_buffer);
		return -200;
	}


	return 0;


}

static int found_section_name (const char* section_name, size_t section_name_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	char dummy_value[8];
	size_t dummy_value_len;
	size_t dummy_value_len_max;
	size_t sect_name_len;

	strcpy(dummy_value, "dummy");
	dummy_value_len = strlen(dummy_value);
	dummy_value_len_max = dummy_value_len + 1;

	rc = utils__cf__check_actual_parameters(section_name, section_name_len, dummy_value, dummy_value_len, dummy_value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	sect_name_len = strlen(i4mp->application_configuration_file_section_name);

	rc = utils__cf__compare_sections_names(section_name, section_name_len, i4mp->application_configuration_file_section_name, sect_name_len);
	if (rc != 0)
	{
		return -200;
	}


	return 0;
}

static int enable_printf(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	size_t value_len_max;

	value_len_max = 8;   /* 8 characters max */

	rc = utils__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	rc = utils__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);

	if (rc == 0)
	{
		i4mp->config.enable_printf = 0;
	}
	else
	{
		i4mp->config.enable_printf = 1;
	}

	return 0;

}

static int enable_log_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	size_t value_len_max;

	value_len_max = 8;   /* 8 characters max */

	rc = utils__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	rc = utils__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);

	if (rc == 0)
	{
		i4mp->config.enable_log_file = 0;
	}
	else
	{
		i4mp->config.enable_log_file = 1;
	}

	return 0;
}

static int set_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	size_t value_len_max;

	value_len_max = sizeof(i4mp->config.fully_qualified_log_file_name);

	rc = utils__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	memcpy(i4mp->config.fully_qualified_log_file_name, value, value_len);
	i4mp->config.fully_qualified_log_file_name[value_len] = '\0';
	i4mp->config.fully_qualified_log_file_name_len = value_len;

	return 0;
}

static int set_max_log_file_lines_per_minute(const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	unsigned long max_log_file_lines_per_minute;
	size_t value_len_max;

	value_len_max = 8;   /* 8 digits max */

	rc = utils__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}


	/*
	 * Default value
	 */
	i4mp->config.max_log_file_lines_per_minute = 30;

	rc = utils__libc__atoul(value, value_len, &max_log_file_lines_per_minute);
	if (rc == 0)
	{
		i4mp->config.max_log_file_lines_per_minute = (size_t)max_log_file_lines_per_minute;
	}

	return 0;
}

static int enable_square_brackets_output (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	size_t value_len_max;

	value_len_max = 8;   /* 8 characters max */

	rc = utils__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	rc = utils__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);

	if (rc == 0)
	{
		i4mp->config.enable_square_brackets_output = 0;
	}
	else
	{
		i4mp->config.enable_square_brackets_output = 1;
	}

	return 0;
}

static int enable_section_name_output (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{
	
	int rc;
	size_t value_len_max;

	value_len_max = 8;   /* 8 characters max */

	rc = utils__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	rc = utils__cf__check_yes_or_no(value, value_len, function_name, error_buffer, error_buffer_size);

	if (rc == 0)
	{
		i4mp->config.enable_section_name_output = 0;
	}
	else
	{
		i4mp->config.enable_section_name_output = 1;
	}


	return 0;
}

static int set_section_name (const char* section_name, size_t section_name_len, const char* value, size_t value_len, char* function_name, char* error_buffer, size_t error_buffer_size)
{

	int rc;
	size_t value_len_max;

	value_len_max = sizeof(i4mp->config.configuration_file_section_name);

	rc = utils__cf__check_actual_parameters(section_name, section_name_len, value, value_len, value_len_max, function_name, error_buffer, error_buffer_size);
	if (rc != 0)
	{
		return -100;
	}

	memcpy(i4mp->config.configuration_file_section_name, value, value_len);
	i4mp->config.configuration_file_section_name[value_len] = '\0';
	i4mp->config.configuration_file_section_name_len = value_len;

	return 0;

}

