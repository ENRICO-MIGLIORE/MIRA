#ifndef FGGR__SUPPLIERS_H
#define FGGR__SUPPLIERS_H


#include "fggr.h"



#define FGGR__SUPPLIERS__FIELD__PK_ID                             FGGR__PRIVATE_FIELDS_MAX
#define FGGR__SUPPLIERS__FIELD__VAT_ID                            (FGGR__PRIVATE_FIELDS_MAX + 1)
#define FGGR__SUPPLIERS__FIELD__NAME                              (FGGR__PRIVATE_FIELDS_MAX + 2)
#define FGGR__SUPPLIERS__FIELD__ADDRESS                           (FGGR__PRIVATE_FIELDS_MAX + 3)
#define FGGR__SUPPLIERS__FIELD__HOUSE_NUMBER                      (FGGR__PRIVATE_FIELDS_MAX + 4)
#define FGGR__SUPPLIERS__FIELD__CITY                              (FGGR__PRIVATE_FIELDS_MAX + 5)
#define FGGR__SUPPLIERS__FIELD__ZIP_CODE                          (FGGR__PRIVATE_FIELDS_MAX + 6)
#define FGGR__SUPPLIERS__FIELD__COUNTY                            (FGGR__PRIVATE_FIELDS_MAX + 7)
#define FGGR__SUPPLIERS__FIELD__NATION                            (FGGR__PRIVATE_FIELDS_MAX + 8)
#define FGGR__SUPPLIERS__FIELD__NOTE                              (FGGR__PRIVATE_FIELDS_MAX + 9)


#define FGGR__SUPPLIERS__FIELDS_MAX                               (FGGR__SUPPLIERS__FIELD__NOTE + 1)




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

	char *module_name;
	unsigned long module_version;
	unsigned long names_map_count;

	fggr__component_t module;

	//char dir_path[FGGR__CONFIG__MAX_PATH_SIZE];
	char sdb_path[FGGR__CONFIG__MAX_PATH_SIZE];
	char sdb_file_name[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long sdb_file_index[FGGR__CONFIG__SDB_RECORDS_MAX];
	unsigned long record_count;	

} suppliers_t;


extern suppliers_t *fgg__suppliers;


int suppliers__init  (void);
int suppliers__config (void);
int suppliers__start  (void);
int suppliers__select_count_from_suppliers (unsigned long *count);
int suppliers__select_active_suppliers_count_from_suppliers (unsigned long *count);
int suppliers__select_supplier_from_suppliers (unsigned long pk_id, utils__sdb_t *data, int* active, const char *language_iso_639_1_code);
int suppliers__insert_supplier_into_suppliers (unsigned long pk_id, const utils__sdb_t *sdb, unsigned long active);
int suppliers__present_supplier (unsigned long presentation_mode, utils__sdb_t *sdb, char *buffer, unsigned long buffer_size, unsigned long *buffer_len);
int suppliers__make_new_data_id (unsigned long *pk_id);

int suppliers__index_file (void);
void suppliers__set_module_data (void);

#endif