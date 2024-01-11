#ifndef FGGR__RMW_IET_H
#define FGGR__RMW_IET_H

#include "fggr.h"

#define FGGR__RMW_IET__FIELD__PK_ID                            FGGR__PRIVATE_FIELDS_MAX
#define FGGR__RMW_IET__FIELD__DESCRIPTION                      (FGGR__PRIVATE_FIELDS_MAX + 1)
#define FGGR__RMW_IET__FIELD__NOTE                             (FGGR__PRIVATE_FIELDS_MAX + 2)


#define FGGR__RMW_IET__FIELDS_MAX                              (FGGR__RMW_IET__FIELD__NOTE + 1)



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


int fgg__rmw_iet__init  (void);
int fgg__rmw_iet__config (const char *sdb_path);
int fgg__rmw_iet__start  (void);
int fgg__rmw_iet__present_rmw_iet (unsigned long presentation_mode, utils__sdb_t *sdb, char *buffer, unsigned long buffer_size, unsigned long *buffer_len);
int fgg__rmw_iet__sdb__select_count_from_rmw_iet (unsigned long *count);
int fgg__rmw_iet__sdb__select_active_count_from_rmw_iet (unsigned long *count);
int fgg__rmw_iet__sdb__select_rmw_iet_from_rmw_iet (unsigned long pk_id, utils__sdb_t *sdb, int *active, const char *language_iso_639_1_code);
int fgg__rmw_iet__sdb__insert_rmw_iet_into_rmw_iet(unsigned long pk_id, const utils__sdb_t *sdb, unsigned long active);



#endif