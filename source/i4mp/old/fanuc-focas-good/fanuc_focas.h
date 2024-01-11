#ifndef FANUC_FOCAS_H
#define FANUC_FOCAS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>


#include <pthread.h>
#include <Fwlib64.h>


#include <utils__percent_encoding.h>
#include <utils__sdb.h>
#include <utils__printf.h>
#include <utils__language_iso_639_1.h>
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

	char opc_ipv4_address[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	char opc_ipv4_port[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	char opc_user_name[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	char opc_password[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	char opc_fully_qualified_certificate_file[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];
	char opc_fully_qualified_private_key_file[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];
	char opc_part_counter_node_path[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];

} fanuc_focas__lathe_machine_config_t;


typedef struct
{

	int connected;
	char name_and_index[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;
	

	size_t part_counter;	
    char part_counter_utf_8[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;
	int part_counter_valid;

	double cycle_time;
	char cycle_time_utf_8[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;
	int cycle_time_valid;
	

	fanuc_focas__read_t connect_to_lathe_machine;
	fanuc_focas__read_t connect_to_lathe_machine__simulated;

	fanuc_focas__read_t read_part_counter_node;
	fanuc_focas__read_t read_part_counter_node__simulated;

	fanuc_focas__read_t read_cycle_time_node;
	fanuc_focas__read_t read_cycle_time_node__simulated;

	fanuc_focas__lathe_machine_config_t config;

	utils__printf_t pf;


	//UA_Client* client;
	unsigned short focas_handle;

} fanuc_focas__lathe_machine_t;



typedef struct
{
	char* name;
	size_t name_len;
	char* default_configuration_file_name;
	char fully_qualified_configuration_file_name[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];
	char* configuration_file_section_name;
	size_t configuration_file_section_name_len;

} fanuc_focas__lathe_machines_data_t;


typedef struct
{
	char* name;
	char* version;
	char name_and_version[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];
	size_t name_and_version_len;
	char* default_configuration_file_name;
	char fully_qualified_configuration_file_name[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];
	char* configuration_file_section_name;
	size_t configuration_file_section_name_len;

} fanuc_focas__application_data_t;


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
	char *sdb_name[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	char *sdb_value[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX];
	char sdb_language_iso_639_1_buffer[FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX * UTILS__LANGUAGE_ISO_639_1__CODE_LEN];


	char error_buffer[FANUC_FOCAS__CONFIG__BUFFER_SIZE_256];


	pthread_t pthread_id;
	pthread_mutex_t pthread_mutex;
	

	
	fanuc_focas__lathe_machine_t* lathe_machine;
	size_t num_machines;
	size_t machine_data_present_in_configuration_file;



	fanuc_focas__application_data_t application_data;
	fanuc_focas__lathe_machines_data_t machines_data;
	

	fanuc_focas__config_t config;
	utils__printf_t pf;

	int configured;
	int started;



} fanuc_focas_t;



int fanuc_focas__init (int argc, char *argv[]);
int fanuc_focas__config (void);
int fanuc_focas__start (void);


int fanuc_focas__get_machine_count (size_t* num_machines);
int fanuc_focas__get_connection_status(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_part_counter (size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_cycle_time (size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);


char* fanuc_focas__get_application_version (void);

#endif
