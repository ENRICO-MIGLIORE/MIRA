#ifndef MACHINE_STAR_H2_FANUC_FOCAS_H
#define MACHINE_STAR_H2_FANUC_FOCAS_H


#ifndef NULL
#define NULL     ((void *) 0)
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#if 0
typedef struct
{

	fgg__buffer_t parameter[FGG__FOCAS__PARAMETERS];

} fgg__focas_configuration_file_t;
#endif

typedef struct
{
	int state[16];
	int fd[16];
	int start[16];
} machine__star__h2__fanuc__focas_t;

extern machine__star__h2__fanuc__focas_t *machine__star__h2__fanuc__focas;

int machine__star__h2__fanuc__focas__config (void);
int machine__star__h2__fanuc__focas__init (void);
int machine__star__h2__fanuc__focas__open (void);
int machine__star__h2__fanuc__focas__start (int fd);
void machine__star__h2__fanuc__focas__task (void);

#endif