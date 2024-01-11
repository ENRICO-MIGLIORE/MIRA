#ifndef UTILS__BASE_64_H
#define UTILS__BASE_64_H


#include <stddef.h>


int utils__base_64__encode (unsigned char *destination, size_t destination_size, size_t *destination_len, const unsigned char *source, size_t source_len);
int utils__base_64__decode (unsigned char *destination, size_t destination_size, size_t *destination_len, const char *source, size_t source_len);
size_t utils__base_64__get_size_of_encoded_buffer (size_t source_len);

#endif
