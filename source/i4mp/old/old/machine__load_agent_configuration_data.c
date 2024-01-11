#include "machine.h"


static int agent__found_section(void* subagent, const char* section_name, size_t section_name_len);
static int agent__set_data(void* subagent, const char* value, size_t value_len);


static utils__sdb__value_callback_t names_values[] =
{
    {"DATA",          agent__set_data}
};



/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */




//int agent__load_configuration_data (machine_t* subagent)

int agent__load_agent_configuration_data (utils__sdb_t* sdb, utils__printf_t* pf)
{
	
	int rc;
	FILE* f;
	size_t record_number;
	size_t start_record;
	size_t names_values_max;
	int end_of_file;
	const char* fn;
	utils__sdb__section_callback_t agent_section_callback;


	fn = "agent__load_agent_configuration_data()";


	if (sdb == NULL)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	if (sdb->configured != 1)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	if (pf == NULL)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	if (pf->configured != 1)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}
	

	f = fopen((const char*)subagent->config.file_name, "rb");
	if (f == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -200, "file %s not found", subagent->config.file_name);
		return -200;
	}
	fclose(f);


	agent_section_callback.name = subagent->config.agent_section_name;
	agent_section_callback.function = agent__found_section;
	names_values_max = sizeof(names_values) / sizeof(utils__sdb__value_callback_t);


	/*
	 * extract data from config file or buffer
	 * 
	 * file or buffer are parsed looking for dele section name like, for example: [SIEMENS-OPEN62541 AGENT] or [FANUC-FOCAS AGENT] or others
	 */
	start_record = 1;

	if (subagent->config.mode == MACHINE__FILE_CONFIG_MODE)
	{
		rc = utils__sdb__read_configuration_from_file((void *) subagent, &subagent->sdb, subagent->config.file_name, &agent_section_callback, names_values, names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			////utils__printf__error(&subagent->pf, fn, -1000, "utils__sdb__read_configuration_from_file() returned %d", rc);
			return -1000;
		}
	}
	else
	{
		rc = utils__sdb__read_configuration_from_buffer((void*)subagent, &subagent->sdb, subagent->config.file_name, &agent_section_callback, names_values, names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			////utils__printf__error(&subagent->pf, fn, -1100, "utils__sdb__read_configuration_from_buffer() returned %d", rc);
			return -1100;
		}
	}


	/* utils__sdb__print_sdb(&delegate->sdb); */

	return 0;
}

static int agent__found_section (void* subagent, const char* section_name, size_t section_name_len)
{

	machine_t* dele;
	const char* fn;
		
	fn = "agent__found_section()";

	if (subagent == NULL)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*) subagent;

	if (section_name == NULL)
	{
		//utils__printf__error(&dele->pf, fn, -200, "section_name is null");
		return -200;
	}

	if (section_name_len == 0)
	{
		//utils__printf__error(&dele->pf, fn, -300, "section_name_len is zero");
		return -300;
	}
	

	return 0;
}


/*
 * example of config file entry:
 *
 * AGENT LOG DATA = AGENT LOG DATA = YES; YES; D:\PROGS\prog-97--i4mp\deployments\i4mp_log.txt; 60; YES; SIEMENS-OPEN62541; YES; 5; 99
 *
 *
 * tokens[0] = YES                                                 ENABLE PRINTF
 * tokens[1] = YES                                                 ENABLE LOG FILE
 * tokens[2] = D:\PROGS\prog-97--i4mp\deployments\i4mp_log.txt     LOG FILE NAME
 * tokens[3] = 120                                                 MAX LOG FILE LINES PER MINUTE
 * tokens[4] = YES                                                 ENABLE TABLE LAYOUT OUTPUT
 * tokens[5] = OKUMA-MT                                            AGENT NAME
 * tokens[6] = YES                                                 ENABLE AGENT NAME ON OUTPUT
 * tokens[7] = 5                                                   MAIN THREAD SLEEP TIME IN SECONDS
 * tokens[8] = 99                                                  PROBABILITY OF SUCCESS OF EVENTS IN SIMULATION MODE IN PERCENTAGE
 *
 */
