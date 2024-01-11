#include "agency_private.h"


//extern int agency__private__check_input_parameters_and_preproccess_input_data(agency_t* a, const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
extern int agency__private__check_input_parameters_and_preproccess_input_data(void* p, const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);

static int load_entry__agency_section(void *p, const char* section_name, size_t section_name_len);
static int load_entry__enable_printf(void *p, const char* data, size_t data_len);
static int load_entry__enable_log_file(void *p, const char* data, size_t data_len);
static int load_entry__log_file(void *p, const char* data, size_t data_len);
static int load_entry__max_log_file_lines_per_minute(void *p, const char* data, size_t data_len);
static int load_entry__probability_of_success_in_simulation_mode(void *p, const char* data, size_t data_len);
static int load_entry__thread_sleep_time(void *p, const char* data, size_t data_len);


/*
 * mapping: entry names to callback functions 
 */
static utils__sdb__name_callback_t names_values[] =
{

	{"ENABLE PRINTF",                                             load_entry__enable_printf                                },
	{"ENABLE LOG FILE",                                           load_entry__enable_log_file                              },
	{"LOG FILE",                                                  load_entry__log_file                                     },
	{"MAX LOG FILE LINES PER MINUTE",                             load_entry__max_log_file_lines_per_minute                }
	//{"PROBABILITY OF SUCCESS OF EVENTS IN SIMULATION MODE",       load_entry__probability_of_success_in_simulation_mode    },
	//{"THREAD SLEEP TIME",                                         load_entry__thread_sleep_time                            }

};

/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */



int agency__read_configuration_file (void)
{
	
	int rc;

	size_t record_number;
	size_t start_record;
	size_t names_values_max;
	int end_of_file;
	const char* fn;
	utils__sdb__section_callback_t section_callback;


	fn = "agency__private__load_configuration_data()";


	if (agency == NULL)
	{
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	if (agency->sdb.configured != 1)
	{
		printf("-100 delegate is null");
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	if (agency->pf.configured != 1)
	{
		printf("-200 delegate is null");
		//utils__printf__error(NULL, fn, -100, "delegate is null");
		return -200;
	}
	





	/*
	 * [AGENCY]
	 */

	memset(&section_callback, 0, sizeof(section_callback));

	section_callback.name = agency->name;
	section_callback.function = load_entry__agency_section;
	names_values_max = sizeof(names_values) / sizeof(utils__sdb__name_callback_t);



	/*
	 * extract data from config file or buffer
	 * 
	 * file or buffer are parsed looking for dele section name like, for example: [SIEMENS-OPEN62541 AGENT] or [FANUC-FOCAS AGENT] or others
	 */
	start_record = 1;

	if (agency->config.file_name != NULL)
	{
		rc = utils__sdb__read_configuration_from_file((void *)agency, &agency->sdb, agency->config.file_name, &section_callback, names_values, names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			printf("-1000 - utils__sdb__read_configuration_from_file() returned %d ", rc);
			utils__printf__error(&agency->pf, fn, -1000, "utils__sdb__read_configuration_from_file() returned %d", rc);
			return -1000;
		}
	}
	else
	{
		rc = utils__sdb__read_configuration_from_buffer((void *)agency, &agency->sdb, agency->config.file_name, &section_callback, names_values, names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			printf("-1100 - utils__sdb__read_configuration_from_buffer() returned %d ", rc);
			utils__printf__error(&agency->pf, fn, -1100, "utils__sdb__read_configuration_from_buffer() returned %d", rc);
			return -1100;
		}
	}


	/* utils__sdb__print_sdb(&agency->sdb); */



	return 0;
}


static int load_entry__agency_section (void *p, const char* section_name, size_t section_name_len)
{

	const char* fn;
	agency_t* a;

	fn = "load_entry__agency_section()";

	a = (agency_t *) p;
	
	if ((p == NULL) || (section_name == NULL) || (section_name_len == 0))
	{
		utils__printf__error(&agency->pf, fn, -100, "agent or section name are null pointers");
		return -100;
	}

	return 0;

}


static int load_entry__enable_printf (void *p, const char* data, size_t data_len)
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

	ag = (agency_t*) p;

	
	
	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void *) ag, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		utils__printf__error(&agency->pf, fn, -100, "input data error");
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


static int load_entry__enable_log_file(void *p, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	agency_t* ag;
	const char* fn;
	size_t minimum_token_count;
	


	fn = "load_entry__enable_log_file()";


	ag = (agency_t*)p;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*) ag, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}




	/*
	 * enable log file
	 */
	rc = utils__libc__write_1_or_0(&agency->pf.config.enable_log_file, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1100, "enable log file - utils__libc__write_1_or_0() returned %d", rc);
		return -1100;
	}

	return 0;
}


