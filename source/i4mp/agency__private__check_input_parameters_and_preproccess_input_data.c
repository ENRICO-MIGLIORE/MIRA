#include "agency_private.h"


int agency__private__check_input_parameters_and_preproccess_input_data (void* p, const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count)
{

	int rc;

	if (p == NULL)
	{
		return -100;
	}

	//subagent = (subagent_t*)subagent;

	//if (subagent->machine_counter < 0)
	//{
	//	return -200;
	//}

	rc = agency__private__check_and_preprocess_input_data(calling_function_name, data, data_len, tokens, tokens_len, tokens_max, token_count, minimum_token_count);
	if (rc != 0)
	{
		return -300;
	}

	return 0;

}

#if 0

static int found_machine_section (void* subagent, const char* section_name, size_t section_name_len);
static int set_machine_id(void* subagent, const char* data, size_t data_len);
static int set_machine_plate_data(void* subagent, const char* data, size_t data_len);
static int set_machine_field_data(void* subagent, const char* data, size_t data_len);
static int set_machine_location_data(void* subagent, const char* data, size_t data_len);
static int set_machine_technical_data(void* subagent, const char* data, size_t data_len);
static int set_machine_feeder_data(void* subagent, const char* data, size_t data_len);
static int set_machine_simulation_data(void* subagent, const char* data, size_t data_len);



/*
 * name to callback function map
 */
static utils__sdb__value_callback_t names_values[] =
{

  {"MACHINE ID",                   set_machine_id                 },
  {"MACHINE PLATE DATA",           set_machine_plate_data         },
  {"MACHINE FIELD DATA",           set_machine_field_data         },    
  {"MACHINE LOCATION DATA",        set_machine_location_data      },
  {"MACHINE TECHNICAL DATA",       set_machine_technical_data     },
  {"MACHINE FEEDER DATA",          set_machine_feeder_data        },
  {"MACHINE SIMULATION DATA",      set_machine_simulation_data    }

};



/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */


