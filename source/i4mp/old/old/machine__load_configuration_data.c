#if 0

#include "machine.h"


static int machine__found_section (void* machine, const char* section_name, size_t section_name_len);
static int machine__set_id(void* machine, const char* value, size_t value_len);
static int machine__set_type(void* machine, const char* value, size_t value_len);
static int machine__set_plate_data(void* machine, const char* value, size_t value_len);
static int machine__set_field_data(void* machine, const char* value, size_t value_len);
static int machine__set_location_data(void* machine, const char* value, size_t value_len);
static int machine__set_technical_data(void* machine, const char* value, size_t value_len);
static int machine__set_feeder_data(void* machine, const char* value, size_t value_len);


static utils__sdb__value_callback_t names_values[] =
{

  {"MACHINE ID",                   machine__set_id              },
  {"MACHINE TYPE",                 machine__set_type            },
  {"MACHINE PLATE DATA",           machine__set_plate_data      },
  {"MACHINE FIELD DATA",           machine__set_field_data      },    
  {"MACHINE LOCATION DATA",        machine__set_location_data   },
  {"MACHINE TECHNICAL DATA",       machine__set_technical_data  },
  {"MACHINE FEEDER DATA",          machine__set_feeder_data     }

};



static char* fn_set_machine_id = "machine__set_id()";
static char* fn_set_machine_type = "machine__set_type()";
static char* fn_set_machine_plate_data = "machine__set_plate_data()";
static char* fn_set_machine_field_data = "machine__set_field_data()";
static char* fn_set_machine_location_data = "machine__set_location_data()";
static char* fn_set_machine_technical_data = "fn_set_machine_technical_data()";



/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */


