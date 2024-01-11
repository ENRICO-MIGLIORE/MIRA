#ifndef UTILS__PRINTF_H
#define UTILS__PRINTF_H


#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


typedef struct
{
	int enable_printf;
	int enable_log_file;
	const char* log_file_name;
	size_t log_file_name_len;
	size_t max_log_file_lines_per_minute;
	int enable_table_layout_output;
	int enable_application_name_on_output;
	const char* application_name;
	size_t application_name_len;

} utils__printf__config_t;



typedef struct
{

	/*
	 * config data
	 */
	utils__printf__config_t config;

	/*
	 * internal data
	 */
	size_t log_file_line_count;
	size_t log_file_flood_in_progress;
	time_t current_time;


	int log_file_flood_detected;

	int info;
	int warning;
	int error;

	int configured;


} utils__printf_t;


int utils__printf__init(utils__printf_t* pf);
int utils__printf__config(utils__printf_t* pf, utils__printf__config_t* config);
int utils__printf__info(utils__printf_t* pf, const char* function_name, int function_return_code, const char* message, ...);
int utils__printf__warning(utils__printf_t* pf, const char* function_name, int function_return_code, const char* message, ...);
int utils__printf__error(utils__printf_t* pf, const char* function_name, int function_return_code, const char* message, ...);


#endif