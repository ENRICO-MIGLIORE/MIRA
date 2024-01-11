#include "subagent.h"


static int subagent__found_agent_section(void* subagent, const char* section_name, size_t section_name_len);

static int subagent__load_agent_enable_printf(void* subagent, const char* data, size_t data_len);
static int subagent__load_agent_enable_log_file(void* subagent, const char* data, size_t data_len);
static int subagent__load_agent_log_file(void* subagent, const char* data, size_t data_len);
static int subagent__load_agent_max_log_file_lines_per_minute(void* subagent, const char* data, size_t data_len);
static int subagent__load_agent_enable_table_layout_output(void* subagent, const char* data, size_t data_len);
static int subagent__load_agent__enable_agent_name_on_output(void* subagent, const char* data, size_t data_len);
static int subagent__load_agent__agent_thread_sleep_time(void* subagent, const char* data, size_t data_len);

//static int subagent__set_agent_data(void* subagent, const char* data, size_t data_len);


/*
 * name to callback function map
 */
static utils__sdb__value_callback_t names_values[] =
{

	{"ENABLE PRINTF",                               subagent__load_agent_enable_printf                         },
    {"ENABLE LOG FILE",                             subagent__load_agent_enable_log_file                       },
	{"LOG FILE",                                    subagent__load_agent_log_file                              },
    {"MAX LOG FILE LINES PER MINUTE",               subagent__load_agent_max_log_file_lines_per_minute         },
	{"ENABLE TABLE LAYOUT OUTPUT",                  subagent__load_agent_enable_table_layout_output            },
	{"ENABLE AGENT NAME ON OUTPUT",                 subagent__load_agent__enable_agent_name_on_output          },
	{"THREAD SLEEP TIME",                           subagent__load_agent__agent_thread_sleep_time              }

};


/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */

int subagent__load_agent_configuration_data (subagent_t *subagent)
{
	
	int rc;
	FILE* f;
	size_t record_number;
	size_t start_record;
	size_t names_values_max;
	int end_of_file;
	const char* fn;
	utils__sdb__section_callback_t section_callback;


	fn = "subagent__load_agent_configuration_data()";

	if (subagent == NULL)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	if (subagent->sdb.configured != 1)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	if (subagent->pf.configured != 1)
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


	/*
	 * example: [SIEMENS-OPEN62541 AGENT]
	 */

	memset(&section_callback, 0, sizeof(section_callback));

	section_callback.name = subagent->config.agent_section_name;
	section_callback.function = subagent__found_agent_section;
	names_values_max = sizeof(names_values) / sizeof(utils__sdb__value_callback_t);



	/*
	 * extract data from config file or buffer
	 * 
	 * file or buffer are parsed looking for dele section name like, for example: [SIEMENS-OPEN62541 AGENT] or [FANUC-FOCAS AGENT] or others
	 */
	start_record = 1;

	if (1 == 1)
	//if (subagent->config.mode == SUBAGENT__FILE_CONFIG_MODE)
	{
		rc = utils__sdb__read_configuration_from_file((void *) subagent, &subagent->sdb, subagent->config.file_name, &section_callback, names_values, names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			utils__printf__error(&subagent->pf, fn, -1000, "utils__sdb__read_configuration_from_file() returned %d", rc);
			return -1000;
		}
	}
	else
	{
		rc = utils__sdb__read_configuration_from_buffer((void*)subagent, &subagent->sdb, subagent->config.file_name, &section_callback, names_values, names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			utils__printf__error(&subagent->pf, fn, -1100, "utils__sdb__read_configuration_from_buffer() returned %d", rc);
			return -1100;
		}
	}


	/* utils__sdb__print_sdb(&subagent->sdb); */



	return 0;
}


static int subagent__found_agent_section (void* subagent, const char* section_name, size_t section_name_len)
{

	subagent_t* sub;
	const char* fn;
		
	fn = "subagent__found_agent_section()";

	if (subagent == NULL)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	sub = (subagent_t*) subagent;

	if (section_name == NULL)
	{
		utils__printf__error(&sub->pf, fn, -200, "section_name is null");
		return -200;
	}

	if (section_name_len == 0)
	{
		utils__printf__error(&sub->pf, fn, -300, "section_name_len is zero");
		return -300;
	}
	

	return 0;
}





