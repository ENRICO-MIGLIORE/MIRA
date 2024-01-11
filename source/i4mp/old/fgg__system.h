#ifndef FGGR__SYSTEM_H
#define FGGR__SYSTEM_H


#include "fggr.h"


#define FGGR__SYSTEM__FIELD__PK_ID                             FGGR__PRIVATE_FIELDS_MAX
#define FGGR__SYSTEM__FIELD__YEAR                              (FGGR__PRIVATE_FIELDS_MAX + 1)
#define FGGR__SYSTEM__FIELDS_MAX                               (FGGR__SYSTEM__FIELD__YEAR + 1)



typedef struct  
{  

	utils__sdb_t sdb;
	char sdb_buffer[FGGR__CONFIG__SDB_BUFFER_SIZE];
	char *sdb_name[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *sdb_value[FGGR__CONFIG__SDB_FIELDS_MAX];	
	unsigned long sdb_name_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long sdb_value_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[FGGR__CONFIG__SDB_FIELDS_MAX];
	char sdb_language_iso_639_1_code[FGGR__CONFIG__SDB_FIELDS_MAX * UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	utils__sdb_t sdb_2;
	char sdb_2_buffer[FGGR__CONFIG__SDB_BUFFER_SIZE];
	char *sdb_2_name[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *sdb_2_value[FGGR__CONFIG__SDB_FIELDS_MAX];	
	unsigned long sdb_2_name_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long sdb_2_value_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	int sdb_2_encoding[FGGR__CONFIG__SDB_FIELDS_MAX];
	char sdb_2_language_iso_639_1_code[FGGR__CONFIG__SDB_FIELDS_MAX * UTILS__LANGUAGE_ISO_639_1__CODE_LEN];


	char sdb_file_name[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long sdb_file_index[FGGR__CONFIG__SDB_RECORDS_MAX];
	unsigned long sdb_file_record_count;

	fggr__component_t module;

	char *module_name;
	unsigned long module_version;
	unsigned long names_map_count;


	int event__new_year_detected_at_boot_time;
	int event__new_year_detected_at_run_time;	

	int state;

	int time;
	int time_snapshot;
	unsigned long year_snapshot;


} fgg__system_t;


extern fgg__system_t *fgg__system;
extern char *fgg__system__module_name;
extern unsigned long fgg__system__module_version;
extern unsigned long fgg__system__names_map_count;


int system__init  (void);
int system__config (void);


int fgg__system__start  (void);
int fgg__system__stop (void);
int fgg__system__exit (void);
void fgg__system__task (void);
void fgg__system__new_year_detection_task (void);
void *fgg__system__thread (void *arg);
int fgg__system__select_count_from_system (unsigned long *count);
int fgg__system__insert_data_into_system(unsigned long pk_id, const utils__sdb_t *sdb, unsigned long active);
int fgg__system__make_new_data_id (unsigned long *pk_id);

int fgg__system__event__new_year_at_boot_time (void);

int system__select_data_from_system (unsigned long pk_id, utils__sdb_t *sdb, int *active, const char *language_iso_639_1_code);
int fgg__system__index_sdb_file (void);
void system__set_module_data (void);

#endif