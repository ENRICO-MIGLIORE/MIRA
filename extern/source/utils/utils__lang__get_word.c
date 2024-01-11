#include "utils__lang.h"
#include "utils__lang__private.h"


char * utils__lang__get_word (size_t dictionary, size_t language, size_t word)
{
	char **w;
	utils__lang__language_t *l;
	utils__lang__dictionary_t *d;
	

	if (lang.configured == 0)
	{
		return NULL;
	}

	if (dictionary >= lang.config.dictionary_count)
	{
		return NULL;
	}

	d = lang.config.dictionary;
	d += dictionary;

	if (dictionary >= d->language_count)
	{
		return NULL;
	}

	l = d->language;
	l += language;

	if (word >= l->word_count)
	{
		return NULL;
	}
	
	w = l->word;	
	w += word;

	return *w;
	
}
