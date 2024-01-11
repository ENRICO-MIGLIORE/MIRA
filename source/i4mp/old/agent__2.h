#ifndef AGENT__2_H
#define AGENT__2_H


#include <stddef.h>


#define AGENT__2__CONFIG__MAX_PATH_SIZE                                    1024
#define AGENT__2__CONFIG__SDB_FIELDS_MAX                                   128
#define AGENT__2__CONFIG__SDB_BUFFER_SIZE                                  (1024 * 128)
#define AGENT__2__CONFIG__BUFFER_SIZE_256                                  256


#define AGENT__2__MACHINE_DISCONNECTED                                     0
#define AGENT__2__MACHINE_CONNECTED                                        1



typedef int (*machine__read_t) (int);

//
//
//typedef struct
//{
//
//	
//
//	char opc_ipv4_address[AGENT__2__CONFIG__BUFFER_SIZE_256];
//	char opc_ipv4_port[AGENT__2__CONFIG__BUFFER_SIZE_256];
//	char opc_user_name[AGENT__2__CONFIG__BUFFER_SIZE_256];
//	char opc_password[AGENT__2__CONFIG__BUFFER_SIZE_256];
//	char opc_certificate_file[AGENT__2__CONFIG__MAX_PATH_SIZE];
//	char opc_private_key_file[AGENT__2__CONFIG__MAX_PATH_SIZE];
//	char opc_part_counter_path[AGENT__2__CONFIG__MAX_PATH_SIZE];
//	char opc_cycle_time_path[AGENT__2__CONFIG__MAX_PATH_SIZE];
//
//} siemens_open62541__machine_config_t;




