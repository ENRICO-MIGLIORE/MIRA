#include "okuma_mt__private.h"


static int found_agent_section (const char* section_name, size_t section_name_len);

static int enable_printf(const char* value, size_t value_len);
static int enable_log_file(const char* value, size_t value_len);
static int set_log_file(const char* value, size_t value_len);
static int set_max_log_file_lines_per_minute(const char* value, size_t value_len);
static int enable_table_layout_output(const char* value, size_t value_len);
static int enable_application_name_on_output(const char* value, size_t value_len);
static int set_application_name(const char* value, size_t value_len);
static int set_thread_sleep_time_seconds (const char* value, size_t value_len);
static int enable_connection_monitor_task(const char* value, size_t value_len);
static int set_probability_of_success_of_events_in_simulation_mode(const char* value, size_t value_len);


static utils__sdb__section_callback_t section;


static utils__sdb__value_callback_t names_values[] =
{ 
  {"ENABLE PRINTF",                                          enable_printf                                             },
  {"ENABLE LOG FILE",                                        enable_log_file                                           },
  {"LOG FILE",                                               set_log_file                                              },
  {"MAX LOG FILE LINES PER MINUTE",                          set_max_log_file_lines_per_minute                         },
  {"ENABLE TABLE LAYOUT OUTPUT",                             enable_table_layout_output                                },
  {"ENABLE APPLICATION NAME ON OUTPUT",                      enable_application_name_on_output                         },
  {"APPLICATION NAME",                                       set_application_name                                      },
  {"THREAD SLEEP TIME SECONDS",                              set_thread_sleep_time_seconds                             },
  {"ENABLE CONNECTION MONITOR TASK",                         enable_connection_monitor_task                            },
  {"PROBABILITY OF SUCCESS OF EVENTS IN SIMULATION MODE",    set_probability_of_success_of_events_in_simulation_mode   }

};


static char* fn = "okuma_mt__private__load_application_configuration()";


int okuma_mt__private__load_application_configuration(void)
{

	int rc;
	size_t record_number;
	size_t start_record;
	size_t application_names_values_max;
	int end_of_file;
	void* p;

	p = NULL;


	/*
	 * Set section data of the agent:  [OKUMA-MT AGENT]
	 */
	section.name = om->agent_section_name;
	section.function = found_agent_section;
	application_names_values_max = sizeof(names_values) / sizeof(utils__sdb__value_callback_t);


	/*
	 * extract data from config file or buffer looking for section: om->agent_section_name
	 */
	start_record = 1;

	if (om->config_mode == 0)
	{
		rc = utils__sdb__read_configuration_from_file(p, &om->sdb, om->agent_configuration_file_name, &section, names_values, application_names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__sdb__read_configuration_from_file() returned %d\n", fn, rc);
			return -100;
		}

	}
	else
	{
		rc = utils__sdb__read_configuration_from_buffer(p, &om->sdb, om->agent_configuration_file_name, &section, names_values, application_names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__sdb__read_configuration_from_buffer() returned %d\n", fn, rc);
			return -200;
		}
	}


	/*  utils__sdb__print_sdb(&om->sdb);  */

	return 0;
}


static int found_agent_section (const char* section_name, size_t section_name_len)
{

	/*
	 * Nothing to do: just keep the compiler happy
	 */
	section_name = section_name;
	section_name_len = 0;

	return 0;
}

static int enable_printf (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->config.enable_printf;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

static int enable_log_file (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->config.enable_log_file;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

static int set_log_file (const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->config.log_file_name;
	buffer_size = sizeof(om->config.log_file_name);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_max_log_file_lines_per_minute (const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->config.max_log_file_lines_per_minute;

	rc = utils__libc__write_size_t(data, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (om->config.max_log_file_lines_per_minute == 0)
	{
		return -200;
	}

	return 0;
}

static int enable_table_layout_output (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->config.enable_table_layout_output;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

static int enable_application_name_on_output (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->config.enable_application_name_on_output;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;
}

static int set_application_name (const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->config.application_name;
	buffer_size = sizeof(om->config.application_name);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_thread_sleep_time_seconds(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->config.thread_sleep_time_seconds;

	rc = utils__libc__write_size_t(data, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (om->config.thread_sleep_time_seconds == 0)
	{
		om->config.thread_sleep_time_seconds = 5;
	}

	return 0;

}

static int enable_connection_monitor_task(const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->config.enable_connection_monitor_task;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

static int set_probability_of_success_of_events_in_simulation_mode (const char* value, size_t value_len)
{

	int rc;
	double* data;

	data = &om->config.probability_of_success_of_events_in_simulation_mode_in_percentage;

	rc = utils__libc__write_double(data, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if ((om->config.probability_of_success_of_events_in_simulation_mode_in_percentage < 0) || (om->config.probability_of_success_of_events_in_simulation_mode_in_percentage > 1))
	{
		return -200;
	}

	om->probability_of_success_of_events_in_simulation_mode_in_percentage = (int) (om->config.probability_of_success_of_events_in_simulation_mode_in_percentage * 1000);

	return rc;

}
