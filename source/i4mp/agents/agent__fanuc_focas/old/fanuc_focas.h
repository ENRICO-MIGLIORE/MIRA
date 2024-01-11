#ifndef FANUC_FOCAS_H
#define FANUC_FOCAS_H


#include <stddef.h>


#define FANUC_FOCAS__BUFFER_SIZE          256


typedef struct
{
	char* file_name;
	char* buffer;
	size_t buffer_len;
	int mode;

} fanuc_focas__config_t;


int fanuc_focas__init (void);
int fanuc_focas__config(fanuc_focas__config_t* config);
int fanuc_focas__start (void);


/*
 * get the total number of machines
 */
int fanuc_focas__get_machine_count(char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * config data - machine descriptor md range: 0, 1, ..., (machine_count - 1)
 */
int fanuc_focas__get_networked_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_simulated_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_type(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_manufacturer(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_model(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_serial_number(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_facility(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_department(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_cnc_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * live data
 */
int fanuc_focas__get_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_alarm_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_operating_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int fanuc_focas__get_part_program_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * miscellaneous functions
 */
char* fanuc_focas__get_application_version(void);


#endif
