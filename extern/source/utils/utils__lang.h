#ifndef UTILS__LANG_H
#define UTILS__LANG_H


#include <stddef.h>
#include <string.h>
#include <stdio.h>


typedef struct
{
	size_t *word_len;
	char **word;
	size_t word_count;

} utils__lang__language_t;


typedef struct
{
	utils__lang__language_t *language;
	size_t language_count;

} utils__lang__dictionary_t;


typedef struct  
{
	utils__lang__dictionary_t *dictionary;
	size_t dictionary_count;

} utils__lang__config_t;


int utils__lang__init (void);
int utils__lang__config (utils__lang__config_t *config);
char * utils__lang__get_word (size_t dictionary, size_t language, size_t word);

int utils__lang__print_dictionary(size_t dictionary, size_t language);

#endif