int machine__load_configuration_data (machine_t* machine)
{


#if 0
	int rc;
	FILE* f;
	int i;
	int j;
	size_t record_number;
	size_t start_record;
	size_t machine_names_values_max;
	int done;
	size_t section_count;
	size_t size;
	int end_of_file;
	const char* fn;
	utils__printf__config_t pf_config;
	utils__sdb__section_callback_t machine_section_callback;

	section_count = 0;
	rc = 0;
	end_of_file = 0;
	record_number = 0;


	fn = "machine__load_configuration_data()";

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	f = fopen((const char*)machine->config.file_name, "rb");
	if (f == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -200, "file %s not found", subagent->config.file_name);
		return -200;
	}
	fclose(f);



	/*
	 * count the number of sections, for example: [SIEMENS-OPEN62541 MACHINE]
	 */
	start_record = 1;

	//if (machine->config.mode == MACHINE__FILE_CONFIG_MODE)
	if (1 == 1)
	{
		//rc = utils__sdb__count_sections_from_file(&subagent->sdb, subagent->config.file_name, subagent->config.agent_machines_section_name, start_record, &section_count, &end_of_file);
		if (rc != 0)
		{		
			//utils__printf__error(&subagent->pf, fn, -1000, "utils__sdb__count_sections_from_file() returned %d", rc);
			return -1000;
		}
	}
	else
	{
		//rc = utils__sdb__count_sections_from_buffer(&subagent->sdb, subagent->config.file_name, subagent->config.agent_machines_section_name, start_record, &section_count, &end_of_file);
		if (rc != 0)
		{			
			//utils__printf__error(&subagent->pf, fn, -1100, "utils__sdb__count_sections_from_buffer() returned %d", rc);
			return -1100;
		}
	}

	if (section_count == 0)
	{		
		//utils__printf__error(&subagent->pf, fn, -1200, "can't find any [%s] sections in the configuration file or buffer", subagent->config.agent_machines_section_name);
		return -1200;
	}


	/*
	 * Allocate memory for the machines
	 */
	size = sizeof(machine_data_t) * section_count;

	machine->machine_local = (machine_data_t*) malloc(size);

	if (machine->machine_local == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -1300, "delegate->machine - malloc() error");
		return -1300;
	}

	memset(machine->machine_local, '\0', size);



	/*
	 * Set section data of the machines: [SIEMENS-OPEN62541 MACHINE]
	 */
	machine_section_callback.name = machine->config.agent_machines_section_name;
	machine_section_callback.function = machine__found_section;
	machine_names_values_max = sizeof(names_values) / sizeof(utils__sdb__value_callback_t);

	machine->machine_count = -1;


	done = 0;
	start_record = 1;
	do
	{
		//if (machine->config.mode == MACHINE__FILE_CONFIG_MODE)
		if (1 == 1)
		{
			//rc = utils__sdb__read_configuration_from_file((subagent__machine_t *) subagent, &subagent->sdb, subagent->config.file_name, &machine_section_callback, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		else
		{
			//rc = utils__sdb__read_configuration_from_buffer((subagent__machine_t*) subagent, &subagent->sdb, subagent->config.file_name, &machine_section_callback, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		
		if (rc != 0)
		{
			if (end_of_file == 0)
			{
				//if (machine->config.mode == MACHINE__FILE_CONFIG_MODE)
				if (1 == 1)
				{
					//utils__printf__error(&subagent->pf, fn, -2000, "utils__sdb__read_configuration_file() returned %d", rc);
					return -2000;
				}
				
				//utils__printf__error(&subagent->pf, fn, -2100, "utils__sdb__read_configuration_from_buffer() returned %d", rc);
				return -2100;				
			}

			done = 1;
		}
		else if (end_of_file == 1)
		{
			done = 1;
		}
		else
		{
			start_record = record_number + 1;
		}

	}
	while (done == 0);


	machine->machine_count++;


	if (machine->machine_count != section_count)
	{		
		//utils__printf__error(&subagent->pf, fn, -2200, "delegate->machine_count = %d - section_count = %d - they must be equal", subagent->machine_count, section_count);
		return -2200;
	}


	if (machine->machine_count > 1)
	{

		/*
		 * Check for duplicate machines' ID
		 */
		for (i = 0; i < machine->machine_count; i++)
		{
			for (j = i + 1; j < machine->machine_count; j++)
			{
				if (machine->machine_local[i].config_2.id == machine->machine_local[j].config_2.id)
				{
					///utils__printf__error(&delegate->pf, fn_local, -1300, "Duplicate id found - id = %d - i = %d - j = %d", delegate->machine[i].config_2.id, i, j);
					///return -1300;
				}
			}
		}
	}


		/*
		 * Check for potential buffer overflow
		 */
	//	for (i = 0; i < delegate->machine_count; i++)
	//	{

	//		len = strlen(delegate->machine[i].config_2.part_program_name_in_simulation_mode);

	//		if (len > sizeof(delegate->machine[i].part_program_name_simulated))
	//		{
	//			printf("%s - error - len > delegate->machine[%d].part_program_name_utf_8_simulated\n", fn, delegate->machine[i].config_2.id);
	//			utils__printf__error(&delegate->pf, fn_local, -1400, "Duplicate id found - id = %d - i = %d - j = %d", delegate->machine[i].config_2.id, i, j);
	//			return -1400;
	//		}

	//		if (len > sizeof(delegate->machine[i].part_program_name_utf_8))
	//		{
	//			printf("%s - error - len > delegate->machine[%d].part_program_name_utf_8\n", fn, delegate->machine[i].config_2.id);
	//			return -700;
	//		}
	//	}
	//}



	for (i = 0; i < machine->machine_count; i++)
	{
		sprintf(machine->machine_local[i].name_and_index, "%s %d", machine->config.agent_machines_section_name, i + 1);
		machine->machine_local[i].name_and_index_len = strlen(machine->machine_local[i].name_and_index);
	}



	/*
	 * initialize the utils__printf subsystem
	 */
	for (i = 0; i < machine->machine_count; i++)
	{


		rc = utils__printf__init(&machine->machine_local[i].pf);
		if (rc != 0)
		{
			utils__printf__error(NULL, fn, -200, "utils__printf__init() error");
			return -200;
		}


		/*
		 * configure the utils__printf subsystem
		 */
		memset(&pf_config, 0, sizeof(pf_config));

		pf_config.enable_printf = 1;
		pf_config.enable_log_file = 0;
		pf_config.log_file_name = "";
		pf_config.log_file_name_len = 0;
		pf_config.max_log_file_lines_per_minute = 120;
		pf_config.enable_table_layout_output = 1;
		pf_config.enable_application_name_on_output = 0;
		pf_config.application_name = "";
		pf_config.application_name_len = 0;

		rc = utils__printf__config(&machine->machine_local[i].pf, &pf_config);
		if (rc != 0)
		{
			utils__printf__error(NULL, fn, -300, "utils__printf__config() returned %d", rc);
			return -300;
		}

	}


#endif

	return 0;
}
 
 
static int machine__found_section (void* machine, const char* section_name, size_t section_name_len)
{

	const char* fn;
	machine_t* dele;


	fn = "machine__found_section()";

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}	

	dele = (machine_t*)machine;

	if (section_name == NULL)
	{
		//utils__printf__error(&dele->pf, fn, -200, "section_name is null");
		return -200;
	}

	if (section_name_len == 0)
	{
		//utils__printf__error(&dele->pf, fn, -300, "section_name_len is zero");
		return -300;
	}

	if (dele->machine_count == -1)
	{
		dele->machine_count = 0;     /* first time */
	}
	else
	{
		dele->machine_count++;
	}

	return 0;
}


