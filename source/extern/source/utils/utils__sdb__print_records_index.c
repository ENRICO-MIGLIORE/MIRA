#include <stdio.h>


int utils__sdb__print_records_index (const char *file_name, size_t *record_index, size_t record_index_max)
{
	FILE *f;
	char c;
	size_t i;

	if (record_index == NULL)
	{
		return -10;
	}

	if (record_index_max == 0)
	{
		return -20;
	}

	if (file_name == NULL)
	{
		return -30;
	}

	f = fopen ((const char *) file_name, "rb");
	if (f == NULL)
	{
		return -40;
	}

	for (i = 0; i < record_index_max; i++)
	{
		fseek(f, (long) record_index[i], SEEK_SET);

		fread(&c, 1, 1, f);

		printf("%c\n", c);
	}
	
	fclose(f);

	return 0;
}
