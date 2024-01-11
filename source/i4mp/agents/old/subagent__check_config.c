#include "subagent.h"


int subagent__check_config (subagent__machine__config_t* config)
{
	//size_t i;
	size_t len;
	const char* fn = "subagent__check_config()";


	fn = "delegate__private__check_config()";
	//delegate_config_t* conf;

	if (config == NULL)
	{		
		utils__printf__error(NULL, fn, -100, "config is null");
		return -100;
	}

	//conf = (delegate_config_t*) config;


	//if (config->mode == MACHINE__FILE_CONFIG_MODE)
	if (1 == 1)
	{
		//if (config->file_name == NULL)
		if (1 == 1)
		{
			utils__printf__error(NULL, fn, -200, "config file name is null");			
			return -200;
		}

		//len = strlen(config->file_name);
		len = 0;

		if (len == 0)
		{
			utils__printf__error(NULL, fn, -300, "file name len is zero");
			return -300;
		}

		//memcpy(delegate->config.config_file_name, config->secondary.file_name, len);
		//delegate->config.config_file_name[len] = '\0';
	}
	//else if (config->mode == MACHINE__BUFFER_CONFIG_MODE)
	else if (2 > 1)
	{
		//if ((config->buffer == NULL) || (config->buffer_len == 0))
		if (1 == 1)
		{
			utils__printf__error(NULL, fn, -400, "config buffer is null or buffer len is zero");
			return -400;
		}

	/*	delegate->config.secondary.buffer = config->secondary.buffer;
		delegate->config.secondary.buffer_len = config->secondary.buffer_len;*/

		//len = strlen(delegate->default_configuration_file_name);

		//if (len >= sizeof(delegate->settings_file_name))
		//{
		//	utils__printf__error(&delegate->pf, fn, -1100, "the default configuration file name is too long");
		//	return -1100;
		//}

		//memcpy(delegate->settings_file_name, delegate->default_configuration_file_name, len);
		//delegate->settings_file_name[len] = '\0';
	}
	else
	{
		utils__printf__error(NULL, fn, -500, "config mode must be: 0, 1");		
		return -500;
	}


	//char* file_name;
	//char* buffer;
	//size_t buffer_len;
	//int mode;

	//if (config->option == 0)
	//{

	//}
	//else
	//{

	//}

	//if (config->delegate == NULL)
	//{
	//	return -200;
	//}

	//if (config->agents_max == 0)
	//{
	//	return -300;
	//}


	//i4mp__agent = config->delegate;

	//for (i = 0; i < config->agents_max; i++)
	//{

	//	if (i4mp__agent[i].name == NULL)
	//	{
	//		return -1000;
	//	}

	//	if (i4mp__agent[i].buffer_size == 0)
	//	{
	//		return -1100;
	//	}

	//	if (i4mp__agent[i].init == NULL)
	//	{
	//		return -2000;
	//	}

	//	if (i4mp__agent[i].config == NULL)
	//	{
	//		return -2100;
	//	}

	//	if (i4mp__agent[i].start == NULL)
	//	{
	//		return -2200;
	//	}
	//}

	return 0;
}

