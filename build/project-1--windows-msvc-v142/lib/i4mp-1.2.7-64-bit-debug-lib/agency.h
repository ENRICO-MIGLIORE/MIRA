#ifndef AGENCY_H
#define AGENCY_H


#include <stdio.h>
#include <stddef.h>
#include <string.h>


#define AGENCY__BUFFER_SIZE     1024


typedef struct
{
	const char* file_name;
	char* buffer;
	size_t buffer_len;

} agency__config_t;


int agency__init(void);
int agency__config(agency__config_t* config);
int agency__start(void);

int agency__get_number_of_machines(int* number_of_machines);

int agency__get_machine_id(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agency__get_machine_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agency__get_machine_part_counter(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agency__get_machine_cycle_time(int md, char* buffer, size_t buffer_size, size_t* buffer_len);
int agency__get_machine_part_program_name(int md, char* buffer, size_t buffer_size, size_t* buffer_len);

void i4_agency__sleep(size_t milliseconds);

#endif


