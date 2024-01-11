#ifndef SUBAGENT_H
#define SUBAGENT_H
 

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>


#include <pthread.h>


#include <utils__platform.h>
#include <utils__libc.h>
#include <utils__printf.h>
#include <utils__sdb.h>



#define SUBAGENT__MACHINE_ID                                               0
#define SUBAGENT__MACHINE_NAME                                             1





#define SUBAGENT__CONFIG__MAX_PATH_SIZE                                    1024
#define SUBAGENT__CONFIG__SDB_FIELDS_MAX                                   64
#define SUBAGENT__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define SUBAGENT__CONFIG__BUFFER_SIZE                                      SUBAGENT__CONFIG__MAX_PATH_SIZE
#define SUBAGENT__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS                   5
#define SUBAGENT__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE                    60
#define SUBAGENT__CONFIG__TOKENS_MAX                                       32

#define SUBAGENT__PROBABILITY_OF_SUCCESS_OF_EVENTS_IN_SIMULATION_MODE      95
#define SUBAGENT__PART_COUNTER_INITIAL_VALUE_IN_SIMULATION_MODE           100
#define SUBAGENT__AVERAGE_CYCLE_TIME_IN_SIMULATION_MODE                  30.0


#define SUBAGENT__TYPE_1                                                   1



#define SUBAGENT__FILE_CONFIG_MODE                                 0
#define SUBAGENT__BUFFER_CONFIG_MODE                               1
#define SUBAGENT__UNESCAPE_SEQUENCE                                "!s"
#define SUBAGENT__UNESCAPE_SEQUENCE_LEN                            2
#define SUBAGENT__UNESCAPE_REPLACEMENT_CHAR                        ';'
#define SUBAGENT__FIELDS_SEPARATORS                                {";"}
#define SUBAGENT__FIELDS_SEPARATORS_MAX                            1
#define SUBAGENT__CHARACTER_TO_TRIM                                ' '



typedef int (*subagent__read_machine_data_t) (int md);
typedef int (*subagent__connect_to_machine_t) (int md);
typedef int (*subagent__disconnect_from_machine_t) (int md);
typedef void* (*subagent__thread_t) (void* arg);



typedef struct
{
	int do_filtering;
	char prefix[SUBAGENT__CONFIG__BUFFER_SIZE];
	char suffix[SUBAGENT__CONFIG__BUFFER_SIZE];
	size_t prefix_len;
	size_t suffix_len;

} subagent__settings__part_program_name_filter_t;



