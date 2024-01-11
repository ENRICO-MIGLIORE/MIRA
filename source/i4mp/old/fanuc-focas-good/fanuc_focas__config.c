#include "fanuc_focas.h"


extern fanuc_focas_t* fanuc_focas;
extern int fanuc_focas__read_configuration_file (int mode);
extern int fanuc_focas__attach_functions (void);



static char *fn = "fanuc_focas__config()";





int fanuc_focas__config (void)
{

	int rc;
	size_t fd;
	size_t machine_id;
	utils__sdb__config_t sdb_config;
	utils__printf__config_t pf__config;

	sdb_config.buffer = fanuc_focas->sdb_buffer;
	sdb_config.buffer_size = sizeof(fanuc_focas->sdb_buffer);
	sdb_config.name = fanuc_focas->sdb_name;
	sdb_config.name_len = fanuc_focas->sdb_name_len;
	sdb_config.value = fanuc_focas->sdb_value;
	sdb_config.value_len = fanuc_focas->sdb_value_len;
	sdb_config.language_iso_639_1_buffer = fanuc_focas->sdb_language_iso_639_1_buffer;
	sdb_config.encoding = fanuc_focas->sdb_encoding;
	sdb_config.fields_max = FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX;

	rc = utils__sdb__config_sdb(&fanuc_focas->sdb, &sdb_config);
	if (rc != 0)
	{
		printf("error in function %s - utils__sdb__config_sdb() returned %d\n", fn, rc);
		return -100;
	}


	rc = fanuc_focas__read_configuration_file(0);
	if (rc != 0)
	{		

		rc = utils__printf__init(&fanuc_focas->pf);
		if (rc != 0)
		{
			printf("error in function %s - utils__printf__init() returned %d\n", fn, rc);
			return -200;
		}

		pf__config.enable_printf = 1;
		pf__config.enable_log_file = 0;
		pf__config.fully_qualified_log_file_name = "";
		pf__config.fully_qualified_log_file_name_len = 0;
		pf__config.max_log_file_lines_per_minute = 0;
		pf__config.enable_square_brackets_output = 1;
		pf__config.enable_section_name_output = 1;
		pf__config.section_name = fanuc_focas->application_data.name_and_version;
		pf__config.section_name_len = fanuc_focas->application_data.name_and_version_len;

		rc = utils__printf__config(&fanuc_focas->pf, &pf__config);
		if (rc != 0)
		{
			printf("error in function %s - utils__printf__config() returned %d\n", fn, rc);
			return -300;
		}

		fanuc_focas->configured = 1;

		utils__printf__info(&fanuc_focas->pf, fn, 0, "can't find %s in config file - use default values", fanuc_focas->application_data.configuration_file_section_name);

		return 0;
	}



	rc = utils__printf__init(&fanuc_focas->pf);
	if (rc != 0)
	{
		printf("error in function %s - utils__printf__init() returned %d\n", fn, rc);
		return -400;
	}

	pf__config.enable_printf = fanuc_focas->config.enable_printf;
	pf__config.enable_log_file = fanuc_focas->config.enable_log_file;
	pf__config.fully_qualified_log_file_name = fanuc_focas->config.fully_qualified_log_file_name;
	pf__config.fully_qualified_log_file_name_len = fanuc_focas->config.fully_qualified_log_file_name_len;
	pf__config.max_log_file_lines_per_minute = fanuc_focas->config.max_log_file_lines_per_minute;
	pf__config.enable_square_brackets_output = fanuc_focas->config.enable_square_brackets_output;
	pf__config.enable_section_name_output = fanuc_focas->config.enable_section_name_output;
	pf__config.section_name = fanuc_focas->application_data.name_and_version;
	pf__config.section_name_len = fanuc_focas->application_data.name_and_version_len;

	rc = utils__printf__config(&fanuc_focas->pf, &pf__config);
	if (rc != 0)
	{
		printf("error in function %s - utils__printf__config() returned %d\n", fn, rc);
		return -500;
	}
	

	fanuc_focas->configured = 1;



	rc = fanuc_focas__read_configuration_file(1);
	if (rc != 0)
	{
		utils__printf__info(&fanuc_focas->pf, fn, 0, "can't find %s in config file - no fanuc lathe machines found", fanuc_focas->machines_data.configuration_file_section_name);
		return 0;
	}



	for (fd = 0; fd < fanuc_focas->num_machines; fd++)
	{
		rc = utils__printf__init(&fanuc_focas->lathe_machine[fd].pf);
		if (rc != 0)
		{			
			utils__printf__error(&fanuc_focas->pf, fn, 0, "error in function %s - utils__printf__init() returned %d - fd = %zu\n", fn, rc, fd);
			return -500;
		}

		pf__config.enable_printf = fanuc_focas->lathe_machine[fd].config.enable_printf;
		pf__config.enable_log_file = fanuc_focas->lathe_machine[fd].config.enable_log_file;
		pf__config.fully_qualified_log_file_name = fanuc_focas->lathe_machine[fd].config.fully_qualified_log_file_name;
		pf__config.fully_qualified_log_file_name_len = fanuc_focas->lathe_machine[fd].config.fully_qualified_log_file_name_len;
		pf__config.max_log_file_lines_per_minute = fanuc_focas->lathe_machine[fd].config.max_log_file_lines_per_minute;
		pf__config.enable_square_brackets_output = fanuc_focas->lathe_machine[fd].config.enable_square_brackets_output;
		pf__config.enable_section_name_output = fanuc_focas->lathe_machine[fd].config.enable_section_name_output;

		pf__config.section_name = fanuc_focas->lathe_machine[fd].name_and_index;
		pf__config.section_name_len = fanuc_focas->lathe_machine[fd].name_and_index_len;

		rc = utils__printf__config(&fanuc_focas->lathe_machine[fd].pf, &pf__config);
		if (rc != 0)
		{
			utils__printf__error(&fanuc_focas->pf, fn, 0, "error in function %s - utils__printf__config() returned %d - fd = %zu\n", fn, rc, fd);			
			return -600;
		}

	}


	utils__printf__info(&fanuc_focas->pf, fn, 0, "%zu fanuc lathe machines successfully configured", fanuc_focas->num_machines);


	rc = fanuc_focas__attach_functions();
	if (rc != 0)
	{
		utils__printf__error(&fanuc_focas->pf, fn, 0, "error in function %s - fanuc_focas__attach_functions() returned % d\n", fn, rc);		
		return -700;
	}


	return 0;
}