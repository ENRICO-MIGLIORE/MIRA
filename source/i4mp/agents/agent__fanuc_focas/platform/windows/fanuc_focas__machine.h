#ifndef FANUC_FOCAS__MACHINE_H
#define FANUC_FOCAS__MACHINE_H


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stddef.h>

#include <pthread.h>

#include <utils__platform.h>
#include <utils__libc.h>
#include <utils__printf.h>
#include <utils__sdb.h>

#include "agency_config.h"


typedef int (*agent__connect_to_machine_t) (void* arg);
typedef int (*agent__disconnect_from_machine_t) (int md);
typedef int (*agent__read_machine_data_t) (void* arg);
typedef int (*agent__start_t) (void* arg);
typedef int (*agent__stop_t) (void* arg);

typedef void* (*agent__thread_t) (void* arg);


typedef struct
{

	char agent_name[AGENCY__CONFIG__BUFFER_SIZE];
	char agent_machine_section_name[AGENCY__CONFIG__BUFFER_SIZE];

	agent__connect_to_machine_t connect_to_machine;
	agent__read_machine_data_t read_machine_part_counter;
	agent__read_machine_data_t read_machine_cycle_time;
	agent__read_machine_data_t read_machine_part_program_name;
	agent__read_machine_data_t read_machine_data_stream;


	//agent__disconnect_from_machine_t disconnect_from_machine;	

} fanuc_focas__machine__config_t;


