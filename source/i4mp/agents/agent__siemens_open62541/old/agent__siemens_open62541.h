#ifndef AGENT__SIEMENS_OPEN62541_H
#define AGENT__SIEMENS_OPEN62541_H

 
#include <stddef.h>


typedef struct
{
	const char* file_name;         /* config file name */
	char* buffer;                  /* config buffer to be used in alternative to the of config file */
	size_t buffer_len;

} agent__siemens_open62541__config_t;



typedef struct
{
	const char* file_name;         /* config file name */
	char* buffer;                  /* config buffer to be used in alternative to the of config file */
	size_t buffer_len;

} agent____config_t;


/*
 * framework functions
 */
int agent__siemens_open62541__init (void);
int agent__siemens_open62541__config (agent__siemens_open62541__config_t* config);
int agent__siemens_open62541__start (void);


/*
 * application functions
 */
int agent__siemens_open62541__get_application_name(char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * i4_agency functions
 */
int agent__siemens_open62541__get_agent_name(char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_agent_number_of_machines (int* number_of_machines);
int agent__siemens_open62541__get_agent_buffer_size(size_t* buffer_size);


/*
 * machine functions - config data - machine descriptor md range: 0, 1, ..., (number_of_machines - 1)
 */
 //int agent__siemens_open62541__get_machine_data(int md, char* buffer, size_t buffer_size, size_t* buffer_len, int data);

int agent__siemens_open62541__get_machine_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_agent_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_networked_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_run_mode_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__siemens_open62541__get_machine_manufacturer(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__siemens_open62541__get_machine_model(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__siemens_open62541__get_machine_serial_number(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


//int agent__siemens_open62541__get_machine_organization(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__siemens_open62541__get_machine_facility(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__siemens_open62541__get_machine_department(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


//int agent__siemens_open62541__get_machine_cnc_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__siemens_open62541__get_machine_manufacture_year (int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__siemens_open62541__get_machine_part_program_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 *  machine functions - live data - machine descriptor md range: 0, 1, ..., (number_of_machines - 1)
 */
int agent__siemens_open62541__get_machine_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_alarm_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
//int agent__siemens_open62541__get_machine_active_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agent__siemens_open62541__get_machine_part_program_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);



/*
 * miscellaneous functions
 */





#endif
