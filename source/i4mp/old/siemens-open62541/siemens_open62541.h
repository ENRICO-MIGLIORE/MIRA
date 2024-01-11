#ifndef SIEMENS_OPEN62541_H
#define SIEMENS_OPEN62541_H


#include <stddef.h>


#define SIEMENS_OPEN62541__BUFFER_SIZE          256


typedef struct
{
	char* file_name;
	char* buffer;
	size_t buffer_len;
	int mode;

} siemens_open62541_config_t;


int siemens_open62541__init(void);
int siemens_open62541__config(siemens_open62541_config_t* config);
int siemens_open62541__start(void);


/*
 * get the total number of machines
 */
int siemens_open62541__get_machine_count(char* buffer, size_t buffer_size, size_t* buffer_len);

int siemens_open62541__get_buffer_size(char* buffer, size_t buffer_size, size_t* buffer_len);

/*
 * machine descriptor: md = 0, 1, ..., (machine_count - 1)
 */


/*
 * config data
 */
int siemens_open62541__get_online_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_simulation_mode_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_manufacturer(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_model(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_serial_number(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_facility(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_cnc_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);



/*
 * live data
 */
int siemens_open62541__get_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_operating_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int siemens_open62541__get_part_program_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * miscellaneous functions
 */
char* siemens_open62541__get_application_version(void);


#endif
