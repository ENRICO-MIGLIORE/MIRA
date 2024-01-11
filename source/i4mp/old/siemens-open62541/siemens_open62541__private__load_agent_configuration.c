#include "siemens_open62541__private.h"


static int found_section_name (const char* section_name, size_t section_name_len);

static int enable_printf(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int enable_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_log_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_max_log_file_lines_per_minute(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int enable_table_layout_output(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int enable_application_name_on_output(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_application_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_thread_sleep_time_seconds (const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int enable_connection_monitor_task(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_probability_of_success_of_events_in_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len);


static utils__cf__section_callback_t section;


static utils__cf__name_value_callback_t names_values[] =
{ 
  {"SIEMENS-OPEN62541",     "ENABLE PRINTF",                                          enable_printf                                             },
  {"SIEMENS-OPEN62541",     "ENABLE LOG FILE",                                        enable_log_file                                           },
  {"SIEMENS-OPEN62541",     "LOG FILE",                                               set_log_file                                              },
  {"SIEMENS-OPEN62541",     "MAX LOG FILE LINES PER MINUTE",                          set_max_log_file_lines_per_minute                         },
  {"SIEMENS-OPEN62541",     "ENABLE TABLE LAYOUT OUTPUT",                             enable_table_layout_output                                },
  {"SIEMENS-OPEN62541",     "ENABLE APPLICATION NAME ON OUTPUT",                      enable_application_name_on_output                         },
  {"SIEMENS-OPEN62541",     "APPLICATION NAME",                                       set_application_name                                      },
  {"SIEMENS-OPEN62541",     "THREAD SLEEP TIME SECONDS",                              set_thread_sleep_time_seconds                             },
  {"SIEMENS-OPEN62541",     "ENABLE CONNECTION MONITOR TASK",                         enable_connection_monitor_task                            },
  {"SIEMENS-OPEN62541",     "PROBABILITY OF SUCCESS OF EVENTS IN SIMULATION MODE",    set_probability_of_success_of_events_in_simulation_mode   }

};


static char* fn = "siemens_open62541__private__load_agent_configuration()";


int siemens_open62541__private__load_agent_configuration(void)
{

	int rc;
	size_t record_number;
	size_t start_record;
	size_t application_names_values_max;
	int end_of_file;


	/*
	 * Set section data of the agent:  [SIEMENS-OPEN62541 AGENT]
	 */
	section.name = so->agent_section_name;
	section.function = found_section_name;
	application_names_values_max = sizeof(names_values) / sizeof(utils__cf__name_value_callback_t);


	/*
	 * extract data from config file or buffer looking for section: so->agent_section_name
	 */
	start_record = 1;

	if (so->config_mode == 0)
	{
		rc = utils__cf__read_configuration_from_file(&so->sdb, so->agent_configuration_file_name, &section, names_values, application_names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__cf__read_configuration_from_file() returned %d\n", fn, rc);
			return -100;
		}

	}
	else
	{
		rc = utils__cf__read_configuration_from_buffer(&so->sdb, so->agent_configuration_file_name, &section, names_values, application_names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__cf__read_configuration_from_buffer() returned %d\n", fn, rc);
			return -200;
		}
	}


	/*  utils__sdb__print_sdb(&so->sdb);  */

	return 0;
}



static int found_section_name (const char* section_name, size_t section_name_len)
{

	/*
	 * Nothing to do: just keep the compiler happy
	 */
	section_name = section_name;
	section_name_len = 0;

	return 0;
}

static int enable_printf (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->config.enable_printf;

	rc = utils__cf__write_yes_or_no(data, section_name, section_name_len, value, value_len);


	return rc;

}

static int enable_log_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->config.enable_log_file;

	rc = utils__cf__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_log_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->config.log_file_name;
	buffer_size = sizeof(so->config.log_file_name);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_max_log_file_lines_per_minute (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->config.max_log_file_lines_per_minute;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (so->config.max_log_file_lines_per_minute == 0)
	{
		return -200;
	}

	return 0;
}

static int enable_table_layout_output (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->config.enable_table_layout_output;

	rc = utils__cf__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int enable_application_name_on_output (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->config.enable_application_name_on_output;

	rc = utils__cf__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_application_name (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->config.agent_name;
	buffer_size = sizeof(so->config.agent_name);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_thread_sleep_time_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->pthread_sleep_time_seconds;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (so->pthread_sleep_time_seconds == 0)
	{
		return -200;
	}

	return 0;

}

static int enable_connection_monitor_task(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->config.enable_connection_monitor_task;

	rc = utils__cf__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_probability_of_success_of_events_in_simulation_mode (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	double* data;

	data = &so->config.probability_of_success_of_events_in_simulation_mode;


	rc = utils__cf__write_double(data, section_name, section_name_len, value, value_len);
	if (rc != 0)
	{
		return -100;
	}


	if ((so->config.probability_of_success_of_events_in_simulation_mode < 0) || (so->config.probability_of_success_of_events_in_simulation_mode > 1))
	{
		return -200;
	}

	so->percent_of_success_of_events_in_simulation_mode = (int) (so->config.probability_of_success_of_events_in_simulation_mode * 100);

	return rc;

}