int subagent__load_machines_configuration_data (subagent_t* subagent)
{

	int rc;
	FILE* f;
	int i;
	int j;
	size_t record_number;
	size_t start_record;
	size_t machine_names_values_max;
	int done;
	size_t number_of_sections;
	size_t size;
	int end_of_file;
	const char* fn;
	utils__sdb__section_callback_t section_callback;

	number_of_sections = 0;
	rc = 0;
	end_of_file = 0;
	record_number = 0;


	fn = "agent__load_machines_configuration_data()";

	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "agent is null");
		return -100;
	}


	f = fopen((const char*)subagent->config.file_name, "rb");
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

	//if (subagent->config.mode == SUBAGENT__FILE_CONFIG_MODE)
	if (1 == 1)
	{
		rc = utils__sdb__count_sections_from_file(&subagent->sdb, subagent->config.file_name, subagent->config.machine_section_name, start_record, &number_of_sections, &end_of_file);
		if (rc != 0)
		{		
			//utils__printf__error(&subagent->pf, fn, -1000, "utils__sdb__count_sections_from_file() returned %d", rc);
			return -1000;
		}
	}
	else
	{
		rc = utils__sdb__count_sections_from_buffer(&subagent->sdb, subagent->config.file_name, subagent->config.machine_section_name, start_record, &number_of_sections, &end_of_file);
		if (rc != 0)
		{			
			//utils__printf__error(&subagent->pf, fn, -1100, "utils__sdb__count_sections_from_buffer() returned %d", rc);
			return -1100;
		}
	}

	if (number_of_sections == 0)
	{		
		//utils__printf__error(&subagent->pf, fn, -1200, "can't find any [%s] sections in the configuration file or buffer", subagent->config.agent_machines_section_name);
		return -1200;
	}



	/*
	 * Allocate memory for the machines
	 */
	size = sizeof(subagent__machine_t) * number_of_sections;

	subagent->machine = (subagent__machine_t*) malloc(size);

	if (subagent->machine == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -1300, "delegate->machine - malloc() error");
		return -1300;
	}

	memset(subagent->machine, '\0', size);

	subagent->number_of_machines = number_of_sections;
	subagent->machine_descriptor = -1;


	/*
	 * example: [SIEMENS-OPEN62541 MACHINE]
	 */
	memset(&section_callback, 0, sizeof(section_callback));

	section_callback.name = subagent->config.machine_section_name;
	section_callback.function = found_machine_section;
	machine_names_values_max = sizeof(names_values) / sizeof(utils__sdb__value_callback_t);


	done = 0;
	start_record = 1;
	do
	{
		//if (subagent->config.mode == SUBAGENT__FILE_CONFIG_MODE)
		if (1 == 1)
		{
			rc = utils__sdb__read_configuration_from_file((subagent_t *) subagent, &subagent->sdb, subagent->config.file_name, &section_callback, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		else
		{
			rc = utils__sdb__read_configuration_from_buffer((subagent_t*)subagent, &subagent->sdb, subagent->config.file_name, &section_callback, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		
		if (rc != 0)
		{
			if (end_of_file == 0)
			{
				//if (subagent->config.mode == SUBAGENT__FILE_CONFIG_MODE)
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


	//subagent->number_of_machines++;


	//if (subagent->number_of_machines != number_of_sections)
	//{		
	//	//utils__printf__error(&subagent->pf, fn, -2200, "delegate->number_of_machines = %d - number_of_sections = %d - they must be equal", subagent->number_of_machines, number_of_sections);
	//	return -2200;
	//}


	if (subagent->number_of_machines > 1)
	{

		/*
		 * Check for duplicate machines' ID
		 */
		for (i = 0; i < subagent->number_of_machines; i++)
		{
			for (j = i + 1; j < subagent->number_of_machines; j++)
			{
				//if (subagent->machine[i].config_2.id == subagent->machine[j].config_2.id)
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
	//	for (i = 0; i < delegate->number_of_machines; i++)
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



	for (i = 0; i < subagent->number_of_machines; i++)
	{
		//sprintf(subagent->machine[i].name_and_index, "%s %d", subagent->config.agent_machines_section_name, i + 1);
		//subagent->machine[i].name_and_index_len = strlen(subagent->machine_local[i].name_and_index);
	}



	/*
	 * initialize the utils__printf subsystem
	 */
	for (i = 0; i < subagent->number_of_machines; i++)
	{


		//rc = utils__printf__init(&subagent->machine[i].pf);
		//if (rc != 0)
		//{
		//	utils__printf__error(NULL, fn, -200, "utils__printf__init() error");
		//	return -200;
		//}


		///*
		// * configure the utils__printf subsystem
		// */
		//memset(&pf_config, 0, sizeof(pf_config));

		//pf_config.enable_printf = 1;
		//pf_config.enable_log_file = 0;
		//pf_config.log_file_name = "";
		//pf_config.log_file_name_len = 0;
		//pf_config.max_log_file_lines_per_minute = 120;
		//pf_config.enable_table_layout_output = 1;
		//pf_config.enable_application_name_on_output = 0;
		//pf_config.application_name = "";
		//pf_config.application_name_len = 0;

		//rc = utils__printf__config(&subagent->machine_local[i].pf, &pf_config);
		//if (rc != 0)
		//{
		//	utils__printf__error(NULL, fn, -300, "utils__printf__config() returned %d", rc);
		//	return -300;
		//}

	}



	return 0;
}
 


static int found_machine_section (void* subagent, const char* section_name, size_t section_name_len)
{

	const char* fn;
	subagent_t* subagent;


	fn = "subagent__found_section()";

	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}	

	subagent = (subagent_t*) subagent;

	if (section_name == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -200, "section_name is null");
		return -200;
	}

	if (section_name_len == 0)
	{
		//utils__printf__error(&subagent->pf, fn, -300, "section_name_len is zero");
		return -300;
	}

	if (subagent->machine_descriptor == -1)
	{
		subagent->machine_descriptor = 0;     /* first time */
	}
	else
	{
		subagent->machine_descriptor++;
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
static int set_machine_id (void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* subagent;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent__machine_t* machine;


	fn = "set_id()";


	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	subagent = (subagent_t*)subagent;


	if (subagent->machine_descriptor < 0)
	{
		utils__printf__error(NULL, fn, -100, "machine descriptor is %d", subagent->machine_descriptor);
		return -100;
	}

	machine = &subagent->machine[subagent->machine_descriptor];


	minimum_token_count = 1;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
	
	rc = subagent__preprocess_input_data(fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -1000, "subagent__check_and_preprocess_input_data() returned %d", rc);
		return -1000;
	}
	

	i = subagent->machine_descriptor;


	/*
	 * id
	 */	
	rc = utils__libc__write_int(&machine[i].config_2.id, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -200, "id - utils__libc__write_int() returned %d", rc);
		return -200;
	}


	return 0;
}

///*
// * example of config file entry:
// *
// * MACHINE TYPE = "CNC" or "NO CNC"
// *
// * tokens[0] = CNC              (TYPE)
// *
// */
//static int set_machine_type (void* subagent, const char* data, size_t data_len)
//{
//	int rc;
//	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	subagent_t* subagent;	
//	const char* fn;	
//	size_t i;
//	size_t minimum_token_count;	
//	const char* option_1;
//	const char* option_2;
//	size_t option_1_len;
//	size_t option_2_len;
//	subagent_machine_t* machine;
//	
//
//	fn = "set_id()";
//
//	if (subagent == NULL)
//	{
//		utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}
//
//	subagent = (subagent_t*)subagent;
//
//
//	if (subagent->machine_counter < 0)
//	{
//		utils__printf__error(NULL, fn, -100, "machine descriptor is %d", subagent->machine_counter);
//		return -100;
//	}
//	
//	machine = &subagent->machine[subagent->machine_counter];
//
//
//	minimum_token_count = 1;
//	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;
//
//	rc = subagent__check_and_preprocess_input_data(fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
//	if (rc != 0)
//	{
//		//utils__printf__error(&subagent->pf, fn, -1000, "subagent__check_and_preprocess_input_data() returned %d", rc);
//		return -1000;
//	}
//
//
//	i = subagent->machine_counter;
//
//
//	/*
//	 * type
//	 */
//	option_1 = "CNC";
//	option_1_len = strlen(option_1);
//
//	option_2 = "NO CNC";
//	option_2_len = strlen(option_2);
//
//	rc = utils__libc__write_option(machine[i].config_2.type, sizeof(machine[i].config_2.type), data, data_len, option_1, option_1_len, option_2, option_2_len);
//	if (rc != 0)
//	{
//		//utils__printf__error(&subagent->pf, fn, -2000, "type - utils__libc__write_option() returned %d", rc);
//		return -2000;
//	}
//
//
//	return 0;
//}

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
static int set_machine_plate_data (void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* subagent;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent__machine_t* machine;


	fn = "set_plate_data()";

	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	subagent = (subagent_t*)subagent;


	if (subagent->machine_descriptor < 0)
	{
		utils__printf__error(NULL, fn, -100, "machine descriptor is %d", subagent->machine_descriptor);
		return -100;
	}
	
	machine = &subagent->machine[subagent->machine_descriptor];


	minimum_token_count = 4;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;


	rc = subagent__preprocess_input_data(fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -1000, "subagent__check_and_preprocess_input_data() returned %d", rc);
		return -1000;
	}


	i = subagent->machine_descriptor;


	/*
	 * manufacturer
	 */
	rc = utils__libc__write_string(machine[i].config_2.manufacturer, sizeof(machine[i].config_2.manufacturer) , tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -200, "manufacturer - utils__libc__write_string() returned %d", rc);
		return -200;
	}

	/*
	 * model
	 */
	rc = utils__libc__write_string(machine[i].config_2.model, sizeof(machine[i].config_2.model), tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -300, "model - utils__libc__write_string() returned %d", rc);
		return -300;
	}


	/*
	 * serial number
	 */
	rc = utils__libc__write_string(machine[i].config_2.serial_number, sizeof(machine[i].config_2.serial_number), tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -400, "serial_number - utils__libc__write_string() returned %d", rc);
		return -400;
	}


	/*
	 * manufacture year
	 */
	rc = utils__libc__write_string(machine[i].config_2.manufacture_year, sizeof(machine[i].config_2.manufacture_year), tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -500, "manufacture_year - utils__libc__write_string() returned %d", rc);
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
static int set_machine_field_data (void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* subagent;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent__machine_t* machine;


	fn = "set_field_data()";


	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	subagent = (subagent_t*)subagent;


	if (subagent->machine_descriptor < 0)
	{
		utils__printf__error(NULL, fn, -100, "machine descriptor is %d", subagent->machine_descriptor);
		return -100;
	}

	machine = &subagent->machine[subagent->machine_descriptor];


	minimum_token_count = 3;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__preprocess_input_data(fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -1000, "subagent__check_and_preprocess_input_data() returned %d", rc);
		return -1000;
	}


	i = subagent->machine_descriptor;


	/*
	 * networked
	 */
	rc = utils__libc__write_1_or_0(&machine[i].config_2.networked, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2000, "networked - utils__libc__write_1_or_0() returned %d", rc);
		return -2000;
	}


	/*
	 * operating_mode
	 */
	rc = utils__libc__write_1_or_0(&machine[i].config_2.simulated, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2100, "operating_mode - utils__libc__write_1_or_0() returned %d", rc);
		return -2100;
	}


	/*
	 * active
	 */
	rc = utils__libc__write_1_or_0(&machine[i].config_2.operating, tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2200, "active - utils__libc__write_1_or_0() returned %d", rc);
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
static int set_machine_location_data(void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* subagent;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent__machine_t* machine;


	fn = "set_location_data()";


	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	subagent = (subagent_t*)subagent;


	if (subagent->machine_descriptor < 0)
	{
		utils__printf__error(NULL, fn, -100, "machine descriptor is %d", subagent->machine_descriptor);
		return -100;
	}

	machine = &subagent->machine[subagent->machine_descriptor];


	minimum_token_count = 4;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__preprocess_input_data(fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -1000, "subagent__check_and_preprocess_input_data() returned %d", rc);
		return -1000;
	}


	i = subagent->machine_descriptor;


	/*
	 * organization
	 */
	rc = utils__libc__write_string(machine[i].config_2.organization, sizeof(machine[i].config_2.organization), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2000, "organization - utils__libc__write_string() returned %d", rc);
		return -2000;
	}


	/*
	 * facility
	 */
	rc = utils__libc__write_string(machine[i].config_2.facility, sizeof(machine[i].config_2.facility), tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2100, "facility - utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	/*
	 * department
	 */
	rc = utils__libc__write_string(machine[i].config_2.department, sizeof(machine[i].config_2.department), tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2200, "department - utils__libc__write_string() returned %d", rc);
		return -2200;
	}


	/*
	 * name
	 */
	rc = utils__libc__write_string(machine[i].config_2.name, sizeof(machine[i].config_2.name), tokens[3], tokens_len[3]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2300, "name - utils__libc__write_string() returned %d", rc);
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
static int set_machine_technical_data(void* subagent, const char* data, size_t data_len)
{
	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* subagent;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent__machine_t * machine;


	fn = "set_technical_data()";


	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	subagent = (subagent_t*)subagent;


	if (subagent->machine_descriptor < 0)
	{
		utils__printf__error(NULL, fn, -100, "machine descriptor is %d", subagent->machine_descriptor);
		return -100;
	}

	machine = &subagent->machine[subagent->machine_descriptor];


	minimum_token_count = 2;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__preprocess_input_data(fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -1000, "subagent__check_and_preprocess_input_data() returned %d", rc);
		return -1000;
	}


	i = subagent->machine_descriptor;


	/*
	 * cnc
	 */
	rc = utils__libc__write_string(machine[i].config_2.cnc, sizeof(machine[i].config_2.cnc), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2000, "utils__libc__write_string() returned %d", rc);
		return -2000;
	}

	/*
	 * hmi
	 */
	rc = utils__libc__write_string(machine[i].config_2.hmi, sizeof(machine[i].config_2.hmi), tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2100, "utils__libc__write_string() returned %d", rc);
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
static int set_machine_feeder_data (void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* subagent;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent__machine_t* machine;


	fn = "fn_set_machine_feeder_data()";


	if (subagent == NULL)
	{
		utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}

	subagent = (subagent_t*)subagent;


	if (subagent->machine_descriptor < 0)
	{
		utils__printf__error(NULL, fn, -100, "machine descriptor is %d", subagent->machine_descriptor);
		return -100;
	}

	machine = &subagent->machine[subagent->machine_descriptor];


	minimum_token_count = 4;
	tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__preprocess_input_data(fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -1000, "subagent__check_and_preprocess_input_data() returned %d", rc);
		return -100;
	}


	i = subagent->machine_descriptor;



	/*
	 * feeder manufacturer
	 */
	rc = utils__libc__write_string(machine[i].config_2.feeder_manufacturer, sizeof(machine[i].config_2.feeder_manufacturer), tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	/*
	 * feeder model
	 */
	rc = utils__libc__write_string(machine[i].config_2.feeder_model, sizeof(machine[i].config_2.feeder_model), tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
		return -2200;
	}


	/*
	 * feeder serial number
	 */
	rc = utils__libc__write_string(machine[i].config_2.feeder_serial_number, sizeof(machine[i].config_2.feeder_serial_number), tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
		return -2300;
	}


	/*
	 * feeder manufacture year
	 */
	rc = utils__libc__write_string(machine[i].config_2.feeder_manufacture_year, sizeof(machine[i].config_2.feeder_manufacture_year), tokens[3], tokens_len[3]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2400, "manufacture_year - utils__libc__write_string() returned %d", rc);
		return -2400;
	}


	return 0;
}




