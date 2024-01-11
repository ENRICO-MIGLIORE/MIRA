#ifndef I4_AGENT__SIEMENS_OPEN62541__PRIVATE_H
#define I4_AGENT__SIEMENS_OPEN62541__PRIVATE_H
 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


#include <open62541.h>


#include <utils__platform.h>
#include <utils__libc.h>
#include <utils__printf.h>
#include <utils__sdb.h>



#include "agent__siemens_open62541.h"

#include "i4_agency_private.h"




typedef struct
{

    UA_Client* client;

} agent__siemens_open62541__machine_t;



typedef struct
{

	UA_Client* client;

} i4_agent__siemens_open62541__machine_t;


typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int enable_table_layout_output;
	int enable_agent_name_on_output;
	char agent_name[I4_AGENCY__CONFIG__BUFFER_SIZE];
	size_t thread_sleep_time;
	int probability_of_success_of_events_in_simulation_mode;

} agent__siemens_open62541__config_2_t;


typedef struct
{
	agent__siemens_open62541__config_t config;
	agent__siemens_open62541__machine_t* machine;
	int configured;
	int started;
	
	int number_of_machines;

	const char* name;

	const char* application_name;
	//const char* agent_section_name;
	const char* machine_section_name;

	//subagent_t subagent;
	//subagent__config_2_t config_2;
	
} agent__siemens_open62541__t;



extern agent__siemens_open62541__t* agent_so;


int i4_agent__siemens_open62541__connect_to_machine (void* arg);
int i4_agent__siemens_open62541__read_machine_part_counter (void* arg);
int i4_agent__siemens_open62541__read_machine_cycle_time (void* arg);
int i4_agent__siemens_open62541__read_machine_part_program_name(void* arg);


#if 0


int agent__siemens_open62541__private__check_config(void* config);
int agent__siemens_open62541__private__check_parameters_and_agent_status(int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);




int agent__siemens_open62541__connect_to_machine(int md);


int agent__siemens_open62541__private__disconnect_from_machine(int md);




int agent__siemens_open62541__read_machine_part_counter(int md);
int agent__siemens_open62541__read_machine_cycle_time(int md);
int agent__siemens_open62541__read_machine_part_program_name(int md);


typedef struct
{
	int do_filtering;
	char prefix[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char suffix[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	size_t prefix_len;
	size_t suffix_len;

} siemens_open62541__settings__part_program_name_filter_t;


typedef struct
{

	int id;
	int operating;
	int networked;
	int simulated;

	size_t connection_timeout_seconds;
	size_t reconnection_attempts_time_interval_seconds;
	size_t max_reconnection_attempts;
	size_t no_response_timeout_seconds;
	char part_program_name_in_simulation_mode[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_initial_value_in_simulation_mode;
	double average_cycle_time_in_simulation_mode_seconds;

	char type[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char manufacturer[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char model[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char serial_number[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char facility[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char department[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];

	char cnc_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];

	char opc_ipv4_address[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char opc_ipv4_port[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char opc_user_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char opc_password[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char opc_certificate_file[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_private_key_file[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_part_counter_path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_cycle_time_path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char opc_part_program_name_path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];

	siemens_open62541__settings__part_program_name_filter_t part_program_name_filter;

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
	int connection_status_valid_simulated;

	int production_status;
	int production_status_valid;
	int production_status_simulated;
	int production_status_valid_simulated;

	int alarm_status;
	int alarm_status_valid;
	int alarm_status_simulated;
	int alarm_status_valid_simulated;

	time_t no_response_time;
	int no_response_flag;
	int connection_monitor_task_state;
	size_t reconnection_attempts;


	siemens_open62541__do_action_t connect_to_machine;
	siemens_open62541__do_action_t disconnect_from_machine;

	siemens_open62541__read_data_t read_connection_status;
	siemens_open62541__read_data_t read_production_status;
	siemens_open62541__read_data_t read_alarm_status;

	siemens_open62541__read_data_t read_part_counter;
	siemens_open62541__read_data_t read_cycle_time;
	siemens_open62541__read_data_t read_part_program_name;



	siemens_open62541__private_machine_config_t config;


	UA_Client* client;

} siemens_open62541__machine_t;


typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int enable_table_layout_output;
	int enable_application_name_on_output;
	char application_name[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	size_t thread_sleep_time_seconds;
	int enable_connection_monitor_task;
	double probability_of_success_of_events_in_simulation_mode_in_percentage;

} siemens_open62541__secondary_config_t;





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
	char* agent_version;
	char agent_name_and_version[SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256];
	char* agent_section_name;
	char* agent_default_configuration_file_name;
	char agent_configuration_file_name[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	char* machines_section_name;

	pthread_t thread_id;
	pthread_mutex_t thread_mutex;

	size_t thread_sleep_time;
	size_t thread_ticks_milliseconds;
	int thread_started;


	siemens_open62541__machine_t* machine;
	int machine_count;
	int machine_count_flag;

	int probability_of_success_of_events_in_simulation_mode_in_percentage;

	int config_mode;

	siemens_open62541__secondary_config_t config;
	int configured;
	int started;


} siemens_open62541__application_t;


#endif


#endif

