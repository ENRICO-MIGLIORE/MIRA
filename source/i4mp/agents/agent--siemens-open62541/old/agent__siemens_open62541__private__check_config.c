#include "agent__siemens_open62541__private.h"


int agent__siemens_open62541__private__check_config (void* config)
{
	//size_t i;
	//i4mp__config_t* conf;
	//i4mp__agent_t* i4mp__agent; // size_t agents_max

	if (config == NULL)
	{
		return -100;
	}

	//conf = (i4mp__config_t*) config;

	//if (conf->subagent == NULL)
	//{
	//	return -200;
	//}

	//if (conf->agents_max == 0)
	//{
	//	return -300;
	//}

	//if ((conf->mode != I4MP__FILE_CONFIG_MODE) && (conf->mode != I4MP__BUFFER_CONFIG_MODE))
	//{
	//	return -400;
	//}

	//i4mp__agent = conf->subagent;

	//for (i = 0; i < conf->agents_max; i++)
	//{

	//	if (i4mp__agent[i].name == NULL)
	//	{
	//		return -2000;
	//	}

	//	if (i4mp__agent[i].buffer_size == 0)
	//	{
	//		return -2100;
	//	}

	//	if (i4mp__agent[i].init == NULL)
	//	{
	//		return -2200;
	//	}

	//	if (i4mp__agent[i].config == NULL)
	//	{
	//		return -2300;
	//	}

	//	if (i4mp__agent[i].start == NULL)
	//	{
	//		return -2400;
	//	}
	//}

	return 0;
}