//static int subagent__set_agent_data (void* subagent, const char* data, size_t data_len)
//{
//	int rc;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* sub;
//	const char* fn;
//	size_t minimum_token_count;
//	int tmp_int;
//
//
//	fn = "subagent__set_agent_data()";
//
//
//	minimum_token_count = 9;
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
//
//
//	/*
//	 * i4_agency name
//	 */
//	//rc = utils__libc__write_string(sub->config_2.agent_name, sizeof(sub->config_2.agent_name), tokens[0], tokens_len[0]);
//	//if (rc != 0)
//	//{
//	//	//utils__printf__error(&a->pf, fn, -1500, "subagent name - utils__libc__write_string() returned %d", rc);
//	//	return -1500;
//	//}
//
//
//	/*
//	 * enable printf
//	 */
//	rc = utils__libc__write_1_or_0(&sub->pf.config.enable_printf, tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&a->pf, fn, -1000, "enable printf - utils__libc__write_1_or_0() returned %d", rc);
//		return -1000;
//	}
//
//
//	/*
//	 * enable log file
//	 */	
//	rc = utils__libc__write_1_or_0(&sub->pf.config.enable_log_file, tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&a->pf, fn, -1100, "enable log file - utils__libc__write_1_or_0() returned %d", rc);
//		return -1100;
//	}
//
//
//	/*
//	 * log file name
//	 */
//	rc = utils__libc__write_string(sub->config_2.log_file_name, sizeof(sub->config_2.log_file_name), tokens[3], tokens_len[3]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&a->pf, fn, -1200, "log file name - utils__libc__write_string() returned %d", rc);
//		return -1200;
//	}
//
//
//	/*
//	 * max log file lines per minute
//	 */
//	rc = utils__libc__write_int(&tmp_int, tokens[4], tokens_len[4]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&a->pf, fn, -1300, "max log file lines per minute - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
//		return -1300;
//	}
//
//	if (tmp_int <= 0)
//	{
//		sub->pf.config.max_log_file_lines_per_minute = SUBAGENT__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE;
//	}
//	else
//	{
//		sub->pf.config.max_log_file_lines_per_minute = (size_t)tmp_int;
//	}
//
//
//
//	/*
//	 * enable table layout output
//	 */
//	rc = utils__libc__write_1_or_0(&sub->pf.config.enable_table_layout_output, tokens[5], tokens_len[5]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&a->pf, fn, -1400, "enable table layout output - utils__libc__write_1_or_0() returned %d", rc);
//		return -1400;
//	}
//
//
//	/*
//	 * enable i4_agency name on output
//	 */
//	rc = utils__libc__write_1_or_0(&sub->pf.config.enable_application_name_on_output, tokens[6], tokens_len[6]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&a->pf, fn, -1600, "enable subagent name on output - utils__libc__write_1_or_0() returned %d", rc);
//		return -1600;
//	}
//
//
//	/*
//	 * main thread sleep time expressed in seconds
//	 */
//	rc = utils__libc__write_int(&tmp_int, tokens[7], tokens_len[7]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&a->pf, fn, -1700, "main thread sleep time - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
//		return -1700;
//	}
//
//	if (tmp_int < SUBAGENT__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS)
//	{
//		sub->config_2.thread_sleep_time = SUBAGENT__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS;
//	}
//	else
//	{
//		sub->config_2.thread_sleep_time = (size_t)tmp_int;
//	}
//
//
//	/*
//	 * probability of success of events in simulation mode in percentage
//	 */	
//	rc = utils__libc__write_int(&tmp_int, tokens[8], tokens_len[8]);
//	if (rc != 0)
//	{
//		//utils__printf__error(&a->pf, fn, -1800, "probability of success of events in simulation mode - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
//		return -1800;
//	}
//
//	if (tmp_int > 100)
//	{
//		sub->config_2.probability_of_success_of_events_in_simulation_mode = 100;
//	}
//	else if (tmp_int < 0)
//	{
//		sub->config_2.probability_of_success_of_events_in_simulation_mode = 0;
//	}
//	else
//	{
//		sub->config_2.probability_of_success_of_events_in_simulation_mode = tmp_int;
//	}
//
//	return 0;
//}