/*
 * example of config file entry:
 *
 * MACHINE ID = 14
 *
 * tokens[0] = 14            (ID)
 */
static int machine__set_id(void* machine, const char* value, size_t value_len)
{

	int rc;
	char* tokens[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_len[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	machine_t* dele;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	int* int_data;


	fn = fn_set_machine_id;

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*)machine;

	minimum_token_count = 1;
	tokens_max = MACHINE__CONFIG__TOKENS_MAX;
	
	rc = agent__preprocess_input_data(machine, fn, value, value_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1000, "subagent__preprocess_input_data() returned %d", rc);
		return -1000;
	}
	

	i = dele->machine_count;


	/*
	 * id
	 */
	int_data = &dele->machine_local[i].config_2.id;

	rc = utils__libc__write_int(int_data, tokens[0], tokens_len[0]);	
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -200, "id - utils__libc__write_int() returned %d", rc);
		return -200;
	}


	return 0;
}

/*
 * example of config file entry:
 *
 * MACHINE TYPE = "CNC" or "NO CNC"
 *
 * tokens[0] = CNC              (TYPE)
 *
 */
static int machine__set_type(void* machine, const char* value, size_t value_len)
{
	int rc;
	char* tokens[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_len[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	machine_t* dele;	
	const char* fn;	
	size_t i;
	size_t minimum_token_count;	
	char* b;
	size_t size;
	const char* option_1;
	const char* option_2;
	size_t option_1_len;
	size_t option_2_len;
	

	fn = fn_set_machine_type;

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*)machine;

	minimum_token_count = 1;
	tokens_max = MACHINE__CONFIG__TOKENS_MAX;

	rc = agent__preprocess_input_data(machine, fn, value, value_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1000, "subagent__preprocess_input_data() returned %d", rc);
		return -1000;
	}


	i = dele->machine_count;


	/*
	 * type
	 */
	b = dele->machine_local[i].config_2.type;
	size = sizeof(dele->machine_local[i].config_2.type);

	option_1 = "CNC";
	option_1_len = strlen(option_1);

	option_2 = "NO CNC";
	option_2_len = strlen(option_2);

	rc = utils__libc__write_option(b, size, value, value_len, option_1, option_1_len, option_2, option_2_len);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2000, "type - utils__libc__write_option() returned %d", rc);
		return -2000;
	}


	return 0;
}

/*
 * example of config file entry:
 *
 * MACHINE PLATE DATA = UTIMAC; SCN32HT; 1234; 2018
 *
 * tokens[0] = UTIMAC                      (MANUFACTURER)
 * tokens[1] = SCN32HT                     (MODEL)
 * tokens[2] = 1234                        (SERIAL NUMBER)
 * tokens[3] = 2018                        (MANUFACTURE YEAR)
 *
 */
