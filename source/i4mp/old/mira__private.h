#ifndef MIRA__PRIVATE_H
#define MIRA__PRIVATE_H

 
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <utils__sdb.h>
#include <utils__printf.h>


#include "mira.h"


typedef struct
{
	mira__config_t config;

	int initialized;
	int configured;
	int started;

	int* number_of_machines_per_agent;
	char *buffer;
	size_t buffer_size;
	
	const char* application_name;

	utils__printf_t pf;
	
} mira__t;


extern mira__t* mira;


int mira__private__verify_framework_is_initialized(void);
int mira__private__verify_framework_is_configured(void);
int mira__private__verify_framework_is_started(void);
int mira__private__convert_machine_descriptor_to_agent_descriptor(int md, int* ad, int* ag_md);
int mira__private__check_config(mira__config_t* config);

#endif

