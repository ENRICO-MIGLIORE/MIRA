#ifndef UTILS__LIBC_H
#define UTILS__LIBC_H


#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>



int utils__libc__atoi(const char* buffer, size_t buffer_len, int* number);
int utils__libc__atost(const char* buffer, size_t buffer_len, size_t* number);
int utils__libc__atoul(const char* buffer, size_t buffer_len, unsigned long* number);
int utils__libc__atod(const char* buffer, size_t buffer_len, double* number);
int utils__libc__itoa(int n, char* buffer, size_t buffer_size, size_t* buffer_len);   /* needed by utils__printf() */
int utils__libc__ltoa(long n, char* buffer, size_t buffer_size, size_t* buffer_len);
int utils__libc__stoa(short n, char* buffer, size_t buffer_size, size_t* buffer_len);
int utils__libc__ultoa(unsigned long n, char* buffer, size_t buffer_size, size_t* buffer_len);
int utils__libc__ustoa(unsigned short n, char* buffer, size_t buffer_size, size_t* buffer_len);
int utils__libc__sttoa(size_t n, char* buffer, size_t buffer_size, size_t* buffer_len);


char* utils__libc__strnchr(const char* buffer, size_t buffer_len, char c);
char* utils__libc__strstr(const char* buffer, size_t buffer_len, const char* buffer_2, size_t buffer_2_len);
int utils__libc__tokenize_string(const char* buffer, size_t buffer_len, const char** seps, size_t* seps_len, size_t seps_count, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count);
int utils__libc__trim_tokens(char** tokens, size_t* tokens_len, size_t tokens_max, char c);
int utils__libc__trim_string (char *buffer, size_t buffer_len, size_t *trimmed_buffer_len, char c);
int utils__libc__compact_spaces (char *buffer, size_t buffer_len, size_t *trimmed_buffer_len);
int utils__libc__count_trimmeable_characters (char *buffer, size_t buffer_len, size_t *trimmeable_space_count, char c);
int utils__libc__unescape_buffer(char* buffer, size_t buffer_len, const char* escape_sequence, size_t escape_sequence_len, char c, size_t* buffer_new_len);

int utils__libc__print_tokens(char** tokens, size_t* tokens_len, size_t token_count);

/*
 * validate
 */
int utils__libc__validate_ipv4_address (const char *buffer, size_t buffer_len);
int utils__libc__validate_unsigned_long_number(const char* buffer, size_t buffer_len);
int utils__libc__validate_size_t_number(const char* buffer, size_t buffer_len);
int utils__libc__validate_int_number(const char* buffer, size_t buffer_len);


int utils__libc__build_url_buffer (char *buffer, size_t buffer_size, size_t *buffer_len, char **name, size_t *name_len, char **value, size_t *value_len, size_t pair_count, const char *forbidden_charset);
int utils__libc__copy_buffer (char *buffer, size_t buffer_size, size_t *buffer_len, char *buffer_2, size_t buffer_2_len);

int utils__libc__check_for_duplicate_names(const char** names, const size_t* names_len, size_t names_count);
int utils__libc__check_doubles_for_equality(double n1, double n2, double tolerance);
int utils__libc__convert_utf8_data_to_percent_encoded_data(char* buffer, size_t buffer_len, size_t buffer_size_residual, size_t* buffer_new_len);



int utils__libc__write_option(char* buffer, size_t buffer_size, const char* value, size_t value_len, const char* option_1, size_t option_1_len, const char* option_2, size_t option_2_len);
int utils__libc__write_string(char* buffer, size_t buffer_size, const char* value, size_t value_len);
int utils__libc__write_yes_or_no(int* config_2, const char* value, size_t value_len);
int utils__libc__write_size_t(size_t* config_2, const char* value, size_t value_len);
int utils__libc__write_double(double* config_2, const char* value, size_t value_len);
int utils__libc__write_int(int* config_2, const char* value, size_t value_len);

#endif