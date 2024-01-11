#ifndef LATHE_MACHINES_AGENT_H
#define LATHE_MACHINES_AGENT_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>


#include <pthread.h>


#include <utils__percent_encoding.h>
#include <utils__sdb.h>
#include <utils__printf.h>
#include <utils__language_iso_639_1.h>
#include <utils__time.h>
#include <utils__libc.h>
#include <utils__platform.h>


#include "lathe_machine__config.h"


typedef int (*lathe_machine__read_t) (size_t);


typedef struct
{
	int connected;

	char name_and_index[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;


	size_t part_counter;
	char part_counter_utf_8[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;
	int part_counter_valid;

	double cycle_time;
	char cycle_time_utf_8[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;
	int cycle_time_valid;


	lathe_machine__read_t connect_to_lathe_machine;
	lathe_machine__read_t connect_to_lathe_machine__simulated;

	lathe_machine__read_t read_part_counter;
	lathe_machine__read_t read_part_counter__simulated;

	lathe_machine__read_t read_cycle_time;
	lathe_machine__read_t read_cycle_time__simulated;


	utils__printf__t pf;

} lathe_machine_t;



typedef struct
{

	//utils__sdb_t sdb;
	//char sdb_buffer[LATHE_MACHINE__CONFIG__SDB_BUFFER_SIZE];
	//char *sdb_name[LATHE_MACHINE__CONFIG__SDB_FIELDS_MAX];
	//char *sdb_value[LATHE_MACHINE__CONFIG__SDB_FIELDS_MAX];
	//int sdb_encoding[LATHE_MACHINE__CONFIG__SDB_FIELDS_MAX];
	//size_t sdb_name_len[LATHE_MACHINE__CONFIG__SDB_FIELDS_MAX];
	//size_t sdb_value_len[LATHE_MACHINE__CONFIG__SDB_FIELDS_MAX];
	//char sdb_language_iso_639_1_buffer[LATHE_MACHINE__CONFIG__SDB_FIELDS_MAX * UTILS__LANGUAGE_ISO_639_1__CODE_LEN];


	char error_buffer[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];

	
	lathe_machine_t* machine;

	//siemens_open62541__lathe_machine_t* lathe_machine;

	//size_t machine_data_present_in_configuration_file;



	//siemens_open62541__application_data_t application_data;
	//siemens_open62541__lathe_machines_data_t machines_data;
	

	//siemens_open62541__config_t config;
	utils__printf__t pf;


	/*lathe_machine_application_t appplication;*/


	pthread_t pthread_id;
	pthread_mutex_t pthread_mutex;
	size_t num_machines;



	int configured;
	int started;


} lathe_machines_agent_t;



//int siemens_open62541__init (int argc, char *argv[]);
//int siemens_open62541__config (void);
//int siemens_open62541__start (void);
//
//int siemens_open62541__get_machine_count (size_t* num_machines);
//int siemens_open62541__get_machine_id(size_t* id, size_t index);
//int siemens_open62541__get_connection_status(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
//int siemens_open62541__get_part_counter (size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
//int siemens_open62541__get_cycle_time (size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//char* siemens_open62541__get_application_version(void);

                                    

int lathe_machine__get_part_counter (lathe_machines_agent_t* proxy, size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int lathe_machine__get_cycle_time(lathe_machines_agent_t* proxy, size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);






//typedef struct
//{
//
//	int connected;
//
//	char name_and_index[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t name_and_index_len;
//	
//
//	size_t part_counter;	
//    char part_counter_utf_8[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t part_counter_utf_8_len;
//	int part_counter_valid;
//
//	double cycle_time;
//	char cycle_time_utf_8[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t cycle_time_utf_8_len;
//	int cycle_time_valid;
//	
//
//	siemens_open62541__read_t connect_to_lathe_machine;
//	siemens_open62541__read_t connect_to_lathe_machine__simulated;
//
//	siemens_open62541__read_t read_part_counter_node;
//	siemens_open62541__read_t read_part_counter_node__simulated;
//
//	siemens_open62541__read_t read_cycle_time_node;
//	siemens_open62541__read_t read_cycle_time_node__simulated;
//
//	siemens_open62541__lathe_machine_config_t config;
//
//	utils__printf__t pf;
//
//
//	UA_Client* client;
//
//	lathe_machine_t lathe;
//
//} siemens_open62541__lathe_machine_t;



//typedef struct
//{
//	char* name;
//	size_t name_len;
//	char* default_configuration_file_name;
//	char fully_qualified_configuration_file_name[LATHE_MACHINE__CONFIG__MAX_PATH_SIZE];
//	char* configuration_file_section_name;
//	size_t configuration_file_section_name_len;
//
//} siemens_open62541__lathe_machines_data_t;


//typedef struct
//{
//	char* name;
//	char* version;
//	char name_and_version[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t name_and_version_len;
//	char* default_configuration_file_name;
//	char fully_qualified_configuration_file_name[LATHE_MACHINE__CONFIG__MAX_PATH_SIZE];
//	char* configuration_file_section_name;
//	size_t configuration_file_section_name_len;
//
//} siemens_open62541__application_data_t;


//typedef struct
//{
//
//	int enable_printf;
//	int enable_log_file;
//	char fully_qualified_log_file_name[LATHE_MACHINE__CONFIG__MAX_PATH_SIZE];
//	size_t fully_qualified_log_file_name_len;
//	size_t max_log_file_lines_per_minute;
//	int enable_square_brackets_output;
//	int enable_section_name_output;
//	char configuration_file_section_name[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t configuration_file_section_name_len;
//
//} siemens_open62541__config_t;




//typedef struct
//{
//
//	int enable_printf;
//	int enable_log_file;
//	char fully_qualified_log_file_name[LATHE_MACHINE__CONFIG__MAX_PATH_SIZE];
//	size_t fully_qualified_log_file_name_len;
//	size_t max_log_file_lines_per_minute;
//	int enable_square_brackets_output;
//	int enable_section_name_output;
//	char configuration_file_section_name[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t configuration_file_section_name_len;
//
//	size_t id;
//	int enable_communications;
//	int enable_simulation_mode;
//
//	char opc_ipv4_address[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	char opc_ipv4_port[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	char opc_user_name[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	char opc_password[LATHE_MACHINE__CONFIG__BUFFER_SIZE_256];
//	char opc_fully_qualified_certificate_file[LATHE_MACHINE__CONFIG__MAX_PATH_SIZE];
//	char opc_fully_qualified_private_key_file[LATHE_MACHINE__CONFIG__MAX_PATH_SIZE];
//	char opc_part_counter_node_path[LATHE_MACHINE__CONFIG__MAX_PATH_SIZE];
//
//} siemens_open62541__lathe_machine_config_t;
#endif
