#ifndef UTILS__PERCENT_ENCODING_H
#define UTILS__PERCENT_ENCODING_H

#include <stddef.h>

int utils__percent_encoding__encode (const char *reserved_characters, const char *buffer_in, size_t buffer_in_len, char *buffer_out, size_t buffer_out_size, size_t* buffer_out_len);
int utils__percent_encoding__encode_strict (const char *buffer_in, size_t buffer_in_len, char *buffer_out, size_t buffer_out_size, size_t*buffer_out_len);
int utils__percent_encoding__decode_data_strict (char *buffer, size_t buffer_len, size_t*buffer_new_len);
int utils__percent_encoding__decode__data (char *buffer, size_t buffer_len, size_t*buffer_new_len);

#endif

