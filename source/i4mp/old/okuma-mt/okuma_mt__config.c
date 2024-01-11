#include "okuma_mt__private.h"


static char *fn = "okuma_mt__config()";


int okuma_mt__config (void)
{

	int rc;
	int i;
	utils__sdb__config_t sdb_config;
	utils__printf__config_t pf_config;


	(void) utils__sdb__init(&om->sdb);

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
		return -100;
	}


	rc = okuma_mt__private__load_configuration_file();
	if (rc != 0)
	{		
		utils__printf__error(&om->pf, fn, -200, "okuma_mt__private__load_configuration_file() returned %d", fn, rc);
		return -200;
	}


	/*
	 * reconfigure the printf subsystem with user's data contained in the configuration file
	 */
	rc = utils__printf__init(&om->pf);
	if (rc != 0)
	{		
		utils__printf__error(&om->pf, fn, -300, "utils__printf__init() returned %d", fn, rc);
		return -300;
	}


	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = om->config.enable_printf;
	pf_config.enable_log_file = om->config.enable_log_file;
	pf_config.log_file_name = om->config.log_file_name;
	pf_config.log_file_name_len = strlen(om->config.log_file_name);
	pf_config.max_log_file_lines_per_minute = om->config.max_log_file_lines_per_minute;
	pf_config.enable_table_layout_output = om->config.enable_table_layout_output;
	pf_config.enable_application_name_on_output = om->config.enable_application_name_on_output;
	pf_config.agent_name = om->agent_name_and_version;
	pf_config.application_name_len = strlen(om->agent_name_and_version);


	rc = utils__printf__config(&om->pf, &pf_config);
	if (rc != 0)
	{		
		utils__printf__error(&om->pf, fn, -400, "utils__printf__config() returned %d", fn, rc);
		return -400;
	}


	rc = okuma_mt__private__attach_stub_functions();
	if (rc != 0)
	{
		utils__printf__error(&om->pf, fn, -500, "okuma_mt__private__attach_stub_functions() returned %d", fn, rc);
		return -500;
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