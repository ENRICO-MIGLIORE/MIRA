#include "utils__printf.h"


int utils__printf__config (utils__printf_t *pf, utils__printf__config_t *config)
{


	/*
	 * Initial time mark
	 */
	pf->current_time = time(NULL);
	if (pf->current_time < 0)
	{
		return -10;
	}

	pf->config.enable_printf = config->enable_printf;	
	pf->config.enable_log_file = config->enable_log_file;
	pf->config.enable_table_layout_output = config->enable_table_layout_output;


	/*
	 * Application name
	 */
	pf->config.application_name = "";
	pf->config.application_name_len = 0;
	if ((config->application_name != NULL) && (config->application_name_len > 0))
	{
		pf->config.application_name = config->application_name;
		pf->config.application_name_len = config->application_name_len;
	}
	
	pf->config.enable_application_name_on_output = 0;
	if (config->enable_application_name_on_output != 0)
	{
		pf->config.enable_application_name_on_output = 1;
	}

	/*
	 * Log file name
	 */
	pf->config.log_file_name = "";
	pf->config.log_file_name_len = 0;
	if ((config->log_file_name != NULL) && (config->log_file_name_len > 0))
	{
		pf->config.log_file_name = config->log_file_name;
		pf->config.log_file_name_len = config->log_file_name_len;
	}

	/*
	 * Log file lines per minute
	 */
	pf->config.max_log_file_lines_per_minute = 30;
	if (config->max_log_file_lines_per_minute > 0)
	{
		pf->config.max_log_file_lines_per_minute = config->max_log_file_lines_per_minute;
	}


	pf->info = 1;
	pf->warning = 2;
	pf->error = 3;

	pf->configured = 1;

	return 0;
}