static int agent__set_data (void* subagent, const char* value, size_t value_len)
{
	int rc;
	int* int_data;
	int int_tmp;
	char* tokens[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_len[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	const char* fn;
	machine_t* dele;
	size_t minimum_token_count;
	char* b;
	size_t size;

	
	fn = "agent__set_data()";

	if (subagent == NULL)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*)subagent;
	

	minimum_token_count = 9;
	tokens_max = MACHINE__CONFIG__TOKENS_MAX;

	rc = machine__preprocess_input_data(subagent, fn, value, value_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -200, "machine__preprocess_input_data() returned %d", rc);
		return -200;
	}


	/*
	 * enable printf
	 */
	int_data = &dele->config_2.enable_printf;

	rc = utils__libc__write_yes_or_no(int_data, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1000, "enable printf - utils__libc__write_yes_or_no() returned %d", rc);
		return -1000;
	}


	/*
	 * enable log file
	 */
	int_data = &dele->config_2.enable_log_file;

	rc = utils__libc__write_yes_or_no(int_data, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1100, "enable log file - utils__libc__write_yes_or_no() returned %d", rc);
		return -1100;
	}


	/*
	 * log file name
	 */
	b = dele->config_2.log_file_name;
	size = sizeof(dele->config_2.log_file_name);

	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1200, "log file name - utils__libc__write_string() returned %d", rc);
		return -1200;
	}


	/*
	 * max log file lines per minute
	 */
	int_data = &int_tmp;
	
	rc = utils__libc__write_int(int_data, tokens[3], tokens_len[3]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1300, "max log file lines per minute - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
		return -1300;
	}

	if (int_tmp <= 0)
	{
		dele->config_2.max_log_file_lines_per_minute = SUBAGENT__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE;
	}
	else
	{
		dele->config_2.max_log_file_lines_per_minute = (size_t) int_tmp;
	}


	/*
	 * enable table layout output
	 */
	int_data = &dele->config_2.enable_table_layout_output;

	rc = utils__libc__write_yes_or_no(int_data, tokens[4], tokens_len[4]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1400, "enable table layout output - utils__libc__write_yes_or_no() returned %d", rc);
		return -1400;
	}


	/*
	 * agent name
	 */
	b = dele->config_2.agent_name;
	size = sizeof(dele->config_2.agent_name);

	rc = utils__libc__write_string(b, size, tokens[5], tokens_len[5]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1500, "agent name - utils__libc__write_string() returned %d", rc);
		return -1500;
	}


	/*
	 * enable agent name on output
	 */
	int_data = &dele->config_2.enable_agent_name_on_output;

	rc = utils__libc__write_yes_or_no(int_data, tokens[6], tokens_len[6]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1600, "enable agent name on output - utils__libc__write_yes_or_no() returned %d", rc);
		return -1600;
	}



	/*
	 * main thread sleep time expressed in seconds
	 */
	int_data = &int_tmp;
	
	rc = utils__libc__write_int(int_data, tokens[7], tokens_len[7]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1700, "main thread sleep time - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
		return -1700;
	}

	if (int_tmp < SUBAGENT__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS)
	{
		dele->config_2.main_thread_sleep_time_in_seconds = SUBAGENT__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS;
	}
	else
	{
		dele->config_2.main_thread_sleep_time_in_seconds = int_tmp;
	}


	/*
	 * probability of success of events in simulation mode in percentage
	 */	
	int_data = &int_tmp;

	rc = utils__libc__write_int(int_data, tokens[8], tokens_len[8]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1800, "probability of success of events in simulation mode - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
		return -1800;
	}

	if (int_tmp > 100)
	{
		dele->config_2.probability_of_success_of_events_in_simulation_mode_in_percentage = 100;
	}
	else if (int_tmp < 0)
	{
		dele->config_2.probability_of_success_of_events_in_simulation_mode_in_percentage = 0;
	}
	else
	{
		dele->config_2.probability_of_success_of_events_in_simulation_mode_in_percentage = int_tmp;
	}

	return 0;
}


