#ifndef FGGR__MEDIA_H
#define FGGR__MEDIA_H


#include "fgg__common.h"


#define FGGR__MEDIA__DEFAULT_VALUE_MAX                                          6




#define FGGR__MEDIA__R_ID                                                       0
#define FGGR__MEDIA__R_VERSION                                                  1
#define FGGR__MEDIA__R_ACTIVE								                   2
#define FGGR__MEDIA__R_DATE                                                     3
#define FGGR__MEDIA__R_TIME                                                     4
#define FGGR__MEDIA__PK_ID__V1                                                  5
#define FGGR__MEDIA__FILE_NAME__V1                                              6
#define FGGR__MEDIA__COMMENT__V1                                                7



#define FGGR__MEDIA__PAIRS_MAX_V1                                               8

typedef struct  
{
	fgg__buffer_t field_names[FGGR__MEDIA__PAIRS_MAX_V1];
	unsigned long fields_max;
	unsigned long record_version;
	fgg__buffer_t dir_path;
	
} fgg__media_t;


extern fgg__media_t *fgg__media;



void fgg__media__fill_media_names (fgg__buffer_t *name, int option);
int fgg__media__db__select_count_from_media (unsigned long *count);
int fgg__media__make_new_media_id (unsigned long *pk_id);
int fgg__media__init (void);
int fgg__media__start (void);
void fgg__media__task (void);
int fgg__media__db__insert_media_into_media (unsigned long id, const fgg__buffer_t *value, unsigned long values_max);
int fgg__media__db__select_media_from_media (unsigned long id, fgg__buffer_t *name, fgg__buffer_t *value, unsigned long pairs_max, unsigned long *pairs_read, int *active);
int fgg__media__db__select_media_from_media_c(unsigned long id, fgg__buffer_t* name, fgg__buffer_t* value, unsigned long pairs_max, unsigned long* pairs_read, int* active);

int fgg__media__present_media (unsigned long presentation_mode, fgg__buffer_t *value, unsigned long pairs_max, fgg__buffer_t *presentation_buffer);



#endif