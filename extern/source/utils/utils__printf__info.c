#include "utils__libc.h"
#include "utils__printf.h"


extern int utils__printf__flush (utils__printf_t* pf, char** token, int* token_type, size_t tokens_max);




/*
 *
 * Example of output:
 *
 * Section name                 2020-09-28  08:42:43      INFO|WARNING|ERROR    Function name     Function return code      Custom printf message
 *
 * Application name 1.89.23     DATE          TIME        INFO                  fgg__config()     -100                      Hello World: f = 16.34
 *
 */

static char strftime_time_buffer[32];
static char strftime_date_buffer[32];


int utils__printf__info (utils__printf_t *pf, const char *function_name, int function_return_code, const char *message, ...)
{
	int rc;
	char *token[10];
	int token_type[10];
	size_t token_count;
	char buffer[256];
	size_t buffer_len;
	size_t buffer_size;
	size_t len;
	int vsnprintf_len;
	va_list argptr;
	char *func_name;
	time_t current_time;
	time_t diff;
	struct tm *local_time;
	const char* fn;
	int message_type;



	fn = "utils__printf__info()";


	if (pf == NULL)
	{
		return -10;
	}

	if (pf->configured != 1)
	{
		return -20;
	}

	if (message == NULL)
	{
		return -30;
	}

	if (function_name == NULL)
	{
		return -40;
	}

	message_type = pf->info;
	pf->log_file_flood_detected = 0;
	memset(token, 0, sizeof(token));
	memset(token_type, 0, sizeof(token_type));



	func_name = (char*)function_name;
	len = strlen(function_name);



	/*
	 * get current time
	 */
	current_time = time(NULL);
	if (current_time < 0)
	{
		return -200;
	}

	if (current_time < pf->current_time)
	{
		return -300;
	}


	local_time = localtime(&current_time);

	len = strftime(strftime_date_buffer, sizeof(strftime_date_buffer), "%Y-%m-%d", local_time);

	len = strftime(strftime_time_buffer, sizeof(strftime_time_buffer), "%H:%M:%S", local_time);


	
	if (pf->log_file_line_count == 0)
	{
		pf->log_file_line_count = 1;
		pf->current_time = current_time;
	}


	if ((pf->config.enable_log_file != 0) && (pf->config.log_file_name_len > 0))
	{
	
		if (pf->log_file_line_count > pf->config.max_log_file_lines_per_minute)
		{
			pf->log_file_line_count = 0;

			if (pf->current_time > current_time)
			{
				return -400;
			}

			diff = (time_t) (current_time - pf->current_time);

			pf->current_time = current_time;


			if (diff < 60)
			{
				pf->log_file_flood_in_progress++;

				if (pf->log_file_flood_in_progress < 3)
				{
					message_type = pf->error;
					func_name = (char *) fn;
					message = "too many log lines per minute";
				}
				else
				{
					message_type = pf->error;
					func_name = (char*) fn;
					message = "too many log lines: log file no more updated";				
				}

				pf->log_file_flood_detected = 1;
			}
			else
			{
				pf->log_file_flood_in_progress = 0;
			}
		}
	}


	token_count = 0;
	buffer_size = sizeof(buffer);


	if (pf->config.enable_table_layout_output == 0)
	{
		va_start(argptr, message); 
		vsnprintf_len = vsnprintf(buffer, buffer_size, message, argptr);
		va_end(argptr);
		if (vsnprintf_len < 0)
		{
			return -600;
		}
		len = (size_t) vsnprintf_len;

		token[0] = (char *) buffer;
		token_count = 1;		
		rc = utils__printf__flush(pf, token, token_type, token_count);
		return rc;
	}


	/*
	 * section name 
	 */
	if ((pf->config.enable_table_layout_output != 0) && (pf->config.enable_application_name_on_output != 0))
	{	
		if (pf->config.application_name_len > 0)
		{
			token[token_count] = (char*) pf->config.application_name;
			token_count++;
		}
	}


	buffer_len = 0;


	/*
	 * date 
	 *	 
	 * ISO extended format:  "2017-04-21"
	 */
	//len = strftime (&buffer[buffer_len], buffer_size, "%Y-%m-%d", local_time);
	//if (len == 0)
	//{
	//	buffer[0] = '-';
	//	len = 1;
	//}
	//token[token_count] = buffer;
	//token_count++;
	

	//buffer_len += (len + 1);
	//if (buffer_len > buffer_size)
	//{		
	//	return -700;
	//}
	//buffer_size -= buffer_len;


	/*
	 * time
	 *
	 * ISO extended format:  "23:15:58"
	 */	
	//len = strftime (&buffer[buffer_len], buffer_size, "%H:%M:%S", local_time);
	//if (len == 0)
	//{
	//	buffer[buffer_len] = '-';
	//	len = 1;
	//}
	//token[token_count] = &buffer[buffer_len];
	//token_count++;

	//buffer_len += (len + 1);
	//if (buffer_len > buffer_size)
	//{
	//	return -800;
	//}

	//buffer_size -= buffer_len;


	/*
	 * INFO | WARNING | ERROR
	 */
	if (message_type == pf->info)
	{
		token[token_count] = "INFO";
		token_type[token_count] = pf->info;
	}
	else if (message_type == pf->warning)
	{
		token[token_count] = "WARNING";
		token_type[token_count] = pf->warning;
	}
	else if (message_type == pf->error)
	{
		token[token_count] = "ERROR";
		token_type[token_count] = pf->error;
	}
	else 
	{
		return -900;
	}
	token_count++;



	/*
	 * function name
	 */	
	token[token_count] = func_name;
	token_count++;


	/*
	 * function return code
	 */
	rc = utils__libc__itoa (function_return_code, &buffer[buffer_len], buffer_size, &len);
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
		return -1000;
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
		return -1200;
	}
	len = (size_t)vsnprintf_len;

	token[token_count] = (char*)&buffer[buffer_len];
	token_count++;

		
	rc = utils__printf__flush(pf, token, token_type, token_count);


	return rc;

}