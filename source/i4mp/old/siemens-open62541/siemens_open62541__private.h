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
#define SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256                                  256


typedef int (*siemens_open62541__read_data_t) (int);
typedef int (*siemens_open62541__do_action_t) (int);


typedef struct
{

	int id;
	int operating;
	int online;
	int simulation_mode;

	size_t connection_timeout_seconds;
	size_t reconnection_attempts_time_interval_seconds;
	size_t max_reconnection_attempts;
	size_t no_response_timeout_seconds;
	char part_program_name_in_simulation_mode[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_initial_value_in_simulation_mode;
	double average_cycle_time_in_simulation_mode_seconds;

	char manufacturer[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char model[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char serial_number[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char facility[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];

	char cnc_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	
	char opc_ipv4_address[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char opc_ipv4_port[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char opc_user_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char opc_password[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char opc_certificate_file[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_private_key_file[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_part_counter_path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_cycle_time_path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];

} siemens_open62541__private_machine_config_t;

 
typedef struct
{
	
	char name_and_index[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;
	
	
	size_t part_counter;
	int part_counter_valid;
	size_t part_counter_simulated;
	int part_counter_simulated_valid;	
    char part_counter_utf_8[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;
	
	double cycle_time;
	int cycle_time_valid;
	double cycle_time_simulated;
	int cycle_time_simulated_valid;	
	char cycle_time_utf_8[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;
	  
	char part_program_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	int part_program_name_valid;
	char part_program_name_simulated[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	int part_program_name_simulated_valid;
	char part_program_name_utf_8[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
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

	siemens_open62541__do_action_t allocate_machine_resources;
	siemens_open62541__do_action_t connect_to_machine;
	siemens_open62541__do_action_t disconnect_from_machine;
	siemens_open62541__do_action_t reconnect_to_machine;

	siemens_open62541__read_data_t read_part_counter;
	siemens_open62541__read_data_t read_cycle_time;
	siemens_open62541__read_data_t read_part_program_name;
	siemens_open62541__read_data_t read_machine_connection_status;
	siemens_open62541__read_data_t read_machine_production_status;
			
	siemens_open62541__private_machine_config_t config;


	int resources_allocated;
	UA_Client* client;

} siemens_open62541__private_machine_t;



typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int enable_table_layout_output;
	int enable_application_name_on_output;
	char agent_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	int enable_connection_monitor_task;
	double probability_of_success_of_events_in_simulation_mode;

} siemens_open62541__private_config_t;



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

	char* agent_name;
	char* agent_version;
	char agent_name_and_version[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char* agent_section_name;
	char* agent_default_configuration_file_name;	
	char agent_configuration_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char* machines_section_name;
	
	pthread_t pthread_id;
	pthread_mutex_t pthread_mutex;
	size_t pthread_sleep_time_seconds;
	int pthread_started;

	siemens_open62541__private_machine_t* machine;	
	int machine_count;
	int machine_count_flag;

	int percent_of_success_of_events_in_simulation_mode;

	int config_mode;

	siemens_open62541__private_config_t config;
	int configured;	
	int started;


} siemens_open62541_private_t;


extern siemens_open62541_private_t* so;


int siemens_open62541__private__load_configuration(void);
int siemens_open62541__private__load_agent_configuration(void);
int siemens_open62541__private__load_machines_configuration(void);
int siemens_open62541__private__check_parameters_and_agent_status(int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
int siemens_open62541__private__check_parameters_and_agent_status_2(int md, char* buffer, size_t buffer_size, size_t len);

void* siemens_open62541__private__thread(void* arg);
void siemens_open62541__private__task__read_machines_data(void);
void siemens_open62541__private__task__connection_monitor(void);
void siemens_open62541__private__task__simulate_machines_data(void);

int siemens_open62541__private__allocate_machine_resources(int md);
int siemens_open62541__private__allocate_machines_resources__real(int md);
int siemens_open62541__private__allocate_machines_resources__simulated(int md);

int siemens_open62541__private__connect_to_machine(int md);
int siemens_open62541__private__connect_to_machine__real(int md);
int siemens_open62541__private__connect_to_machine__simulated(int md);

int siemens_open62541__private__disconnect_from_machine(int md);
int siemens_open62541__private__disconnect_from_machine__real(int md);
int siemens_open62541__private__disconnect_from_machine__simulated(int md);

int siemens_open62541__private__reconnect_to_machine(int md);
int siemens_open62541__private__reconnect_to_machine__real(int md);
int siemens_open62541__private__reconnect_to_machine__simulated(int md);

int siemens_open62541__private__read_connection_status(int md);
int siemens_open62541__private__read_connection_status__real(int md);
int siemens_open62541__private__read_connection_status__simulated(int md);

int siemens_open62541__private__read_production_status(int md);
int siemens_open62541__private__read_production_status__real(int md);
int siemens_open62541__private__read_production_status__simulated(int md);

int siemens_open62541__private__read_part_counter(int md);
int siemens_open62541__private__read_part_counter__real(int md);
int siemens_open62541__private__read_part_counter__simulated(int md);

int siemens_open62541__private__read_cycle_time(int md);
int siemens_open62541__private__read_cycle_time__real(int md);
int siemens_open62541__private__read_cycle_time__simulated(int md);

int siemens_open62541__private__read_part_program_name(int md);
int siemens_open62541__private__read_part_program_name__real(int md);
int siemens_open62541__private__read_part_program_name__simulated(int md);



#endif
