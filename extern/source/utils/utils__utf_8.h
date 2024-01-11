#ifndef UTILS__UTF_8_H
#define UTILS__UTF_8_H

#include <stdio.h>
#include <string.h>
#include <stddef.h>

//
//typedef struct
//{
//	size_t offset;
//	size_t len;
//
//} utils__utf_8_token_t;
//
//typedef struct
//{
//	unsigned char *buffer;
//	size_t len;
//	size_t size; 
//
//} utils__utf_8__row_t;
//
//
//
//
//typedef struct
//{
//    int state;
//	int row_increment;
//	int backslash_r;
//	size_t row_count;
//
//} utils__utf_8__row_writer_t;
//
//typedef struct
//{
//	int state;
//    char name_value_separator;
//	size_t name_len;
//	size_t value_len;
//	size_t utf_8_token_count;
//	size_t windows_row_count;
//	size_t unix_and_mac_row_count;
//	size_t pre_2001_mac_row_count;
//	size_t row_number_of_the_name;
//	size_t white_space_count;
//
//} utils__utf_8__nvp_parser_t;
//
//
//
//typedef struct
//{
//	int state;
//	unsigned char buffer[16];
//
//} utils__utf_8__tokenizer_t;
//
//
//typedef struct
//{
//	size_t first_token_index;
//	size_t token_count;
//
//} utils__utf_8_match_t;

//
//int utils__utf_8__tokenizer__init (utils__utf_8__tokenizer_t *t);
//int utils__utf_8__tokenizer__get_first_token (utils__utf_8__tokenizer_t *t, unsigned char *buffer, size_t buffer_len, unsigned char *token, size_t *token_len);
//int utils__utf_8__row_writer__init (utils__utf_8__row_writer_t *w);
//int utils__utf_8__row_writer__write_token (utils__utf_8__row_writer_t *w, const char *utf_8_token, size_t utf_8_token_len, utils__utf_8__row_t *row_1, utils__utf_8__row_t *row_2);
//int utils__utf_8__nvp_parser__init (utils__utf_8__nvp_parser_t *p, char separator);
//int utils__utf_8__nvp_parser__find_name_value_pair (utils__utf_8__nvp_parser_t *nvp, const char *utf_8_token, size_t utf_8_token_len, char *name, size_t name_size, size_t *name_len, char *value, size_t value_size, size_t *value_len);
//int utils__utf_8__print_name_value_pair (char *name, size_t name_len, char *value, size_t value_len, size_t row_number, size_t span);
//int utils__utf_8__row_writer__tokenize_row (utils__utf_8__row_t *row, const char* seps, size_t seps_len, utils__utf_8_token_t *token, size_t tokens_max, size_t *token_count, int zero_terminate_tokens);
//int utils__utf_8__find (utils__utf_8__row_t *row_1, utils__utf_8_token_t *token_1, size_t token_1_count, const utils__utf_8__row_t *row_2, const utils__utf_8_token_t *token_2, size_t token_2_count, utils__utf_8_match_t *match, size_t matches_max, size_t *match_count);
int utils__utf_8__memcmp (const void *buffer_1, const void *buffer_2, size_t len, int uppercase_flag);



int utils__utf_8__count_symbols (const void *buffer, size_t buffer_len, size_t *token_count);
int utils__utf_8__get_next_symbol (const void *buffer, size_t buffer_len, char **token, size_t *token_len);
int utils__utf_8__get_symbol (const void *buffer, size_t buffer_len, size_t token_index, char **token, size_t *token_len);
int utils__utf_8__validate_data (const char *buffer, size_t buffer_len);

#endif

