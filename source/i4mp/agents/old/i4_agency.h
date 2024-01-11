#ifndef I4_AGENCY_H
#define I4_AGENCY_H
 

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>


#include "agent__siemens_open62541__private.h"
 
#include <pthread.h>


#include <utils__platform.h>
#include <utils__libc.h>
#include <utils__printf.h>
#include <utils__sdb.h>


#define I4_AGENCY__MACHINE_ID                                                   0
#define I4_AGENCY__MACHINE_NAME                                                 1


#define I4_AGENCY__CONFIG__MAX_PATH_SIZE                                    1024
#define I4_AGENCY__CONFIG__SDB_FIELDS_MAX                                   64
#define I4_AGENCY__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define I4_AGENCY__CONFIG__BUFFER_SIZE                                      I4_AGENCY__CONFIG__MAX_PATH_SIZE
#define I4_AGENCY__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS                   5
#define I4_AGENCY__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE                    60
#define I4_AGENCY__CONFIG__TOKENS_MAX                                       32

#define I4_AGENCY__CONFIG__MIN_PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE      5
//#define I4_AGENCY__PART_COUNTER_INITIAL_VALUE_IN_SIMULATION_MODE           100
//#define I4_AGENCY__AVERAGE_CYCLE_TIME_IN_SIMULATION_MODE                  30.0


#define I4_AGENCY__TYPE_1                                                   1



#define I4_AGENCY__FILE_CONFIG_MODE                                 0
#define I4_AGENCY__BUFFER_CONFIG_MODE                               1
#define I4_AGENCY__UNESCAPE_SEQUENCE                                "!s"
#define I4_AGENCY__UNESCAPE_SEQUENCE_LEN                            2
#define I4_AGENCY__UNESCAPE_REPLACEMENT_CHAR                        ';'
#define I4_AGENCY__FIELDS_SEPARATORS                                {";"}
#define I4_AGENCY__FIELDS_SEPARATORS_MAX                            1
#define I4_AGENCY__CHARACTER_TO_TRIM                                ' '



typedef int (*agent__read_machine_data_t) (int md);
typedef int (*agent__connect_to_machine_t) (int md);
typedef int (*agent__disconnect_from_machine_t) (int md);
typedef void* (*agent__thread_t) (void* arg);



typedef struct
{
	int do_filtering;
	char prefix[I4_AGENCY__CONFIG__BUFFER_SIZE];
	char suffix[I4_AGENCY__CONFIG__BUFFER_SIZE];
	size_t prefix_len;
	size_t suffix_len;

} agent__settings__part_program_name_filter_t;



