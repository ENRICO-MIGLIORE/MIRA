#ifndef I4MP_H
#define I4MP_H


#include <stddef.h>


/*
 * I4MP__BUFFER_SIZE must be grater than 256 used by the agents
 * 
 * clients must allocate a buffer of size: I4MP__BUFFER_SIZE
 */
#define I4MP__BUFFER_SIZE  1024


typedef struct
{
	char* file_name;
	char* buffer;
	size_t buffer_len;
	int mode;

} i4mp__config_t;


int i4mp__init(void);
int i4mp__config(i4mp__config_t* config);
int i4mp__start(void);



/*
 * get the total number of machines
 */
int i4mp__get_machine_count(char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * machine descriptor: md = 0, 1, ..., (machine_count - 1)
 */


 /*
  * config data
  */
int i4mp__get_networked_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_simulated_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_operating_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_type(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_manufacturer(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_model(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_serial_number(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_facility(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_department(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_cnc_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * live data
 */
int i4mp__get_alarm_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_part_program_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * miscellaneous functions
 */
char* i4mp__get_application_version(void);
void i4mp__sleep_milliseconds(size_t milliseconds);
int i4mp__print_agents(void);


#endif