static int machine__set_plate_data(void* machine, const char* value, size_t value_len)
{

	int rc;
	char* tokens[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_len[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	machine_t* dele;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	char* b;
	size_t size;


	fn = fn_set_machine_plate_data;

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*)machine;

	minimum_token_count = 4;
	tokens_max = MACHINE__CONFIG__TOKENS_MAX;

	rc = agent__preprocess_input_data(machine, fn, value, value_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -100, "subagent__preprocess_input_data() returned %d", rc);
		return -100;
	}


	i = dele->machine_count;


	/*
	 * manufacturer
	 */
	b = dele->machine_local[i].config_2.manufacturer;
	size = sizeof(dele->machine_local[i].config_2.manufacturer);

	rc = utils__libc__write_string(b, size, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -200, "manufacturer - utils__libc__write_string() returned %d", rc);
		return -200;
	}

	/*
	 * model
	 */
	b = dele->machine_local[i].config_2.model;
	size = sizeof(dele->machine_local[i].config_2.model);

	rc = utils__libc__write_string(b, size, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -300, "model - utils__libc__write_string() returned %d", rc);
		return -300;
	}


	/*
	 * serial number
	 */
	b = dele->machine_local[i].config_2.serial_number;
	size = sizeof(dele->machine_local[i].config_2.serial_number);

	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -400, "serial_number - utils__libc__write_string() returned %d", rc);
		return -400;
	}


	/*
	 * manufacture year
	 */
	b = dele->machine_local[i].config_2.manufacture_year;
	size = sizeof(dele->machine_local[i].config_2.manufacture_year);

	rc = utils__libc__write_string(b, size, tokens[3], tokens_len[3]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -500, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -500;
	}


	return 0;
}

/*
 * example of config file entry:
 * 
 * MACHINE FIELD DATA = YES; NO; YES
 * 
 * tokens[0] = YES      (NETWORKED)
 * tokens[1] = NO       (SIMULATED)
 * tokens[2] = YES      (OPERATING)
 * 
 */
static int machine__set_field_data (void* machine, const char* value, size_t value_len)
{

	int rc;
	char* tokens[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_len[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	machine_t* dele;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	int* int_data;

	fn = fn_set_machine_field_data;

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*)machine;


	minimum_token_count = 3;
	tokens_max = MACHINE__CONFIG__TOKENS_MAX;

	rc = agent__preprocess_input_data(machine, fn, value, value_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1000, "subagent__preprocess_input_data() returned %d", rc);
		return -1000;
	}


	i = dele->machine_count;


	/*
	 * networked
	 */
	int_data = &dele->machine_local[i].config_2.networked;

	rc = utils__libc__write_yes_or_no(int_data, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2000, "networked - utils__libc__write_1_or_0() returned %d", rc);
		return -2000;
	}


	/*
	 * simulated
	 */
	int_data = &dele->machine_local[i].config_2.simulated;

	rc = utils__libc__write_yes_or_no(int_data, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2100, "simulated - utils__libc__write_1_or_0() returned %d", rc);
		return -2100;
	}


	/*
	 * operating
	 */
	int_data = &dele->machine_local[i].config_2.operating;

	rc = utils__libc__write_yes_or_no(int_data, tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2200, "operating - utils__libc__write_1_or_0() returned %d", rc);
		return -2200;
	}

	return 0;

}

/*
 * example of config file entry:
 *
 * MACHINE LOCATION DATA = FATTI MECCANICA srl; FINOTTO; LEFT 2; SCY45HT-2018
 *
 * tokens[0] = FATTI MECCANICA srl        (ORGANIZATION)
 * tokens[1] = FINOTTO                    (FACILITY)
 * tokens[2] = LEFT 2                     (DEPARTMENT)
 * tokens[3] = SCY45HT-2018               (NAME)
 *
 */
