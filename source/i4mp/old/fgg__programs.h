#ifndef FGGR__PROGRAMS_H
#define FGGR__PROGRAMS_H


#include "fgg__common.h"

#define FGGR__PROGRAMS__PAIRS_MAX_V1                                         10


typedef struct  
{
	fgg__buffer_t dir_path;

	unsigned long record_index[FGGR__CONFIG__SDB_RECORDS_MAX];

} fgg__programs_t;




extern fgg__programs_t *fgg__programs;


int fgg__programs__init  (void);
int fgg__programs__start (void);
int fgg__programs__get_program_count (unsigned long *count);
int fgg__programs__select_program_from_programs (unsigned long pk_id, utils__sdb_t *data, int* active, const char *ascii_7_bit_characters_to_escape, unsigned long ascii_7_bit_characters_to_escape_len, unsigned long lang);
int fgg__programs__present_program (unsigned long presentation_mode, utils__sdb_t *sdb, char *buffer, unsigned long buffer_size, unsigned long *buffer_len);



#endif