static int load_entry__log_file (void *p, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	agency_t* ag;
	const char* fn;
	size_t minimum_token_count;


	fn = "load_entry__log_file()";


	ag = (agency_t*)p;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*) ag, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}






	/*
	 * log file name
	 */
	rc = utils__libc__write_string(agency->config_2.log_file_name, sizeof(agency->config_2.log_file_name), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1200, "log file name - utils__libc__write_string() returned %d", rc);
		return -1200;
	}



	return 0;
}


static int load_entry__max_log_file_lines_per_minute (void *p, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	agency_t* ag;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "agency__load__max_log_file_lines_per_minute()";


	ag = (agency_t*)p;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void*) ag, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}





	/*
	 * ag name
	 */
	 //rc = utils__libc__write_string(agency->config_2.agent_name, sizeof(agency->config_2.agent_name), tokens[0], tokens_len[0]);
	 //if (rc != 0)
	 //{
	 //	//utils__printf__error(&agency->pf, fn, -1500, "ag name - utils__libc__write_string() returned %d", rc);
	 //	return -1500;
	 //}




	/*
	 * max log file lines per minute
	 */
	rc = utils__libc__write_int(&tmp_int, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1300, "max log file lines per minute - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
		return -1300;
	}

	if (tmp_int <= 0)
	{
		agency->pf.config.max_log_file_lines_per_minute = AGENCY__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE;
		utils__printf__warning(&agency->pf, fn, -0, "max log file lines per minute set to %zu instead of user's value %d", agency->config_2.max_log_file_lines_per_minute, tmp_int);
	}
	else
	{
		agency->pf.config.max_log_file_lines_per_minute = (size_t)tmp_int;
	}



	return 0;
}




static int load_entry__thread_sleep_time (void *p, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	agency_t* ag;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "load_entry__thread_sleep_time()";


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
	 * thread sleep time expressed in seconds
	 */
	rc = utils__libc__write_int(&tmp_int, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1700, "main thread sleep time - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
		return -1700;
	}

	if (tmp_int < AGENCY__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS)
	{
		agency->config_2.thread_sleep_time = AGENCY__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS;
		utils__printf__warning(&agency->pf, fn, -0, "thread sleep time set to %zu instead of user's value %d", agency->config_2.thread_sleep_time, tmp_int);
	}
	else
	{
		agency->config_2.thread_sleep_time = (size_t)tmp_int;
	}


	return 0;
}


static int load_entry__probability_of_success_in_simulation_mode (void *p, const char* data, size_t data_len)
{
	int rc;
	char* tokens[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_len[AGENCY__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	agency_t* ag;
	const char* fn;
	size_t minimum_token_count;
	int tmp_int;


	fn = "load_entry__probability_of_success_in_simulation_mode()";


	ag = (agency_t*)p;


	minimum_token_count = 1;
	tokens_max = AGENCY__CONFIG__TOKENS_MAX;

	rc = agency__private__check_input_parameters_and_preproccess_input_data((void *) ag, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}





	/*
	 * thread sleep time expressed in seconds
	 */
	rc = utils__libc__write_int(&tmp_int, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&agency->pf, fn, -1700, "main thread sleep time - utils__libc__write_int() returned %d - value = %d", rc, int_tmp);
		return -1700;
	}

	if (tmp_int < AGENCY__CONFIG__MIN_PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE)
	{
		agency->config_2.probability_of_success_of_events_in_simulation_mode = AGENCY__CONFIG__MIN_PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE;
		utils__printf__warning(&agency->pf, fn, -0, "probability of success set to %d instead of user's value %d", agency->config_2.probability_of_success_of_events_in_simulation_mode, tmp_int);
	}
	else
	{
		agency->config_2.probability_of_success_of_events_in_simulation_mode = tmp_int;
	}


	return 0;
}