static int machine__set_location_data(void* machine, const char* value, size_t value_len)
{

	int rc;
	char* tokens[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_len[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	machine_t* dele;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	char* b;
	size_t size;


	fn = fn_set_machine_location_data;

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*)machine;


	minimum_token_count = 4;
	tokens_max = MACHINE__CONFIG__TOKENS_MAX;

	rc = agent__preprocess_input_data(machine, fn, value, value_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1000, "subagent__preprocess_input_data() returned %d", rc);
		return -1000;
	}


	i = dele->machine_count;


	/*
	 * organization
	 */
	b = dele->machine_local[i].config_2.organization;
	size = sizeof(dele->machine_local[i].config_2.organization);

	rc = utils__libc__write_string(b, size, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2000, "organization - utils__libc__write_string() returned %d", rc);
		return -2000;
	}


	/*
	 * facility
	 */
	b = dele->machine_local[i].config_2.facility;
	size = sizeof(dele->machine_local[i].config_2.facility);

	rc = utils__libc__write_string(b, size, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2100, "facility - utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	/*
	 * department
	 */
	b = dele->machine_local[i].config_2.department;
	size = sizeof(dele->machine_local[i].config_2.department);

	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2200, "department - utils__libc__write_string() returned %d", rc);
		return -2200;
	}


	/*
	 * name
	 */
	b = dele->machine_local[i].config_2.name;
	size = sizeof(dele->machine_local[i].config_2.name);

	rc = utils__libc__write_string(b, size, tokens[3], tokens_len[3]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2300, "name - utils__libc__write_string() returned %d", rc);
		return -2300;
	}


	return 0;
}

/*
 * example of config file entry:
 *
 * MACHINE TECHNICAL DATA = -; ESA AUTOMATION VT550
 *
 * tokens[0] = -                                  (CNC NAME)
 * tokens[1] = ESA AUTOMATION VT550               (HMI)
 *
 */
static int machine__set_technical_data(void* machine, const char* value, size_t value_len)
{
	int rc;
	char* tokens[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_len[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	machine_t* dele;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	char* b;
	size_t size;

	fn = fn_set_machine_technical_data;

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*)machine;


	minimum_token_count = 2;
	tokens_max = MACHINE__CONFIG__TOKENS_MAX;

	rc = agent__preprocess_input_data(machine, fn, value, value_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1000, "subagent__preprocess_input_data() returned %d", rc);
		return -1000;
	}


	i = dele->machine_count;


	/*
	 * cnc
	 */
	b = dele->machine_local[i].config_2.cnc;
	size = sizeof(dele->machine_local[i].config_2.cnc);

	rc = utils__libc__write_string(b, size, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2000, "utils__libc__write_string() returned %d", rc);
		return -2000;
	}

	/*
	 * hmi
	 */
	b = dele->machine_local[i].config_2.hmi;
	size = sizeof(dele->machine_local[i].config_2.hmi);

	rc = utils__libc__write_string(b, size, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2100, "utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	
	return 0;
}

/*
 * examples of config file entry: 
 *
 * 
 * MACHINE FEEDER DATA = FUMAGALLI; A!s13-41; 1234; 2017
 *
 * tokens[0] = FUMAGALLI              (MANUFACTURER)
 * tokens[1] = A;13-41                (MODEL)   (note that !s will be converted to ;)
 * tokens[2] = 1234                   (SERIAL NUMBER)
 * tokens[3] = 2017                   (MANUFACTURE YEAR)
 *
 * 
 * MACHINE FEEDER DATA = -;-;-;-
 *
 * tokens[0] = -                      (MANUFACTURER)
 * tokens[1] = -                      (MODEL)
 * tokens[2] = -                      (SERIAL NUMBER)
 * tokens[3] = -                      (MANUFACTURE YEAR)
 * 
 */
