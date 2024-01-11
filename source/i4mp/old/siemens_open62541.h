#ifndef SIEMENS_OPEN62541_H
#define SIEMENS_OPEN62541_H


#include <stddef.h>


#define SIEMENS_OPEN62541__BUFFER_SIZE          256


/*
 * framework: init, config, start
 */
int okuma_tcp__init (int argc, char *argv[]);
int okuma_tcp__config (void);
int okuma_tcp__start (void);


/*
 * get the total number of machines
 */
int okuma_tcp__get_machine_count(char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * machine descriptor: md = 0, 1, ..., (machine_count - 1)
 */


/*
 * config data
 */
int okuma_tcp__get_connect_to_machine_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_simulation_mode_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_brand(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_model(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_sn(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_facility(int md, char* buffer, size_t buffer_size, size_t* buffer_len);

/*
 * live data
 */
int okuma_tcp__get_machine_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_tcp__get_machine_part_program_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * miscellaneous functions
 */
char* okuma_tcp__get_application_version(void);


#endif
