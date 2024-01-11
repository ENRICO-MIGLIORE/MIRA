#include "mira__private.h"


int mira__private__verify_framework_is_initialized (void)
{
	if (mira == NULL)
	{
		return -100;
	}

	if (mira->initialized != 1)
	{
		return -200;
	}

	return 0;
}


int mira__private__verify_framework_is_configured (void)
{
	if (mira == NULL)
	{
		return -100;
	}

	if (mira->configured != 1)
	{
		return -200;
	}

	return 0;
}


int mira__private__verify_framework_is_started (void)
{
	if (mira == NULL)
	{
		return -100;
	}

	if (mira->started != 1)
	{
		return -200;
	}

	return 0;
}



int mira__private__check_config (mira__config_t* config)
{
	size_t i;
	mira__agent_t* i4mp__agent;


	if (mira == NULL)
	{
		return -10000;
	}

	if (config == NULL)
	{
		return -100;
	}

	if (config->i4_agency == NULL)
	{
		return -200;
	}

	if (config->agents_max == 0)
	{
		return -300;
	}

	//if ((config->agent_config_mode != I4MP__AGENT__FILE_CONFIG_MODE) && (config->agent_config_mode != I4MP__AGENT__BUFFER_CONFIG_MODE))
	//{
	//	return -400;
	//}

	i4mp__agent = config->i4_agency;

	for (i = 0; i < config->agents_max; i++)
	{

		//if (i4mp__agent[i].name == NULL)
		//{
		//	return -2000;
		//}

		//if (i4mp__agent[i].agent_buffer_size == 0)
		//{
		//	return -2100;
		//}

		if (i4mp__agent[i].init == NULL)
		{
			return -2200;
		}

		if (i4mp__agent[i].config == NULL)
		{
			return -2300;
		}

		if (i4mp__agent[i].start == NULL)
		{
			return -2400;
		}
	}

	return 0;
}