static int machine__set_feeder_data (void* machine, const char* value, size_t value_len)
{

	int rc;
	char* tokens[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_len[MACHINE__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	machine_t* dele;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	char* b;
	size_t size;


	fn = "fn_set_machine_feeder_data()";

	if (machine == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	dele = (machine_t*) machine;	

	minimum_token_count = 4;
	tokens_max = MACHINE__CONFIG__TOKENS_MAX;

	rc = agent__preprocess_input_data(machine, fn, value, value_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -1000, "subagent__preprocess_input_data() returned %d", rc);
		return -100;
	}


	i = dele->machine_count;



	/*
	 * feeder manufacturer
	 */
	b = dele->machine_local[i].config_2.feeder_manufacturer;
	size = sizeof(dele->machine_local[i].config_2.feeder_manufacturer);

	rc = utils__libc__write_string(b, size, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	/*
	 * feeder model
	 */
	b = dele->machine_local[i].config_2.feeder_model;
	size = sizeof(dele->machine_local[i].config_2.feeder_model);

	rc = utils__libc__write_string(b, size, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
		return -2200;
	}


	/*
	 * feeder serial number
	 */
	b = dele->machine_local[i].config_2.feeder_serial_number;
	size = sizeof(dele->machine_local[i].config_2.feeder_serial_number);

	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
		return -2300;
	}


	/*
	 * feeder manufacture year
	 */
	b = dele->machine_local[i].config_2.feeder_manufacture_year;
	size = sizeof(dele->machine_local[i].config_2.feeder_manufacture_year);

	rc = utils__libc__write_string(b, size, tokens[3], tokens_len[3]);
	if (rc != 0)
	{
		//utils__printf__error(&dele->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;
}



//
//
//
//	{"CNC NAME",                                        set_cnc_name                                         },
//  {"FEEDER PLATE DATA",                                  set_feeder_plate_data                                },
//     {"MANUFACTURER",                                    set_manufacturer                                     },
//	 {"MODEL",                                           set_model                                            },
//	 {"SERIAL NUMBER",                                   set_serial_number                                    },
//	 {"NAME",                                            set_name                                             },
//
//  {"SIMULATION DATA",                                   set_simulation_data  },
//	{"PART PROGRAM NAME IN SIMULATION MODE",            set_part_program_name_in_simulation_mode             },
//	{"PART COUNTER INITIAL VALUE IN SIMULATION MODE",   set_part_counter_initial_value_in_simulation_mode    },
//	{"AVERAGE CYCLE TIME SECONDS IN SIMULATION MODE",   set_average_cycle_time_seconds_in_simulation_mode    },
//  
//
//  {"CONNECTION MONITOR DATA",                         set_connection_timeout_seconds                       },
//	{"CONNECTION TIMEOUT SECONDS",                      set_connection_timeout_seconds                       },
//	{"RECONNECTION ATTEMPTS TIME INTERVAL SECONDS",     set_reconnection_attempts_time_interval_seconds      },
//	{"MAX RECONNECTION ATTEMPTS",                       set_max_reconnection_attempts                        },
//	{"NO RESPONSE TIMEOUT SECONDS",                     set_no_response_timeout_seconds                      },
//
//
//  {"OPC SERVER CONNECTION DATA",                             set_opc_connection_data                              },
//     {"OPC IP-V4 ADDRESS",                               set_opc_ipv4_address                                 },
//     {"OPC IP-V4 PORT",                                  set_opc_ipv4_port                                    },
//     {"OPC USER NAME",                                   set_opc_user_name                                    },
//     {"OPC PASSWORD",                                    set_opc_password                                     },
//     {"OPC CERTIFICATE FILE",                            set_opc_certificate_file                             },
//     {"OPC PRIVATE KEY FILE",                            set_opc_private_key_file                             },
//
//  {"OPC SERVER NODES DATA",                                            set_opc_nodes_data                                   },
//     {"OPC PART COUNTER PATH",                           set_opc_part_counter_path                            },
//     {"OPC CYCLE TIME PATH",                             set_opc_cycle_time_path                              },
//     {"OPC PART PROGRAM NAME PATH",                      set_opc_part_program_name_path                       },
//
//
// {"TCP SERVER CONNECTION DATA",                                set_connection_timeout_seconds                       },
//
//     {"TCP SERVER IP-V4 ADDRESS",                        set_tcp_server_ipv4_address                          },
//     {"TCP SERVER IP-V4 PORT",                           set_tcp_server_ipv4_port                             },
//     {"TCP CLIENT RECEIVE BUFFER SIZE",                  set_tcp_client_receive_buffer_size                   },
//     {"TCP CLIENT SEND STRING",                          set_tcp_client_send_string                           },
//     {"TCP CLIENT ENABLE PRINTF",                        set_tcp_enable_printf                                },
//
//
//  {"CYCLE TIME DATA FROM ",                           set_cycle_time_from_part_counter                     },
//  {"CYCLE TIME FROM PART COUNTER",                    set_cycle_time_from_part_counter                     },
//
//  {"PART PROGRAM NAME FILTER",                        set_part_program_name_filter                         }
//
//
//};


#endif