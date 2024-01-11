#ifndef FGGR__USERS__PRIVATE_H
#define FGGR__USERS__PRIVATE_H

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


	char dir_path[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long dir_path_len;

	char absolute_file_name[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long absolute_file_name_len;

	/*fggr__names_map_t *names_map;
	unsigned long names_map_count;
	unsigned long names_map_version;*/

	/*char *module_name;*/

	fggr__component_t module;

	unsigned long sdb_file_index[FGGR__CONFIG__SDB_RECORDS_MAX];
	unsigned long record_count;	

} fgg__users_t;


extern fgg__users_t *fgg__users;
extern char *fgg__users__module_name;
extern unsigned long fgg__users__module_version;
extern unsigned long fgg__users__names_map_count;


int users__index_file (void);
void users__set_module_data (void);


#endif