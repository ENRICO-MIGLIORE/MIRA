#ifndef I4MP__AGENT_H
#define I4MP__AGENT_H


#include <stddef.h>


typedef int (*i4mp__agent_function__init_t) (int argc, char* argv[]);
typedef int (*i4mp__agent_function__config_t) (void);
typedef int (*i4mp__agent_function__start_t) (void);

typedef int (*i4mp__agent_function__get_t) (int md, char* buffer, size_t buffer_size, size_t* buffer_len);



//typedef struct
//{
//
//	i4mp__agent_function__init_t init;
//	const char* init__function_name;
//
//	i4mp__agent_function__config_t config;
//	const char* config__function_name;
//
//	i4mp__agent_function__start_t start;
//	const char* start__function_name;
//
//	i4mp__agent_function__get_t get_machine_count;
//	const char* get_machine_count__function_name;
//
//	i4mp__agent_function__get_t get_machine_id;
//	const char* get_machine_id__function_name;
//
//	i4mp__agent_function__get_t get_machine_enable_communications;
//	const char* get_machine_enable_communications__function_name;
//
//	i4mp__agent_function__get_t get_machine_enable_simulation_mode;
//	const char* get_machine_enable_simulation_mode__function_name;
//
//	i4mp__agent_function__get_t  get_machine_brand;
//	const char* get_machine_brand__function_name;
//
//	i4mp__agent_function__get_t  get_machine_model;
//	const char* get_machine_model__function_name;
//
//	i4mp__agent_function__get_t  get_machine_sn;
//	const char* get_machine_sn__function_name;
//
//	i4mp__agent_function__get_t  get_machine_facility;
//	const char* get_machine_facility__function_name;
//
//	i4mp__agent_function__get_t  get_machine_name;
//	const char* get_machine_name__function_name;
//
//	i4mp__agent_function__get_t  get_machine_connection_status;
//	const char* get_machine_connection_status__function_name;
//
//	i4mp__agent_function__get_t  get_machine_part_counter;
//	const char* get_machine_part_counter__function_name;
//
//	i4mp__agent_function__get_t get_machine_cycle_time;
//	const char* get_machine_cycle_time__function_name;
//
//	i4mp__agent_function__get_t get_machine_part_program_name;
//	const char* get_machine_part_program_name__function_name;
//
//} i4mp__agent_functions_t;



typedef struct
{
	const char* name;
	size_t buffer_size;

	i4mp__agent_function__init_t init;
	const char* init__function_name;

	i4mp__agent_function__config_t config;
	const char* config__function_name;

	i4mp__agent_function__start_t start;
	const char* start__function_name;

	i4mp__agent_function__get_t get_machine_count;
	const char* get_machine_count__function_name;

	i4mp__agent_function__get_t get_machine_id;
	const char* get_machine_id__function_name;

	i4mp__agent_function__get_t get_machine_enable_communications;
	const char* get_machine_enable_communications__function_name;

	i4mp__agent_function__get_t get_machine_enable_simulation_mode;
	const char* get_machine_enable_simulation_mode__function_name;

	i4mp__agent_function__get_t  get_machine_brand;
	const char* get_machine_brand__function_name;

	i4mp__agent_function__get_t  get_machine_model;
	const char* get_machine_model__function_name;

	i4mp__agent_function__get_t  get_machine_sn;
	const char* get_machine_sn__function_name;

	i4mp__agent_function__get_t  get_machine_facility;
	const char* get_machine_facility__function_name;

	i4mp__agent_function__get_t  get_machine_name;
	const char* get_machine_name__function_name;

	i4mp__agent_function__get_t  get_machine_connection_status;
	const char* get_machine_connection_status__function_name;

	i4mp__agent_function__get_t  get_machine_part_counter;
	const char* get_machine_part_counter__function_name;

	i4mp__agent_function__get_t get_machine_cycle_time;
	const char* get_machine_cycle_time__function_name;

	i4mp__agent_function__get_t get_machine_part_program_name;
	const char* get_machine_part_program_name__function_name;

} i4mp__agent_2_t;

#endif
