#include <stdio.h>


#include "utils__lang.h"
#include "utils__lang__private.h"


int utils__lang__print_dictionary (size_t dictionary, size_t language)
{
	size_t i;
	char **w;
	utils__lang__language_t *l;
	utils__lang__dictionary_t *d;
	size_t *len;

	d = lang.config.dictionary;
	d += dictionary;


	l = d->language;
	l += language;


	w = l->word;
	len = l->word_len;
	
	for (i = 0; i < l->word_count; i++)
	{
		printf ("%s\n", *w);
		w++;
	}

	printf ("\n\n");

	for (i = 0; i < l->word_count; i++)
	{
		printf ("%zu\n", *len);
		len++;
	}

	printf ("-------------------------------------------------------\n");

	return 0;
}


