#include "fanuc_focas__private.h"
#include "fanuc_focas.h"


static char *fn = "fanuc_focas__config()";


int fanuc_focas__config (fanuc_focas__config_t* config)
{

	int rc;
	int i;
	size_t len;
	utils__sdb__config_t sdb_config;
	utils__printf__config_t pf_config;
	size_t application_section_count;
	size_t machines_section_count;

	if (config == NULL)
	{
		return -100;
	}

	ff->agent_configuration_file_name[0] = '\0';

	if (config->mode == 0)
	{

		len = strlen(config->file_name);

		if (len >= sizeof(ff->agent_configuration_file_name))
		{
			utils__printf__error(&ff->pf, fn, -200, "the configuration file name is too long");
			return -200;
		}

		memcpy(ff->agent_configuration_file_name, config->file_name, len);
		ff->agent_configuration_file_name[len] = '\0';
	}
	else if (config->mode == 1)
	{
		;
	}
	else if (config->mode == 2)
	{
		len = strlen(ff->agent_default_configuration_file_name);

		if (len >= sizeof(ff->agent_configuration_file_name))
		{
			utils__printf__error(&ff->pf, fn, -300, "the default configuration file name is too long");
			return -300;
		}

		memcpy(ff->agent_configuration_file_name, ff->agent_default_configuration_file_name, len);
		ff->agent_configuration_file_name[len] = '\0';
	}
	else
	{
		utils__printf__error(&ff->pf, fn, -400, "mode must be: 0, 1, or 2");
		return -400;
	}

	ff->config_mode = config->mode;


	(void)utils__sdb__init(&ff->sdb);

	memset(&sdb_config, 0, sizeof(sdb_config));

	sdb_config.buffer = ff->sdb_buffer;
	sdb_config.buffer_size = sizeof(ff->sdb_buffer);
	sdb_config.name = ff->sdb_name;
	sdb_config.name_len = ff->sdb_name_len;
	sdb_config.value = ff->sdb_value;
	sdb_config.value_len = ff->sdb_value_len;
	sdb_config.encoding = ff->sdb_encoding;
	sdb_config.fields_max = FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX;

	rc = utils__sdb__config(&ff->sdb, &sdb_config);
	if (rc != 0)
	{
		utils__printf__error(&ff->pf, fn, -500, "utils__sdb__config() returned %d", rc);
		return -500;
	}


	/*
	 * null the configuration structure
	 */
	memset(&ff->config, 0, sizeof(fanuc_focas__application_settings_t));

	/*
	 * read the configuration file or buffer and extract data for the agent
	 */
	rc = fanuc_focas__private__load_application_configuration(&application_section_count);
	if (rc != 0)
	{
		utils__printf__error(&ff->pf, fn, -600, "fanuc_focas__private__load_application_configuration() returned %d", rc);
		return -600;
	}


	if (application_section_count == 0)
	{
		ff->machine_count = 0;
		utils__printf__info(&ff->pf, fn, 0, "can't find section [%s] in config file - no machines loaded", ff->agent_section_name);
	}
	else
	{
		/*
		 * read the configuration file or buffer and extract data for the machines
		 */
		rc = fanuc_focas__private__load_machines_configuration(&machines_section_count);
		if (rc != 0)
		{
			utils__printf__error(&ff->pf, fn, -700, "fanuc_focas__private__load_machines_configuration() returned % d", rc);
			return -700;
		}

		if (machines_section_count == 0)
		{
			ff->machine_count = 0;
			utils__printf__info(&ff->pf, fn, 0, "can't find section [%s] in config file - no machines loaded", ff->machines_section_name);
		}
	}




	/*
	 * reconfigure the printf subsystem with user's data contained in the configuration file
	 */
	rc = utils__printf__init(&ff->pf);
	if (rc != 0)
	{
		utils__printf__error(&ff->pf, fn, -800, "utils__printf__init() returned %d", rc);
		return -800;
	}


	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = ff->config.enable_printf;
	pf_config.enable_log_file = ff->config.enable_log_file;
	pf_config.log_file_name = ff->config.log_file_name;
	pf_config.log_file_name_len = strlen(ff->config.log_file_name);
	pf_config.max_log_file_lines_per_minute = ff->config.max_log_file_lines_per_minute;
	pf_config.enable_table_layout_output = ff->config.enable_table_layout_output;
	pf_config.enable_application_name_on_output = ff->config.enable_application_name_on_output;
	pf_config.application_name = ff->agent_name_and_version;
	pf_config.application_name_len = strlen(ff->agent_name_and_version);


	rc = utils__printf__config(&ff->pf, &pf_config);
	if (rc != 0)
	{
		utils__printf__error(&ff->pf, fn, -900, "utils__printf__config() returned %d", rc);
		return -900;
	}


	for (i = 0; i < ff->machine_count; i++)
	{
		if (ff->machine[i].config.simulated == 1)
		{

			ff->machine[i].read_connection_status = fanuc_focas__private__read_connection_status__simulated;
			ff->machine[i].read_production_status = fanuc_focas__private__read_production_status__simulated;
			ff->machine[i].read_alarm_status = fanuc_focas__private__read_alarm_status__simulated;
			ff->machine[i].read_part_counter = fanuc_focas__private__read_part_counter__simulated;
			ff->machine[i].read_part_program_name = fanuc_focas__private__read_part_program_name__simulated;

		}
		else
		{

			ff->machine[i].read_connection_status = fanuc_focas__private__read_connection_status__real;
			ff->machine[i].read_production_status = fanuc_focas__private__read_production_status__real;
			ff->machine[i].read_alarm_status = fanuc_focas__private__read_alarm_status__real;
			ff->machine[i].read_part_counter = fanuc_focas__private__read_part_counter__real;			
			ff->machine[i].read_part_program_name = fanuc_focas__private__read_part_program_name__real;

		}
	}



	for (i = 0; i < ff->machine_count; i++)
	{
		ff->machine[i].connection_status = 0;
		ff->machine[i].part_counter_simulated = ff->machine[i].config.part_counter_initial_value_in_simulation_mode;
		ff->machine[i].cycle_time_simulated = ff->machine[i].config.average_cycle_time_in_simulation_mode_seconds;
	}


	ff->configured = 1;


	return 0;
}

