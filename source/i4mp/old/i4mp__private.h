#ifndef MIRA__PRIVATE_H
#define MIRA__PRIVATE_H

 
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <utils__sdb.h>
#include <utils__printf.h>


#include "i4mp.h"


typedef struct
{
	mira__config_t config;
	int configured;
	int started;

	int* machine_count;

	utils__printf_t pf;
	
	char *buffer;
	size_t buffer_size;

	size_t size;

} mira__t;


extern mira__t* mira;



/*
 * md = machine descriptor
 * ad = agent descriptor
 * ag_md = agent's machine descriptor
 */


int mira__private__check_config(mira__config_t* config);
int mira__private__check_configured(void);
int mira__private__check_started(void);
int mira__private__convert_machine_descriptor_to_agent_descriptor(int md, int* ad, int* ag_md);


#endif
