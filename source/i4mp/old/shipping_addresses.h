#ifndef FGGR__SHIPPING_ADDRESSES_H
#define FGGR__SHIPPING_ADDRESSES_H

#include "fggr.h"



#define FGGR__SHIPPING_ADDRESSES__FIELD__PK_ID                             FGGR__PRIVATE_FIELDS_MAX
#define FGGR__SHIPPING_ADDRESSES__FIELD__NAME                              (FGGR__PRIVATE_FIELDS_MAX + 1)
#define FGGR__SHIPPING_ADDRESSES__FIELD__ADDRESS                           (FGGR__PRIVATE_FIELDS_MAX + 2)
#define FGGR__SHIPPING_ADDRESSES__FIELD__HOUSE_NUMBER                      (FGGR__PRIVATE_FIELDS_MAX + 3)
#define FGGR__SHIPPING_ADDRESSES__FIELD__CITY                              (FGGR__PRIVATE_FIELDS_MAX + 4)
#define FGGR__SHIPPING_ADDRESSES__FIELD__ZIP_CODE                          (FGGR__PRIVATE_FIELDS_MAX + 5)
#define FGGR__SHIPPING_ADDRESSES__FIELD__COUNTY                            (FGGR__PRIVATE_FIELDS_MAX + 6)
#define FGGR__SHIPPING_ADDRESSES__FIELD__NATION                            (FGGR__PRIVATE_FIELDS_MAX + 7)
#define FGGR__SHIPPING_ADDRESSES__FIELD__NOTE                              (FGGR__PRIVATE_FIELDS_MAX + 8)


#define FGGR__SHIPPING_ADDRESSES__FIELDS_MAX                               (FGGR__SHIPPING_ADDRESSES__FIELD__NOTE + 1)




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

	char dir_path[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long dir_path_len;

	char absolute_file_name[FGGR__CONFIG__MAX_PATH_SIZE];
	unsigned long absolute_file_name_len;


	unsigned long sdb_file_index[FGGR__CONFIG__SDB_RECORDS_MAX];
	unsigned long record_count;	

} sa_t;


extern sa_t *sa;


int sa__init  (void);
int sa__config (const char *sdb_path);
int sa__start  (void);
int sa__select_count_form_shipping_addresses (unsigned long *count);
int sa__select_shipping_address_from_shipping_addresses (unsigned long pk_id, utils__sdb_t *data, int* active, unsigned long lang);
int sa__insert_shipping_address_into_shipping_addresses (unsigned long pk_id, const utils__sdb_t *sdb, unsigned long active);
int sa__present_shipping_addresses (unsigned long presentation_mode, utils__sdb_t *sdb, char *buffer, unsigned long buffer_size, unsigned long *buffer_len);
int sa__sdb__make_new_data_id (unsigned long *pk_id);
int sa__sdb__index_file (void);
void sa__set_module_data (void);

#endif