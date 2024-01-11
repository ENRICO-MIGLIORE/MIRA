#ifndef AGENT_H
#define AGENT_H
 
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

#define AGENT__FILE_CONFIG_MODE       0
#define AGENT__BUFFER_CONFIG_MODE     1


#define DELEGATE__CONFIG__MAX_PATH_SIZE                                    1024
#define DELEGATE__CONFIG__SDB_FIELDS_MAX                                   128
#define DELEGATE__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define DELEGATE__CONFIG__BUFFER_SIZE_256                                  256

#define AGENT__CONFIG__UNESCAPE_SEQUENCE                                  "\\;"
#define AGENT__CONFIG__UNESCAPE_SEQUENCE_LEN                              2
#define AGENT__CONFIG__UNESCAPE_REPLACEMENT_CHAR                          ';'
#define AGENT__CONFIG__FIELDS_SEPARATORS                                  {";", " ", "\t"}
#define AGENT__CONFIG__FIELDS_SEPARATORS_COUNT                            3
#define AGENT__CONFIG__TOKENS_MAX                                         16


#define AGENT__CONFIG__THREAD_SLEEP_TIME_SECONDS                        5


typedef int (*delegate__read_data_t) (int);
typedef int (*delegate__do_action_t) (int);
typedef void* (*delegate__thread_t) (void* arg);
//typedef int (*agent__read_part_counter__real_t) (agent_t* agent, int md);


