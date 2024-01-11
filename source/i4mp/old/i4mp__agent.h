#ifndef I4MP__AGENT_H
#define I4MP__AGENT_H


#include <stddef.h>


typedef int (*i4mp__agent__init_t) (int argc, char* argv[]);
typedef int (*i4mp__agent__config_t) (void);
typedef int (*i4mp__agent__start_t) (void);


typedef int (*i4mp__agent__init_2_t) (void);
typedef int (*i4mp__agent__config_2_t) (void* config);
typedef int (*i4mp__agent__start_2_t) (void);


typedef int (*i4mp__agent__get_t) (int md, char* buffer, size_t buffer_size, size_t* buffer_len);
typedef int (*i4mp__agent__get_2_t) (char* buffer, size_t buffer_size, size_t* buffer_len);



typedef struct
{
	const char* name;
	size_t buffer_size;

	//i4mp__agent__init_t init;
	//i4mp__agent__config_t config;
	//i4mp__agent__start_t start;

	i4mp__agent__init_2_t init;
	i4mp__agent__config_2_t config;
	i4mp__agent__start_2_t start;


	i4mp__agent__get_2_t get_machine_count;

	i4mp__agent__get_t get_online_status;
	i4mp__agent__get_t get_simulation_mode_status;

	i4mp__agent__get_t get_id;
	i4mp__agent__get_t get_manufacturer;
	i4mp__agent__get_t get_model;
	i4mp__agent__get_t get_serial_number;
	i4mp__agent__get_t get_name;
	i4mp__agent__get_t get_facility;
	i4mp__agent__get_t get_cnc_name;
	
	i4mp__agent__get_t get_connection_status;
	i4mp__agent__get_t get_production_status;
	i4mp__agent__get_t get_operating_status;
	i4mp__agent__get_t get_part_counter;
	i4mp__agent__get_t get_cycle_time;
	i4mp__agent__get_t get_part_program_name;


} i4mp__agent_t;

#endif