static int subagent__load_agent_enable_printf (void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "subagent__load_agent_enable_printf()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*) subagent;



	 /*
	  * enable printf
	  */
	rc = utils__libc__write_1_or_0(&sub->pf.config.enable_printf, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&a->pf, fn, -1000, "enable printf - utils__libc__write_1_or_0() returned %d", rc);
		return -1000;
	}



	return 0;
}


static int subagent__load_agent_enable_log_file(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "subagent__load_agent_enable_log_file()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;



	/*
	 * enable log file
	 */
	rc = utils__libc__write_1_or_0(&sub->pf.config.enable_log_file, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&a->pf, fn, -1100, "enable log file - utils__libc__write_1_or_0() returned %d", rc);
		return -1100;
	}

	return 0;
}


static int subagent__load_agent_log_file(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "subagent__set_agent_data()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;


	/*
	 * i4_agency name
	 */
	 //rc = utils__libc__write_string(sub->config_2.agent_name, sizeof(sub->config_2.agent_name), tokens[0], tokens_len[0]);
	 //if (rc != 0)
	 //{
	 //	//utils__printf__error(&a->pf, fn, -1500, "subagent name - utils__libc__write_string() returned %d", rc);
	 //	return -1500;
	 //}



	/*
	 * log file name
	 */
	rc = utils__libc__write_string(sub->config_2.log_file_name, sizeof(sub->config_2.log_file_name), tokens[3], tokens_len[3]);
	if (rc != 0)
	{
		//utils__printf__error(&a->pf, fn, -1200, "log file name - utils__libc__write_string() returned %d", rc);
		return -1200;
	}



	return 0;
}


static int subagent__load_agent_max_log_file_lines_per_minute(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "subagent__load_agent__max_log_file_lines_per_minute()";


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;


	/*
	 * i4_agency name
	 */
	 //rc = utils__libc__write_string(sub->config_2.agent_name, sizeof(sub->config_2.agent_name), tokens[0], tokens_len[0]);
	 //if (rc != 0)
	 //{
	 //	//utils__printf__error(&a->pf, fn, -1500, "subagent name - utils__libc__write_string() returned %d", rc);
	 //	return -1500;
	 //}




	/*
	 * max log file lines per minute
	 */
	rc = utils__libc__write_int(&tmp_int, tokens[4], tokens_len[4]);
	if (rc != 0)
	{
		//utils__printf__error(&a->pf, fn, -1300, "max log file lines per minute - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
		return -1300;
	}

	if (tmp_int <= 0)
	{
		sub->pf.config.max_log_file_lines_per_minute = SUBAGENT__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE;
	}
	else
	{
		sub->pf.config.max_log_file_lines_per_minute = (size_t)tmp_int;
	}



	return 0;
}


static int subagent__load_agent_enable_table_layout_output(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "subagent__load_agent__enable_table_layout_output()";


	minimum_token_count = 9;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;


	/*
	 * enable table layout output
	 */
	rc = utils__libc__write_1_or_0(&sub->pf.config.enable_table_layout_output, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&a->pf, fn, -1400, "enable table layout output - utils__libc__write_1_or_0() returned %d", rc);
		return -1400;
	}


	return 0;
}


static int subagent__load_agent__enable_agent_name_on_output(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "subagent__set_agent_data()";


	minimum_token_count = 9;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;


	/*
	 * enable i4_agency name on output
	 */
	rc = utils__libc__write_1_or_0(&sub->pf.config.enable_application_name_on_output, tokens[6], tokens_len[6]);
	if (rc != 0)
	{
		//utils__printf__error(&a->pf, fn, -1600, "enable subagent name on output - utils__libc__write_1_or_0() returned %d", rc);
		return -1600;
	}



	return 0;
}


static int subagent__load_agent__agent_thread_sleep_time(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* sub;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "subagent__set_agent_data()";


	minimum_token_count = 9;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	sub = (subagent_t*)subagent;



	/*
	 * thread sleep time expressed in seconds
	 */
	rc = utils__libc__write_int(&tmp_int, tokens[7], tokens_len[7]);
	if (rc != 0)
	{
		//utils__printf__error(&a->pf, fn, -1700, "main thread sleep time - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
		return -1700;
	}

	if (tmp_int < SUBAGENT__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS)
	{
		sub->config_2.thread_sleep_time = SUBAGENT__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS;
	}
	else
	{
		sub->config_2.thread_sleep_time = (size_t)tmp_int;
	}


	return 0;
}