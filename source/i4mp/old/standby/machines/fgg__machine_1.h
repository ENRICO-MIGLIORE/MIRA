#ifndef FGG__MACHINE_1_H
#define FGG__MACHINE_1_H

#include "..\fgg__common.h"


typedef struct  
{
	fgg__buffer_t dir_path;

} fgg__machine_1__config_t;

int fgg__machine_1__init (void);
int fgg__machine_1__config (fgg__machine_1__config_t *config);
int fgg__machine_1__start (void);
int fgg__machine__1__create_thread (void);


#endif