#include "utils__sdb.h"


int utils__sdb__config (utils__sdb_t *sdb, utils__sdb__config_t *config)
{

	if (sdb == NULL)
	{
		return -10;
	}

	if (config->buffer == NULL)
	{
		return -20;
	}

	if (config->buffer_size == 0)
	{
		return -30;
	}

	if (config->name == NULL)
	{
		return -40;
	}

	if (config->value == NULL)
	{
		return -50;
	}

	if (config->name_len == NULL)
	{
		return -60;
	}

	if (config->value_len == NULL)
	{
		return -70;
	}

	if (config->encoding == NULL)
	{
		return -80;
	}



	sdb->buffer = config->buffer;
	sdb->buffer_size = config->buffer_size;
	sdb->buffer_len = 0;

	sdb->num_fields = 0;
	sdb->fields_max = config->fields_max;
	
	sdb->name = config->name;
	sdb->value = config->value;
	sdb->name_len = config->name_len;
	sdb->value_len = config->value_len;

	sdb->encoding = config->encoding;
	
	sdb->end_of_record_signature = -1;

	sdb->configured = 1;

	return 0;
}




