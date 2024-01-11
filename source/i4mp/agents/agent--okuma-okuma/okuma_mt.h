#ifndef OKUMA_MT_H
#define OKUMA_MT_H


#include <stddef.h>


#define OKUMA_MT__BUFFER_SIZE          256


typedef struct
{
	char* file_name;
	char* buffer;
	size_t buffer_len;
	int mode;

} okuma_mt__config_t;


int okuma_mt__init (void);
int okuma_mt__config(okuma_mt__config_t* config);
int okuma_mt__start (void);


/*
 * get the total number of machines
 */
int okuma_mt__get_machine_count(char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * config data - machine descriptor md range: 0, 1, ..., (machine_count - 1)
 */
int okuma_mt__get_networked_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_simulated_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_type(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_manufacturer(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_model(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_serial_number(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_facility(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_department(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_cnc_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * live data
 */
int okuma_mt__get_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_alarm_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_operating_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int okuma_mt__get_part_program_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * miscellaneous functions
 */
char* okuma_mt__get_application_version(void);


#endif
