#include <stdio.h>
#include <stddef.h>


int utils__utf_8__validate_data (const char *buffer, size_t buffer_len)
{

	size_t i;
	int end;
	unsigned char *b;


	if (buffer == NULL)
	{
		return -100;
	}

	if (buffer_len == 0)
	{
		return -200;
	}


	b = (unsigned char *) buffer;

	end = 0;
	i = 0;

	do
	{
		if (b[i] < 0x80)
		{
			/*
			 * 0xxxxxxx
			 */
			i++;
		}
		else if ((b[i] & 0xE0) == 0xC0)
		{
			if (i + 1 < buffer_len)
			{
				/*
				 * 110xxxxx 10xxxxxx
				 */
				if ((b[i + 1] & 0xC0) != 0x80 ||
					(b[i] & 0xFE) == 0xC0)                        /* overlong? */
				{
					return -300;
				}
				else
				{
					i += 2;
				}
			}
			else
			{
				return -400;
			}
		}
		else if ((b[i] & 0xF0) == 0xE0)
		{
			if (i + 2 < buffer_len)
			{
				/*
				 * 1110xxxx 10Xxxxxx 10xxxxxx
				 */
				if ((b[i + 1] & 0xC0) != 0x80 || (b[i + 2] & 0xC0) != 0x80 || (b[i] == 0xE0 && (b[i + 1] & 0xE0) == 0x80) ||    /* overlong? */
					(b[i] == 0xED && (b[i + 1] & 0xE0) == 0xA0) ||    /* surrogate? */
					(b[i] == 0xEF && b[i + 1] == 0xBF &&
					(b[i + 2] & 0xFE) == 0xBE))                      /* U+FFFE or U+FFFF? */
				{
					return -500;
				}
				else
				{
					i += 3;
				}
			}
			else
			{
				return -600;
			}
		}
		else if ((b[i] & 0xF8) == 0xF0)
		{
			if (i + 3 < buffer_len)
			{
				/*
				 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
				 */
				if ((b[i + 1] & 0xC0) != 0x80 || (b[i + 2] & 0xC0) != 0x80 || (b[i + 3] & 0xC0) != 0x80 ||
					(b[i] == 0xF0 && (b[i + 1] & 0xF0) == 0x80) || (b[i] == 0xF4 && b[i + 1] > 0x8F) || b[i] > 0xF4) /* > U+10FFFF? */
				{
					return -700;
				}
				else
				{
					i += 4;
				}
			}
			else
			{
				return -800;
			}
		}
		else
		{
			return -900;
		}

		if (i >= buffer_len)
		{
			end = 1;
		}

	}
	while (end == 0);


	return 0;

}





#if 0

/*
 * The utf8_check() function scans the '\0'-terminated string starting
 * at s. It returns a pointer to the first byte of the first malformed
 * or overlong UTF-8 sequence found, or NULL if the string contains
 * only correct UTF-8. It also spots UTF-8 sequences that could cause
 * trouble if converted to UTF-16, namely surrogate characters
 * (U+D800..U+DFFF) and non-Unicode positions (U+FFFE..U+FFFF). This
 * routine is very likely to find a malformed sequence if the input
 * uses any other encoding than UTF-8. It therefore can be used as a
 * very effective heuristic for distinguishing between UTF-8 and other
 * encodings.
 *
 * I wrote this code mainly as a specification of functionality; there
 * are no doubt performance optimizations possible for certain CPUs.
 *
 * Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/> -- 2005-03-30
 * License: http://www.cl.cam.ac.uk/~mgk25/short-license.html
 */


#include <stdlib.h>

unsigned char *utf8_check(unsigned char *s)
{
	while (*s) {
		if (*s < 0x80)
			/* 0xxxxxxx */
				s++;
		else if ((s[0] & 0xe0) == 0xc0) {
			/* 110XXXXx 10xxxxxx */
			if ((s[1] & 0xc0) != 0x80 ||
				(s[0] & 0xfe) == 0xc0)                        /* overlong? */
				return s;
			else
				s += 2;
		} else if ((s[0] & 0xf0) == 0xe0) {
			/* 1110XXXX 10Xxxxxx 10xxxxxx */
			if ((s[1] & 0xc0) != 0x80 ||
				(s[2] & 0xc0) != 0x80 ||
				(s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||    /* overlong? */
				(s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||    /* surrogate? */
				(s[0] == 0xef && s[1] == 0xbf &&
				(s[2] & 0xfe) == 0xbe))                      /* U+FFFE or U+FFFF? */
				return s;
			else
				s += 3;
		} else if ((s[0] & 0xf8) == 0xf0) {
			/* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
			if ((s[1] & 0xc0) != 0x80 ||
				(s[2] & 0xc0) != 0x80 ||
				(s[3] & 0xc0) != 0x80 ||
				(s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||    /* overlong? */
				(s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) /* > U+10FFFF? */
				return s;
			else
				s += 4;
		} else
			return s;
	}

	return NULL;
}

#endif

