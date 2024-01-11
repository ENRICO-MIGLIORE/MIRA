#ifndef MIRA_H
#define MIRA_H
 

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int (*mira__agent__init_t) (void);
typedef int (*mira__agent__config_t) (void* config);
typedef int (*mira__agent__start_t) (void);

typedef int (*mira__agent__get_agent_name_t) (char* buffer, size_t buffer_size, size_t* buffer_len);
typedef int (*mira__agent__get_agent_buffer_size_t) (size_t* buffer_size);
typedef int (*mira__agent__get_agent_total_number_of_machines_t) (int* number_of_machines);

typedef int (*mira__agent__get_machine_data_t) (int md, char* buffer, size_t buffer_size, size_t* buffer_len);

typedef int (*mira__agent__get_machine_data_2_t) (int md, char* buffer, size_t buffer_size, size_t* buffer_len, int data);



typedef struct
{


	const char* config_file_name;
	char* config_buffer;
	size_t config_buffer_len;

	mira__agent__init_t init;
	mira__agent__config_t config;
	mira__agent__start_t start;

	mira__agent__get_agent_buffer_size_t get_agent_buffer_size;
	mira__agent__get_agent_name_t get_agent_name;
	mira__agent__get_agent_total_number_of_machines_t get_agent_total_number_of_machines;


	//mira__agent__get_machine_data_2_t get_machine_data;

	mira__agent__get_machine_data_t get_machine_id;	
	mira__agent__get_machine_data_t get_machine_agent_name;	
	mira__agent__get_machine_data_t get_machine_name;



	mira__agent__get_machine_data_t get_machine_connection_status;
	mira__agent__get_machine_data_t get_machine_production_status;
	mira__agent__get_machine_data_t get_machine_alarm_status;

	mira__agent__get_machine_data_t get_machine_networked_status;
	mira__agent__get_machine_data_t get_machine_run_mode_status;
	
	

	mira__agent__get_machine_data_t get_machine_part_counter;
	mira__agent__get_machine_data_t get_machine_cycle_time;
	mira__agent__get_machine_data_t get_machine_part_program_name;

} mira__agent_t;


typedef struct
{

	mira__agent_t* i4_agency;
	size_t agents_max;
	
	int enable_printf;
	int enable_log_file;
	const char* log_file_name;
	int enable_table_layout_output;
	
} mira__config_t;



/*
 * framework functions
 */
int mira__init(void);
int mira__config (mira__config_t* config);
int mira__start(void);



/*
 * application functions
 */
int mira__get_application_name(char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_buffer_size(size_t* buffer_size);
int mira__get_number_of_machines(int* number_of_machines);
int mira__print_agents(void);
void mira__sleep (size_t milliseconds);





 /*
  * functions to read machines' configuration data - machine descriptor: md = 0, 1, ..., (number_of_machines - 1)
  */
int mira__get_machine_agent_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int mira__get_machine_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);

int mira__get_machine_networked_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_run_mode_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);





int mira__get_machine_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);




/*
 * functions to read machines' live data - machine descriptor: md = 0, 1, ..., (number_of_machines - 1)
 */

int mira__get_machine_alarm_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_connection_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_production_status(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int mira__get_machine_part_program_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);


#endif