typedef struct
{

	int id;
	int enable_communications;
	int enable_simulation_mode;

	size_t connection_timeout_seconds;
	size_t reconnection_attempts_time_interval_seconds;
	size_t max_reconnection_attempts;
	size_t no_response_timeout_seconds;
	char part_program_name_in_simulation_mode[AGENT__2__CONFIG__BUFFER_SIZE_256];

	char brand[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char model[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char sn[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char name[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char facility[AGENT__2__CONFIG__BUFFER_SIZE_256];

	*void ext;

} machine_config_t;



 
//typedef struct
//{
//	
//	machine_t machine;
//
//	//char name_and_index[AGENT__2__CONFIG__BUFFER_SIZE_256];
//	//size_t name_and_index_len;
//	//
//	//int connection_status;
//	//time_t no_response_time;
//	//int no_response_flag;
//	//int no_response_state;	
//	//size_t reconnection_attempts;
//
//	//size_t part_counter;
// //   char part_counter_utf_8[AGENT__2__CONFIG__BUFFER_SIZE_256];
//	//size_t part_counter_utf_8_len;
//	//int part_counter_valid;
//	//size_t part_counter_simulated;
//
//	//double cycle_time;
//	//char cycle_time_utf_8[AGENT__2__CONFIG__BUFFER_SIZE_256];
//	//size_t cycle_time_utf_8_len;
//	//int cycle_time_valid;
//	//double cycle_time_simulated;
//
//	//char part_program_name_utf_8[AGENT__2__CONFIG__BUFFER_SIZE_256];
//	//size_t part_program_name_utf_8_len;
//	//int part_program_name_valid;
//	//char part_program_name_utf_8_simulated[AGENT__2__CONFIG__BUFFER_SIZE_256];
//
//
//	//siemens_open62541__read_t allocate_resources;
//	//siemens_open62541__read_t connect_to_machine;
//	//siemens_open62541__read_t reconnect_to_machine;
//	//siemens_open62541__read_t read_part_counter;
//	//siemens_open62541__read_t read_cycle_time;
//	//siemens_open62541__read_t read_part_program_name;
//	
//
//	UA_Client* client;
//	int resources_allocated;
//
//	siemens_open62541__machine_config_t config;
//
//} siemens_open62541__machine_t;




typedef struct
{

	char name_and_index[AGENT__2__CONFIG__BUFFER_SIZE_256];
	size_t name_and_index_len;

	int connection_status;
	time_t no_response_time;
	int no_response_flag;
	int no_response_state;
	size_t reconnection_attempts;

	size_t part_counter;
	char part_counter_utf_8[AGENT__2__CONFIG__BUFFER_SIZE_256];
	size_t part_counter_utf_8_len;
	int part_counter_valid;
	size_t part_counter_simulated;

	double cycle_time;
	char cycle_time_utf_8[AGENT__2__CONFIG__BUFFER_SIZE_256];
	size_t cycle_time_utf_8_len;
	int cycle_time_valid;
	double cycle_time_simulated;

	char part_program_name_utf_8[AGENT__2__CONFIG__BUFFER_SIZE_256];
	size_t part_program_name_utf_8_len;
	int part_program_name_valid;
	char part_program_name_utf_8_simulated[AGENT__2__CONFIG__BUFFER_SIZE_256];


	machine__read_t allocate_resources;
	machine__read_t connect_to_machine;
	machine__read_t reconnect_to_machine;
	machine__read_t read_part_counter;
	machine__read_t read_cycle_time;
	machine__read_t read_part_program_name;


	//UA_Client* client;

	void* ext;
	int resources_allocated;

	machine_config_t config;

	//siemens_open62541__machine_config_t config;

} machine_t;



//typedef struct
//{
//
//	int enable_printf;
//	int enable_log_file;
//	char log_file_name[AGENT__2__CONFIG__MAX_PATH_SIZE];
//	size_t max_log_file_lines_per_minute;
//	int enable_square_brackets_output;
//	int enable_application_name_output;
//	char application_name[AGENT__2__CONFIG__BUFFER_SIZE_256];
//
//} siemens_open62541__config_t;


typedef struct
{

	int enable_printf;
	int enable_log_file;
	char log_file_name[AGENT__2__CONFIG__MAX_PATH_SIZE];
	size_t max_log_file_lines_per_minute;
	int enable_square_brackets_output;
	int enable_application_name_output;
	char application_name[AGENT__2__CONFIG__BUFFER_SIZE_256];

} machine_application__config_t;




//typedef struct
//{
//
//
//
//	siemens_open62541__machine_t* machine;	
//	int machine_count;
//	int machine_count_flag;
//
//	siemens_open62541__config_t config;
//	int configured;	
//	int started;
//
//	machine__manufacturer__t manufacturer;
//
//} siemens_open62541_t;



typedef struct
{

	utils__sdb_t sdb;
	char sdb_buffer[AGENT__2__CONFIG__SDB_BUFFER_SIZE];
	char* sdb_name[AGENT__2__CONFIG__SDB_FIELDS_MAX];
	char* sdb_value[AGENT__2__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[AGENT__2__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[AGENT__2__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[AGENT__2__CONFIG__SDB_FIELDS_MAX];

	utils__printf_t pf;

	char* application_name;
	char* application_version;
	char application_name_and_version[AGENT__2__CONFIG__BUFFER_SIZE_256];
	char* application_section_name;
	char* machines_section_name;
	char* default_configuration_file_name;
	char configuration_file_name[AGENT__2__CONFIG__MAX_PATH_SIZE];

	pthread_t pthread_id;
	pthread_mutex_t pthread_mutex;
	size_t pthread_sleep_time_seconds;
	int pthread_started;


	machine_t* machine;
	int machine_count;
	int machine_count_flag;

	machine_application__config_t config;
	int configured;
	int started;


} machine__manufacturer__t;


//extern siemens_open62541_t* so;


int agent__read_configuration_file(void);
int agent__read_configuration_file__application(void);
int agent__read_configuration_file__machines(void);
int agent__attach_stub_functions(void);
int agent__check_parameters_and_agent_status(int md, char* buffer, size_t buffer_size, size_t buffer_size_min, size_t* buffer_len);

void* agent__thread(void* arg);

//int siemens_open62541__disconnect_from_machine(int md);
//int siemens_open62541__disconnect_from_machine__real(int md);
//int siemens_open62541__disconnect_from_machine__simulated(int md);
//
//int siemens_open62541__reconnect_to_machine(int md);
//int siemens_open62541__reconnect_to_machine__real(int md);
//int siemens_open62541__reconnect_to_machine__simulated(int md);
//
//int siemens_open62541__is_machine_responding(int md);
//int siemens_open62541__is_machine_connected(int md);
//int siemens_open62541__is_machine_set_for_disconnection(int md);
//
//int siemens_open62541__set_machine_for_disconnection(int md);


int agent__allocate_machines_resources(int md);
int agent__allocate_machines_resources__real(int md);
int agent__allocate_machines_resources__simulated(int md);

int agent__connect_to_machine(int md);
int agent__connect_to_machine__real(int md);
int agent__connect_to_machine__simulated(int md);

int agent__read_machine_part_counter(int md);
int agent__read_part_counter__real(int md);
int agent__read_machine_part_counter__simulated(int md);

int agent__read_machine_cycle_time(int md);
int agent__read_machine_cycle_time__real(int md);
int agent__read_machine_cycle_time__simulated(int md);

int siemens_open62541__read_machine_part_program_name(int md);
int siemens_open62541__read_machine_part_program_name__real(int md);
int siemens_open62541__read_machine_part_program_name__simulated(int md);


#endif
