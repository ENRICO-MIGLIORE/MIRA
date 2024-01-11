#ifndef OKUMA_MT_H
#define OKUMA_MT_H


#include <stddef.h>


#define OKUMA_MT__BUFFER_SIZE          256


/*
 * framework: init, config, start
 */
int okuma_mt__init (int argc, char *argv[]);
int okuma_mt__config (void);
int okuma_mt__start (void);


/*
 * get the total number of machines
 */
int okuma_mt__get_machine_count(char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * machine descriptor: md = 0, 1, ..., (machine_count - 1)
 */


/*
 * config data
 */
int okuma_mt__get_online_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_simulation_mode_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_manufacturer(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_model(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_serial_number(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_facility(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_cnc_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);

/*
 * live data
 */
int okuma_mt__get_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_operating_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_part_program_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * miscellaneous functions
 */
char* okuma_mt__get_application_version(void);


#endif
