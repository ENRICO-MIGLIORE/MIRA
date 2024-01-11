#ifndef I4LMP_H
#define I4LMP_H


//#include "fggr__common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


//#include <nbuf.h>
#include <utils__percent_encoding.h>
#include <utils__sdb.h>
#include <utils__printf.h>
#include <utils__language_iso_639_1.h>
#include <utils__time.h>
#include <utils__libc.h>
#include <utils__platform.h>
//#include <clp.h>

//#include <fggr__platform.h>
#include "clmp__config.h"
//#include "fggr__macros.h"
//#include "fggr__data_types.h"
//#include "fggr__util_file.h"


#define FGGR__CONFIG__SDB_RECORDS_MAX  1024
#define FGGR__CONFIG__SDB_BUFFER_SIZE  1024
#define FGGR__CONFIG__SDB_FIELDS_MAX     64



typedef struct
{

	int enable_printf;
	int enable_log_file;
	const char fully_qualified_log_file_name[1024];
	size_t fully_qualified_log_file_name_len;
	size_t max_log_file_lines_per_minute;
	int enable_square_brackets_output;
	int enable_application_name_output;
	const char application_name[32];
	size_t application_name_len;
	

} i4lmp__config_t;






typedef struct
{


	utils__sdb_t sdb;
	char sdb_buffer[CLMP__CONFIG__SDB_BUFFER_SIZE];
	char *sdb_name[CLMP__CONFIG__SDB_FIELDS_MAX];
	char *sdb_value[CLMP__CONFIG__SDB_FIELDS_MAX];
	int sdb_encoding[CLMP__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_name_len[CLMP__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_value_len[CLMP__CONFIG__SDB_FIELDS_MAX];
	char sdb_language_iso_639_1_buffer[CLMP__CONFIG__SDB_FIELDS_MAX * UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	utils__sdb_t sdb_2;
	char sdb_2_buffer[CLMP__CONFIG__SDB_BUFFER_SIZE];
	size_t sdb_2_name_len[CLMP__CONFIG__SDB_FIELDS_MAX];
	char *sdb_2_name[CLMP__CONFIG__SDB_FIELDS_MAX];
	size_t sdb_2_value_len[CLMP__CONFIG__SDB_FIELDS_MAX];
	char *sdb_2_value[CLMP__CONFIG__SDB_FIELDS_MAX];
	int sdb_2_encoding[CLMP__CONFIG__SDB_FIELDS_MAX];
	char sdb_2_language_iso_639_1_buffer[CLMP__CONFIG__SDB_FIELDS_MAX * UTILS__LANGUAGE_ISO_639_1__CODE_LEN];


	char *sdb_3_buffer;
	char **sdb_3_name;
	char **sdb_3_value;
	int *sdb_3_encoding;
	size_t* sdb_3_name_len;
	size_t* sdb_3_value_len;
	char *sdb_3_language_iso_639_1_buffer;

	/*fgg__buffer_t system_file_name;*/


	size_t first_fiscal_year;
	size_t last_fiscal_year;

	size_t lang;
	size_t dictionar_error_log;

	int log__state;
	FILE *log__file;




	i4lmp__config_t config;
	utils__printf__t pf;



	int boot;

	size_t record_index[CLMP__CONFIG__SDB_RECORDS_MAX];

	

	char *application_name;
	size_t application_name_len;
	char *application_version;
	char application_name_and_version[128];
	char *default_configuration_file_name;
	char fully_qualified_configuration_file_name[CLMP__CONFIG__MAX_PATH_SIZE];

} i4lmp__t;


extern i4lmp__t * i4lmp;

int i4lmp__main (int argc, char *argv[]);
int i4lmp__init(int argc, char *argv[]);
int i4lmp__config (void);
int i4lmp__read_configuration_file (void);
char * i4lmp__version (void);


//
//int fggr__config (void);
//
//int fggr__init_cnc_lathes_proxy (int argc, char *argv[]);
//
//int fggr__init_sdb_components (void);
//int fggr__init_web_components (void);
//int fggr__init_print_components (void);
//
//
//int fggr__config_sdb_components (void);
//int fggr__config_lathes_components (void);
//int fggr__config_print_components (void);
//int fggr__config_web_components (void);
//
//int fggr__start_sdb_components (void);
//int fggr__start_lathes_components (void);
//int fggr__start_print_components (void);
//int fggr__start_web_components (void);
//
//
//
//
//int fggr__stop (void);

//int fgg__get_stop_request (void);
//int fgg__set_stop_request (void);
//
//int fggr__read_configuration_file (void);
//int fggr__insert_reserved_names (utils__sdb_t *sdb, unsigned long id, unsigned long record_version, unsigned long record_active);
//int fggr__write_data_to_sdb_file (unsigned long *pk_vector, unsigned long pk_vector_len, const utils__sdb_t *sdb, fggr__component_t *component, char *absolute_file_name, unsigned long *record_count, unsigned long *sdb_file_index, unsigned long active, int insert_mode);
//
//
//int fgg__select_data_from_sdb_module (unsigned long pk_id, utils__sdb_t *sdb, int *active, unsigned long record_count, char* absolute_file_name, unsigned long *sdb_file_index, const char *language_iso_639_1_code, unsigned long language_iso_639_1_code_len);
//
//int fggr__start_type_1_component (utils__sdb_t *sdb, fggr__component_t *component, char *file_path, char *file_full_name, unsigned long fields_max, unsigned long *sdb_file_record_count, unsigned long *sdb_file_index);
//int fggr__start_type_2_component (utils__sdb_t *sdb, fggr__component_t *component, file_sdb_t **file_sdb, unsigned long *file_sdb_len, char *dir_path, unsigned long fields_max, unsigned long *pk_vector, unsigned long pk_vector_len, unsigned long pk_vector_year_index, unsigned long year);
//int fggr__start_type_3_component (utils__sdb_t *sdb, fggr__component_t *component, char *file_path, char *file_full_name, unsigned long fields_max, unsigned long *record_count_master, unsigned long *sdb_file_index_master);
//int fggr__start_type_4_component (utils__sdb_t *sdb, fggr__component_t *component, file_sdb_t **file_sdb_output, unsigned long *file_sdb_len, char *dir_path, unsigned long fields_max, unsigned long *pk_vector, unsigned long pk_vector_len, unsigned long pk_vector_year_index, unsigned long year);
//
//int fggr__update_sdb_module(unsigned long pk_id, unsigned long year, fggr__component_t *module, unsigned long index_user, unsigned long offset_start, char *dir_path, utils__sdb_t *sdb_input, utils__sdb_t *sdb_tmp, utils__sdb_t *sdb_out, const char *language_iso_639_1_code, unsigned long language_iso_639_1_code_len);
//int fgg__format_js_buffer (unsigned long presentation_mode, char *buffer, unsigned long buffer_size, unsigned long *buffer_len, char **name, unsigned long *name_len, unsigned long pair_count, char **value, unsigned long *value_len);
//
//
//
//int fggr__build_absolute_sdb_file_name_with_year (char *file_name, unsigned long file_name_size, unsigned long *file_name_len, const char *path, const char *path_separator, unsigned long year, const char *name_prefix, const char *name, const char *name_separator, const char *file_extension);
////int fggr__build_absolute_sdb_file_name_with_year (char *file_name, unsigned long file_name_size, unsigned long *file_name_len, const char *path, const char *path_separator, unsigned long year, const char *name_prefix, const char *name, const char *name_separator, const char *file_extension);
//int fggr__build_absolute_file_name_with_year_and_id (char *file_name, unsigned long file_name_size, const char *path, const char *path_separator, unsigned long year, unsigned long id, const char *name_prefix, const char *name, const char *name_separator, const char *file_extension);
//int fggr__build_absolute_sdb_file_name (char *file_name, unsigned long file_name_size, const char *path, const char *path_separator, const char *name_prefix, const char *name_separator, const char *name, const char *file_extension);
//int fggr__build_absolute_sdb_file_name_with_id (char *file_name, unsigned long file_name_size, unsigned long *file_name_len, const char *path, const char *path_separator, unsigned long id, const char *name_prefix, const char *name, const char *name_separator, const char *file_extension);
////int fgg__utils__build_absolute_sdb_file_name_with_year (char *file_name, unsigned long file_name_size, unsigned long *file_name_len, const char *path, char path_separator, unsigned long year, const char *name_prefix, const char *name, const char *name_separator, const char *file_extension);
//
//int fggr__print_labels (unsigned long pk_id_fp_ie, unsigned long year, unsigned long pk_company, utils__sdb_t *data, const char *language_iso_639_1_code, unsigned long language_iso_639_1_code_len);

#endif
