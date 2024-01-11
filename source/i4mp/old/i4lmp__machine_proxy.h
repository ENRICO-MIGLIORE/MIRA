#ifndef I4MP__MACHINE_AGENT_H
#define I4MP__MACHINE_AGENT_H


#include <stddef.h>


typedef int (*i4mp__machine_agent__init_t) (int argc, char* argv[]);
typedef int (*i4mp__machine_agent__config_t) (void);
typedef int (*i4mp__machine_agent__start_t) (void);
typedef int (*i4mp__machine_agent__get_machine_count_t) (size_t* machine_count);
typedef int (*i4mp__machine_agent__get_connection_status_t) (size_t* machine_count);
typedef int (*i4mp__machine_agent__get_cycle_time_t) (size_t* machine_count);


typedef struct
{
	i4mp__machine_agent__init_t init;
	i4mp__machine_agent__config_t config;
	i4mp__machine_agent__start_t start;
	i4mp__machine_agent__get_machine_count_t get_machine_count;
	i4mp__machine_agent__get_connection_status_t get_connection_status;
	i4mp__machine_agent__get_cycle_time_t get_cycle_time;

} i4mp__machine_agent_t;


#endif
