#include "siemens_open62541__private.h"
#include "siemens_open62541.h"


static char *fn = "siemens_open62541__config()";


int siemens_open62541__config (siemens_open62541_config_t* config)
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

	so->agent_configuration_file_name[0] = '\0';

	if (config->mode == 0)
	{
		
		len = strlen(config->file_name);

		if (len >= sizeof(so->agent_configuration_file_name))
		{
			utils__printf__error(&so->pf, fn, -200, "the configuration file name is too long", fn);
			return -200;
		}

		memcpy(so->agent_configuration_file_name, config->file_name, len);
		so->agent_configuration_file_name[len] = '\0';
	}
	else if (config->mode == 1)
	{
		;
	}
	else if (config->mode == 2)
	{
		len = strlen(so->agent_default_configuration_file_name);

		if (len >= sizeof(so->agent_configuration_file_name))
		{
			utils__printf__error(&so->pf, fn, -200, "the default configuration file name is too long", fn);
			return -300;
		}

		memcpy(so->agent_configuration_file_name, so->agent_default_configuration_file_name, len);
		so->agent_configuration_file_name[len] = '\0';
	}
	else
	{
		utils__printf__error(&so->pf, fn, -300, "mode must be: 0, 1, or 2", fn);
		return -400;
	}
	
	so->config_mode = config->mode;


	(void)utils__sdb__init(&so->sdb);

	memset(&sdb_config, 0, sizeof(sdb_config));

	sdb_config.buffer = so->sdb_buffer;
	sdb_config.buffer_size = sizeof(so->sdb_buffer);
	sdb_config.name = so->sdb_name;
	sdb_config.name_len = so->sdb_name_len;
	sdb_config.value = so->sdb_value;
	sdb_config.value_len = so->sdb_value_len;
	sdb_config.encoding = so->sdb_encoding;
	sdb_config.fields_max = SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX;

	rc = utils__sdb__config(&so->sdb, &sdb_config);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -100, "utils__sdb__config() returned %d", fn, rc);
		return -2000;
	}


	rc = siemens_open62541__private__load_configuration();
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -200, "siemens_open62541__private__load_configuration() returned %d", rc);
		return -2100;
	}


	/*
	 * reconfigure the printf subsystem with user's data contained in the configuration file
	 */
	rc = utils__printf__init(&so->pf);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -300, "utils__printf__init() returned %d", fn, rc);
		return -2200;
	}


	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = so->config.enable_printf;
	pf_config.enable_log_file = so->config.enable_log_file;
	pf_config.log_file_name = so->config.log_file_name;
	pf_config.log_file_name_len = strlen(so->config.log_file_name);
	pf_config.max_log_file_lines_per_minute = so->config.max_log_file_lines_per_minute;
	pf_config.enable_table_layout_output = so->config.enable_table_layout_output;
	pf_config.enable_application_name_on_output = so->config.enable_application_name_on_output;
	pf_config.agent_name = so->agent_name_and_version;
	pf_config.application_name_len = strlen(so->agent_name_and_version);


	rc = utils__printf__config(&so->pf, &pf_config);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -400, "utils__printf__config() returned %d", fn, rc);
		return -2300;
	}


	for (i = 0; i < so->machine_count; i++)
	{
		if (so->machine[i].config.simulation_mode == 1)
		{
			so->machine[i].allocate_machine_resources = siemens_open62541__private__allocate_machines_resources__simulated;
			so->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__simulated;
			so->machine[i].reconnect_to_machine = siemens_open62541__private__disconnect_from_machine__simulated;
			so->machine[i].reconnect_to_machine = siemens_open62541__private__reconnect_to_machine__simulated;
			so->machine[i].read_machine_connection_status = siemens_open62541__private__read_connection_status__simulated;
			so->machine[i].read_machine_production_status = siemens_open62541__private__read_production_status__simulated;
			so->machine[i].read_part_counter = siemens_open62541__private__read_part_counter__simulated;
			so->machine[i].read_cycle_time = siemens_open62541__private__read_cycle_time__simulated;
			so->machine[i].read_part_program_name = siemens_open62541__private__read_part_program_name__simulated;

		}
		else
		{
			so->machine[i].allocate_machine_resources = siemens_open62541__private__allocate_machines_resources__real;
			so->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__real;
			so->machine[i].reconnect_to_machine = siemens_open62541__private__disconnect_from_machine__real;
			so->machine[i].reconnect_to_machine = siemens_open62541__private__reconnect_to_machine__real;
			so->machine[i].read_machine_connection_status = siemens_open62541__private__read_connection_status__real;
			so->machine[i].read_machine_production_status = siemens_open62541__private__read_production_status__real;
			so->machine[i].read_part_counter = siemens_open62541__private__read_part_counter__real;
			so->machine[i].read_cycle_time = siemens_open62541__private__read_cycle_time__real;
			so->machine[i].read_part_program_name = siemens_open62541__private__read_part_program_name__real;
		}
	}



	for (i = 0; i < so->machine_count; i++)
	{
		so->machine[i].connection_status = 0;
		so->machine[i].part_counter_simulated = so->machine[i].config.part_counter_initial_value_in_simulation_mode;
		so->machine[i].cycle_time_simulated = so->machine[i].config.average_cycle_time_in_simulation_mode_seconds;
	}


	so->configured = 1;


	return 0;
}