typedef struct
{

	/*
	 * MACHINE ID
	 */
	int id;


	/*
	 * MACHINE NAME
	 */
	char name[I4_AGENCY__CONFIG__BUFFER_SIZE];


	/*
	 * MACHINE OPERATING MODE DATA
	 */
	int networked;
	int run_mode;



	/*
	 * MACHINE OPC SERVER DATA
	 */
	char opc_server_ipv4_address[I4_AGENCY__CONFIG__BUFFER_SIZE];
	char opc_server_ipv4_port[I4_AGENCY__CONFIG__BUFFER_SIZE];
	char opc_server_user_name[I4_AGENCY__CONFIG__BUFFER_SIZE];
	char opc_server_password[I4_AGENCY__CONFIG__BUFFER_SIZE];
	char opc_server_private_key_file[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_server_certificate_file[I4_AGENCY__CONFIG__MAX_PATH_SIZE];


	

	/*
	 * MACHINE OPC SERVER NODES DATA
	 */
	char opc_server_part_counter_node_path[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_server_cycle_time_node_path[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_server_part_program_name_node_path[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
	

	size_t thread_sleep_time;                                                   /* seconds */
    //int probability_of_success_of_events_in_simulation_mode;                    /* percentage: integer value from 0 to 100 */
	//int average_cycle_time_in_simulation_mode;                                  /* seconds */
	//int part_counter_initial_value_in_simulation_mode;
	char part_program_name_in_simulation_mode[I4_AGENCY__CONFIG__BUFFER_SIZE];

} agent__machine__config_2_t;



typedef struct
{

	int md;
	agent__connect_to_machine_t connect_to_machine;
	agent__disconnect_from_machine_t disconnect_from_machine;
	agent__read_machine_data_t read_part_counter;
	agent__read_machine_data_t read_cycle_time;
	agent__read_machine_data_t read_part_program_name;

} agent__machine__config_t;




typedef struct
{
	agent__machine__config_t config;
	agent__machine__config_2_t config_2;
	int configured;
	int started;

	utils__printf_t pf;

	agent__thread_t thread;
	pthread_t thread_id;
	pthread_mutex_t thread_mutex;
	size_t thread_sleep_time_milliseconds;
	size_t thread_ticks_milliseconds;
	int thread_started;
	int thread_stop_request;

	int connection_status_valid;
	int connection_status;

	int alarm_status_valid;
	int alarm_status;

	int production_status_valid;
	int production_status;

	int part_counter_valid;
	int part_counter_native;
	char part_counter[I4_AGENCY__CONFIG__BUFFER_SIZE];
	int part_counter_simulation_mode_first_time;

	int cycle_time_valid;
	double cycle_time_native;
	char cycle_time[I4_AGENCY__CONFIG__BUFFER_SIZE];

	int part_program_name_valid;
	char part_program_name[I4_AGENCY__CONFIG__BUFFER_SIZE];


} agent__machine_t;


//typedef struct
//{
//	int agent_type;
//	const char* file_name;
//	char* buffer;
//	size_t buffer_len;
//
//	const char* agent_section_name;
//	const char* machine_section_name;
//
//} agent__config_good_t;



typedef struct
{
	agent____config_t config;

	agent__machine_t* machine;
	int number_of_machines;

	int configured;
	int started;


	const char* name;
	//const char* section_name;
	const char* machine_section_name;

} i4_agent_t;


typedef struct
{

	const char* file_name;
	char* buffer;
	size_t buffer_len;

	//const char* agent_section_name;
	//const char* machine_section_name;

} i4_agency__config_t;


typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int probability_of_success_of_events_in_simulation_mode;
	size_t thread_sleep_time;

	//int enable_table_layout_output;
    //int enable_agent_name_on_output;
    //char agent_name[I4_AGENCY__CONFIG__BUFFER_SIZE];

} agency__config_2_t;





typedef struct
{
	i4_agency__config_t config;
	agency__config_2_t config_2;
	
	utils__sdb_t sdb;
	char sdb_buffer[I4_AGENCY__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];

	utils__printf_t pf;

	i4_agent_t* agent;
	int number_of_agents;
	int number_of_machines;

	char* section_name;

	char* name;

	int configured;
	int started;

} i4_agency_t;


extern i4_agency_t *i4_agency;


int i4_agency__init(void);
int i4_agency__config(i4_agency__config_t* config);
int i4_agency__start(void);


int i4_agency__get_machine_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4_agency__get_machine_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


void* i4_agency__thread(void* arg);
void i4_agency__suspend_thread(agent__machine_t* machine, size_t milliseconds);
int i4_agency__convert_machine_descriptor_to_agent_descriptor(int md, int* ad, int* ag_md);
int i4_agency__check_machine_and_input_parameters(agent__machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
int i4_agency__get_machine_config_data(int data_id, int md, char* buffer, size_t buffer_size, size_t* buffer_len);


//int agent__load_agent_configuration_data(subagent_t* subagent);
//int agent__load_machines_configuration_data(subagent_t* subagent, int* number_of_machines);
//
//int agent__get_machine_id(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_manufacturer(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_model(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_serial_number(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_manufacture_year(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int agent__get_machine_organization(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int agent__get_machine_alarm_status(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_connection_status(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_part_counter(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_production_status(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_part_program_name(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_facility(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_active_status(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_networked_status(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_run_mode_status(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_department(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_name(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_model(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_cycle_time(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);





//
//
//
//
//int agent__check_machine_and_input_parameters(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
//int agent__check_input_parameters_and_preproccess_input_data(subagent_t* subagent, const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
//int agent__check_and_preprocess_input_data(const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
//int agent__check_config(agent__machine__config_t* config);
//
//
//void agent__suspend_thread(agent_machine_t* machine, size_t milliseconds);
//void* agent__thread(void* arg);
//
//
//
//
//int agent__connect_to_machine(agent_machine_t* machine);
//int agent__read_machine_part_counter(agent_machine_t* machine);
//int agent__read_machine_cycle_time(agent_machine_t* machine);
//int agent__read_machine_part_program_name(agent_machine_t* machine);
//
//
//
//int agents__load_agents_configuration_data(i4_agency_t* a);
//int agents__load_machines_configuration_data(i4_agency_t* a, int* number_of_machines);
//int i4_agency__check_input_parameters_and_preproccess_input_data(i4_agency_t* a, const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
//
//

//
//typedef int (*agent__read_machine_data_t) (int);
//typedef int (*agent__connect_to_machine_t) (int);
//typedef void* (*agent__thread_t) (void* arg);
//
//
//
//typedef struct
//{
//	int do_filtering;
//	char prefix[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char suffix[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t prefix_len;
//	size_t suffix_len;
//
//} agent__settings__part_program_name_filter_t;
//
//
//delegate__do_action_t connect_to_machine;
//
//
//
//typedef struct
//{
//	agent__connect_to_machine_t connect_to_machine;
//
//	agent__read_machine_data_t read_part_counter;
//
//} agent__machine__config_t;
//
//
//typedef struct
//{
//
//	/*
//	 * MACHINE ID
//	 */
//	int id;
//
//	/*
//	 * MACHINE TYPE
//	 */
//	char type[I4_AGENCY__CONFIG__BUFFER_SIZE];
//
//	/*
//	 * MACHINE PLATE DATA
//	 */
//	char manufacturer[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char model[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char serial_number[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char manufacture_year[I4_AGENCY__CONFIG__BUFFER_SIZE];
//
//	/*
//	 * MACHINE FIELD DATA
//	 */	
//	int networked;
//	int run_mode;
//	int active;
//
//	/*
//	 * MACHINE LOCATION DATA
//	 */	
//	char organization[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char facility[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char department[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char name[I4_AGENCY__CONFIG__BUFFER_SIZE];
//
//	/*
//	 * MACHINE TECHNICAL DATA
//	 */
//	char cnc[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char hmi[I4_AGENCY__CONFIG__BUFFER_SIZE];
//
//
//	/*
//	 * MACHINE FEEDER DATA
//	 */
//	char feeder_manufacturer[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char feeder_model[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char feeder_serial_number[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char feeder_manufacture_year[I4_AGENCY__CONFIG__BUFFER_SIZE];
//
//
//
//
//
//	size_t connection_timeout_seconds;
//	size_t reconnection_attempts_time_interval_seconds;
//	size_t max_reconnection_attempts;
//	size_t no_response_timeout_seconds;
//	char part_program_name_in_simulation_mode[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t part_counter_initial_value_in_simulation_mode;
//	double average_cycle_time_in_simulation_mode_seconds;
//
//
//	char opc_ipv4_address[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char opc_ipv4_port[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char opc_user_name[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char opc_password[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	char opc_certificate_file[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
//	char opc_private_key_file[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
//
//
//	char opc_part_counter_path[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
//	char opc_cycle_time_path[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
//	char opc_part_program_name_path[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
//
//	agent__settings__part_program_name_filter_t part_program_name_filter;
//
//} agent__machine_config_2_t;
//
//
//
//typedef struct
//{
//
//	int md;
//	agent__machine__config_t config;
//	agent__machine_config_2_t config_2;
//
//	char name_and_index[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t name_and_index_len;
//
//
//	utils__printf_t pf;
//
//
//	utils__sdb_t sdb;
//	char sdb_buffer[I4_AGENCY__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//
//	size_t part_counter;
//	int part_counter_valid;
//	size_t part_counter_simulated;
//	int part_counter_simulated_valid;
//	char part_counter_utf_8[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t part_counter_utf_8_len;
//
//	double cycle_time;
//	int cycle_time_valid;
//	double cycle_time_simulated;
//	int cycle_time_simulated_valid;
//	char cycle_time_utf_8[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t cycle_time_utf_8_len;
//
//	char part_program_name[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	int part_program_name_valid;
//	char part_program_name_simulated[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	int part_program_name_simulated_valid;
//	char part_program_name_utf_8[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t part_program_name_utf_8_len;
//
//	int connection_status;
//	int connection_status_valid;
//	int connection_status_simulated;
//	int connection_status_valid_simulated;
//
//	int production_status;
//	int production_status_valid;
//	int production_status_simulated;
//	int production_status_valid_simulated;
//
//	int alarm_status;
//	int alarm_status_valid;
//	int alarm_status_simulated;
//	int alarm_status_valid_simulated;
//
//	time_t no_response_time;
//	int no_response_flag;
//	int connection_monitor_task_state;
//	size_t reconnection_attempts;
//
//
//	agent__thread_t thread;
//	pthread_t thread_id;
//	pthread_mutex_t thread_mutex;
//	size_t thread_sleep_time_milliseconds;
//	size_t thread_ticks_milliseconds;
//	int thread_started;
//	int thread_stop_request;
//
//	int probability_of_success_of_events_in_simulation_mode;
//	/*UA_Client* client;*/
//
//} machine_data_t;
//
//
//
//typedef struct
//{
//
//	int enable_printf;
//	int enable_log_file;
//	char log_file_name[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
//	size_t max_log_file_lines_per_minute;
//	int enable_table_layout_output;
//	int enable_agent_name_on_output;
//	char agent_name[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t thread_sleep_time;
//	int probability_of_success_of_events_in_simulation_mode;
//
//} agent__machine__config_2_t;
//
//
//
//typedef struct
//{
//	int agent_type;
//	int mode;
//	const char* file_name;
//	char* buffer;
//	size_t buffer_len;
//
//	const char* agent_name;
//	const char* agent_version;
//	char agent_name_and_version[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	const char* agent_default_config_file_name;
//	const char* agent_section_name;
//	const char* agent_machines_section_name;
//
//	agent__connect_to_machine_t connect_to_machine;
//	agent__connect_to_machine_t disconnect_from_machine;
//
//	delegate__read_data_t read_connection_status;
//	delegate__read_data_t read_production_status;
//	delegate__read_data_t read_alarm_status;
//
//	agent__read_machine_data_t read_part_counter;
//	agent__read_machine_data_t read_cycle_time;
//	agent__read_machine_data_t read_part_program_name;
//
//} agent__machine__config_t;
//
//
//typedef struct
//{
//	agent__machine__config_t config;
//	agent__machine__config_2_t config_2;
//	int configured;
//	int started;
//
//	utils__printf_t pf;
//
//	utils__sdb_t sdb;
//	char sdb_buffer[I4_AGENCY__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	
//
//	machine_data_t* machine_local;
//	int number_of_machines;	
//	
//
//} agent_machine_t;
//
//
//
//int machine__init(agent_machine_t* subagent);
//int machine__config(agent_machine_t* subagent, agent__machine__config_t* config);
//int machine__start(agent_machine_t* subagent);
//int machine__stop(agent_machine_t* subagent);
//int machine__exit(agent_machine_t* subagent);
//
//
//
//int agent__get_machine_alarm_status(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_connection_status(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_part_counter(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_production_status(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int agent__get_total_number_of_machines(agent_machine_t* subagent, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int agent__get_machine_id(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_type(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_name(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int agent__get_machine_part_program_name(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_facility(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_serial_number(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int agent__get_machine_active_status(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_networked_status(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_run_mode_status(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int agent__get_machine_department(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_manufacturer(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int delegate__get_model(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//
//int agent__connect_to_machine(machine_data_t* machine_local);
//int agent__read_machine_part_counter(machine_data_t* machine_local);
//
//
//
//int agent__get_machine_cycle_time(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//
//
//int agents__load_agents_configuration_data(agent_machine_t* machine);
//int machine__load_configuration_data(agent_machine_t* subagent);
//
//int agent__check_and_preprocess_input_data(agent_machine_t* machine, const char* calling_function_name, const char* config_2, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
//
//
//int delegate__private__read_alarm_status__simulated(agent_machine_t* subagent, int md);
//int delegate__private__read_production_status__simulated(agent_machine_t* subagent, int md);
//int delegate__private__read_connection_status__simulated(agent_machine_t* subagent, int md);
//
//int delegate__private__read_cycle_time__simulated(agent_machine_t* subagent, int md);
//int delegate__private__read_part_program_name__simulated(agent_machine_t* subagent, int md);
//
//
//void delegate__private__task__read_machines_data(agent_machine_t* subagent);
//void agent__private__task__simulate_machine(machine_data_t* machine_local);
//
//void agent__private__task__connection_manager(machine_data_t *machine_local);
//
//int agent__read_part_counter__real(agent_machine_t* subagent, int md);
//void* agent__thread(void* arg);
//int agent__check_machine_and_input_parameters(agent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
//int delegate__private__check_parameters_and_agent_status_2(agent_machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
//int agent__check_config(agent__machine__config_t* config);



//typedef struct
//{
//
//	int md;
//	//agent__machine__config_t config;
//	//agent__machine_config_2_t config_2;
//
//	char name_and_index[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t name_and_index_len;
//
//
//	utils__printf_t pf;
//
//
//	utils__sdb_t sdb;
//	char sdb_buffer[I4_AGENCY__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[I4_AGENCY__CONFIG__SDB_FIELDS_MAX];
//
//	size_t part_counter;
//	int part_counter_valid;
//	//size_t part_counter_simulated;
//	//int part_counter_simulated_valid;
//	char part_counter_utf_8[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t part_counter_utf_8_len;
//
//	double cycle_time;
//	int cycle_time_valid;
//	double cycle_time_simulated;
//	int cycle_time_simulated_valid;
//	char cycle_time_utf_8[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t cycle_time_utf_8_len;
//
//	char part_program_name[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	int part_program_name_valid;
//	char part_program_name_simulated[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	int part_program_name_simulated_valid;
//	char part_program_name_utf_8[I4_AGENCY__CONFIG__BUFFER_SIZE];
//	size_t part_program_name_utf_8_len;
//
//	int connection_status;
//	int connection_status_valid;
//	int connection_status_simulated;
//	int connection_status_valid_simulated;
//
//	int production_status;
//	int production_status_valid;
//	int production_status_simulated;
//	int production_status_valid_simulated;
//
//	int alarm_status;
//	int alarm_status_valid;
//	int alarm_status_simulated;
//	int alarm_status_valid_simulated;
//
//	time_t no_response_time;
//	int no_response_flag;
//	int connection_monitor_task_state;
//	size_t reconnection_attempts;
//
//
//	agent__thread_t thread;
//	pthread_t thread_id;
//	pthread_mutex_t thread_mutex;
//	size_t thread_sleep_time_milliseconds;
//	size_t thread_ticks_milliseconds;
//	int thread_started;
//	int thread_stop_request;
//
//	int probability_of_success_of_events_in_simulation_mode;
//	/*UA_Client* client;*/
//
//} machine_data_22_t;
#endif

