#include "utils__libc.h"
#include "utils__printf.h"
#include "utils__version.h"


extern int utils__printf__flush(utils__printf_t* pf, char** token, int* token_type, size_t tokens_max);


static char* fn = "utils__printf__error()";

/*
 *
 * Example of output:
 *
 * [Section name]                 [2020-09-28]  [08:42:43]   [INFO|WARNING|ERROR]  [Function name]   [Function return code]    [Custom printf message]
 *
 * [Application name 1.89.23]     [DATE]        [TIME]       [INFO]                [fgg__config()]   [0]                       [Hello World: f = 16.34]
 *
 */



int utils__printf__error (utils__printf_t* pf, const char* function_name, int function_return_code, const char* message, ...)
{
	int rc;
	char* token[8];
	int token_type[8];
	size_t token_count;
	static char buffer[256];
	size_t buffer_len;
	size_t buffer_size;
	size_t len;
	int vsnprintf_len;
	va_list argptr;
	char* func_name;
	time_t current_time;
	time_t diff;
	struct tm* local_time;
	struct tm local_time_2;
	int message_type;
	utils__printf_t local_pf;
	utils__printf__config_t local_pf_config;
	utils__printf_t* actual_pf;
	const char* actual_message;
	const char* actual_function_name;	


	//return -100;
	
	if (message == NULL)
	{		
		actual_message = "no message";
	}

	if (function_name == NULL)
	{
		actual_function_name = fn;
	}
	
	if (pf == NULL)
	{
		return -100;
	}

	if (pf == NULL)
	{
		rc = utils__printf__init(&local_pf);
		if (rc != 0)
		{
			return -100;
		}

		local_pf_config.enable_printf = 1;
		local_pf_config.enable_log_file = 0;
		local_pf_config.log_file_name = "";
		local_pf_config.log_file_name_len = 0;
		local_pf_config.max_log_file_lines_per_minute = 0;
		local_pf_config.enable_table_layout_output = 1;
		local_pf_config.enable_application_name_on_output = 1;
		local_pf_config.application_name = utils__get_application_name_and_version();
		local_pf_config.application_name_len = strlen(local_pf_config.application_name);

		rc = utils__printf__config(&local_pf, &local_pf_config);

		if (rc != 0)
		{
			return -200;
		}

		actual_pf = &local_pf;
	}
	else
	{
		actual_pf = pf;
	}

	/*actual_pf = pf;*/

	if (actual_pf->configured != 1)
	{
		return -1000;
	}


	message_type = actual_pf->error;
	actual_pf->log_file_flood_detected = 0;
	memset(token, 0, sizeof(token));
	memset(token_type, 0, sizeof(token_type));



	func_name = (char*)function_name;
	len = strlen(function_name);



	/*
	 * Get current time
	 */
	current_time = time(NULL);
	if (current_time < 0)
	{
		return -1100;
	}

	if (current_time < actual_pf->current_time)
	{
		return -1200;
	}

	
	local_time = localtime((const time_t *) &current_time);

	memcpy(&local_time_2, local_time, sizeof(struct tm));


	if (actual_pf->log_file_line_count == 0)
	{
		actual_pf->log_file_line_count = 1;
		actual_pf->current_time = current_time;
	}


	if ((actual_pf->config.enable_log_file != 0) && (actual_pf->config.log_file_name_len > 0))
	{

		if (actual_pf->log_file_line_count > actual_pf->config.max_log_file_lines_per_minute)
		{
			actual_pf->log_file_line_count = 0;

			if (actual_pf->current_time > current_time)
			{
				return -1300;
			}

			diff = (time_t)(current_time - actual_pf->current_time);

			actual_pf->current_time = current_time;


			if (diff < 60)
			{
				actual_pf->log_file_flood_in_progress++;

				if (actual_pf->log_file_flood_in_progress < 3)
				{
					message_type = actual_pf->error;
					func_name = fn;
					message = "too many log lines per minute";
				}
				else
				{
					message_type = actual_pf->error;
					func_name = fn;
					message = "too many log lines: log file no more updated";
				}

				actual_pf->log_file_flood_detected = 1;
			}
			else
			{
				actual_pf->log_file_flood_in_progress = 0;
			}
		}
	}


	token_count = 0;
	buffer_size = sizeof(buffer);


	if (actual_pf->config.enable_table_layout_output == 0)
	{
		va_start(argptr, message);
		vsnprintf_len = vsnprintf(buffer, buffer_size, message, argptr);
		va_end(argptr);
		if (vsnprintf_len < 0)
		{
			return -1400;
		}
		len = (size_t)vsnprintf_len;

		token[0] = (char*)buffer;
		token_count = 1;
		rc = utils__printf__flush(actual_pf, token, token_type, token_count);
		return rc;
	}


	/*
	 * [Section name]
	 */
	if ((actual_pf->config.enable_table_layout_output != 0) && (actual_pf->config.enable_application_name_on_output != 0))
	{
		if (actual_pf->config.application_name_len > 0)
		{
			token[token_count] = (char*)actual_pf->config.application_name;
			token_count++;
		}
	}


	buffer_len = 0;


	/*
	 * [Date]
	 *
	 * ISO extended format:  "2017-04-21"
	 */
	//len = strftime(&buffer[buffer_len], buffer_size, "%Y-%m-%d", (const struct tm*) &local_time_2);
	//_tzset();
	len = strftime(&buffer[buffer_len], buffer_size, "%Y", (const struct tm*) &local_time_2);
	if (len == 0)
	{
		buffer[0] = '-';
		len = 1;
	}
	token[token_count] = buffer;
	token_count++;


	buffer_len += (len + 1);
	if (buffer_len > buffer_size)
	{
		return -1500;
	}
	buffer_size -= buffer_len;


	/*
	 * [Time]
	 *
	 * ISO extended format:  "23:15:58"
	 */
	//len = strftime(&buffer[buffer_len], buffer_size, "%H:%M:%S", (const struct tm*) &local_time_2);
	len = strftime(&buffer[buffer_len], buffer_size, "%H", (const struct tm*)&local_time_2);
 	if (len == 0)
	{
		buffer[buffer_len] = '-';
		len = 1;
	}
	token[token_count] = &buffer[buffer_len];
	token_count++;

	buffer_len += (len + 1);
	if (buffer_len > buffer_size)
	{
		return -1600;
	}

	buffer_size -= buffer_len;


	/*
	 * [INFO | WARNING | ERROR]
	 */
	if (message_type == actual_pf->info)
	{
		token[token_count] = "INFO";
		token_type[token_count] = actual_pf->info;
	}
	else if (message_type == actual_pf->warning)
	{
		token[token_count] = "WARNING";
		token_type[token_count] = actual_pf->warning;
	}
	else if (message_type == actual_pf->error)
	{
		token[token_count] = "ERROR";
		token_type[token_count] = actual_pf->error;
	}
	else
	{
		token[token_count] = "I_ERR";
		token_type[token_count] = actual_pf->error;
	}
	token_count++;



	/*
	 * [Function name]
	 */
	token[token_count] = func_name;
	token_count++;


	/*
	 * [Function return code]
	 */	
	rc = utils__libc__itoa(function_return_code, &buffer[buffer_len], buffer_size, &len);
	if (rc != 0)
	{
		buffer[buffer_len] = '-';
		len = 1;
	}
	token[token_count] = &buffer[buffer_len];
	token_count++;


	buffer_len += (len + 1);
	if (buffer_len > buffer_size)
	{
		return -1700;
	}

	buffer_size -= buffer_len;


	/*
	 * [Message]
	 */
	va_start(argptr, message);
	vsnprintf_len = vsnprintf(&buffer[buffer_len], buffer_size, message, argptr);
	va_end(argptr);
	if (vsnprintf_len < 0)
	{
		return -1800;
	}
	len = (size_t)vsnprintf_len;

	token[token_count] = (char*)&buffer[buffer_len];
	token_count++;


	rc = utils__printf__flush(actual_pf, token, token_type, token_count);


	return rc;

}