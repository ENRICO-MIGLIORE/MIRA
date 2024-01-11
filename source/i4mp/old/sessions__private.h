#ifndef SESSIONS__PRIVATE_H
#define SESSIONS__PRIVATE_H

#include "fggr.h"

#define SESSIONS__PRIVATE__ID_SIZE   32

typedef struct  
{
	unsigned long user_pk_id;
	int status;
	char time[UTILS__TIME__BUFFER_SIZE];
	char date[UTILS__TIME__BUFFER_SIZE];
	char id[SESSIONS__PRIVATE__ID_SIZE];

} sessions__data_t;

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

	

	/*fggr__names_map_t *names_map;
	unsigned long names_map_count;
	unsigned long names_map_version;*/

	/*char *module_name;*/

	fggr__component_t module;

	/*char absolute_file_name[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long absolute_file_name_len;
	unsigned long sdb_file_index[FGGR__CONFIG__SDB_RECORDS_MAX];
	unsigned long record_count;	
		*/

	file_sdb_t *file_sdb;
	unsigned long file_sdb_len;	

	//unsigned long year;
	unsigned long len;	

	sessions__data_t *data;
	unsigned long data_count;

} sessions_t;


extern sessions_t *sessions;
extern char *sessions__module_name;
extern unsigned long sessions__module_version;
extern unsigned long sessions__names_map_count;


int sessions__sdb__index_file (void);
void sessions__set_module_data (void);

#endif