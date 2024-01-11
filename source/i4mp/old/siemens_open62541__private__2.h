#ifndef SIEMENS_OPEN62541__PRIVATE__2_H
#define SIEMENS_OPEN62541__PRIVATE__2_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>

#include <pthread.h>
#include <open62541.h>

#include <utils__platform.h>
#include <utils__libc.h>
#include <utils__printf.h>
#include <utils__sdb.h>
#include <utils__cf.h>

#include "agent__2.h"


//#define SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE                                    1024
//#define SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX                                   128
//#define SIEMENS_OPEN62541__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
//#define SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256                                  256
//
//
//#define SIEMENS_OPEN62541__MACHINE_DISCONNECTED                                     0
//#define SIEMENS_OPEN62541__MACHINE_CONNECTED                                        1


//typedef int (*siemens_open62541__read_t) (int);


typedef struct
{

	char opc_ipv4_address[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char opc_ipv4_port[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char opc_user_name[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char opc_password[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char opc_certificate_file[AGENT__2__CONFIG__MAX_PATH_SIZE];
	char opc_private_key_file[AGENT__2__CONFIG__MAX_PATH_SIZE];
	char opc_part_counter_path[AGENT__2__CONFIG__MAX_PATH_SIZE];
	char opc_cycle_time_path[AGENT__2__CONFIG__MAX_PATH_SIZE];

} siemens_open62541__machine_config_t;




//typedef struct
//{
//
//	int id;
//	int enable_communications;
//	int enable_simulation_mode;
//
//	size_t connection_timeout_seconds;
//	size_t reconnection_attempts_time_interval_seconds;
//	size_t max_reconnection_attempts;
//	size_t no_response_timeout_seconds;
//	char part_program_name_in_simulation_mode[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//
//	char brand[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//	char model[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//	char sn[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//	char name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//	char facility[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//
//	*void ext;
//
//} machine_config_t;



 
typedef struct
{
	
	
	UA_Client* client;
	//int resources_allocated;

	machine_t machine;
	siemens_open62541__machine_config_t config;

} siemens_open62541__machine_t;




//typedef struct
//{
//
//	char name_and_index[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//	size_t name_and_index_len;
//
//	int connection_status;
//	time_t no_response_time;
//	int no_response_flag;
//	int no_response_state;
//	size_t reconnection_attempts;
//
//	size_t part_counter;
//	char part_counter_utf_8[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//	size_t part_counter_utf_8_len;
//	int part_counter_valid;
//	size_t part_counter_simulated;
//
//	double cycle_time;
//	char cycle_time_utf_8[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//	size_t cycle_time_utf_8_len;
//	int cycle_time_valid;
//	double cycle_time_simulated;
//
//	char part_program_name_utf_8[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//	size_t part_program_name_utf_8_len;
//	int part_program_name_valid;
//	char part_program_name_utf_8_simulated[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//
//
//	machine__read_t allocate_resources;
//	machine__read_t connect_to_machine;
//	machine__read_t reconnect_to_machine;
//	machine__read_t read_part_counter;
//	machine__read_t read_cycle_time;
//	machine__read_t read_part_program_name;
//
//
//	//UA_Client* client;
//
//	void* ext;
//	int resources_allocated;
//
//	machine_config_t config;
//
//	//siemens_open62541__machine_config_t config;
//
//} machine_t;



//typedef struct
//{
//
//	int enable_printf;
//	int enable_log_file;
//	char log_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
//	size_t max_log_file_lines_per_minute;
//	int enable_square_brackets_output;
//	int enable_application_name_output;
//	char application_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//
//} siemens_open62541__config_t;
//
//
//typedef struct
//{
//
//	int enable_printf;
//	int enable_log_file;
//	char log_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
//	size_t max_log_file_lines_per_minute;
//	int enable_square_brackets_output;
//	int enable_application_name_output;
//	char application_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
//
//} machine_application__config_t;




typedef struct
{



	siemens_open62541__machine_t* machine;	
	int machine_count;
	int machine_count_flag;

	machine_application__config_t config;
	int configured;	
	int started;

	machine__manufacturer__t manufacturer;

} siemens_open62541_t;



typedef struct
{

	utils__sdb_t sdb;
	char sdb_buffer[SIEMENS_OPEN62541__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX];

	utils__printf_t pf;

	char* application_name;
	char* application_version;
	char application_name_and_version[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char* application_section_name;
	char* machines_section_name;
	char* default_configuration_file_name;
	char configuration_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];

	pthread_t pthread_id;
	pthread_mutex_t pthread_mutex;
	size_t pthread_sleep_time_seconds;
	int pthread_started;


	//siemens_open62541__machine_t* machine;
	//int machine_count;
	//int machine_count_flag;

	//siemens_open62541__config_t config;
	//int configured;
	//int started;


} machine__manufacturer__t;


extern siemens_open62541_t* so;


int siemens_open62541__read_configuration_file(void);
int siemens_open62541__read_configuration_file__application(void);
int siemens_open62541__read_configuration_file__machines(void);
int siemens_open62541__attach_stub_functions(void);
int siemens_open62541__check_parameters_and_agent_status(int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);

void* siemens_open62541__thread(void* arg);

//int siemens_open62541__disconnect_from_machine(int md);
//int siemens_open62541__disconnect_from_machine__real(int md);
//int siemens_open62541__disconnect_from_machine__simulated(int md);
//
//int siemens_open62541__reconnect_to_machine(int md);
//int siemens_open62541__reconnect_to_machine__real(int md);
//int siemens_open62541__reconnect_to_machine__simulated(int md);
//
//int siemens_open62541__is_machine_responding(int md);
//int siemens_open62541__is_machine_connected(int md);
//int siemens_open62541__is_machine_set_for_disconnection(int md);
//
//int siemens_open62541__set_machine_for_disconnection(int md);


int siemens_open62541__allocate_machines_resources(int md);
int siemens_open62541__allocate_machines_resources__real(int md);
int siemens_open62541__allocate_machines_resources__simulated(int md);

int siemens_open62541__connect_to_machine(int md);
int siemens_open62541__connect_to_machine__real(int md);
int siemens_open62541__connect_to_machine__simulated(int md);

int siemens_open62541__read_machine_part_counter(int md);
int siemens_open62541__read_part_counter__real(int md);
int siemens_open62541__read_machine_part_counter__simulated(int md);

int siemens_open62541__read_machine_cycle_time(int md);
int siemens_open62541__read_machine_cycle_time__real(int md);
int siemens_open62541__read_machine_cycle_time__simulated(int md);

int siemens_open62541__read_machine_part_program_name(int md);
int siemens_open62541__read_machine_part_program_name__real(int md);
int siemens_open62541__read_machine_part_program_name__simulated(int md);


#endif
