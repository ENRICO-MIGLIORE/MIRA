#ifndef UTILS__SDB_H
#define UTILS__SDB_H


#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>


#define UTILS__SDB__ENCODING__UTF_8                    1
#define UTILS__SDB__ENCODING__BINARY                   2
#define UTILS__SDB__ENCODING__CIPHERED                 3


#define UTILS__SDB__SECTION_NAME_SIZE                128



typedef struct
{
	char* buffer;
	size_t buffer_size;
	char** name;
	size_t* name_len;
	char** value;
	size_t* value_len;
	size_t fields_max;
	int* encoding;

} utils__sdb__config_t;


typedef struct
{
	char* buffer;
	size_t buffer_size;
	size_t buffer_len;
	size_t num_fields;
	size_t fields_max;
	char section_name[UTILS__SDB__SECTION_NAME_SIZE];
	size_t section_name_len;
	char** name;
	char** value;		
	size_t* name_len;
	size_t* value_len;
    int* encoding;

	int end_of_record_signature;
	size_t comment_lines;

	int configured;
 
} utils__sdb_t;


int utils__sdb__init(utils__sdb_t* sdb);
int utils__sdb__config(utils__sdb_t* sdb, utils__sdb__config_t* config);

int utils__sdb__append_sdb (utils__sdb_t *sdb_1, const utils__sdb_t *sdb_2);
int utils__sdb__check_names (const utils__sdb_t *sdb, const char **names, const size_t *names_len, size_t names_count, size_t *names_index);
int utils__sdb__clear_sdb (utils__sdb_t *sdb);
int utils__sdb__compare_two_sdbs (const utils__sdb_t *sdb_1, const utils__sdb_t *sdb_2, int mode);
int utils__sdb__index_file (const char *file_name, size_t *record_count, size_t *record_index, size_t record_index_max);
int utils__sdb__match_sdb_names (const utils__sdb_t *sdb_1, const utils__sdb_t *sdb_2, int *match_vector_index, size_t match_vector_size);
int utils__sdb__match_sdb_names_rows(const utils__sdb_t* sdb_1, const utils__sdb_t* sdb_2, int* match_vector_index, size_t match_vector_size, size_t rows_index, size_t* index_of_each_rows);
int utils__sdb__print_records_index (const char *file_name, size_t *record_index, size_t record_index_max);
int utils__sdb__print_sdb (const utils__sdb_t *sdb);
int utils__sdb__read_record_from_file(utils__sdb_t* sdb, const char* file_name, size_t record_number, size_t record_index, int* end_of_file);
int utils__sdb__read_record_from_buffer(utils__sdb_t* sdb, const char* file_name, size_t record_number, size_t record_index, int* end_of_file);
int utils__sdb__replace_value_in_position(utils__sdb_t* sdb, const char* value, size_t value_len, size_t value_index, int encoding);
int utils__sdb__search_index_by_name (utils__sdb_t *sdb, const char *name, size_t name_len, size_t *index);
int utils__sdb__validate_name (const char *name, size_t name_len);
int utils__sdb__write_pair_to_sdb(utils__sdb_t* sdb, const char* name, size_t name_len, const char* value, size_t value_len, int encoding);
int utils__sdb__write_record_to_file (const char *file_name, const utils__sdb_t *sdb);
int utils__sdb__write_urlencoded_data_to_sdb(utils__sdb_t* sdb, const char* buffer, size_t buffer_len);





/*
 * structures and functions for reading configuration files or configuration buffers
 */
typedef int (*utils__sdb__section_function_t) (void*, const char* section_name, size_t section_name_len);
typedef int (*utils__sdb__value_function_t) (void*, const char* value, size_t value_len);


typedef struct
{
	const char* name;
	utils__sdb__section_function_t function;

} utils__sdb__section_callback_t;


typedef struct
{
	const char* name;
	utils__sdb__value_function_t function;

} utils__sdb__name_callback_t;


int utils__sdb__count_sections_from_file(utils__sdb_t* sdb, const char* file_name, const char* section_name, size_t start_record, size_t* section_count, int* end_of_file);
int utils__sdb__count_sections_from_buffer(utils__sdb_t* sdb, const char* file_name, const char* section_name, size_t start_record, size_t* section_count, int* end_of_file);
int utils__sdb__read_configuration_from_file(void *p, utils__sdb_t* sdb, const char* file_name, utils__sdb__section_callback_t* section, utils__sdb__name_callback_t* name_value, size_t names_values_max, size_t start_record, size_t* record_number, int* eof);
int utils__sdb__read_configuration_from_buffer(void* p, utils__sdb_t* sdb, const char* file_name, utils__sdb__section_callback_t* section, utils__sdb__name_callback_t* name_value, size_t names_values_max, size_t start_record, size_t* record_number, int* eof);



#endif