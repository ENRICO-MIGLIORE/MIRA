#ifndef FGGR__RMW_IE_H
#define FGGR__RMW_IE_H


#include "fggr.h"
 


#define FGGR__RMW_IE__FIELD__PK_ID                                           FGGR__PRIVATE_FIELDS_MAX
#define FGGR__RMW_IE__FIELD__PK_YEAR                                         (FGGR__PRIVATE_FIELDS_MAX + 1)
#define FGGR__RMW_IE__FIELD__PK_TID                                          (FGGR__PRIVATE_FIELDS_MAX + 2)
#define FGGR__RMW_IE__FIELD__FK_USERS__PK_ID                                 (FGGR__PRIVATE_FIELDS_MAX + 3)
#define FGGR__RMW_IE__FIELD__FK_RMW_IET__PK_ID                               (FGGR__PRIVATE_FIELDS_MAX + 4)
#define FGGR__RMW_IE__FIELD__FK_SUPPLIERS__PK_ID                             (FGGR__PRIVATE_FIELDS_MAX + 5)
#define FGGR__RMW_IE__FIELD__FK_RM__PK_ID                                    (FGGR__PRIVATE_FIELDS_MAX + 6)
#define FGGR__RMW_IE__FIELD__FK_JOBS__PK_ID                                  (FGGR__PRIVATE_FIELDS_MAX + 7)
#define FGGR__RMW_IE__FIELD__FK_JOBS__PK_YEAR                                (FGGR__PRIVATE_FIELDS_MAX + 8)
#define FGGR__RMW_IE__FIELD__WEIGHT                                          (FGGR__PRIVATE_FIELDS_MAX + 9)
#define FGGR__RMW_IE__FIELD__REFERENCE_1                                     (FGGR__PRIVATE_FIELDS_MAX + 10)
#define FGGR__RMW_IE__FIELD__REFERENCE_2                                     (FGGR__PRIVATE_FIELDS_MAX + 11)
#define FGGR__RMW_IE__FIELD__REFERENCE_3                                     (FGGR__PRIVATE_FIELDS_MAX + 12)
#define FGGR__RMW_IE__FIELD__REFERENCE_4                                     (FGGR__PRIVATE_FIELDS_MAX + 13)
#define FGGR__RMW_IE__FIELD__NOTE                                            (FGGR__PRIVATE_FIELDS_MAX + 14)
#define FGGR__RMW_IE__FIELD__FK_RMW__PK_ID                                   (FGGR__PRIVATE_FIELDS_MAX + 15)

#define FGGR__RMW_IE__FIELDS_MAX                                (FGGR__RMW_IE__FIELD__NOTE + 1)

#define FGGR__RMW_IE__PK_MAX                                   3

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

	unsigned long year;
	unsigned long len;	

} fgg__rmw_ie_t;


extern fgg__rmw_ie_t *fgg__rmw_ie;
extern char *fgg__rmw_ie__module_name;
extern unsigned long fgg__rmw_ie__module_version;
extern unsigned long fgg__rmw_ie__names_map_count;


int fgg__rmw_ie__sdb__index_file (void);
void fgg__rmw_ie__set_module_data (void);
int fgg__rmw_ie__search_year (unsigned long pk_year, unsigned long *index);

int fgg__rmw_ie__init (void);
int fgg__rmw_ie__config(const char *sdb_path);
int fgg__rmw_ie__start (void);
int fgg__rmw_ie__get_state (void);
void fgg__rmw_ie__task_1__new_year_change (void);
int fgg__rmw_ie__sdb__select_count_from_rmw_ie(unsigned long pk_year, unsigned long *count);
int fgg__rmw_ie__sdb__insert_inventory_entry_into_rmw_ie (unsigned long id, unsigned long year, unsigned long tid, const utils__sdb_t *sdb, unsigned long active);
int fgg__rmw_ie__make_new_id_year (unsigned long *year, unsigned long *pk_id);
int fgg__rmw_ie__make_new_id_year_tid (unsigned long *year, unsigned long *pk_id, unsigned long *tid);
int fgg__rmw_ie__1_2_3_4_5__adjustment__manual (utils__sdb_t *sdb);
int fgg__rmw_ie__procedure_1__calculate_overall_inventory(unsigned long year, unsigned long count_of_total_material, unsigned long *weight, const char *language_iso_639_1_code);
int fgg__rmw_ie__procedure_2__calculate_inventory(unsigned long pk_id, unsigned long year, double *weight, const char *language_iso_639_1_code);
int fgg__rmw_ie__procedure_3__calculate_inventory_in_rmw(unsigned long pk_id, unsigned long year, unsigned long pk_id_rmw,double *weight, const char *language_iso_639_1_code);
int fgg__rmw_ie__sdb__select_inventory_entry_from_rmw_ie(unsigned long pk_id, unsigned long pk_year, utils__sdb_t *sdb, int *active, int present, const char *language_iso_639_1_code);
#endif