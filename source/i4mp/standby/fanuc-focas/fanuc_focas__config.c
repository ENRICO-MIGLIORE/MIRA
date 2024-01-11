#include "fanuc_focas__private.h"


static char *fn = "fanuc_focas__config()";


int fanuc_focas__config (void)
{

	int rc;
	int error;
	size_t fd;
	utils__sdb__config_t sdb_config;
	utils__printf__config_t pf_config;


	sdb_config.buffer = ff->sdb_buffer;
	sdb_config.buffer_size = sizeof(ff->sdb_buffer);
	sdb_config.name = ff->sdb_name;
	sdb_config.name_len = ff->sdb_name_len;
	sdb_config.value = ff->sdb_value;
	sdb_config.value_len = ff->sdb_value_len;
	sdb_config.language_iso_639_1_buffer = ff->sdb_language_iso_639_1_buffer;
	sdb_config.encoding = ff->sdb_encoding;
	sdb_config.fields_max = FANUC_FOCAS__CONFIG__SDB_FIELDS_MAX;

	rc = utils__sdb__config_sdb(&ff->sdb, &sdb_config);
	if (rc != 0)
	{
		printf("error in function %s - utils__sdb__config_sdb() returned %d\n", fn, rc);
		return -100;
	}


	rc = fanuc_focas__process_configuration_file();
	if (rc != 0)
	{
		printf("error in function %s - fggr__read_configuration_file() returned %d\n", fn, rc);
		return -200;
	}

	rc = utils__printf__init(&ff->pf);
	if (rc != 0)
	{
		printf("error in function %s - utils__printf__init() returned %d\n", fn, rc);
		return -300;
	}


	pf_config.enable_printf = ff->config.enable_printf;
	pf_config.enable_log_file = ff->config.enable_log_file;
	pf_config.fully_qualified_log_file_name = ff->config.fully_qualified_log_file_name;
	pf_config.fully_qualified_log_file_name_len = ff->config.fully_qualified_log_file_name_len;
	pf_config.max_log_file_lines_per_minute = ff->config.max_log_file_lines_per_minute;
	pf_config.enable_square_brackets_output = ff->config.enable_square_brackets_output;
	pf_config.enable_section_name_output = ff->config.enable_section_name_output;
	pf_config.section_name = ff->application_name_and_version;
	pf_config.section_name_len = ff->application_name_and_version_len;


	rc = utils__printf__config(&ff->pf, &pf_config);
	if (rc != 0)
	{
		printf("error in function %s - utils__printf__config() returned %d\n", fn, rc);
		return -400;
	}



	for (fd = 0; fd < ff->machine_count; fd++)
	{

		rc = utils__printf__init(&ff->machine[fd].pf);
		
		if (rc != 0)
		{
			error = -500;
			utils__printf__error(&ff->pf, fn, error, "utils__printf__init() returned %d - fd = %zu\n", fn, rc, fd);
			return error;
		}

		pf_config.enable_printf = ff->machine[fd].config.enable_printf;		
		pf_config.enable_log_file = ff->machine[fd].config.enable_log_file;		
		pf_config.fully_qualified_log_file_name = ff->machine[fd].config.fully_qualified_log_file_name;
		pf_config.fully_qualified_log_file_name_len = ff->machine[fd].config.fully_qualified_log_file_name_len;	
		pf_config.max_log_file_lines_per_minute = ff->machine[fd].config.max_log_file_lines_per_minute;
		pf_config.enable_square_brackets_output = ff->machine[fd].config.enable_square_brackets_output;	
		pf_config.enable_section_name_output = ff->machine[fd].config.enable_section_name_output;		
		pf_config.section_name = ff->machine[fd].name_and_index;
		pf_config.section_name_len = ff->machine[fd].name_and_index_len;
		rc = utils__printf__config(&ff->machine[fd].pf, &pf_config);
		
		if (rc != 0)
		{
			error = -600;
			utils__printf__error(&ff->pf, fn, error, "utils__printf__config() returned %d - fd = %zu\n", fn, rc, fd);
			return error;
		}
	}


	rc = fanuc_focas__attach_read_functions();
	if (rc != 0)
	{
		error = -700;
		utils__printf__error(&ff->pf, fn, error, " fanuc_focas__attach_read_functions() returned %d\n", fn, rc);
		return error;
	}


	
	ff->configured = 1;

	return 0;
}