#ifndef FGGR__PO__PRIVATE_H
#define FGGR__PO__PRIVATE_H

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

	file_sdb_t *file_sdb;
	unsigned long file_sdb_len;	

	unsigned long year;
	unsigned long len;	

	fggr__component_t module;

} fgg__po_t;




extern fgg__po_t *fgg__po;
extern char *fgg__po__module_name;
extern unsigned long fgg__po__module_version;
extern unsigned long fgg__po__names_map_count;


int fgg__po__sdb__index_file (void);
void fgg__po__set_module_data (void);
int fgg__po__search_year (unsigned long year, unsigned long *year_index);

#endif

