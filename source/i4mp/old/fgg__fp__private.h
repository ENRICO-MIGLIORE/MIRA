#ifndef FGGR__FP__PRIVATE_H
#define FGGR__FP__PRIVATE_H

#include "fggr.h"

typedef struct  
{
	utils__sdb_t sdb;
	char sdb_buffer[FGGR__CONFIG__SDB_BUFFER_SIZE];
	unsigned long sdb_name_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *sdb_name[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long sdb_value_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *sdb_value[FGGR__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[FGGR__CONFIG__SDB_FIELDS_MAX];

	utils__sdb_t sdb_2;
	char sdb_2_buffer[FGGR__CONFIG__SDB_BUFFER_SIZE];
	unsigned long sdb_2_name_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *sdb_2_name[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long sdb_2_value_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *sdb_2_value[FGGR__CONFIG__SDB_FIELDS_MAX];
	int sdb_2_encoding[FGGR__CONFIG__SDB_FIELDS_MAX];

	utils__sdb_t sdb_3;
	char sdb_3_buffer[FGGR__CONFIG__SDB_BUFFER_SIZE];
	unsigned long sdb_3_name_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *sdb_3_name[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long sdb_3_value_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *sdb_3_value[FGGR__CONFIG__SDB_FIELDS_MAX];
	int sdb_3_encoding[FGGR__CONFIG__SDB_FIELDS_MAX];


	char dir_path[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long dir_path_len;

	char absolute_file_name_master[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long absolute_file_name_master_len;
	unsigned long sdb_file_index_master[FGGR__CONFIG__SDB_RECORDS_MAX];
	unsigned long record_count_master;

	fggr__component_t module;

} fgg__fp_t;


extern fgg__fp_t *fgg__fp;
extern char *fgg__fp__module_name;
extern unsigned long fgg__fp__module_version;
extern unsigned long fgg__fp__names_map_count;


int fgg__fp__sdb__index_file (void);
void fgg__fp__set_module_data (void);


#endif

