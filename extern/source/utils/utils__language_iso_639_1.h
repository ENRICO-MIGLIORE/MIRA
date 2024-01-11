#ifndef UTILS__LANGUAGE_ISO_639_1__H
#define UTILS__LANGUAGE_ISO_639_1__H

#include <stddef.h>


#define UTILS__LANGUAGE_ISO_639_1__CODE_LEN         2


int utils__language_iso_639_1__validate_code (const char *code, size_t code_len);


#endif