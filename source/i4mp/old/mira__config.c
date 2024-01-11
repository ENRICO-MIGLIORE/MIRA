#include "mira__private.h"


typedef struct
{
	const char* file_name;
	char* buffer;
	size_t buffer_len;

} mira__agent_config_t;



int mira__config (mira__config_t* config)
{
	int rc;
	int i;
	utils__printf__config_t pf_config;
	mira__agent_config_t mira__agent_config;
	size_t size;
	size_t max_buffer_size;	
	size_t buffer_size;
	char agent_name[256];
	size_t agent_name_len;
	const char* fn;


	fn = "mira__config()";


	rc = mira__private__verify_framework_is_initialized();
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -100, "mira__private__check_configured returned %d", rc);
		return -100;
	}


	rc = mira__private__check_config(config);
	if (rc != 0)
	{
		utils__printf__error(&mira->pf, fn, -200, "mira__private__check_config() returned %d", rc);
		return -200;
	}



	/*
	 * copy the config structure
	 */
	memcpy(&mira->config, config, sizeof(mira__config_t));



	/*
	 * reinitialize the utils__printf subsystem
	 */
	rc = utils__printf__init(&mira->pf);
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -300, "utils__printf__init() error");
		return -300;
	}


	/*
	 * reconfigure the utils__printf subsystem
	 */
	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = mira->config.enable_printf;
	pf_config.enable_log_file = mira->config.enable_log_file;
	pf_config.log_file_name = mira->config.log_file_name;
	pf_config.log_file_name_len = strlen(mira->config.log_file_name);
	pf_config.max_log_file_lines_per_minute = 120;
	pf_config.enable_table_layout_output = mira->config.enable_table_layout_output;
	pf_config.enable_application_name_on_output = 1;
	pf_config.application_name = mira->application_name;
	pf_config.application_name_len = strlen(mira->application_name);

	rc = utils__printf__config(&mira->pf, &pf_config);
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -400, "utils__printf__config() returned %d", rc);
		return -400;
	}



	/*
	 * allocate an array of integers
	 */
	size = sizeof(int) * mira->config.agents_max;
	mira->number_of_machines_per_agent = (int*)malloc(size);
	if (mira->number_of_machines_per_agent == NULL)
	{
		utils__printf__error(&mira->pf, fn, -500, "mira__private__check_config() returned %d", rc);
		return -500;
	}

	
	memset(mira->number_of_machines_per_agent, 0, size);



	/*
	 * call i4_agency' init() function
	 */
	for (i = 0; i < mira->config.agents_max; i++)
	{
		rc = mira->config.i4_agency[i].init();
		if (rc != 0)
		{			
			rc = mira->config.i4_agency[i].get_agent_name(agent_name, sizeof(agent_name), &agent_name_len);
			if (rc == 0)
			{
				utils__printf__error(&mira->pf, fn, -700, "init() function of agent %s returned %d - rc = %d", agent_name, rc);
			}
			else
			{
				utils__printf__error(&mira->pf, fn, -700, "init() function of agent %d returned %d - rc = %d", i, rc);
			}			
			return -700;
		}
	}


	/*
	 * find the maximum buffer size among the i4_agency
	 */
	max_buffer_size = 0;
	for (i = 0; i < mira->config.agents_max; i++)
	{
		rc = mira->config.i4_agency[i].get_agent_buffer_size(&buffer_size);
		if ((rc == 0) && (buffer_size > max_buffer_size))
		{
			max_buffer_size = buffer_size;
		}
	}

	if (max_buffer_size == 0)
	{
		utils__printf__error(&mira->pf, fn, -600, "max_buffer_size is zero");
		return -600;
	}

	mira->buffer = (char*)malloc(max_buffer_size);
	if (mira->buffer == NULL)
	{
		utils__printf__error(&mira->pf, fn, -600, "buffer malloc() returned null - max_buffer_size = %zu", max_buffer_size);
		return -600;
	}
	mira->buffer_size = max_buffer_size;
	
	/*
	 * call i4_agency' config() function
	 */
	for (i = 0; i < mira->config.agents_max; i++)
	{		
		memset(&mira__agent_config, 0, sizeof(mira__agent_config));

		mira__agent_config.file_name = mira->config.i4_agency[i].config_file_name;
		mira__agent_config.buffer = mira->config.i4_agency[i].config_buffer;
		mira__agent_config.buffer_len = mira->config.i4_agency[i].config_buffer_len;

		rc = mira->config.i4_agency[i].config((void*)&mira__agent_config);
		if (rc != 0)
		{
			rc = mira->config.i4_agency[i].get_agent_name(agent_name, sizeof(agent_name), &agent_name_len);
			if (rc == 0)
			{
				utils__printf__error(&mira->pf, fn, -700, "config() function of agent %s returned %d - rc = %d", agent_name, rc);
			}
			else
			{
				utils__printf__error(&mira->pf, fn, -700, "config() function of agent %d returned %d - rc = %d", i, rc);
			}
			return -800;
		}
	}

	mira->configured = 1;

	return 0;
}
