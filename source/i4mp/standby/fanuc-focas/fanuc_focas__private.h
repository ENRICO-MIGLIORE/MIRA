#ifndef FANUC_FOCAS__PRIVATE_H
#define FANUC_FOCAS__PRIVATE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>

#include <pthread.h>
#include <Fwlib64.h>

#include <utils__sdb.h>
#include <utils__cf.h>
#include <utils__printf.h>
#include <utils__time.h>
#include <utils__libc.h>
#include <utils__platform.h>

#include "fanuc_focas__config.h"



typedef int (*fanuc_focas__read_t) (size_t);


typedef struct
{

	int enable_printf;
	int enable_log_file;
	char fully_qualified_log_file_name[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];
	size_t fully_qualified_log_file_name_len;
	size_t max_log_file_lines_per_minute;
	int enable_square_brackets_output;
	int enable_section_name_output;
	char configuration_file_section_name[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t configuration_file_section_name_len;

	size_t id;
	int enable_communications;
	int enable_simulation_mode;

	char cnc_ipv4_address[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	char cnc_ipv4_port[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	

} fanuc_focas__lathe_machine_config_t;

 
typedef struct
{
	
	char name_and_index[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;
	
	int connected;


	size_t part_counter;	
    char part_counter_utf_8[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;
	int part_counter_valid;

	double cycle_time;
	char cycle_time_utf_8[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;
	int cycle_time_valid;
	

	fanuc_focas__read_t connect_to_machine;
	fanuc_focas__read_t read_part_counter;
	fanuc_focas__read_t read_cycle_time;
	
	unsigned short handle;

	char error_buffer[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	utils__printf_t pf;

	fanuc_focas__lathe_machine_config_t config;
	int configured;

} fanuc_focas__lathe_machine_t;



typedef struct
{

	int enable_printf;
	int enable_log_file;
	char fully_qualified_log_file_name[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];
	size_t fully_qualified_log_file_name_len;
	size_t max_log_file_lines_per_minute;
	int enable_square_brackets_output;
	int enable_section_name_output;
	char configuration_file_section_name[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t configuration_file_section_name_len;

} fanuc_focas__config_t;



typedef struct
{

	utils__sdb_t sdb;
	char sdb_buffer[FANUC_FOCAS__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	char sdb_language_iso_639_1_buffer[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX * UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	utils__printf_t pf;


	char* application_name;
	char* application_version;
	char application_name_and_version[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t application_name_and_version_len;
	char* application_default_configuration_file_name;
	char application_fully_qualified_configuration_file_name[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];
	char* application_configuration_file_section_name;
	size_t application_configuration_file_section_name_len;


	char* machines_configuration_file_section_name;
	size_t machines_configuration_file_section_name_len;

	char error_buffer[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];



	pthread_t pthread_id;
	pthread_mutex_t pthread_mutex;
	size_t pthread_sleep_time_seconds;

	fanuc_focas__lathe_machine_t* machine;
	size_t machine_count;
	size_t cnc_connection_attempt_timeout_seconds;


	size_t machine_flag;

	fanuc_focas__config_t config;
	int configured;	
	int pthread_started;


} fanuc_focas_t;


extern fanuc_focas_t* ff;


extern char* fanuc_focas__get_version(void);
extern int fanuc_focas__process_configuration_file(void);
extern int fanuc_focas__attach_read_functions(void);
extern int fanuc_focas__check_parameters(size_t machine_id, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
extern int fanuc_focas__allocate_clients(void);
extern int fanuc_focas__check_machine_id(size_t machine_id);
extern void* fanuc_focas__thread(void* arg);

extern int fanuc_focas__connect_to_machine(size_t machine_id);
extern int fanuc_focas__connect_to_machine__real(size_t machine_id);
extern int fanuc_focas__connect_to_machine__simulated(size_t machine_id);

extern int fanuc_focas__read_part_counter(size_t machine_id);
extern int fanuc_focas__read_part_counter__real(size_t machine_id);
extern int fanuc_focas__read_part_counter__simulated(size_t machine_id);

extern int fanuc_focas__read_cycle_time(size_t machine_id);
extern int fanuc_focas__read_cycle_time__real(size_t machine_id);
extern int fanuc_focas__read_cycle_time__simulated(size_t machine_id);




//
//int fanuc_focas__init (int argc, char *argv[]);
//int fanuc_focas__config (void);
//int fanuc_focas__start (void);
//
//int fanuc_focas__get_machine_id(size_t* machine_id, size_t machine_index);
//
//
//int fanuc_focas__get_machine_count (size_t* num_machines);
//int fanuc_focas__get_machine_id(size_t* id, size_t index);
//int fanuc_focas__get_connection_status(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len, int mode);
//
//
//int fanuc_focas__get_part_counter(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len, int mode);
//int fanuc_focas__get_cycle_time(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len, int mode);
//
//
//char* fanuc_focas__get_version(void);

#endif
