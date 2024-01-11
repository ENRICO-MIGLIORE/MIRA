#include "okuma_mt__private.h"
#include "okuma_mt.h"


static char *fn = "okuma_mt__config()";


int okuma_mt__config (okuma_mt__config_t* config)
{

	int rc;
	int i;
	size_t len;
	utils__sdb__config_t sdb_config;
	utils__printf__config_t pf_config;


	if (config == NULL)
	{
		return -100;
	}

	om->agent_configuration_file_name[0] = '\0';

	if (config->mode == 0)
	{

		len = strlen(config->file_name);

		if (len >= sizeof(om->agent_configuration_file_name))
		{
			utils__printf__error(&om->pf, fn, -200, "the configuration file name is too long", fn);
			return -200;
		}

		memcpy(om->agent_configuration_file_name, config->file_name, len);
		om->agent_configuration_file_name[len] = '\0';
	}
	else if (config->mode == 1)
	{
		;
	}
	else if (config->mode == 2)
	{
		len = strlen(om->agent_default_configuration_file_name);

		if (len >= sizeof(om->agent_configuration_file_name))
		{
			utils__printf__error(&om->pf, fn, -200, "the default configuration file name is too long", fn);
			return -300;
		}

		memcpy(om->agent_configuration_file_name, om->agent_default_configuration_file_name, len);
		om->agent_configuration_file_name[len] = '\0';
	}
	else
	{
		utils__printf__error(&om->pf, fn, -300, "mode must be: 0, 1, or 2", fn);
		return -400;
	}

	om->config_mode = config->mode;


	(void)utils__sdb__init(&om->sdb);

	memset(&sdb_config, 0, sizeof(sdb_config));

	sdb_config.buffer = om->sdb_buffer;
	sdb_config.buffer_size = sizeof(om->sdb_buffer);
	sdb_config.name = om->sdb_name;
	sdb_config.name_len = om->sdb_name_len;
	sdb_config.value = om->sdb_value;
	sdb_config.value_len = om->sdb_value_len;
	sdb_config.encoding = om->sdb_encoding;
	sdb_config.fields_max = OKUMA_MT__CONFIG__SDB_FIELDS_MAX;

	rc = utils__sdb__config(&om->sdb, &sdb_config);
	if (rc != 0)
	{
		utils__printf__error(&om->pf, fn, -100, "utils__sdb__config() returned %d", fn, rc);
		return -500;
	}


	/*
	 * null the configuration structure
	 */
	memset(&om->config, 0, sizeof(okuma_mt__application_settings_t));

	/*
	 * read the configuration file or buffer and extract data for the agent
	 */
	rc = okuma_mt__private__load_application_configuration();
	if (rc != 0)
	{
		printf("%s - error - okuma_mt__private__load_application_configuration() returned %d\n", fn, rc);
		return -1000;
	}


	/*
	 * read the configuration file or buffer and extract data for the machines
	 */
	rc = okuma_mt__private__load_machines_configuration();
	if (rc != 0)
	{
		printf("%s - error - okuma_mt__private__load_machines_configuration() returned %d\n", fn, rc);
		return -1100;
	}



	/*
	 * reconfigure the printf subsystem with user's data contained in the configuration file
	 */
	rc = utils__printf__init(&om->pf);
	if (rc != 0)
	{
		utils__printf__error(&om->pf, fn, -300, "utils__printf__init() returned %d", fn, rc);
		return -1200;
	}


	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = om->config.enable_printf;
	pf_config.enable_log_file = om->config.enable_log_file;
	pf_config.log_file_name = om->config.log_file_name;
	pf_config.log_file_name_len = strlen(om->config.log_file_name);
	pf_config.max_log_file_lines_per_minute = om->config.max_log_file_lines_per_minute;
	pf_config.enable_table_layout_output = om->config.enable_table_layout_output;
	pf_config.enable_application_name_on_output = om->config.enable_application_name_on_output;
	pf_config.application_name = om->agent_name_and_version;
	pf_config.application_name_len = strlen(om->agent_name_and_version);


	rc = utils__printf__config(&om->pf, &pf_config);
	if (rc != 0)
	{
		utils__printf__error(&om->pf, fn, -400, "utils__printf__config() returned %d", fn, rc);
		return -1300;
	}


	for (i = 0; i < om->machine_count; i++)
	{
		if (om->machine[i].config.simulated == 1)
		{

			om->machine[i].read_connection_status = okuma_mt__private__read_connection_status__simulated;
			om->machine[i].read_production_status = okuma_mt__private__read_production_status__simulated;
			om->machine[i].read_alarm_status = okuma_mt__private__read_alarm_status__simulated;
			om->machine[i].read_part_counter = okuma_mt__private__read_part_counter__simulated;
			om->machine[i].read_part_program_name = okuma_mt__private__read_part_program_name__simulated;

		}
		else
		{

			om->machine[i].read_connection_status = okuma_mt__private__read_connection_status__real;
			om->machine[i].read_production_status = okuma_mt__private__read_production_status__real;
			om->machine[i].read_alarm_status = okuma_mt__private__read_alarm_status__real;
			om->machine[i].read_part_counter = okuma_mt__private__read_part_counter__real;			
			om->machine[i].read_part_program_name = okuma_mt__private__read_part_program_name__real;

		}
	}



	for (i = 0; i < om->machine_count; i++)
	{
		om->machine[i].connection_status = 0;
		om->machine[i].part_counter_simulated = om->machine[i].config.part_counter_initial_value_in_simulation_mode;
		om->machine[i].cycle_time_simulated = om->machine[i].config.average_cycle_time_in_simulation_mode_seconds;
	}


	om->configured = 1;


	return 0;
}

