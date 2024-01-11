#include <stdio.h>
#include <string.h>
#include <stddef.h>


#include "utils__language_iso_639_1.h"


static char *utils__language_iso_639_1_codes[] = {"ab", "aa", "af", "ak", "sq", "am", "ar", "an",
	                                              "hy", "as", "av", "ae", "ay", "az", "bm", "ba",
	                                              "en", "de", "fr", "it", "es", "ru", "zz", "zz",
	                                              "eu", "be", "bn", "bh", "bi", "bs", "br", "bg",
	                                              "my", "ca", "ch", "ce", "ny", "zh", "cv", "kw"};


int utils__language_iso_639_1__validate_code (const char *code, size_t code_len)
{
	size_t i;
	int rc;
	size_t code_count;


	if (code == NULL)
	{
		return -10;
	}

	if (code_len != UTILS__LANGUAGE_ISO_639_1__CODE_LEN)
	{
		return -20;
	}

	code_count = sizeof (utils__language_iso_639_1_codes) / sizeof (char *);

	for (i = 0; i < code_count; i++)
	{
		rc = memcmp(code, utils__language_iso_639_1_codes[i], UTILS__LANGUAGE_ISO_639_1__CODE_LEN);
		if (rc == 0)
		{
			return 0;
		}
	}

	return -100;
}





