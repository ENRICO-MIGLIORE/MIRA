#ifndef SUBAGENT_H
#define SUBAGENT_H
 

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


#define SUBAGENT__CONFIG__MAX_PATH_SIZE                                    1024
#define SUBAGENT__CONFIG__SDB_FIELDS_MAX                                   64
#define SUBAGENT__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define SUBAGENT__CONFIG__BUFFER_SIZE_256                                  256
#define SUBAGENT__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS                   5
#define SUBAGENT__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE                    60
#define SUBAGENT__CONFIG__TOKENS_MAX                                       32



#define SUBAGENT__TYPE_1                                                   1



#define MACHINE__FILE_CONFIG_MODE                                 0
#define MACHINE__BUFFER_CONFIG_MODE                               1
#define MACHINE__UNESCAPE_SEQUENCE                                "!s"
#define MACHINE__UNESCAPE_SEQUENCE_LEN                            2
#define MACHINE__UNESCAPE_REPLACEMENT_CHAR                        ';'
#define MACHINE__FIELDS_SEPARATORS                                {";"}
#define MACHINE__FIELDS_SEPARATORS_MAX                            1
#define MACHINE__CHARACTER_TO_TRIM                                ' '



typedef int (*machine__read_data_t) (int);
typedef int (*machine__do_action_t) (int);
typedef void* (*machine__thread_t) (void* arg);



