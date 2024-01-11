#ifndef MIRA_H
#define MIRA_H
 

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define I4MP__AGENT__FILE_CONFIG_MODE       0
#define I4MP__AGENT__BUFFER_CONFIG_MODE     1


typedef int (*mira__agent__init_t) (void);
typedef int (*mira__agent__config_t) (void* config);
typedef int (*mira__agent__start_t) (void);
typedef int (*mira__agent__get_data_t) (char* buffer, size_t buffer_size, size_t* buffer_len);
typedef int (*mira__agent__get_machine_data_t) (int md, char* buffer, size_t buffer_size, size_t* buffer_len);



typedef struct
{
	
	const char* name;	
	
	int type;
	int config_mode;
	const char* config_file_name;
	char* config_buffer;
	size_t config_buffer_len;

	size_t buffer_size;

	mira__agent__init_t init;
	mira__agent__config_t config;
	mira__agent__start_t start;

	mira__agent__get_data_t get_total_number_of_machines;

	mira__agent__get_machine_data_t get_connection_status;
	mira__agent__get_machine_data_t get_production_status;
	mira__agent__get_machine_data_t get_alarm_status;

	mira__agent__get_machine_data_t get_networked_status;
	mira__agent__get_machine_data_t get_operating_status;
	mira__agent__get_machine_data_t get_simulated_status;

	mira__agent__get_machine_data_t get_machine_id;
	mira__agent__get_machine_data_t get_machine_type;
	mira__agent__get_machine_data_t get_machine_manufacturer;
	mira__agent__get_machine_data_t get_machine_model;
	mira__agent__get_machine_data_t get_serial_number;
	mira__agent__get_machine_data_t get_machine_name;
	mira__agent__get_machine_data_t get_machine_facility;
	mira__agent__get_machine_data_t get_machine_department;
	mira__agent__get_machine_data_t get_machine_cnc_name;

	mira__agent__get_machine_data_t get_machine_part_counter;
	mira__agent__get_machine_data_t get_machine_cycle_time;
	mira__agent__get_machine_data_t get_machine_part_program_name;

} mira__agent_t;


typedef struct
{

	mira__agent_t* agent;
	size_t agents_max;
	
	int enable_printf;
	int enable_log_file;
	const char* log_file_name;
	int enable_table_layout_output;
	
} mira__config_t;




int mira__init(void);
int mira__config(mira__config_t* config);
int mira__start(void);



/*
 * get the total number of machines
 */
int mira__get_total_number_of_machines(char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * machine descriptor: md = 0, 1, ..., (machine_count - 1)
 */


 /*
  * static data
  */
int mira__get_machine_networked_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_simulated_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_type(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_manufacturer(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_model(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_serial_number(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_facility(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_department(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_cnc_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * live data
 */
int mira__get_machine_operating_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_alarm_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_part_program_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


/*
 * application name and version
 */
const char* mira__get_application_name(void);
const char* mira__get_application_version(void);
const char* mira__get_application_name_and_version(void);

/*
 * miscellaneous functions
 */
void mira__sleep_milliseconds(size_t milliseconds);
int mira__print_agents(void);


#endif
