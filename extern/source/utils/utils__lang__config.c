#include "utils__lang.h"
#include "utils__lang__private.h"


int utils__lang__config (utils__lang__config_t *config)
{

	if (config == NULL)
	{
		return -10;
	}

	if (config->dictionary == NULL)
	{
		return -20;
	}

	if (config->dictionary_count == 0)
	{
		return -30;
	}

	if (config->dictionary->language == NULL)
	{
		return -40;
	}

	if (config->dictionary->language_count == 0)
	{
		return -50;
	}
	
	memcpy(&lang.config, config, sizeof(utils__lang__config_t));

	lang.configured = 1;

	return 0;
}