typedef struct
{

	/*
	 * MACHINE ID
	 */
	int id;


	/*
	 * MACHINE NAME
	 */
	char name[SUBAGENT__CONFIG__BUFFER_SIZE];


	/*
	 * MACHINE OPERATING MODE DATA
	 */
	int networked;
	int operating_mode;
	//int active;


	///*
	// * MACHINE PLATE DATA
	// */
	//char manufacturer[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char model[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char serial_number[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char manufacture_year[SUBAGENT__CONFIG__BUFFER_SIZE];


	///*
	// * MACHINE GEOLOCATION DATA
	// */
	//char organization[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char facility[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char department[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char department_location_coordinates[SUBAGENT__CONFIG__BUFFER_SIZE];
	


	///*
	// * MACHINE TECHNICAL DATA
	// */
	//char cnc[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char hmi[SUBAGENT__CONFIG__BUFFER_SIZE];


	///*
	// * MACHINE FEEDER DATA
	// */
	//char feeder_manufacturer[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char feeder_model[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char feeder_serial_number[SUBAGENT__CONFIG__BUFFER_SIZE];
	//char feeder_manufacture_year[SUBAGENT__CONFIG__BUFFER_SIZE];


	/*
	 * MACHINE OPC SERVER DATA
	 */
	char opc_server_ipv4_address[SUBAGENT__CONFIG__BUFFER_SIZE];
	char opc_server_ipv4_port[SUBAGENT__CONFIG__BUFFER_SIZE];
	char opc_server_user_name[SUBAGENT__CONFIG__BUFFER_SIZE];
	char opc_server_password[SUBAGENT__CONFIG__BUFFER_SIZE];
	char opc_server_private_key_file[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	char opc_server_certificate_file[SUBAGENT__CONFIG__MAX_PATH_SIZE];


	

	/*
	 * MACHINE OPC SERVER NODES DATA
	 */
	char opc_server_part_counter_node_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	char opc_server_cycle_time_node_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	char opc_server_part_program_name_node_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	

	size_t thread_sleep_time;                                                   /* seconds */
    //int probability_of_success_of_events_in_simulation_mode;                    /* percentage: integer value from 0 to 100 */
	//int average_cycle_time_in_simulation_mode;                                  /* seconds */
	//int part_counter_initial_value_in_simulation_mode;
	char part_program_name_in_simulation_mode[SUBAGENT__CONFIG__BUFFER_SIZE];

} subagent__machine__config_2_t;



typedef struct
{

	int md;
	subagent__connect_to_machine_t connect_to_machine;
	subagent__disconnect_from_machine_t disconnect_from_machine;
	subagent__read_machine_data_t read_part_counter;
	subagent__read_machine_data_t read_cycle_time;
	subagent__read_machine_data_t read_part_program_name;

} subagent__machine__config_t;


typedef struct
{
	subagent__machine__config_t config;
	subagent__machine__config_2_t config_2;
	int configured;
	int started;

	utils__printf_t pf;

	subagent__thread_t thread;
	pthread_t thread_id;
	pthread_mutex_t thread_mutex;
	size_t thread_sleep_time;
	size_t thread_ticks;
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
	char part_counter[SUBAGENT__CONFIG__BUFFER_SIZE];
	int part_counter_simulation_mode_first_time;

	int cycle_time_valid;
	double cycle_time_native;
	char cycle_time[SUBAGENT__CONFIG__BUFFER_SIZE];

	int part_program_name_valid;
	char part_program_name[SUBAGENT__CONFIG__BUFFER_SIZE];


} subagent_machine_t;




typedef struct
{
	int agent_type;
	const char* file_name;
	char* buffer;
	size_t buffer_len;

	const char* agent_section_name;
	const char* machine_section_name;

} subagent__config_t;



typedef struct
{

	//int enable_printf;
	//int enable_log_file;

	char log_file_name[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	//size_t max_log_file_lines_per_minute;
	//int enable_table_layout_output;
	//int enable_agent_name_on_output;

	//char agent_name[SUBAGENT__CONFIG__BUFFER_SIZE];

	size_t thread_sleep_time;
	//int probability_of_success_of_events_in_simulation_mode;

} subagent__config_2_t;


typedef struct
{
	subagent__config_t config;
	subagent__config_2_t config_2;

	
    subagent_machine_t* machine;
	int machine_counter;

	utils__sdb_t sdb;
	char sdb_buffer[SUBAGENT__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];

	utils__printf_t pf;


} subagent_t;



int subagent__load_agent_configuration_data(subagent_t* subagent);
int subagent__load_machines_configuration_data(subagent_t* subagent, int* number_of_machines);

int subagent__get_machine_id(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_manufacturer(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_model(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_serial_number(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_manufacture_year(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);

int subagent__get_machine_organization(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);

int subagent__get_machine_alarm_status(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_connection_status(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_part_counter(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_production_status(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_part_program_name(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_facility(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_active_status(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_networked_status(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_run_mode_status(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_department(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_name(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_model(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_cycle_time(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);









int subagent__check_machine_and_input_parameters(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
int subagent__check_input_parameters_and_preproccess_input_data(subagent_t* subagent, const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
int subagent__check_and_preprocess_input_data(const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
int subagent__check_config(subagent__machine__config_t* config);


void subagent__suspend_thread(subagent_machine_t* machine, size_t milliseconds);
void* subagent__thread(void* arg);




int subagent__connect_to_machine(subagent_machine_t* machine);
int subagent__read_machine_part_counter(subagent_machine_t* machine);
int subagent__read_machine_cycle_time(subagent_machine_t* machine);
int subagent__read_machine_part_program_name(subagent_machine_t* machine);







//
//typedef int (*subagent__read_machine_data_t) (int);
//typedef int (*subagent__connect_to_machine_t) (int);
//typedef void* (*subagent__thread_t) (void* arg);
//
//
//
//typedef struct
//{
//	int do_filtering;
//	char prefix[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char suffix[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t prefix_len;
//	size_t suffix_len;
//
//} subagent__settings__part_program_name_filter_t;
//
//
//delegate__do_action_t connect_to_machine;
//
//
//
//typedef struct
//{
//	subagent__connect_to_machine_t connect_to_machine;
//
//	subagent__read_machine_data_t read_part_counter;
//
//} subagent__machine__config_t;
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
//	char type[SUBAGENT__CONFIG__BUFFER_SIZE];
//
//	/*
//	 * MACHINE PLATE DATA
//	 */
//	char manufacturer[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char model[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char serial_number[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char manufacture_year[SUBAGENT__CONFIG__BUFFER_SIZE];
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
//	char organization[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char facility[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char department[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char name[SUBAGENT__CONFIG__BUFFER_SIZE];
//
//	/*
//	 * MACHINE TECHNICAL DATA
//	 */
//	char cnc[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char hmi[SUBAGENT__CONFIG__BUFFER_SIZE];
//
//
//	/*
//	 * MACHINE FEEDER DATA
//	 */
//	char feeder_manufacturer[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char feeder_model[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char feeder_serial_number[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char feeder_manufacture_year[SUBAGENT__CONFIG__BUFFER_SIZE];
//
//
//
//
//
//	size_t connection_timeout_seconds;
//	size_t reconnection_attempts_time_interval_seconds;
//	size_t max_reconnection_attempts;
//	size_t no_response_timeout_seconds;
//	char part_program_name_in_simulation_mode[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t part_counter_initial_value_in_simulation_mode;
//	double average_cycle_time_in_simulation_mode_seconds;
//
//
//	char opc_ipv4_address[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char opc_ipv4_port[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char opc_user_name[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char opc_password[SUBAGENT__CONFIG__BUFFER_SIZE];
//	char opc_certificate_file[SUBAGENT__CONFIG__MAX_PATH_SIZE];
//	char opc_private_key_file[SUBAGENT__CONFIG__MAX_PATH_SIZE];
//
//
//	char opc_part_counter_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
//	char opc_cycle_time_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
//	char opc_part_program_name_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
//
//	subagent__settings__part_program_name_filter_t part_program_name_filter;
//
//} subagent__machine_config_2_t;
//
//
//
//typedef struct
//{
//
//	int md;
//	subagent__machine__config_t config;
//	subagent__machine_config_2_t config_2;
//
//	char name_and_index[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t name_and_index_len;
//
//
//	utils__printf_t pf;
//
//
//	utils__sdb_t sdb;
//	char sdb_buffer[SUBAGENT__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//
//	size_t part_counter;
//	int part_counter_valid;
//	size_t part_counter_simulated;
//	int part_counter_simulated_valid;
//	char part_counter_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t part_counter_utf_8_len;
//
//	double cycle_time;
//	int cycle_time_valid;
//	double cycle_time_simulated;
//	int cycle_time_simulated_valid;
//	char cycle_time_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t cycle_time_utf_8_len;
//
//	char part_program_name[SUBAGENT__CONFIG__BUFFER_SIZE];
//	int part_program_name_valid;
//	char part_program_name_simulated[SUBAGENT__CONFIG__BUFFER_SIZE];
//	int part_program_name_simulated_valid;
//	char part_program_name_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE];
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
//	subagent__thread_t thread;
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
//	char log_file_name[SUBAGENT__CONFIG__MAX_PATH_SIZE];
//	size_t max_log_file_lines_per_minute;
//	int enable_table_layout_output;
//	int enable_agent_name_on_output;
//	char agent_name[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t thread_sleep_time;
//	int probability_of_success_of_events_in_simulation_mode;
//
//} subagent__machine__config_2_t;
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
//	char agent_name_and_version[SUBAGENT__CONFIG__BUFFER_SIZE];
//	const char* agent_default_config_file_name;
//	const char* agent_section_name;
//	const char* agent_machines_section_name;
//
//	subagent__connect_to_machine_t connect_to_machine;
//	subagent__connect_to_machine_t disconnect_from_machine;
//
//	delegate__read_data_t read_connection_status;
//	delegate__read_data_t read_production_status;
//	delegate__read_data_t read_alarm_status;
//
//	subagent__read_machine_data_t read_part_counter;
//	subagent__read_machine_data_t read_cycle_time;
//	subagent__read_machine_data_t read_part_program_name;
//
//} subagent__machine__config_t;
//
//
//typedef struct
//{
//	subagent__machine__config_t config;
//	subagent__machine__config_2_t config_2;
//	int configured;
//	int started;
//
//	utils__printf_t pf;
//
//	utils__sdb_t sdb;
//	char sdb_buffer[SUBAGENT__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	
//
//	machine_data_t* machine_local;
//	int number_of_machines;	
//	
//
//} subagent_machine_t;
//
//
//
//int machine__init(subagent_machine_t* subagent);
//int machine__config(subagent_machine_t* subagent, subagent__machine__config_t* config);
//int machine__start(subagent_machine_t* subagent);
//int machine__stop(subagent_machine_t* subagent);
//int machine__exit(subagent_machine_t* subagent);
//
//
//
//int subagent__get_machine_alarm_status(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_connection_status(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__get_machine_part_counter(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_production_status(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int subagent__get_total_number_of_machines(subagent_machine_t* subagent, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int subagent__get_machine_id(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_type(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_name(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int subagent__get_machine_part_program_name(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_facility(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_serial_number(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int subagent__get_machine_active_status(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_networked_status(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_run_mode_status(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//int subagent__get_machine_department(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int subagent__get_machine_manufacturer(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int delegate__get_model(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//
//int subagent__connect_to_machine(machine_data_t* machine_local);
//int subagent__read_machine_part_counter(machine_data_t* machine_local);
//
//
//
//int subagent__get_machine_cycle_time(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//
//
//
//int agents__load_agents_configuration_data(subagent_machine_t* machine);
//int machine__load_configuration_data(subagent_machine_t* subagent);
//
//int subagent__check_and_preprocess_input_data(subagent_machine_t* machine, const char* calling_function_name, const char* config_2, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);
//
//
//int delegate__private__read_alarm_status__simulated(subagent_machine_t* subagent, int md);
//int delegate__private__read_production_status__simulated(subagent_machine_t* subagent, int md);
//int delegate__private__read_connection_status__simulated(subagent_machine_t* subagent, int md);
//
//int delegate__private__read_cycle_time__simulated(subagent_machine_t* subagent, int md);
//int delegate__private__read_part_program_name__simulated(subagent_machine_t* subagent, int md);
//
//
//void delegate__private__task__read_machines_data(subagent_machine_t* subagent);
//void subagent__private__task__simulate_machine(machine_data_t* machine_local);
//
//void subagent__private__task__connection_manager(machine_data_t *machine_local);
//
//int subagent__read_part_counter__real(subagent_machine_t* subagent, int md);
//void* subagent__thread(void* arg);
//int subagent__check_machine_and_input_parameters(subagent_machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
//int delegate__private__check_parameters_and_agent_status_2(subagent_machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);
//int subagent__check_config(subagent__machine__config_t* config);



//typedef struct
//{
//
//	int md;
//	//subagent__machine__config_t config;
//	//subagent__machine_config_2_t config_2;
//
//	char name_and_index[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t name_and_index_len;
//
//
//	utils__printf_t pf;
//
//
//	utils__sdb_t sdb;
//	char sdb_buffer[SUBAGENT__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[SUBAGENT__CONFIG__SDB_FIELDS_MAX];
//
//	size_t part_counter;
//	int part_counter_valid;
//	//size_t part_counter_simulated;
//	//int part_counter_simulated_valid;
//	char part_counter_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t part_counter_utf_8_len;
//
//	double cycle_time;
//	int cycle_time_valid;
//	double cycle_time_simulated;
//	int cycle_time_simulated_valid;
//	char cycle_time_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE];
//	size_t cycle_time_utf_8_len;
//
//	char part_program_name[SUBAGENT__CONFIG__BUFFER_SIZE];
//	int part_program_name_valid;
//	char part_program_name_simulated[SUBAGENT__CONFIG__BUFFER_SIZE];
//	int part_program_name_simulated_valid;
//	char part_program_name_utf_8[SUBAGENT__CONFIG__BUFFER_SIZE];
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
//	subagent__thread_t thread;
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