typedef struct
{
	int do_filtering;
	char prefix[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char suffix[DELEGATE__CONFIG__BUFFER_SIZE_256];
	size_t prefix_len;
	size_t suffix_len;

} agent__settings__part_program_name_filter_t;


typedef struct
{

	int id;
	int operating;
	int networked;
	int simulated;
	int cnc;

	size_t connection_timeout_seconds;
	size_t reconnection_attempts_time_interval_seconds;
	size_t max_reconnection_attempts;
	size_t no_response_timeout_seconds;
	char part_program_name_in_simulation_mode[DELEGATE__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_initial_value_in_simulation_mode;
	double average_cycle_time_in_simulation_mode_seconds;


	char year[DELEGATE__CONFIG__BUFFER_SIZE_256];

	char type[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char manufacturer[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char model[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char serial_number[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char name[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char facility[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char department[DELEGATE__CONFIG__BUFFER_SIZE_256];

	char cnc_name[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char hmi[DELEGATE__CONFIG__BUFFER_SIZE_256];

	char weight[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char max_power_consumption[DELEGATE__CONFIG__BUFFER_SIZE_256];


	int feeder_present;
	char feeder_manufacturer[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char feeder_model[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char feeder_serial_number[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char feeder_year[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char feeder_hmi[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char feeder_weight[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char feeder_max_power_consumption[DELEGATE__CONFIG__BUFFER_SIZE_256];


	char opc_ipv4_address[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char opc_ipv4_port[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char opc_user_name[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char opc_password[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char opc_certificate_file[DELEGATE__CONFIG__MAX_PATH_SIZE];
	char opc_private_key_file[DELEGATE__CONFIG__MAX_PATH_SIZE];
	char opc_part_counter_path[DELEGATE__CONFIG__MAX_PATH_SIZE];
	char opc_cycle_time_path[DELEGATE__CONFIG__MAX_PATH_SIZE];
	char opc_part_program_name_path[DELEGATE__CONFIG__MAX_PATH_SIZE];

	agent__settings__part_program_name_filter_t part_program_name_filter;

} agent__private_machine_config_t;


typedef struct
{

	char name_and_index[DELEGATE__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;


	size_t part_counter;
	int part_counter_valid;
	size_t part_counter_simulated;
	int part_counter_simulated_valid;
	char part_counter_utf_8[DELEGATE__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;

	double cycle_time;
	int cycle_time_valid;
	double cycle_time_simulated;
	int cycle_time_simulated_valid;
	char cycle_time_utf_8[DELEGATE__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;

	char part_program_name[DELEGATE__CONFIG__BUFFER_SIZE_256];
	int part_program_name_valid;
	char part_program_name_simulated[DELEGATE__CONFIG__BUFFER_SIZE_256];
	int part_program_name_simulated_valid;
	char part_program_name_utf_8[DELEGATE__CONFIG__BUFFER_SIZE_256];
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


	delegate__do_action_t connect_to_machine;
	delegate__do_action_t disconnect_from_machine;

	delegate__read_data_t read_connection_status;
	delegate__read_data_t read_production_status;
	delegate__read_data_t read_alarm_status;

	delegate__read_data_t read_part_counter;
	delegate__read_data_t read_cycle_time;
	delegate__read_data_t read_part_program_name;



	agent__private_machine_config_t config;


	/*UA_Client* client;*/

} agent__machine_t;


typedef struct
{
	int mode;
	const char* config_file_name;
	char* buffer;
	size_t buffer_len;

}  delegate__secondary_config_t;


typedef struct
{
	delegate__secondary_config_t secondary;

	char* name;
	char* version;
	char name_and_version[DELEGATE__CONFIG__BUFFER_SIZE_256];
	char* section_name;
	char* default_config_file_name;
	char* machines_section_name;

	delegate__do_action_t connect_to_machine;
	delegate__do_action_t disconnect_from_machine;

	delegate__read_data_t read_connection_status;
	delegate__read_data_t read_production_status;
	delegate__read_data_t read_alarm_status;

	delegate__read_data_t read_part_counter;
	delegate__read_data_t read_cycle_time;
	delegate__read_data_t read_part_program_name;

} delegate_config_t;


typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[DELEGATE__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int enable_table_layout_output;
	int enable_agent_name_on_output;
	char agent_name[DELEGATE__CONFIG__BUFFER_SIZE_256];

	size_t main_thread_sleep_time_expressed_in_seconds;
	int enable_connection_monitor_task;
	double probability_of_success_of_events_in_simulation_mode;

} delegate_settings_t;


typedef struct
{
	

	utils__printf_t pf;

	utils__sdb_t sdb;
	char sdb_buffer[DELEGATE__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[DELEGATE__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[DELEGATE__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[DELEGATE__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[DELEGATE__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[DELEGATE__CONFIG__SDB_FIELDS_MAX];
	
	delegate__thread_t thread;
	pthread_t thread_id;
	pthread_mutex_t thread_mutex;
	size_t thread_sleep_time_milliseconds;
	size_t thread_ticks_milliseconds;
	int thread_started;

	agent__machine_t* machine;
	int machine_count;
	int machine_count_flag;

	int probability_of_success_of_events_in_simulation_mode;

	
	delegate_settings_t settings;

	delegate_config_t config;
	int configured;
	int started;

} delegate_t;



int delegate__init(delegate_t* agent);
int delegate__config(delegate_t* agent, delegate_config_t* config);
int delegate__start(delegate_t* agent);
int agent__stop(delegate_t* agent);
int agent__exit(delegate_t* agent);


int agent__get_alarm_status(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_connection_status(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_part_counter(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_production_status(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int delegate__get_machine_count(delegate_t* agent, char* buffer, size_t buffer_size, size_t* buffer_len);

int agent__get_id(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_type(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_name(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int agent__get_part_program_name(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_facility(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_serial_number(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int agent__get_operating_status(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_networked_status(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_simulated_status(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int agent__get_department(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_manufacturer(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__get_model(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);



int agent__get_cycle_time(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);


int delegate__private__load_agent_settings(delegate_t* agent);
int agent__private__load_machines_settings(delegate_t* agent);



int agent__private__read_alarm_status__simulated(delegate_t* agent, int md);
int agent__private__read_production_status__simulated(delegate_t* agent, int md);
int agent__private__read_connection_status__simulated(delegate_t* agent, int md);
int agent__private__read_part_counter__simulated(delegate_t* agent, int md);
int agent__private__read_cycle_time__simulated(delegate_t* agent, int md);
int agent__private__read_part_program_name__simulated(delegate_t* agent, int md);


void delegate__private__task__read_machines_data(delegate_t* agent);
void delegate__private__task__simulate_machines_data(delegate_t* agent);
void delegate__private__task__connection_monitor(delegate_t* agent);


int agent__read_part_counter__real(delegate_t* agent, int md);
void* delegate__private__thread(void* arg);
int delegate__private__check_parameters_and_agent_status(delegate_t* agent, int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
int delegate__private__check_config(void* config);

#endif

