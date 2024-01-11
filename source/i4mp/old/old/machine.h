#ifndef MACHINE_H
#define MACHINE_H
 

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


#define MACHINE__CONFIG__MAX_PATH_SIZE                                    1024
#define MACHINE__CONFIG__SDB_FIELDS_MAX                                   64
#define MACHINE__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define MACHINE__CONFIG__BUFFER_SIZE_256                                  256
#define MACHINE__CONFIG__MAIN_THREAD_SLEEP_TIME_SECONDS                   5
#define MACHINE__CONFIG__MIN_LOG_FILE_LINES_PER_MINUTE                    60
#define MACHINE__CONFIG__TOKENS_MAX                                       32



#define MACHINE__TYPE_1                                                   1



#define MACHINE__FILE_CONFIG_MODE                                 0
#define MACHINE__BUFFER_CONFIG_MODE                               1
#define MACHINE__UNESCAPE_SEQUENCE                                "!s"
#define MACHINE__UNESCAPE_SEQUENCE_LEN                            2
#define MACHINE__UNESCAPE_REPLACEMENT_CHAR                        ';'
#define MACHINE__FIELDS_SEPARATORS                                {";"}
#define MACHINE__FIELDS_SEPARATORS_MAX                            1
#define MACHINE__CHARACTER_TO_TRIM                                ' '



typedef int (*subagent__machine__read_data_t) (int);
typedef int (*subagent__machine__do_action_t) (int);
typedef void* (*subagent__machine__thread_t) (void* arg);



typedef struct
{
	int do_filtering;
	char prefix[MACHINE__CONFIG__BUFFER_SIZE_256];
	char suffix[MACHINE__CONFIG__BUFFER_SIZE_256];
	size_t prefix_len;
	size_t suffix_len;

} subagent__settings__part_program_name_filter_t;




//typedef struct
//{
//
//	int md;
//	//subagent__machine_config_t config;
//	//subagent__machine_config_2_t config_2;
//
//	char name_and_index[MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t name_and_index_len;
//
//
//	utils__printf_t pf;
//
//
//	utils__sdb_t sdb;
//	char sdb_buffer[MACHINE__CONFIG__SDB_BUFFER_SIZE];
//	char* sdb_name[MACHINE__CONFIG__SDB_FIELDS_MAX];
//	char* sdb_value[MACHINE__CONFIG__SDB_FIELDS_MAX];
//	int sdb_encoding[MACHINE__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_name_len[MACHINE__CONFIG__SDB_FIELDS_MAX];
//	size_t sdb_value_len[MACHINE__CONFIG__SDB_FIELDS_MAX];
//
//	size_t part_counter;
//	int part_counter_valid;
//	//size_t part_counter_simulated;
//	//int part_counter_simulated_valid;
//	char part_counter_utf_8[MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t part_counter_utf_8_len;
//
//	double cycle_time;
//	int cycle_time_valid;
//	double cycle_time_simulated;
//	int cycle_time_simulated_valid;
//	char cycle_time_utf_8[MACHINE__CONFIG__BUFFER_SIZE_256];
//	size_t cycle_time_utf_8_len;
//
//	char part_program_name[MACHINE__CONFIG__BUFFER_SIZE_256];
//	int part_program_name_valid;
//	char part_program_name_simulated[MACHINE__CONFIG__BUFFER_SIZE_256];
//	int part_program_name_simulated_valid;
//	char part_program_name_utf_8[MACHINE__CONFIG__BUFFER_SIZE_256];
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
//	subagent__machine__thread_t thread;
//	pthread_t thread_id;
//	pthread_mutex_t thread_mutex;
//	size_t thread_sleep_time_milliseconds;
//	size_t thread_ticks_milliseconds;
//	int thread_started;
//	int thread_stop_request;
//
//	int probability_of_success_of_events_in_simulation_mode_in_percentage;
//	/*UA_Client* client;*/
//
//} machine_data_22_t;



