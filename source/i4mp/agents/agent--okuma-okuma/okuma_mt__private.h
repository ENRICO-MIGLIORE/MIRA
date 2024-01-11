#ifndef OKUMA_MT__PRIVATE_H
#define OKUMA_MT__PRIVATE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>

#include <pthread.h>

#include <utils__platform.h>
#include <utils__libc.h>
#include <utils__printf.h>
#include <utils__sdb.h>
#include <utils__xml.h>


#define OKUMA_MT__CONFIG__MAX_PATH_SIZE                                    1024
#define OKUMA_MT__CONFIG__SDB_FIELDS_MAX                                   128
#define OKUMA_MT__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define OKUMA_MT__CONFIG__BUFFER_SIZE_256                                  256


typedef int (*okuma_mt__read_data_t) (int);
typedef int (*okuma_mt__do_action_t) (int);

typedef struct
{
	size_t getaddrinfo_ok;
	size_t socket_ok;
	size_t connect_ok;
	size_t send_ok;
	size_t recv_ok;
	size_t closesocket_ok;

	size_t getaddrinfo_error;
	size_t socket_error;
	size_t connect_error;
	size_t send_error;
	size_t recv_error;
	size_t closesocket_error;

} okuma_mt__statistics_t;


typedef struct
{
	int do_estimation;
	int enable_printf;
	size_t time_to_first_estimation_seconds;
	size_t time_interval_for_estimations_seconds;
	size_t timeout_seconds;
	size_t minium_acceptable_cycle_time_seconds;

} okuma_mt__settings__cycle_time_from_part_counter_t;


typedef struct
{
	double cycle_time;
	char part_counter[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
		
	size_t ticks;
	size_t ticks_start;
	size_t ticks_stop;
	size_t ticks_timeout;
	
	int in_progress;
	int valid;	
	int first_time;
	int task_state;

} okuma_mt__cycle_time_from_part_counter_t;


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
	char part_program_name_in_simulation_mode[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_initial_value_in_simulation_mode;
	double average_cycle_time_in_simulation_mode_seconds;

	char type[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	char manufacturer[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	char model[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	char serial_number[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	char name[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	char facility[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	char department[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
		
	char cnc_name[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	
	char tcp_server_ipv4_address[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	char tcp_server_ipv4_port[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	size_t tcp_client_receive_buffer_size;
	char tcp_client_send_string[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	int tcp_client_enable_printf;

	okuma_mt__settings__cycle_time_from_part_counter_t cycle_time_fpc;
	

} okuma_mt__settings_t;



 
typedef struct
{
	
	//char name_and_index[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;	
	
	size_t part_counter;
	int part_counter_valid;
	size_t part_counter_simulated;
	int part_counter_simulated_valid;	
    char part_counter_utf_8[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;
	
	double cycle_time;
	int cycle_time_valid;
	double cycle_time_estimated;
	int cycle_time_estimated_valid;
	double cycle_time_simulated;
	int cycle_time_simulated_valid;
	char cycle_time_utf_8[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;
	  
	char part_program_name[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	int part_program_name_valid;
	char part_program_name_simulated[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	int part_program_name_simulated_valid;
	char part_program_name_utf_8[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	size_t part_program_name_utf_8_len;

	char alarm_utf_8[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	size_t alarm_utf_8_len;

	
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
	
	//time_t no_response_time;
	//int no_response_flag;	
	int connection_monitor_task_state;
	time_t connection_monitor_start_time;
	time_t connection_monitor_connection_status;
	

	okuma_mt__do_action_t allocate_machine_resources;
	okuma_mt__do_action_t connect_to_machine;
	okuma_mt__do_action_t disconnect_from_machine;
	okuma_mt__do_action_t reconnect_to_machine;

	okuma_mt__read_data_t read_part_counter;
	okuma_mt__read_data_t read_part_program_name;
	okuma_mt__read_data_t read_connection_status;
	okuma_mt__read_data_t read_production_status;
	okuma_mt__read_data_t read_alarm_status;
			

	int read_data_stream_task_state;
	int data_stream_valid;

	char* send_buffer;
	size_t send_buffer_len;

	char* receive_buffer;
	size_t receive_buffer_size;
	size_t receive_buffer_len;

	char* receive_buffer_2;
	size_t receive_buffer_size_2;
	size_t receive_buffer_len_2;

	okuma_mt__statistics_t statistics;
	okuma_mt__cycle_time_from_part_counter_t cycle_time_fpc;

	void* platform;

	okuma_mt__settings_t config;

} okuma_mt__machine_t;



typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[OKUMA_MT__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int enable_table_layout_output;
	int enable_application_name_on_output;
	char application_name[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	size_t thread_sleep_time_seconds;
	int enable_connection_monitor_task;
	double probability_of_success_of_events_in_simulation_mode_in_percentage;

} okuma_mt__application_settings_t;



typedef struct
{

	utils__sdb_t sdb;
	char sdb_buffer[OKUMA_MT__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[OKUMA_MT__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[OKUMA_MT__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[OKUMA_MT__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[OKUMA_MT__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[OKUMA_MT__CONFIG__SDB_FIELDS_MAX];	

	utils__printf_t pf;

	char* application_name;
	char* agent_version;
	char agent_name_and_version[OKUMA_MT__CONFIG__BUFFER_SIZE_256];
	char* agent_section_name;
	char* agent_default_configuration_file_name;	
	char agent_configuration_file_name[OKUMA_MT__CONFIG__MAX_PATH_SIZE];
	char* machines_section_name;
	
	pthread_t thread_id;
	pthread_mutex_t thread_mutex;	
	size_t thread_sleep_time_milliseconds;
	size_t thread_ticks_milliseconds;
	int thread_started;

	pthread_t thread_2_id;
	size_t thread_2_sleep_time_milliseconds;
	size_t thread_2_ticks_milliseconds;
	pthread_mutex_t thread_2_mutex;
	int thread_2_started;

	okuma_mt__machine_t* machine;	
	int machine_count;
	int machine_count_flag;

	int probability_of_success_of_events_in_simulation_mode_in_percentage;
	int config_mode;
	
	int configured;	
	int started;

	int cycle_time_estimation_from_part_counter_in_progress;

	okuma_mt__application_settings_t config;

} okuma_mt__application_t;


extern okuma_mt__application_t* om;


int okuma_mt__private__load_application_configuration(void);
int okuma_mt__private__load_machines_configuration(void);
int okuma_mt__private__check_parameters_and_agent_status(int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);


void* okuma_mt__private__thread(void* arg);
void* okuma_mt__private__thread_2(void* arg);

void okuma_mt__private__task__read_machines_data(void);
void okuma_mt__private__task__connection_monitor(void);
void okuma_mt__private__task__simulate_machines_data(void);
void okuma_mt__private__task__estimate_cycle_time_from_part_counter(void);


int okuma_mt__private__read_connection_status__real(int md);
int okuma_mt__private__read_connection_status__simulated(int md);

int okuma_mt__private__read_production_status__real(int md);
int okuma_mt__private__read_production_status__simulated(int md);

int okuma_mt__private__read_alarm_status__real(int md);
int okuma_mt__private__read_alarm_status__simulated(int md);

int okuma_mt__private__read_part_counter__real(int md);
int okuma_mt__private__read_part_counter__simulated(int md);

int okuma_mt__private__read_cycle_time__real(int md);
int okuma_mt__private__read_cycle_time__simulated(int md);

int okuma_mt__private__read_part_program_name__real(int md);
int okuma_mt__private__read_part_program_name__simulated(int md);

#endif
