#ifndef MACHINE__OKUMA_OKUMA_H
#define MACHINE__OKUMA_OKUMA_H


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

} machine__config_t;


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

} machine__config_2_t;










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


extern agency_t* agency;






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



} machine__okuma_okuma_t;


#endif