typedef struct
{


	/*
     * MACHINE ID
     */
	int id;

	/*
	 * MACHINE TYPE
	 */
	char type[MACHINE__CONFIG__BUFFER_SIZE_256];

	/*
	 * MACHINE PLATE DATA
	 */
	char manufacturer[MACHINE__CONFIG__BUFFER_SIZE_256];
	char model[MACHINE__CONFIG__BUFFER_SIZE_256];
	char serial_number[MACHINE__CONFIG__BUFFER_SIZE_256];
	char manufacture_year[MACHINE__CONFIG__BUFFER_SIZE_256];


	/*
	 * MACHINE FIELD DATA
	 */
	int networked;
	int simulated;
	int operating;


	/*
	 * MACHINE LOCATION DATA
	 */
	char organization[MACHINE__CONFIG__BUFFER_SIZE_256];
	char facility[MACHINE__CONFIG__BUFFER_SIZE_256];
	char department[MACHINE__CONFIG__BUFFER_SIZE_256];
	char name[MACHINE__CONFIG__BUFFER_SIZE_256];

	/*
	 * MACHINE TECHNICAL DATA
	 */
	char cnc[MACHINE__CONFIG__BUFFER_SIZE_256];
	char hmi[MACHINE__CONFIG__BUFFER_SIZE_256];


	/*
	 * MACHINE FEEDER DATA
	 */
	char feeder_manufacturer[MACHINE__CONFIG__BUFFER_SIZE_256];
	char feeder_model[MACHINE__CONFIG__BUFFER_SIZE_256];
	char feeder_serial_number[MACHINE__CONFIG__BUFFER_SIZE_256];
	char feeder_manufacture_year[MACHINE__CONFIG__BUFFER_SIZE_256];



	
	size_t main_thread_sleep_time_in_seconds;
	int probability_of_success_of_events_in_simulation_mode_in_percentage;
		

} machine_config_2_t;



typedef struct
{

	int md;
	subagent__machine__do_action_t connect_to_machine;
	subagent__machine__do_action_t disconnect_from_machine;
	subagent__machine__read_data_t read_part_counter;
	subagent__machine__read_data_t read_cycle_time;
	subagent__machine__read_data_t read_part_program_name;

} subagent__machine_config_t;


typedef struct
{
	subagent__machine_config_t config;
	machine_config_2_t config_2;
	int configured;
	int started;

	utils__printf_t pf;

	subagent__machine__thread_t thread;
	pthread_t thread_id;
	pthread_mutex_t thread_mutex;
	size_t thread_sleep_time_milliseconds;
	size_t thread_ticks_milliseconds;
	int thread_started;
	int thread_stop_request;

	
	int connection_status_valid;
	int connection_status;
	
	int part_counter_valid;
	size_t part_counter_native;	
	char part_counter[MACHINE__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_len;

	int cycle_time_valid;
	double cycle_time_native;
	char cycle_time[MACHINE__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_len;

} subagent__machine_t;




int subagent__get_machine_alarm_status(subagent__machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_connection_status(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_part_counter(subagent__machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_production_status(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_total_number_of_machines(subagent__machine_t* subagent, char* buffer, size_t buffer_size, size_t* buffer_len);

int subagent__get_machine_id(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_type(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int subagent__get_machine_part_program_name(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_facility(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_serial_number(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int subagent__get_machine_operating_status(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_networked_status(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_simulated_status(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int subagent__get_machine_department(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_manufacturer(subagent__machine_t* subagent, int md, char* buffer, size_t buffer_size, size_t* buffer_len);


int subagent__get_machine_name(subagent__machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__get_machine_model(subagent__machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);


int subagent__connect_to_machine(subagent__machine_t* machine);
int subagent__read_machine_part_counter(subagent__machine_t* machine);


int subagent__get_machine_cycle_time(subagent__machine_t* machine, char* buffer, size_t buffer_size, size_t* buffer_len);
int subagent__check_machine_parameters(subagent__machine_t* machine, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);


int subagent__preprocess_input_data(const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count);

void* subagent__thread(void* arg);
int subagent__check_config(subagent__machine_config_t* config);



int subagent__get_machine_data(subagent__machine_t* machine, char* data, size_t* data_len, int data_valid, char* buffer, size_t buffer_size, size_t* buffer_len);


#endif

