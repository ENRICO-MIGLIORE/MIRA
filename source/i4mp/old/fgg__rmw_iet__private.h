#ifndef FGGR__RMW_IET__PRIVATE_H
#define FGGR__RMW_IET__PRIVATE_H

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

	
	unsigned long sdb_file_index[FGGR__CONFIG__SDB_RECORDS_MAX];
	unsigned long record_count;	

	char sdb_path[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long sdb_path_len;

	char absolute_file_name[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long absolute_file_name_len;

	int event__new_year_detected_at_boot_time;
	int event__new_year_detected_at_run_time;	

	int state;

	int time;
	int time_snapshot;
	unsigned long year_snapshot;

	fggr__component_t module;

} fgg__rmw_iet_t;


extern fgg__rmw_iet_t *fgg__rmw_iet;
extern char *fgg__rmw_iet__module_name;
extern unsigned long fgg__rmw_iet__module_version;
extern unsigned long fgg__rmw_iet__names_map_count;


int fgg__rmw_iet__sdb__index_file (void);
void fgg__rmw_iet__set_module_data (void);




#endif