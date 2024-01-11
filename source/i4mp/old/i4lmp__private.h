#ifndef I4LMP__PRIVATE_H
#define I4LMP_PRIVATE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <utils__platform.h>
#include <utils__libc.h>
#include <utils__printf.h>
#include <utils__sdb.h>
#include <utils__cf.h>


#include "i4lmp__machine_agent.h"
#include "i4lmp__config.h"


#define I4MP__GROUP__SIEMENS_OPEN62541       1
#define I4MP__GROUP__FANUCA_FOCAS            2
#define I4MP__GROUP__OKUMA_OKUMA             3



typedef struct
{

	size_t id;
	size_t group;
	const char* agent_name;

} i4lmp__machine_t;


typedef struct
{

	int enable_printf;
	int enable_log_file;
	char fully_qualified_log_file_name[I4MP__CONFIG__MAX_PATH_SIZE];
	size_t fully_qualified_log_file_name_len;
	size_t max_log_file_lines_per_minute;
	int enable_square_brackets_output;
	int enable_section_name_output;
	char configuration_file_section_name[I4MP__CONFIG__BUFFER_SIZE_256];
	size_t configuration_file_section_name_len;
	
} i4lmp__config_t;


typedef struct
{

	utils__sdb_t sdb;
	char sdb_buffer[I4MP__CONFIG__SDB_BUFFER_SIZE];
	char *sdb_name[I4MP__CONFIG__SDB_FIELDS_MAX];
	char *sdb_value[I4MP__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[I4MP__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[I4MP__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[I4MP__CONFIG__SDB_FIELDS_MAX];
		
	utils__printf_t pf;

	char error_buffer[I4MP__CONFIG__BUFFER_SIZE_256];

	

	char* application_name;
	char* application_version;
	char application_name_and_version[I4MP__CONFIG__BUFFER_SIZE_256];
	size_t application_name_and_version_len;
	char* application_default_configuration_file_name;
	char application_fully_qualified_configuration_file_name[I4MP__CONFIG__MAX_PATH_SIZE];
	char* application_configuration_file_section_name;
	size_t application_configuration_file_section_name_len;


	i4lmp__machine_t* machine;	
	size_t machine_count;
	size_t communications_enabled_machine_count;
	

	i4mp__machine_agent_t* machine_agent;
	size_t machines_agents_max;


	i4lmp__config_t config;

	int configured;
	int started;

} i4mp_t;


extern i4mp_t* i4mp;


int i4mp__init(int argc, char* argv[], i4mp__machine_agent_t* mp, size_t machine_proxy_count);
int i4mp__config(void);
int i4mp__start(void);
int i4mp__check_machines_agents(i4mp__machine_agent_t* machine_agent, size_t machine_agents_max);
int i4mp__process_configuration_file (void);
int i4mp__translate_machine_id_to_fd(size_t machine_id, size_t* fd);
int i4mp__sort_machines_ids(void);


#endif