typedef struct
{


	/*
	 * ID
	 */
	int id;


	/*
	 * NAME
	 */
	char name[AGENCY__CONFIG__BUFFER_SIZE];


	/*
	 * OPERATING MODES
	 */
	int networked;
	int run;
	int simulation;


	/*
	 * PRINTF AND LOG
	 */
	int enable_printf;
	int enable_log_file;
	char log_file_name[AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;



	/*
	 * OKUMA-OKUMA TCP SERVER
	 */
	char okuma_tcp_server_ipv4_address[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_server_ipv4_port[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_receiver_buffer_size[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_send_buffer_size[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_http_request_string[AGENCY__CONFIG__BUFFER_SIZE];
	int okuma_tcp_data_stream_valid;
	char* okuma_tcp_receive_buffer;
	char* okuma_tcp_send_buffer;


	size_t thread_sleep_time;                                                   /* seconds */
	//int probability_of_success_of_events_in_simulation_mode;                    /* percentage: integer value from 0 to 100 */
	//int average_cycle_time_in_simulation_mode;                                  /* seconds */
	//int part_counter_initial_value_in_simulation_mode;
	int probability_of_success_of_events_in_simulation_mode;
	char part_program_name_in_simulation_mode[AGENCY__CONFIG__BUFFER_SIZE];

} machine__config__okuma_okuma_t;


typedef struct
{


	/*
	 * ID
	 */
	int id;


	/*
	 * NAME
	 */
	char name[AGENCY__CONFIG__BUFFER_SIZE];


	/*
	 * OPERATING MODES
	 */
	int networked;
	int run;
	int simulation;


	/*
	 * PRINTF AND LOG
	 */
	int enable_printf;
	int enable_log_file;
	char log_file_name[AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;


	/*
	 * OPC-UA SERVER AND CLIENT
	 */
	char opc_ua_server_ipv4_address[AGENCY__CONFIG__BUFFER_SIZE];
	char opc_ua_server_ipv4_port[AGENCY__CONFIG__BUFFER_SIZE];
	char opc_ua_server_user_name[AGENCY__CONFIG__BUFFER_SIZE];
	char opc_ua_server_password[AGENCY__CONFIG__BUFFER_SIZE];
	char opc_ua_client_private_key_file[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_client_certificate_file[AGENCY__CONFIG__MAX_PATH_SIZE];

	/*
	 * OPC-UA SERVER NODES
	 */
	unsigned short opc_ua_server_node_id;
	char opc_ua_server_part_counter_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_server_cycle_time_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_server_part_program_name_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_server_machine_status_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_server_alarm_status_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];

	/*
	 * FANUC-TCP SERVER
	 */
	char fanuc_tcp_server_ipv4_address[AGENCY__CONFIG__BUFFER_SIZE];
	char fanuc_tcp_server_ipv4_port[AGENCY__CONFIG__BUFFER_SIZE];

	/*
	 * OKUMA-TCP SERVER
	 */
	char okuma_tcp_server_ipv4_address[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_server_ipv4_port[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_receiver_buffer_size[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_send_buffer_size[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_http_request_string[AGENCY__CONFIG__BUFFER_SIZE];
	int okuma_tcp_data_stream_valid;
	char* okuma_tcp_receive_buffer;
	char* okuma_tcp_send_buffer;

	machine__config__okuma_okuma_t okuma_okuma;


	size_t thread_sleep_time;                                                   /* seconds */
	//int probability_of_success_of_events_in_simulation_mode;                    /* percentage: integer value from 0 to 100 */
	//int average_cycle_time_in_simulation_mode;                                  /* seconds */
	//int part_counter_initial_value_in_simulation_mode;
	int probability_of_success_of_events_in_simulation_mode;
	char part_program_name_in_simulation_mode[AGENCY__CONFIG__BUFFER_SIZE];

} machine__config_3_t;



typedef struct
{
	

	/*
	 * ID
	 */
	int id;


	/*
	 * NAME
	 */
	char name[AGENCY__CONFIG__BUFFER_SIZE];


	/*
	 * OPERATING MODES
	 */
	int networked;
	int run;
	int simulation;


	/*
	 * PRINTF AND LOG
	 */
	int enable_printf;
	int enable_log_file;
	char log_file_name[AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;


	/*
	 * OPC-UA SERVER AND CLIENT
	 */
	char opc_ua_server_ipv4_address[AGENCY__CONFIG__BUFFER_SIZE];
	char opc_ua_server_ipv4_port[AGENCY__CONFIG__BUFFER_SIZE];
	char opc_ua_server_user_name[AGENCY__CONFIG__BUFFER_SIZE];
	char opc_ua_server_password[AGENCY__CONFIG__BUFFER_SIZE];
	char opc_ua_client_private_key_file[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_client_certificate_file[AGENCY__CONFIG__MAX_PATH_SIZE];

	/*
	 * OPC-UA SERVER NODES
	 */
	unsigned short opc_ua_server_node_id;
	char opc_ua_server_part_counter_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_server_cycle_time_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_server_part_program_name_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_server_machine_status_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	char opc_ua_server_alarm_status_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];

	/*
	 * FANUC-TCP SERVER
	 */
	char fanuc_tcp_server_ipv4_address[AGENCY__CONFIG__BUFFER_SIZE];
	char fanuc_tcp_server_ipv4_port[AGENCY__CONFIG__BUFFER_SIZE];

	/*
	 * OKUMA-TCP SERVER
	 */
	char okuma_tcp_server_ipv4_address[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_server_ipv4_port[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_receiver_buffer_size[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_send_buffer_size[AGENCY__CONFIG__BUFFER_SIZE];
	char okuma_tcp_http_request_string[AGENCY__CONFIG__BUFFER_SIZE];
	int okuma_tcp_data_stream_valid;
	char* okuma_tcp_receive_buffer;
	char* okuma_tcp_send_buffer;


	size_t thread_sleep_time;                                                   /* seconds */
	//int probability_of_success_of_events_in_simulation_mode;                    /* percentage: integer value from 0 to 100 */
	//int average_cycle_time_in_simulation_mode;                                  /* seconds */
	//int part_counter_initial_value_in_simulation_mode;
	int probability_of_success_of_events_in_simulation_mode;
	char part_program_name_in_simulation_mode[AGENCY__CONFIG__BUFFER_SIZE];

} fanuc_focas__machine__config_2_t;





typedef struct
{

	machine__config_t config; 
	machine__config_2_t config_2;

	utils__printf_t pf;

	agent__thread_t thread;
	pthread_t thread_id;
	pthread_mutex_t thread_mutex;
	size_t thread_sleep_time;
	size_t thread_ticks;
	int thread_started;
	int thread_stop_request;

	int connection_status_valid;
	int connection_status;
	size_t connection_attempts;

	time_t connection_timestamp;
	time_t connection_timestamp_previous;

	//int alarm_status_valid;
	//int alarm_status;

	//int production_status_valid;
	//int production_status;

	int part_counter_valid;
	int part_counter_native;
	char part_counter[AGENCY__CONFIG__BUFFER_SIZE];
	int part_counter_len;
	int part_counter_simulation_mode_first_time;

	int cycle_time_valid;
	double cycle_time_native;
	char cycle_time[AGENCY__CONFIG__BUFFER_SIZE];

	int part_program_name_valid;
	char part_program_name[AGENCY__CONFIG__BUFFER_SIZE];

	int machine_status_run_valid;
	int machine_status_run_native;
	char machine_status_run[AGENCY__CONFIG__BUFFER_SIZE];

	int machine_status_alarm_valid;
	int machine_status_alarm_native;
	char machine_status_alarm[AGENCY__CONFIG__BUFFER_SIZE];


	int task_state;

	int configured;
	int started;

	


	void* ext_void_pointer;
	int ext_void_pointer_valid;
	unsigned short ext_unsigned_short;//fanucfoca handle
	int ext_unsigned_short_valid;

	

} fanuc_focas__machine_t;




typedef struct
{
	int do_filtering;
	char prefix[AGENCY__CONFIG__BUFFER_SIZE];
	char suffix[AGENCY__CONFIG__BUFFER_SIZE];
	size_t prefix_len;
	size_t suffix_len;

} agent__settings__part_program_name_filter_t;



typedef struct
{	

	const char* name;
	const char* machine_section_name;

	int configured;
	int started;

	machine_t* machine;
	int number_of_machines;
	int machine_index;

} agent_t;




typedef struct
{

	const char* file_name;
	char* buffer;
	size_t buffer_len;

} agency__config_t;


typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int probability_of_success_of_events_in_simulation_mode;
	size_t thread_sleep_time;

	//int enable_table_layout_output;
    //int enable_agent_name_on_output;
    //char agent_name[AGENCY__CONFIG__BUFFER_SIZE];

} agency__config_2_t;


typedef struct
{

	const char* name;
	const char* machine_section_name;

	int configured;
	int started;

	machine_t* machine;
	int number_of_machines;
	int machine_index;

} agent__fanuc_focas_t;


typedef struct
{
	agency__config_t config;
	agency__config_2_t config_2;
	
	utils__sdb_t sdb;
	char sdb_buffer[AGENCY__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[AGENCY__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[AGENCY__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[AGENCY__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[AGENCY__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[AGENCY__CONFIG__SDB_FIELDS_MAX];

	utils__printf_t pf;

	const char* name;
	const char* section_name;
	
	int configured;
	int started;

	agent_t* agent;
	int number_of_agents;

} agency_t;


extern agency_t *agency;






int agency__private__load_agency_configuration_data(void);
int agency__private__load_machines_configuration_data(void);
int agency__private__check_and_preprocess_input_data(const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);


int agency__private__convert_machine_descriptor_to_agent_descriptor(int md, int* ad, int* ag_md);
int agency__private__check_input_parameters_and_preproccess_input_data(void* p, const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
int agency__private__check_machine_and_input_parameters(machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
int agency__private__get_machine_data(int data_id, int md, char* buffer, size_t buffer_size, size_t* buffer_len);


int agency__private__connect_to_machine(machine_t* machine);
int agency__private__read_data_stream(machine_t* machine);
int agency__private__read_machine_part_counter(machine_t* machine);
int agency__private__read_machine_cycle_time(machine_t* machine);
int agency__private__read_machine_part_program_name(machine_t* machine);

void* agency__private__thread(void* arg);
void agency__private__suspend_thread(machine_t* machine);




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
//	char prefix[AGENCY__CONFIG__BUFFER_SIZE];
//	char suffix[AGENCY__CONFIG__BUFFER_SIZE];
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
//} machine__config_t;
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
//	char type[AGENCY__CONFIG__BUFFER_SIZE];
//
//	/*
//	 * MACHINE PLATE DATA
//	 */
//	char manufacturer[AGENCY__CONFIG__BUFFER_SIZE];
//	char model[AGENCY__CONFIG__BUFFER_SIZE];
//	char serial_number[AGENCY__CONFIG__BUFFER_SIZE];
//	char manufacture_year[AGENCY__CONFIG__BUFFER_SIZE];
//
//	/*
//	 * MACHINE FIELD DATA
//	 */	
//	int networked;
//	int operating_mode;
//	int active;
//
//	/*
//	 * MACHINE LOCATION DATA
//	 */	
//	char organization[AGENCY__CONFIG__BUFFER_SIZE];
//	char facility[AGENCY__CONFIG__BUFFER_SIZE];
//	char department[AGENCY__CONFIG__BUFFER_SIZE];
//	char name[AGENCY__CONFIG__BUFFER_SIZE];
//
//	/*
//	 * MACHINE TECHNICAL DATA
//	 */
//	char cnc[AGENCY__CONFIG__BUFFER_SIZE];
//	char hmi[AGENCY__CONFIG__BUFFER_SIZE];
//
//
//	/*
//	 * MACHINE FEEDER DATA
//	 */
//	char feeder_manufacturer[AGENCY__CONFIG__BUFFER_SIZE];
//	char feeder_model[AGENCY__CONFIG__BUFFER_SIZE];
//	char feeder_serial_number[AGENCY__CONFIG__BUFFER_SIZE];
//	char feeder_manufacture_year[AGENCY__CONFIG__BUFFER_SIZE];
//
//
//
//
//
//	size_t connection_timeout_seconds;
//	size_t reconnection_attempts_time_interval_seconds;
//	size_t max_reconnection_attempts;
//	size_t no_response_timeout_seconds;
//	char part_program_name_in_simulation_mode[AGENCY__CONFIG__BUFFER_SIZE];
//	size_t part_counter_initial_value_in_simulation_mode;
//	double average_cycle_time_in_simulation_mode_seconds;
//
//
//	char opc_ipv4_address[AGENCY__CONFIG__BUFFER_SIZE];
//	char opc_ipv4_port[AGENCY__CONFIG__BUFFER_SIZE];
//	char opc_user_name[AGENCY__CONFIG__BUFFER_SIZE];
//	char opc_password[AGENCY__CONFIG__BUFFER_SIZE];
//	char opc_certificate_file[AGENCY__CONFIG__MAX_PATH_SIZE];
//	char opc_private_key_file[AGENCY__CONFIG__MAX_PATH_SIZE];
//
//
//	char opc_part_counter_path[AGENCY__CONFIG__MAX_PATH_SIZE];
//	char opc_cycle_time_path[AGENCY__CONFIG__MAX_PATH_SIZE];
//	char opc_part_program_name_path[AGENCY__CONFIG__MAX_PATH_SIZE];
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
//	machine__config_t config;
//	agent__machine_config_2_t config_2;
//
//	char name_and_index[AGENCY__CONFIG__BUFFER_SIZE];
//	size_t name_and_index_len;
//
//
//	utils__printf_t pf;
//
//
//	utils__sdb_t sdb;
//	char sdb_buffer[AGENCY__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[AGENCY__CONFIG__SDB_FIELDS_MAX];
//
//	size_t part_counter;
//	int part_counter_valid;
//	size_t part_counter_simulated;
//	int part_counter_simulated_valid;
//	char part_counter_utf_8[AGENCY__CONFIG__BUFFER_SIZE];
//	size_t part_counter_utf_8_len;
//
//	double cycle_time;
//	int cycle_time_valid;
//	double cycle_time_simulated;
//	int cycle_time_simulated_valid;
//	char cycle_time_utf_8[AGENCY__CONFIG__BUFFER_SIZE];
//	size_t cycle_time_utf_8_len;
//
//	char part_program_name[AGENCY__CONFIG__BUFFER_SIZE];
//	int part_program_name_valid;
//	char part_program_name_simulated[AGENCY__CONFIG__BUFFER_SIZE];
//	int part_program_name_simulated_valid;
//	char part_program_name_utf_8[AGENCY__CONFIG__BUFFER_SIZE];
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
//	size_t thread_sleep_time;
//	size_t thread_ticks;
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
//	char log_file_name[AGENCY__CONFIG__MAX_PATH_SIZE];
//	size_t max_log_file_lines_per_minute;
//	int enable_table_layout_output;
//	int enable_agent_name_on_output;
//	char agent_name[AGENCY__CONFIG__BUFFER_SIZE];
//	size_t thread_sleep_time;
//	int probability_of_success_of_events_in_simulation_mode;
//
//} machine__config_2_t;
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
//	char agent_name_and_version[AGENCY__CONFIG__BUFFER_SIZE];
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
//} machine__config_t;
//
//
//typedef struct
//{
//	machine__config_t config;
//	machine__config_2_t config_2;
//	int configured;
//	int started;
//
//	utils__printf_t pf;
//
//	utils__sdb_t sdb;
//	char sdb_buffer[AGENCY__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	
//
//	machine_data_t* machine_local;
//	int number_of_machines;	
//	
//
//} agent_machine_t;
//
//




//typedef struct
//{
//
//	int md;
//	//machine__config_t config;
//	//agent__machine_config_2_t config_2;
//
//	char name_and_index[AGENCY__CONFIG__BUFFER_SIZE];
//	size_t name_and_index_len;
//
//
//	utils__printf_t pf;
//
//
//	utils__sdb_t sdb;
//	char sdb_buffer[AGENCY__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[AGENCY__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[AGENCY__CONFIG__SDB_FIELDS_MAX];
//
//	size_t part_counter;
//	int part_counter_valid;
//	//size_t part_counter_simulated;
//	//int part_counter_simulated_valid;
//	char part_counter_utf_8[AGENCY__CONFIG__BUFFER_SIZE];
//	size_t part_counter_utf_8_len;
//
//	double cycle_time;
//	int cycle_time_valid;
//	double cycle_time_simulated;
//	int cycle_time_simulated_valid;
//	char cycle_time_utf_8[AGENCY__CONFIG__BUFFER_SIZE];
//	size_t cycle_time_utf_8_len;
//
//	char part_program_name[AGENCY__CONFIG__BUFFER_SIZE];
//	int part_program_name_valid;
//	char part_program_name_simulated[AGENCY__CONFIG__BUFFER_SIZE];
//	int part_program_name_simulated_valid;
//	char part_program_name_utf_8[AGENCY__CONFIG__BUFFER_SIZE];
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
//	size_t thread_sleep_time;
//	size_t thread_ticks;
//	int thread_started;
//	int thread_stop_request;
//
//	int probability_of_success_of_events_in_simulation_mode;
//	/*UA_Client* client;*/
//
//} machine_data_22_t;
#endif

