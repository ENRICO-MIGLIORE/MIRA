#ifndef SIEMENS_OPEN62541__PRIVATE_H
#define SIEMENS_OPEN62541__PRIVATE_H


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


#define SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE                                    1024
#define SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX                                   128
#define SIEMENS_OPEN62541__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define OKUMA_TCP__CONFIG__BUFFER_SIZE_256                                  256


typedef int (*okuma_tcp__read_data_t) (int);
typedef int (*okuma_tcp__do_action_t) (int);


typedef struct
{

	int id;
	int connect_to_machine;
	int simulation_mode;

	size_t connection_timeout_seconds;
	size_t reconnection_attempts_time_interval_seconds;
	size_t max_reconnection_attempts;
	size_t no_response_timeout_seconds;
	char part_program_name_in_simulation_mode[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_initial_value_in_simulation_mode;
	double average_cycle_time_in_simulation_mode_seconds;

	char brand[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char model[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char sn[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char name[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char facility[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	
	char opc_ipv4_address[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char opc_ipv4_port[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char opc_user_name[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char opc_password[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char opc_certificate_file[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_private_key_file[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_part_counter_path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_cycle_time_path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];

} okuma_tcp__machine_config_t;

 
typedef struct
{
	
	char name_and_index[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;
	
	
	size_t part_counter;
	int part_counter_valid;
	size_t part_counter_simulated;
	int part_counter_simulated_valid;	
    char part_counter_utf_8[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;
	
	double cycle_time;
	int cycle_time_valid;
	double cycle_time_simulated;
	int cycle_time_simulated_valid;	
	char cycle_time_utf_8[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;
	  
	char part_program_name[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	int part_program_name_valid;
	char part_program_name_simulated[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	int part_program_name_simulated_valid;
	char part_program_name_utf_8[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	size_t part_program_name_utf_8_len;
	
    int connection_status;
	int connection_status_valid;
	int connection_status_simulated;
	int connection_status_simulated_valid;

	int production_status;
	int production_status_valid;
	int production_status_simulated;
	int production_status_simulated_valid;

	
	time_t no_response_time;
	int no_response_flag;
	int connection_monitor_task_state;
	size_t reconnection_attempts;

	okuma_tcp__do_action_t allocate_machine_resources;
	okuma_tcp__do_action_t connect_to_machine;
	okuma_tcp__do_action_t disconnect_from_machine;
	okuma_tcp__do_action_t reconnect_to_machine;

	okuma_tcp__read_data_t read_part_counter;
	okuma_tcp__read_data_t read_cycle_time;
	okuma_tcp__read_data_t read_part_program_name;
	okuma_tcp__read_data_t read_machine_connection_status;
	okuma_tcp__read_data_t read_machine_production_status;
			
	okuma_tcp__machine_config_t config;


	int resources_allocated;
	UA_Client* client;

} okuma_tcp__machine_t;



typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int enable_square_brackets_output;
	int enable_application_name_output;
	char application_name[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	int enable_connection_monitor_task;
	double probability_of_success_of_events_in_simulation_mode;

} okuma_tcp__config_t;



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
	char application_name_and_version[OKUMA_TCP__CONFIG__BUFFER_SIZE_256];
	char* application_section_name;
	char* application_default_configuration_file_name;	
	char application_configuration_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char* machines_section_name;
	
	pthread_t pthread_id;
	pthread_mutex_t pthread_mutex;
	size_t pthread_sleep_time_seconds;
	int pthread_started;

	okuma_tcp__machine_t* machine;	
	int machine_count;
	int machine_count_flag;

	int percent_of_success_of_events_in_simulation_mode;

	okuma_tcp__config_t config;
	int configured;	
	int started;


} okuma_tcp_t;


extern okuma_tcp_t* so;


int okuma_tcp__private__read_configuration_file(void);
int okuma_tcp__private__read_configuration_file__application(void);
int okuma_tcp__private__read_configuration_file__machines(void);
int okuma_tcp__private__attach_stub_functions(void);
int okuma_tcp__private__check_parameters_and_agent_status(int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);

void* okuma_tcp__private__thread(void* arg);
void okuma_tcp__private__task__read_machines_data(void);
void okuma_tcp__private__task__connection_monitor(void);
void okuma_tcp__private__task__simulate_machines_data(void);

int okuma_tcp__private__stub__allocate_machine_resources(int md);
int okuma_tcp__private__stub__allocate_machines_resources__real(int md);
int okuma_tcp__private__stub__allocate_machines_resources__simulated(int md);

int okuma_tcp__private__stub__connect_to_machine(int md);
int okuma_tcp__private__stub__connect_to_machine__real(int md);
int okuma_tcp__private__stub__connect_to_machine__simulated(int md);

int okuma_tcp__private__stub__disconnect_from_machine(int md);
int okuma_tcp__private__stub__disconnect_from_machine__real(int md);
int okuma_tcp__private__stub__disconnect_from_machine__simulated(int md);

int okuma_tcp__private__stub__reconnect_to_machine(int md);
int okuma_tcp__private__stub__reconnect_to_machine__real(int md);
int okuma_tcp__private__stub__reconnect_to_machine__simulated(int md);

int okuma_tcp__private__stub__read_machine_connection_status(int md);
int okuma_tcp__private__stub__read_machine_connection_status__real(int md);
int okuma_tcp__private__stub__read_machine_connection_status__simulated(int md);

int okuma_tcp__private__stub__read_machine_production_status(int md);
int okuma_tcp__private__stub__read_machine_production_status__real(int md);
int okuma_tcp__private__stub__read_machine_production_status__simulated(int md);

int okuma_tcp__private__stub__read_machine_part_counter(int md);
int okuma_tcp__private__stub__read_part_counter__real(int md);
int okuma_tcp__private__stub__read_machine_part_counter__simulated(int md);

int okuma_tcp__private__stub__read_machine_cycle_time(int md);
int okuma_tcp__private__stub__read_machine_cycle_time__real(int md);
int okuma_tcp__private__stub__read_machine_cycle_time__simulated(int md);

int okuma_tcp__private__stub__read_machine_part_program_name(int md);
int okuma_tcp__private__stub__read_machine_part_program_name__real(int md);
int okuma_tcp__private__stub__read_machine_part_program_name__simulated(int md);



#endif
