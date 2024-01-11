#include "machine.h"


int machine__config (subagent__machine_t* machine_local, subagent__machine_config_t* config)
{

	int rc;
	int i;
	utils__sdb__config_t sdb_config;
	utils__printf__config_t pf_config;
	const char* fn;

#if 0
	fn = "machine__config()";

	if (machine_local == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	rc = delegate__private__check_config(config);
	if (rc != 0)
	{
		utils__printf__error(NULL, fn, -200, "delegate__private__check_config() returned %d", rc);
		return -200;
	}

	memset(&machine_local->config, 0, sizeof(machine_config_t));

	memcpy(&machine_local->config, config, sizeof(machine_config_t));



	//memset(&pf_config, 0, sizeof(pf_config));

	//pf_config.enable_printf = 1;
	//pf_config.enable_log_file = 0;
	//pf_config.log_file_name = "";
	//pf_config.log_file_name_len = 0;
	//pf_config.max_log_file_lines_per_minute = 0;
	//pf_config.enable_table_layout_output = 1;
	//pf_config.enable_application_name_on_output = 1;
	//pf_config.application_name = machine->config.agent_name_and_version;
	//pf_config.application_name_len = strlen(machine->config.agent_name_and_version);

	//rc = utils__printf__config(&machine->pf, &pf_config);
	//if (rc != 0)
	//{
	//	utils__printf__error(NULL, fn, -400, "utils__printf__config() returned %d", rc);
	//	return -400;
	//}


	/*
	 * we can now use the follwing functions: 
	 * 
	 * utils__printf__info()
	 * utils__printf__error()
	 * utils__printf__warning()
	 */

	//delegate->config.config_file_name[0] = '\0';
	

	//memset(&sdb_config, 0, sizeof(sdb_config));

	//sdb_config.buffer = machine->sdb_buffer;
	//sdb_config.buffer_size = sizeof(machine->sdb_buffer);
	//sdb_config.name = machine->sdb_name;
	//sdb_config.name_len = machine->sdb_name_len;
	//sdb_config.value = machine->sdb_value;
	//sdb_config.value_len = machine->sdb_value_len;
	//sdb_config.encoding = machine->sdb_encoding;
	//sdb_config.fields_max = SUBAGENT__CONFIG__SDB_FIELDS_MAX;

	//rc = utils__sdb__config(&machine->sdb, &sdb_config);
	//if (rc != 0)
	//{
	//	utils__printf__error(&machine->pf, fn, -1300, "utils__sdb__config() returned %d", rc);
	//	return -1300;
	//}




	/*
	 * read the settings file or buffer and extract data for the delegate
	 */
	rc = agent__load_agent_configuration_data(machine_local);
	if (rc != 0)
	{
		//utils__printf__error(&machine->pf, fn, -1400, "delegate__private__load_agent_configuration_data() returned %d", rc);
		return -1400;
	}


	/*
	 * read the settings file or buffer and extract data for the delegate
	 */	
	rc = machine__load_configuration_data(machine_local);
	if (rc != 0)
	{		
		//utils__printf__error(&machine->pf, fn, -1500, "delegate__private__load_agent_configuration_data() returned %d", rc);
		return -1500;
	}



	/*
	 * reconfigure the utils__printf subsystem with user's config data contained in the configuration file or buffer
	 */
	//rc = utils__printf__init(&machine->pf);
	//if (rc != 0)
	//{
	//	//utils__printf__error(&machine->pf, fn, -1600, "utils__printf__init() returned %d", rc);
	//	return -1600;
	//}


	//memset(&pf_config, 0, sizeof(pf_config));

	//pf_config.enable_printf = machine->config_2.enable_printf;
	//pf_config.enable_log_file = machine->config_2.enable_log_file;
	//pf_config.log_file_name = machine->config_2.log_file_name;
	//pf_config.log_file_name_len = strlen(machine->config_2.log_file_name);
	//pf_config.max_log_file_lines_per_minute = machine->config_2.max_log_file_lines_per_minute;
	//pf_config.enable_table_layout_output = machine->config_2.enable_table_layout_output;
	//pf_config.enable_application_name_on_output = machine->config_2.enable_agent_name_on_output;
	//pf_config.application_name = machine->config.agent_name_and_version;
	//pf_config.application_name_len = strlen(machine->config.agent_name_and_version);


	//rc = utils__printf__config(&machine->pf, &pf_config);
	//if (rc != 0)
	//{
	//	utils__printf__error(&machine->pf, fn, -1700, "utils__printf__config() returned %d", rc);
	//	return -1700;
	//}


	//for (i = 0; i < subagent->machine_count; i++)
	//{

	//	subagent->machine[i].config_2.simulated = 1;

	//	if (subagent->machine[i].config_2.simulated == 1)
	//	{

	//		subagent->machine[i].config.connect_to_machine = subagent__simulation__connect_to_machine;

	//		//delegate->machine[i].connect_to_machine = siemens_open62541__private__connect_to_machine__simulated;
	//		//delegate->machine[i].disconnect_from_machine = siemens_open62541__private__disconnect_from_machine__simulated;

	//		//delegate->machine[i].read_connection_status = siemens_open62541__private__read_connection_status__simulated;
	//		//delegate->machine[i].read_production_status = siemens_open62541__private__read_production_status__simulated;
	//		//delegate->machine[i].read_alarm_status = siemens_open62541__private__read_alarm_status__simulated;

	//		//delegate->machine[i].read_part_counter = siemens_open62541__private__read_part_counter__simulated;
	//		//delegate->machine[i].read_cycle_time = siemens_open62541__private__read_cycle_time__simulated;
	//		//delegate->machine[i].read_part_program_name = siemens_open62541__private__read_part_program_name__simulated;


	//	}
	//	else
	//	{

	//		//delegate->machine[i].config.connect_to_machine = siemens_open62541__private__connect_to_machine__real;

	//		subagent->machine[i].config.connect_to_machine = subagent->config.connect_to_machine;


	//		//delegate->machine[i].disconnect_from_machine = siemens_open62541__private__disconnect_from_machine__real;

	//		//delegate->machine[i].read_connection_status = siemens_open62541__private__read_connection_status__real;
	//		//delegate->machine[i].read_production_status = siemens_open62541__private__read_production_status__real;
	//		//delegate->machine[i].read_alarm_status = siemens_open62541__private__read_alarm_status__real;

	//		//delegate->machine[i].read_part_counter = siemens_open62541__private__read_part_counter__real;
	//		//delegate->machine[i].read_cycle_time = siemens_open62541__private__read_cycle_time__real;
	//		//delegate->machine[i].read_part_program_name = siemens_open62541__private__read_part_program_name__real;

	//	}
	//}


	//for (i = 0; i < subagent->machine_count; i++)
	//{
	//	subagent->machine[i].connection_status = 0;
	//	//delegate->machine[i].part_counter_simulated = delegate->machine[i].config_2.part_counter_initial_value_in_simulation_mode;
	//	subagent->machine[i].cycle_time_simulated = subagent->machine[i].config_2.average_cycle_time_in_simulation_mode_seconds;
	//}


	machine_local->configured = 1;


#endif
	return 0;
}