#if 0
int siemens_open62541__config_old(void)
{

	int rc;
	int i;
	utils__sdb__config_t sdb_config;
	utils__printf__config_t pf_config;


	(void)utils__sdb__init(&so->sdb);

	memset(&sdb_config, 0, sizeof(sdb_config));

	sdb_config.buffer = so->sdb_buffer;
	sdb_config.buffer_size = sizeof(so->sdb_buffer);
	sdb_config.name = so->sdb_name;
	sdb_config.name_len = so->sdb_name_len;
	sdb_config.value = so->sdb_value;
	sdb_config.value_len = so->sdb_value_len;
	sdb_config.encoding = so->sdb_encoding;
	sdb_config.fields_max = SIEMENS_OPEN62541__CONFIG__SDB_FIELDS_MAX;

	rc = utils__sdb__config(&so->sdb, &sdb_config);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -100, "utils__sdb__config() returned %d", fn, rc);
		return -100;
	}


	rc = siemens_open62541__private__load_configuration();
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -200, "siemens_open62541__private__load_configuration() returned %d", rc);
		return -200;
	}


	/*
	 * reconfigure the printf subsystem with user's data contained in the configuration file
	 */
	rc = utils__printf__init(&so->pf);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -300, "utils__printf__init() returned %d", fn, rc);
		return -300;
	}


	memset(&pf_config, 0, sizeof(pf_config));

	pf_config.enable_printf = so->config.enable_printf;
	pf_config.enable_log_file = so->config.enable_log_file;
	pf_config.log_file_name = so->config.log_file_name;
	pf_config.log_file_name_len = strlen(so->config.log_file_name);
	pf_config.max_log_file_lines_per_minute = so->config.max_log_file_lines_per_minute;
	pf_config.enable_table_layout_output = so->config.enable_table_layout_output;
	pf_config.enable_application_name_on_output = so->config.enable_application_name_on_output;
	pf_config.agent_name = so->agent_name_and_version;
	pf_config.application_name_len = strlen(so->agent_name_and_version);


	rc = utils__printf__config(&so->pf, &pf_config);
	if (rc != 0)
	{
		utils__printf__error(&so->pf, fn, -400, "utils__printf__config() returned %d", fn, rc);
		return -400;
	}


	//rc = siemens_open62541__private__attach_stub_functions();
	//if (rc != 0)
	//{
	//	utils__printf__error(&so->pf, fn, -500, "siemens_open62541__private__attach_stub_functions() returned %d", fn, rc);
	//	return -500;
	//}


	for (i = 0; i < so->machine_count; i++)
	{
		so->machine[i].connection_status = 0;
		so->machine[i].part_counter_simulated = so->machine[i].config.part_counter_initial_value_in_simulation_mode;
		so->machine[i].cycle_time_simulated = so->machine[i].config.average_cycle_time_in_simulation_mode_seconds;
	}


	so->configured = 1;

	return 0;
}
#endif