typedef struct
{
	int do_filtering;
	char prefix[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char suffix[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	size_t prefix_len;
	size_t suffix_len;

} subagent__settings__part_program_name_filter_t;


//delegate__do_action_t connect_to_machine;



typedef struct
{
	machine__do_action_t connect_to_machine;

	machine__read_data_t read_part_counter;

} subagent__machine_config_t;


typedef struct
{

	/*
	 * MACHINE ID
	 */
	int id;

	/*
	 * MACHINE TYPE
	 */
	char type[SUBAGENT__CONFIG__BUFFER_SIZE_256];

	/*
	 * MACHINE PLATE DATA
	 */
	char manufacturer[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char model[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char serial_number[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char manufacture_year[SUBAGENT__CONFIG__BUFFER_SIZE_256];

	/*
	 * MACHINE FIELD DATA
	 */	
	int networked;
	int simulated;
	int operating;

	/*
	 * MACHINE LOCATION DATA
	 */	
	char organization[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char facility[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char department[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char name[SUBAGENT__CONFIG__BUFFER_SIZE_256];

	/*
	 * MACHINE TECHNICAL DATA
	 */
	char cnc[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char hmi[SUBAGENT__CONFIG__BUFFER_SIZE_256];


	/*
	 * MACHINE FEEDER DATA
	 */
	char feeder_manufacturer[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char feeder_model[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char feeder_serial_number[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char feeder_manufacture_year[SUBAGENT__CONFIG__BUFFER_SIZE_256];





	size_t connection_timeout_seconds;
	size_t reconnection_attempts_time_interval_seconds;
	size_t max_reconnection_attempts;
	size_t no_response_timeout_seconds;
	char part_program_name_in_simulation_mode[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_initial_value_in_simulation_mode;
	double average_cycle_time_in_simulation_mode_seconds;


	char opc_ipv4_address[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char opc_ipv4_port[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char opc_user_name[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char opc_password[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	char opc_certificate_file[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	char opc_private_key_file[SUBAGENT__CONFIG__MAX_PATH_SIZE];


	char opc_part_counter_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	char opc_cycle_time_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	char opc_part_program_name_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];

	subagent__settings__part_program_name_filter_t part_program_name_filter;

} subagent__machine_config_2_t;



typedef struct
{

	int md;
	subagent__machine_config_t config;
	subagent__machine_config_2_t config_2;

	char name_and_index[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;


	utils__printf_t pf;


	utils__sdb_t sdb;
	char sdb_buffer[SUBAGENT__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];

	size_t part_counter;
	int part_counter_valid;
	//size_t part_counter_simulated;
	//int part_counter_simulated_valid;
	char part_counter_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;

	double cycle_time;
	int cycle_time_valid;
	double cycle_time_simulated;
	int cycle_time_simulated_valid;
	char cycle_time_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;

	char part_program_name[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	int part_program_name_valid;
	char part_program_name_simulated[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	int part_program_name_simulated_valid;
	char part_program_name_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE_256];
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


	machine__thread_t thread;
	pthread_t thread_id;
	pthread_mutex_t thread_mutex;
	size_t thread_sleep_time_milliseconds;
	size_t thread_ticks_milliseconds;
	int thread_started;
	int thread_stop_request;

	int probability_of_success_of_events_in_simulation_mode_in_percentage;
	/*UA_Client* client;*/

} machine_data_t;



typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int enable_table_layout_output;
	int enable_agent_name_on_output;
	char agent_name[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	size_t main_thread_sleep_time_in_seconds;
	int probability_of_success_of_events_in_simulation_mode_in_percentage;

} machine_config_2_t;



typedef struct
{
	int agent_type;
	int mode;
	const char* file_name;
	char* buffer;
	size_t buffer_len;

	const char* agent_name;
	const char* agent_version;
	char agent_name_and_version[SUBAGENT__CONFIG__BUFFER_SIZE_256];
	const char* agent_default_config_file_name;
	const char* agent_section_name;
	const char* agent_machines_section_name;

	machine__do_action_t connect_to_machine;
	machine__do_action_t disconnect_from_machine;

	//delegate__read_data_t read_connection_status;
	//delegate__read_data_t read_production_status;
	//delegate__read_data_t read_alarm_status;

	machine__read_data_t read_part_counter;
	machine__read_data_t read_cycle_time;
	machine__read_data_t read_part_program_name;

} machine_config_t;


typedef struct
{
	machine_config_t config;
	machine_config_2_t config_2;
	int configured;
	int started;

	//utils__printf_t pf;

	//utils__sdb_t sdb;
	//char sdb_buffer[SUBAGENT__CONFIG__SDB_BUFFER_SIZE];
	//char* sdb_name[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	//char* sdb_value[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	//int sdb_encoding[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	//size_t sdb_name_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	//size_t sdb_value_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	

	machine_data_t* machine_local;
	int machine_count;	
	

} machine_t;



int machine__init(machine_t* agent);
int machine__config(machine_t* agent, machine_config_t* config);
int machine__start(machine_t* agent);
int machine__stop(machine_t* agent);
int machine__exit(machine_t* agent);



int machine__get_alarm_status(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_connection_status(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_part_counter(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_production_status(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int delegate__get_machine_count(machine_t* agent, char* buffer, size_t buffer_size, size_t* buffer_len);

int machine__get_id(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_type(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int machine__get_name(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int delegate__get_part_program_name(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_facility(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_serial_number(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int delegate__get_operating_status(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_networked_status(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_simulated_status(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int delegate__get_department(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_manufacturer(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int delegate__get_model(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);


int subagent__connect_to_machine(machine_data_t* machine_local);
int machine__read_part_counter(machine_data_t* machine_local);



int delegate__get_cycle_time(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);



int agent__load_configuration_data(machine_t* machine);
int machine__load_configuration_data(machine_t* agent);

int machine__preprocess_input_data(machine_t* machine, const char* calling_function_name, const char* config_2, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);


int delegate__private__read_alarm_status__simulated(machine_t* agent, int md);
int delegate__private__read_production_status__simulated(machine_t* agent, int md);
int delegate__private__read_connection_status__simulated(machine_t* agent, int md);

int delegate__private__read_cycle_time__simulated(machine_t* agent, int md);
int delegate__private__read_part_program_name__simulated(machine_t* agent, int md);


void delegate__private__task__read_machines_data(machine_t* agent);
void subagent__private__task__simulate_machine(machine_data_t* machine_local);

void subagent__private__task__connection_manager(machine_data_t *machine_local);

int subagent__read_part_counter__real(machine_t* agent, int md);
void* machine__thread(void* arg);
int machine__check_parameters_and_agent_status(machine_t* agent, int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
int delegate__private__check_parameters_and_agent_status_2(machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
int delegate__private__check_config(machine_config_t* config);

#endif