/*
 * examples of config file entry:
 *
 * MACHINE SIMULATION DATA = 12; 1000; O0001
 *
 * tokens[0] = 12              (AVERAGE CYCLE TIME SECONDS IN SIMULATION MODE)
 * tokens[1] = 1000            (PART COUNTER INITIAL VALUE IN SIMULATION MODE)
 * tokens[2] = O0001           (PART PROGRAM NAME IN SIMULATION MODE)
 *
 */

static int set_machine_simulation_data (void* subagent, const char* data, size_t data_len)
{

	int rc;
	char* tokens[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_len[SUBAGENT__CONFIG__TOKENS_MAX];
	size_t tokens_max;
	size_t token_count;
	subagent_t* subagent;
	const char* fn;
	size_t i;
	size_t minimum_token_count;
	subagent__machine_t* machine;
	int tmp_int;


	fn = "set_machine_simulation_data()";


	minimum_token_count = 3;
    tokens_max = SUBAGENT__CONFIG__TOKENS_MAX;

	rc = subagent__check_input_parameters_and_preproccess_input_data(subagent, fn, data, data_len, tokens, tokens_len, tokens_max, &token_count, minimum_token_count);
	if (rc != 0)
	{
		//	utils__printf__error(NULL, fn, -100, "delegate is null");
		return -100;
	}


	subagent = (subagent_t*)subagent;
	i = subagent->machine_descriptor;
	machine = &subagent->machine[i];

	
	/*
	 * part counter initial data in simulation mode
	 */
	rc = utils__libc__write_int(&tmp_int, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2200, "feeder model - utils__libc__write_string() returned %d", rc);
		return -2200;
	}

	if (tmp_int <= 0)
	{
		machine->config_2.part_counter_initial_value_in_simulation_mode = 1000;
	}
	else
	{
		machine->config_2.part_counter_initial_value_in_simulation_mode = tmp_int;
	}


	/*
	 * average cycle time seconds in simulation mode
	 */
	rc = utils__libc__write_int(&tmp_int, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2100, "feeder_manufacturer - utils__libc__write_string() returned %d", rc);
		return -2100;
	}

	if (tmp_int <= 0)
	{
		machine->config_2.average_cycle_time_seconds_in_simulation_mode = 100;
	}
	else
	{
		machine->config_2.average_cycle_time_seconds_in_simulation_mode = tmp_int;
	}





	/*
	 * part program name in simulation mode
	 */
	rc = utils__libc__write_string(machine->config_2.part_program_name_in_simulation_mode, sizeof(machine->config_2.part_program_name_in_simulation_mode), tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -2300, "feeder_serial_number - utils__libc__write_string() returned %d", rc);
		return -2300;
	}



	return 0;
}




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