#include "agency_private.h"


int agency__private__check_and_preprocess_input_data (const char* calling_function_name, const char* data, size_t data_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count)
{

	int rc;
	const char* escape_sequence;
	size_t escape_sequence_len;
	char c;
	size_t token_new_len;
	size_t i;
	size_t seps_len[AGENCY__FIELDS_SEPARATORS_MAX];
	size_t seps_count;
	size_t tok_count;
	const char* fn;
	const char* seps[AGENCY__FIELDS_SEPARATORS_MAX] = AGENCY__FIELDS_SEPARATORS;
	

	fn = "agency__private__check_and_preprocess_input_data()";



	if (calling_function_name == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -200, "calling function name is null");
		return -200;
	}

	if (data == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -300, "data is null");
		return -300;
	}

	if (tokens == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -400, "tokens are null");
		return -400;
	}

	if (tokens_len == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -500, "tokens_len is null");
		return -500;
	}

	if (token_count == NULL)
	{
		//utils__printf__error(&subagent->pf, fn, -500, "token_count is null");
		return -600;
	}

	if (minimum_token_count > tokens_max)
	{
		//utils__printf__error(&subagent->pf, fn, -700, "minimum_token_count is greater than tokens_max");
		return -700;
	}

	for (i = 0; i < AGENCY__FIELDS_SEPARATORS_MAX; i++)
	{
		seps_len[i] = strlen(seps[i]);
	}


	seps_count = AGENCY__FIELDS_SEPARATORS_MAX;
	rc = utils__libc__tokenize_string(data, data_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &tok_count);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -1000, "%s - utils__libc__tokenize_string() returned %d", calling_function_name, rc);
		return -1000;
	}


	if (tok_count < minimum_token_count)
	{
		//utils__printf__error(&subagent->pf, fn, -1100, "%s - token_count is %zu and but should be at least %zu", calling_function_name, token_count, minimum_token_count);
		return -1100;
	}

	rc = utils__libc__trim_tokens(&tokens[0], tokens_len, tok_count, AGENCY__CHARACTER_TO_TRIM);
	if (rc != 0)
	{
		//utils__printf__error(&subagent->pf, fn, -1200, "utils__libc__trim_tokens() returned %d", calling_function_name, rc);
		return -1200;
	}

	
	escape_sequence = AGENCY__UNESCAPE_SEQUENCE;
	escape_sequence_len = AGENCY__UNESCAPE_SEQUENCE_LEN;
	c = AGENCY__UNESCAPE_REPLACEMENT_CHAR;

	for (i = 0; i < tok_count; i++)
	{	
		rc = utils__libc__unescape_buffer(tokens[i], tokens_len[i], escape_sequence, escape_sequence_len, c, &token_new_len);
		if (rc != 0)
		{
			//utils__printf__error(&subagent->pf, fn, -1300, "%s - utils__libc__unescape_buffer() returned %d", calling_function_name, rc);
			return -1300;
		}

		tokens_len[i] = token_new_len;
	}

	*token_count = tok_count;

	return 0;

}



//
//static int agents__load_entry__machine_section (void* delegate, const char* section_name, size_t section_name_len);
//static int set_machine_id(void* delegate, const char* value, size_t value_len);
//static int set_machine_type(void* delegate, const char* value, size_t value_len);
//static int set_machine_plate_data(void* delegate, const char* value, size_t value_len);
//static int set_machine_field_data(void* delegate, const char* value, size_t value_len);
//static int set_machine_location_data(void* delegate, const char* value, size_t value_len);
//
//static int set_machine_technical_data(void* delegate, const char* value, size_t value_len);
//static int set_machine_feeder_data(void* delegate, const char* value, size_t value_len);
//
//
//static utils__sdb__name_callback_t names_values[] =
//{
//
//  {"MACHINE ID",                   set_machine_id              },
//  {"MACHINE TYPE",                 set_machine_type            },
//  {"MACHINE PLATE DATA",           set_machine_plate_data      },
//  {"MACHINE FIELD DATA",           set_machine_field_data      },    
//  {"MACHINE LOCATION DATA",        set_machine_location_data   },
//  {"MACHINE TECHNICAL DATA",       set_machine_technical_data  },
//  {"MACHINE FEEDER DATA",          set_machine_feeder_data     }
//
//};
//
//
//static char* fn_delegate__private__load_machines_data = "delegate__private__load_machines_data()";
//static char* fn_found_machine_section = "agents__load_entry__machine_section()";
//static char* fn_set_machine_id = "set_machine_id()";
//static char* fn_set_machine_type = "set_machine_type()";
//static char* fn_set_machine_plate_data = "set_machine_plate_data()";
//static char* fn_set_machine_field_data = "set_machine_field_data()";
//static char* fn_set_machine_location_data = "set_machine_location_data()";
//
//
///*
// * No need to lock the thread in all of these functions because it hasn't started yet
// */
//
//
//
//int delegate__private__load_machines_data (delegate_t* delegate)
//{
//
//	int rc;
//	FILE* f;
//	int i;
//	int j;
//	size_t record_number;
//	size_t start_record;
//	size_t machine_names_values_max;
//	int done;
//	size_t section_count;
//	size_t size;
//	int end_of_file;
//	char* fn;
//	utils__sdb__section_callback_t agent_section;
//
//
//	fn = fn_delegate__private__load_machines_data;
//
//
//	f = fopen((const char*)delegate->config.file_name, "rb");
//	if (f == NULL)
//	{
//		utils__printf__error(&delegate->pf, fn, -100, "file %s not found", delegate->config.file_name);
//		return -100;
//	}
//	fclose(f);
//
//
//
//	/*
//	 * count the number of sections, for example: [SIEMENS-OPEN62541 MACHINE]
//	 */
//	start_record = 1;
//
//	if (delegate->config.mode == DELEGATE__FILE_CONFIG_MODE)
//	{
//		rc = utils__sdb__count_sections_from_file(&delegate->sdb, delegate->config.file_name, delegate->config.machines_section_name, start_record, &section_count, &end_of_file);
//		if (rc != 0)
//		{		
//			utils__printf__error(&delegate->pf, fn, -200, "utils__sdb__count_sections_from_file() returned %d", rc);
//			return -200;
//		}
//	}
//	else
//	{
//		rc = utils__sdb__count_sections_from_buffer(&delegate->sdb, delegate->config.file_name, delegate->config.machines_section_name, start_record, &section_count, &end_of_file);
//		if (rc != 0)
//		{			
//			utils__printf__error(&delegate->pf, fn, -300, "utils__sdb__count_sections_from_buffer() returned %d", rc);
//			return -300;
//		}
//	}
//
//	if (section_count == 0)
//	{		
//		utils__printf__error(&delegate->pf, fn, -300, "can't find any [%s] sections in the configuration file or buffer", delegate->config.machines_section_name);
//		return -300;
//	}
//
//
//	/*
//	 * Allocate memory for the machines
//	 */
//	size = sizeof(deleagate__machine_t) * section_count;
//
//	delegate->machine = (deleagate__machine_t*) malloc(size);
//
//	if (delegate->machine == NULL)
//	{
//		utils__printf__error(&delegate->pf, fn, -400, "delegate->machine - malloc() error");
//		return -400;
//	}
//
//	memset(delegate->machine, '\0', size);
//
//
//
//	/*
//	 * Set section data of the machines: [SIEMENS-OPEN62541 MACHINE]
//	 */
//	agent_section.name = delegate->config.machines_section_name;
//	agent_section.function = agents__load_entry__machine_section;
//	machine_names_values_max = sizeof(names_values) / sizeof(utils__sdb__name_callback_t);
//
//	delegate->number_of_machines = -1;
//
//
//	done = 0;
//	start_record = 1;
//	do
//	{
//		if (delegate->config.mode == DELEGATE__FILE_CONFIG_MODE)
//		{
//			rc = utils__sdb__read_configuration_from_file((delegate_t *) delegate, &delegate->sdb, delegate->config.file_name, &agent_section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
//		}
//		else
//		{
//			rc = utils__sdb__read_configuration_from_buffer((delegate_t*) delegate, &delegate->sdb, delegate->config.file_name, &agent_section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
//		}
//		
//		if (rc != 0)
//		{
//			if (end_of_file == 0)
//			{
//				if (delegate->config.mode == DELEGATE__FILE_CONFIG_MODE)
//				{
//					utils__printf__error(&delegate->pf, fn, -1000, "utils__sdb__read_configuration_file() returned %d", rc);
//					return -1000;
//				}
//				
//				utils__printf__error(&delegate->pf, fn, -1100, "utils__sdb__read_configuration_from_buffer() returned %d", rc);
//				return -1100;				
//			}
//
//			done = 1;
//		}
//		else if (end_of_file == 1)
//		{
//			done = 1;
//		}
//		else
//		{
//			start_record = record_number + 1;
//		}
//
//	}
//	while (done == 0);
//
//
//	delegate->number_of_machines++;
//
//
//	if (delegate->number_of_machines != section_count)
//	{		
//		utils__printf__error(&delegate->pf, fn, -1200, "delegate->number_of_machines = %d - section_count = %d - they must be equal", delegate->number_of_machines, section_count);
//		return -1200;
//	}
//
//
//	if (delegate->number_of_machines > 1)
//	{
//
//		/*
//		 * Check for duplicate machines' ID
//		 */
//		for (i = 0; i < delegate->number_of_machines; i++)
//		{
//			for (j = i + 1; j < delegate->number_of_machines; j++)
//			{
//				if (delegate->machine[i].config.id == delegate->machine[j].config.id)
//				{
//					utils__printf__error(&delegate->pf, fn_local, -1300, "Duplicate id found - id = %d - i = %d - j = %d", delegate->machine[i].config.id, i, j);
//					return -1300;
//				}
//			}
//		}
//	}
//
//
//		/*
//		 * Check for potential buffer overflow
//		 */
//		for (i = 0; i < delegate->number_of_machines; i++)
//		{
//
//			len = strlen(delegate->machine[i].config.part_program_name_in_simulation_mode);
//
//			if (len > sizeof(delegate->machine[i].part_program_name_simulated))
//			{
//				printf("%s - error - len > delegate->machine[%d].part_program_name_utf_8_simulated\n", fn, delegate->machine[i].config.id);
//				utils__printf__error(&delegate->pf, fn_local, -1400, "Duplicate id found - id = %d - i = %d - j = %d", delegate->machine[i].config.id, i, j);
//				return -1400;
//			}
//
//			if (len > sizeof(delegate->machine[i].part_program_name_utf_8))
//			{
//				printf("%s - error - len > delegate->machine[%d].part_program_name_utf_8\n", fn, delegate->machine[i].config.id);
//				return -700;
//			}
//		}
//	}
//
//
//
//	for (i = 0; i < delegate->number_of_machines; i++)
//	{
//		sprintf(delegate->machine[i].name_and_index, "%s %d", delegate->config.machines_section_name, i + 1);
//		delegate->machine[i].name_and_index_len = strlen(delegate->machine[i].name_and_index);
//	}
//
//
//	return 0;
//}
// 
// 
//static int agents__load_entry__machine_section (void* delegate, const char* section_name, size_t section_name_len)
//{
//
//	char* fn;
//	delegate_t* dele;
//
//
//	fn = fn_found_machine_section;
//
//	if (delegate == NULL)
//	{
//		utils__printf__error(NULL, fn, -100, "delegate is null");
//		return -100;
//	}	
//
//	dele = (delegate_t*)delegate;
//
//	if (section_name == NULL)
//	{
//		utils__printf__error(&dele->pf, fn, -200, "section_name is null");
//		return -200;
//	}
//
//	if (section_name_len == 0)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "section_name_len is zero");
//		return -300;
//	}
//
//	if (dele->number_of_machines == -1)
//	{
//		dele->number_of_machines = 0;
//	}
//	else
//	{
//		dele->number_of_machines++;
//	}
//
//	return 0;
//}
//
///*
// * example of config file entry:
// *
// * MACHINE ID = 14
// *
// * tokens[0] = ID (14)
// */
//
//
//static int delegate__private__check_input_data (void* delegate, const char* function_name, const char* value, size_t value_len, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count, size_t minimum_token_count)
//{
//	int rc;
//	const char* escape_sequence;
//	size_t escape_sequence_len;
//	char c;
//	size_t value_new_len;
//	delegate_t* dele;
//	size_t i;
//	size_t seps_len[DELEGATE__FIELDS_SEPARATORS_MAX];
//	size_t seps_count;
//	size_t tokens_max;
//	size_t token_count;
//	const char* seps[DELEGATE__FIELDS_SEPARATORS_MAX] = DELEGATE__FIELDS_SEPARATORS;
//
//	dele = (delegate_t*)delegate;
//
//
//	escape_sequence = DELEGATE__UNESCAPE_SEQUENCE;
//	escape_sequence_len = DELEGATE__UNESCAPE_SEQUENCE_LEN;
//	c = DELEGATE__UNESCAPE_REPLACEMENT_CHAR;
//
//	rc = utils__libc__unescape_buffer((char*)value, value_len, escape_sequence, escape_sequence_len, c, &value_new_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, function_name, -100, "utils__libc__unescape_buffer() returned %d", rc);
//		return -100;
//	}
//
//	for (i = 0; i < DELEGATE__FIELDS_SEPARATORS_MAX; i++)
//	{
//		seps_len[i] = strlen(seps[i]);
//	}
//
//	seps_count = DELEGATE__FIELDS_SEPARATORS_MAX;
//	tokens_max = DELEGATE__CONFIG__TOKENS_MAX;
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, function_name, -200, "utils__libc__tokenize_string() returned %d", rc);
//		return -200;
//	}
//
//	if (token_count < minimum_token_count)
//	{
//		utils__printf__error(&dele->pf, function_name, -300, "token_count is %zu and it's out of range", token_count);
//		return -300;
//	}
//
//	return 0;
//
//}
//
//
//static int set_machine_id(void* delegate, const char* value, size_t value_len)
//{
//	int rc;
//	size_t i;
//	char* tokens[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_len[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	char c;
//	delegate_t* dele;
//	const char* escape_sequence;
//	size_t escape_sequence_len;
//	size_t value_new_len;
//	char* fn;
//	int *int_data;
//	size_t seps_len[DELEGATE__FIELDS_SEPARATORS_MAX];
//	const char* seps[DELEGATE__FIELDS_SEPARATORS_MAX] = DELEGATE__FIELDS_SEPARATORS;
//
//
//	dele = (delegate_t*)delegate;
//
//	fn = fn_set_machine_id;
//
//	i = dele->number_of_machines;
//
//
//	escape_sequence = DELEGATE__UNESCAPE_SEQUENCE;
//	escape_sequence_len = DELEGATE__UNESCAPE_SEQUENCE_LEN;
//	c = DELEGATE__UNESCAPE_REPLACEMENT_CHAR;
//
//	rc = utils__libc__unescape_buffer((char*)value, value_len, escape_sequence, escape_sequence_len, c, &value_new_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_set_machine_plate_data, -100, "utils__libc__unescape_buffer() returned %d", rc);
//		return -100;
//	}
//
//	for (i = 0; i < DELEGATE__FIELDS_SEPARATORS_MAX; i++)
//	{
//		seps_len[i] = strlen(seps[i]);
//	}
//
//
//	seps_count = DELEGATE__FIELDS_SEPARATORS_MAX;
//	tokens_max = DELEGATE__CONFIG__TOKENS_MAX;
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -200, "utils__libc__tokenize_string() returned %d", rc);
//		return -200;
//	}
//
//	rc = utils__libc__trim_tokens(&tokens[0], tokens_len, token_count, DELEGATE__CHARACTER_TO_TRIM);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "utils__libc__trim_tokens() returned %d", rc);
//		return -300;
//	}
//
//	(void) utils__libc__print_tokens(tokens, tokens_len, token_count);
//
//
//	if (token_count < 1)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "token_count is %zu and it's out of range", token_count);
//		return -400;
//	}
//
//	/*
//	 * id
//	 */
//	int_data = &dele->machine[dele->number_of_machines].config.id;
//
//	rc = utils__libc__write_int(int_data, tokens[0], tokens_len[0]);	
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "id - utils__libc__write_int() returned %d", rc);
//		return -400;
//	}
//
//
//	return 0;
//}
//
//
///*
// * example of config file entry:
// *
// * MACHINE TYPE = "CNC" or "NO CNC"
// *
// * tokens[0] = TYPE (CNC)
// *
// */
//static int set_machine_type(void* delegate, const char* value, size_t value_len)
//{
//	int rc;
//	size_t i;
//	char* tokens[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_len[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	char c;
//	delegate_t* dele;
//	const char* escape_sequence;
//	size_t escape_sequence_len;
//	size_t value_new_len;
//	char* fn;
//	char* b;
//	size_t size;
//	const char* option_1;
//	const char* option_2;
//	size_t option_1_len;
//	size_t option_2_len;
//	size_t seps_len[DELEGATE__FIELDS_SEPARATORS_MAX];
//	const char* seps[DELEGATE__FIELDS_SEPARATORS_MAX] = DELEGATE__FIELDS_SEPARATORS;
//
//
//	dele = (delegate_t*)delegate;
//
//	fn = fn_set_machine_type;
//
//	i = dele->number_of_machines;
//
//
//	escape_sequence = DELEGATE__UNESCAPE_SEQUENCE;
//	escape_sequence_len = DELEGATE__UNESCAPE_SEQUENCE_LEN;
//	c = DELEGATE__UNESCAPE_REPLACEMENT_CHAR;
//
//	rc = utils__libc__unescape_buffer((char*)value, value_len, escape_sequence, escape_sequence_len, c, &value_new_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_set_machine_plate_data, -100, "utils__libc__unescape_buffer() returned %d", rc);
//		return -100;
//	}
//
//	for (i = 0; i < DELEGATE__FIELDS_SEPARATORS_MAX; i++)
//	{
//		seps_len[i] = strlen(seps[i]);
//	}
//
//
//	seps_count = DELEGATE__FIELDS_SEPARATORS_MAX;
//	tokens_max = DELEGATE__CONFIG__TOKENS_MAX;
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -200, "utils__libc__tokenize_string() returned %d", rc);
//		return -200;
//	}
//
//	rc = utils__libc__trim_tokens(&tokens[0], tokens_len, token_count, DELEGATE__CHARACTER_TO_TRIM);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "utils__libc__trim_tokens() returned %d", rc);
//		return -300;
//	}
//
//	(void) utils__libc__print_tokens(tokens, tokens_len, token_count);
//
//
//	if (token_count < 1)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "token_count is %zu and it's out of range", token_count);
//		return -400;
//	}
//
//	/*
//	 * type
//	 */
//	b = dele->machine[dele->number_of_machines].config.type;
//	size = sizeof(dele->machine[dele->number_of_machines].config.type);
//
//	option_1 = "CNC";
//	option_1_len = strlen(option_1);
//
//	option_2 = "NO CNC";
//	option_2_len = strlen(option_2);
//
//	rc = utils__libc__write_option(b, size, value, value_len, option_1, option_1_len, option_2, option_2_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "type - utils__libc__write_option() returned %d", rc);
//		return -400;
//	}
//
//
//	return 0;
//}
//
///*
// * example of config file entry:
// *
// * MACHINE PLATE DATA = UTIMAC; SCN32HT; 1234; 2018
// *
// * tokens[0] = MANUFACTURER (UTIMAC)
// * tokens[1] = MODEL (SCN32HT)
// * tokens[2] = SERIAL NUMBER (1234)
// * tokens[3] = MANUFACTURE YEAR (2018)
// *
// */
//static int set_machine_plate_data(void* delegate, const char* value, size_t value_len)
//{
//	int rc;
//	size_t i;
//	char* tokens[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_len[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	char c;
//	delegate_t* dele;
//	const char* escape_sequence;
//	size_t escape_sequence_len;
//	size_t value_new_len;
//	char* fn;
//	char* b;
//	size_t size;
//	size_t seps_len[DELEGATE__FIELDS_SEPARATORS_MAX];
//	const char* seps[DELEGATE__FIELDS_SEPARATORS_MAX] = DELEGATE__FIELDS_SEPARATORS;
//
//
//	dele = (delegate_t*)delegate;
//
//	fn = fn_set_machine_plate_data;
//
//	i = dele->number_of_machines;
//
//
//	/*
//	 *  DELEGATE__CONFIG__UNESCAPE_SEQUENCE          =  \;
//	 *  DELEGATE__CONFIG__UNESCAPE_SEQUENCE_LEN      =  2
//	 *  DELEGATE__CONFIG__UNESCAPE_REPLACEMENT_CHAR  =  ;
//	 */
//	escape_sequence = DELEGATE__UNESCAPE_SEQUENCE;
//	escape_sequence_len = DELEGATE__UNESCAPE_SEQUENCE_LEN;
//	c = DELEGATE__UNESCAPE_REPLACEMENT_CHAR;
//
//	rc = utils__libc__unescape_buffer((char*)value, value_len, escape_sequence, escape_sequence_len, c, &value_new_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_set_machine_plate_data, -100, "utils__libc__unescape_buffer() returned %d", rc);
//		return -100;
//	}
//
//	for (i = 0; i < DELEGATE__FIELDS_SEPARATORS_MAX; i++)
//	{
//		seps_len[i] = strlen(seps[i]);
//	}
//
//
//	seps_count = DELEGATE__FIELDS_SEPARATORS_MAX;
//	tokens_max = DELEGATE__CONFIG__TOKENS_MAX;
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -200, "utils__libc__tokenize_string() returned %d", rc);
//		return -200;
//	}
//
//	rc = utils__libc__trim_tokens(&tokens[0], tokens_len, token_count, DELEGATE__CHARACTER_TO_TRIM);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "utils__libc__trim_tokens() returned %d", rc);
//		return -300;
//	}
//
//	(void)utils__libc__print_tokens(tokens, tokens_len, token_count);
//
//
//	if (token_count < 4)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "token_count is %zu and it's out of range", token_count);
//		return -400;
//	}
//
//	/*
//	 * manufacturer
//	 */
//	b = dele->machine[dele->number_of_machines].config.manufacturer;
//	size = sizeof(dele->machine[dele->number_of_machines].config.manufacturer);
//
//	rc = utils__libc__write_string(b, size, tokens[0], tokens_len[0]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -500, "manufacturer - utils__libc__write_string() returned %d", rc);
//		return -500;
//	}
//
//	/*
//	 * model
//	 */
//	b = dele->machine[dele->number_of_machines].config.model;
//	size = sizeof(dele->machine[dele->number_of_machines].config.model);
//
//	rc = utils__libc__write_string(b, size, tokens[1], tokens_len[1]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -600, "model - utils__libc__write_string() returned %d", rc);
//		return -600;
//	}
//
//
//	/*
//	 * serial number
//	 */
//	b = dele->machine[dele->number_of_machines].config.serial_number;
//	size = sizeof(dele->machine[dele->number_of_machines].config.serial_number);
//
//	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -700, "serial_number - utils__libc__write_string() returned %d", rc);
//		return -700;
//	}
//
//
//	/*
//	 * manufacture year
//	 */
//	b = dele->machine[dele->number_of_machines].config.year;
//	size = sizeof(dele->machine[dele->number_of_machines].config.model);
//
//	rc = utils__libc__write_string(b, size, tokens[3], tokens_len[3]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -800, "utils__libc__write_string() returned %d", rc);
//		return -800;
//	}
//
//
//	return 0;
//}
//
//
///*
// * example of config file entry:
// * 
// * MACHINE FIELD DATA = YES; NO; YES
// * 
// * tokens[0] = NETWORKED (YES)
// * tokens[1] = SIMULATED (NO)
// * tokens[2] = OPERATING (YES)
// * 
// */
//static int set_machine_field_data (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	size_t i;
//	int* int_data;	
//	char* tokens[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_len[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	char c;
//	delegate_t* dele;
//	const char* escape_sequence;
//	size_t escape_sequence_len;
//	size_t value_new_len;	
//	char *fn;
//	size_t seps_len[DELEGATE__FIELDS_SEPARATORS_MAX];
//	const char* seps[DELEGATE__FIELDS_SEPARATORS_MAX] = DELEGATE__FIELDS_SEPARATORS;
//	
//
//	dele = (delegate_t*) delegate;
//
//	fn = fn_set_machine_field_data;
//
//	i = dele->number_of_machines;
//
//
//	/*
//	 *  DELEGATE__CONFIG__UNESCAPE_SEQUENCE          =  \;
//	 *  DELEGATE__CONFIG__UNESCAPE_SEQUENCE_LEN      =  2
//	 *  DELEGATE__CONFIG__UNESCAPE_REPLACEMENT_CHAR  =  ;
//	 */
//	escape_sequence = DELEGATE__UNESCAPE_SEQUENCE;
//	escape_sequence_len = DELEGATE__UNESCAPE_SEQUENCE_LEN;
//	c = DELEGATE__UNESCAPE_REPLACEMENT_CHAR;
//
//	rc = utils__libc__unescape_buffer((char*) value, value_len, escape_sequence, escape_sequence_len, c, &value_new_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -100, "utils__libc__unescape_buffer() returned %d", rc);
//		return -100;
//	}
//
//	for (i = 0; i < DELEGATE__FIELDS_SEPARATORS_MAX; i++)
//	{
//		seps_len[i] = strlen(seps[i]);
//	}
//
//
//	seps_count = DELEGATE__FIELDS_SEPARATORS_MAX;
//	tokens_max = DELEGATE__CONFIG__TOKENS_MAX;
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count);	
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -200, "utils__libc__tokenize_string() returned %d", rc);
//		return -200;
//	}
//
//	rc = utils__libc__trim_tokens(&tokens[0], tokens_len, token_count, DELEGATE__CHARACTER_TO_TRIM);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "utils__libc__trim_tokens() returned %d", rc);
//		return -300;
//	}
//
//	(void)utils__libc__print_tokens(tokens, tokens_len, token_count);
//
//
//	if (token_count < 3)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "token_count is %zu and it's out of range", token_count);
//		return -300;
//	}
//
//
//	/*
//	 * networked
//	 */
//	int_data = &dele->machine[i].config.networked;
//
//	rc = utils__libc__write_1_or_0(int_data, tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -400, "utils__libc__write_1_or_0() returned %d", rc);
//		return -400;
//	}
//
//
//	/*
//	 * operating_mode
//	 */
//	int_data = &dele->machine[i].config.operating_mode;
//
//	rc = utils__libc__write_1_or_0(int_data, tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -500, "utils__libc__write_1_or_0() returned %d", rc);
//		return -500;
//	}
//
//
//	/*
//	 * active
//	 */
//	int_data = &dele->machine[i].config.active;
//
//	rc = utils__libc__write_1_or_0(int_data, tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -600, "utils__libc__write_1_or_0() returned %d", rc);
//		return -600;
//	}
//
//	return 0;
//
//}
//
//
//
//
//
//
///*
// * example of config file entry:
// *
// * MACHINE LOCATION DATA = FATTI MECCANICA srl; FINOTTO; LEFT 2; SCY45HT-2018
// *
// * tokens[0] = ORGANIZATION (FATTI MECCANICA srl)
// * tokens[0] = FACILITY (FINOTTO)
// * tokens[1] = DEPARTMENT (LEFT 2)
// * tokens[2] = NAME (SCY45HT-2018)
// *
// */
//static int set_machine_location_data(void* delegate, const char* value, size_t value_len)
//{
//	int rc;
//	size_t i;
//	char* tokens[16];
//	size_t tokens_len[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	char c;
//	delegate_t* dele;
//	const char* escape_sequence;
//	size_t escape_sequence_len;
//	size_t value_new_len;
//	char* fn;
//	char* b;
//	size_t size;
//	size_t seps_len[DELEGATE__FIELDS_SEPARATORS_MAX];
//	const char* seps[DELEGATE__FIELDS_SEPARATORS_MAX] = DELEGATE__FIELDS_SEPARATORS;
//
//
//	dele = (delegate_t*) delegate;
//
//	fn = fn_set_machine_location_data;
//
//	i = dele->number_of_machines;
//
//
//	/*
//	 *  AGENT__CONFIG__UNESCAPE_SEQUENCE          =  \;
//	 *  AGENT__CONFIG__UNESCAPE_SEQUENCE_LEN      =  2
//	 *  AGENT__CONFIG__UNESCAPE_REPLACEMENT_CHAR  =  ;
//	 */
//	escape_sequence = DELEGATE__UNESCAPE_SEQUENCE;
//	escape_sequence_len = DELEGATE__UNESCAPE_SEQUENCE_LEN;
//	c = DELEGATE__UNESCAPE_REPLACEMENT_CHAR;
//
//	rc = utils__libc__unescape_buffer((char*)value, value_len, escape_sequence, escape_sequence_len, c, &value_new_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -100, "utils__libc__unescape_buffer() returned %d", rc);
//		return -100;
//	}
//
//	for (i = 0; i < DELEGATE__FIELDS_SEPARATORS_MAX; i++)
//	{
//		seps_len[i] = strlen(seps[i]);
//	}
//
//
//	
//	seps_count = DELEGATE__FIELDS_SEPARATORS_MAX;
//	tokens_max = DELEGATE__CONFIG__TOKENS_MAX;
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -200, "utils__libc__tokenize_string() returned %d", rc);
//		return -200;
//	}
//
//	(void)utils__libc__print_tokens(tokens, tokens_len, token_count);
//
//
//	rc = utils__libc__trim_tokens(&tokens[0], tokens_len, token_count, DELEGATE__CHARACTER_TO_TRIM);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "utils__libc__trim_tokens() returned %d", rc);
//		return -300;
//	}
//
//
//	(void)utils__libc__print_tokens(tokens, tokens_len, token_count);
//
//
//	if (token_count < 4)
//	{
//		utils__printf__error(&dele->pf, fn, -300, "token_count is %zu and it's out of range", token_count);
//		return -300;
//	}
//
//
//
//	/*
//	 * organization
//	 */
//	b = dele->machine[dele->number_of_machines].config.organization;
//	size = sizeof(dele->machine[dele->number_of_machines].config.organization);
//
//	rc = utils__libc__write_string(b, size, tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -400, "utils__libc__write_string() returned %d", rc);
//	}
//
//
//	/*
//	 * facility
//	 */
//	b = dele->machine[dele->number_of_machines].config.facility;
//	size = sizeof(dele->machine[dele->number_of_machines].config.facility);
//
//	rc = utils__libc__write_string(b, size, tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -400, "utils__libc__write_string() returned %d", rc);
//		return -400;
//	}
//
//	/*
//	 * department
//	 */
//	b = dele->machine[dele->number_of_machines].config.department;
//	size = sizeof(dele->machine[dele->number_of_machines].config.department);
//
//	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -500, "utils__libc__write_string() returned %d", rc);
//		return -500;
//	}
//
//
//	/*
//	 * name
//	 */
//	b = dele->machine[dele->number_of_machines].config.name;
//	size = sizeof(dele->machine[dele->number_of_machines].config.name);
//
//	rc = utils__libc__write_string(b, size, tokens[3], tokens_len[3]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn, -600, "utils__libc__write_string() returned %d", rc);
//		return -600;
//	}
//
//
//	return 0;
//}
//
//
//
///*
// * example of config file entry:
// *
// * MACHINE TECHNICAL DATA = SIEMENS 840D; ESA AUTOMATION VT550; 6000 kg; 55 kW
// *
// * tokens[0] = CNC NAME (SIEMENS 840D)
// * tokens[1] = HMI (ESA AUTOMATION VT550)
// * tokens[2] = WEIGHT (6000 kg)
// * tokens[3] = MAX POWER CONSUMPTION (55 kW)
// *
// */
//static int set_machine_technical_data(void* delegate, const char* value, size_t value_len)
//{
//	int rc;
//	size_t i;
//	char* tokens[16];
//	size_t tokens_len[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	char c;
//	delegate_t* dele;
//	const char* escape_sequence;
//	size_t escape_sequence_len;
//	size_t value_new_len;
//	char* fn_local;
//	char* b;
//	size_t size;
//	size_t seps_len[DELEGATE__FIELDS_SEPARATORS_MAX];
//	const char* seps[DELEGATE__FIELDS_SEPARATORS_MAX] = DELEGATE__FIELDS_SEPARATORS;
//
//
//	dele = (delegate_t*) delegate;
//	fn_local = "set_machine_location_data()";
//
//	i = dele->number_of_machines;
//
//
//	/*
//	 *  AGENT__CONFIG__UNESCAPE_SEQUENCE          =  \;
//	 *  AGENT__CONFIG__UNESCAPE_SEQUENCE_LEN      =  2
//	 *  AGENT__CONFIG__UNESCAPE_REPLACEMENT_CHAR  =  ;
//	 */
//	escape_sequence = DELEGATE__UNESCAPE_SEQUENCE;
//	escape_sequence_len = DELEGATE__UNESCAPE_SEQUENCE_LEN;
//	c = DELEGATE__UNESCAPE_REPLACEMENT_CHAR;
//
//	rc = utils__libc__unescape_buffer((char*)value, value_len, escape_sequence, escape_sequence_len, c, &value_new_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -100, "utils__libc__unescape_buffer() returned %d", rc);
//		return -100;
//	}
//
//	for (i = 0; i < DELEGATE__FIELDS_SEPARATORS_MAX; i++)
//	{
//		seps_len[i] = strlen(seps[i]);
//	}
//
//
//
//	seps_count = DELEGATE__FIELDS_SEPARATORS_MAX;
//	tokens_max = DELEGATE__CONFIG__TOKENS_MAX;
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -200, "utils__libc__tokenize_string() returned %d", rc);
//		return -200;
//	}
//
//
//	if (token_count < 4)
//	{
//		utils__printf__error(&dele->pf, fn_local, -300, "token_count is %zu and it's out of range", token_count);
//		return -300;
//	}
//
//	/*
//	 * cnc name
//	 */
//	b = dele->machine[dele->number_of_machines].config.cnc_name;
//	size = sizeof(dele->machine[dele->number_of_machines].config.cnc_name);
//
//	rc = utils__libc__write_string(b, size, tokens[0], tokens_len[0]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -400, "utils__libc__write_string() returned %d", rc);
//		return -400;
//	}
//
//	/*
//	 * hmi
//	 */
//	b = dele->machine[dele->number_of_machines].config.hmi;
//	size = sizeof(dele->machine[dele->number_of_machines].config.hmi);
//
//	rc = utils__libc__write_string(b, size, tokens[1], tokens_len[1]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -500, "utils__libc__write_string() returned %d", rc);
//		return -500;
//	}
//
//
//	/*
//	 * weight
//	 */
//	b = dele->machine[dele->number_of_machines].config.weight;
//	size = sizeof(dele->machine[dele->number_of_machines].config.name);
//
//	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -600, "utils__libc__write_string() returned %d", rc);
//		return -600;
//	}
//
//
//	/*
//	 * max_power_consumption
//	 */
//	b = dele->machine[dele->number_of_machines].config.max_power_consumption;
//	size = sizeof(dele->machine[dele->number_of_machines].config.max_power_consumption);
//
//	rc = utils__libc__write_string(b, size, tokens[3], tokens_len[3]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -700, "utils__libc__write_string() returned %d", rc);
//		return -700;
//	}
//
//	
//	return 0;
//}
//
//
//
///*
// * example of config file entry:
// *
// * MACHINE FEEDER DATA = YES; FUMAGALLI; A\;13-41; 1234; 2017; ????; 1000 kg;  22 kW
// *
// * tokens[0] = PRESENT (YES)
// * tokens[0] = MANUFACTURER (FUMAGALLI)
// * tokens[1] = MODEL (A;13-41)
// * tokens[2] = SERIAL NUMBER (1234)
// * tokens[3] = YEAR (2017)
// * tokens[4] = HMI (????)
// * tokens[5] = WEIGHT (1000 kg) 
// * tokens[6] = MAX POWER CONSUMPTION (22 kW)  
// *
// */
//
//char feeder_manufacturer[AGENT__CONFIG__BUFFER_SIZE_256];
//char feeder_model[AGENT__CONFIG__BUFFER_SIZE_256];
//char feeder_serial_number[AGENT__CONFIG__BUFFER_SIZE_256];
//char feeder_year[AGENT__CONFIG__BUFFER_SIZE_256];
//char feeder_hmi[AGENT__CONFIG__BUFFER_SIZE_256];
//char feeder_weight[AGENT__CONFIG__BUFFER_SIZE_256];
//char feeder_max_power_consumption[AGENT__CONFIG__BUFFER_SIZE_256];
//
//static int set_machine_feeder_data(void* delegate, const char* value, size_t value_len)
//{
//	int rc;
//	size_t i;
//	int* int_data;
//	char* tokens[16];
//	size_t tokens_len[DELEGATE__CONFIG__TOKENS_MAX];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	char c;
//	delegate_t* dele;
//	const char* escape_sequence;
//	size_t escape_sequence_len;
//	size_t value_new_len;
//	char* fn_local;
//	char* b;
//	size_t size;
//	size_t seps_len[DELEGATE__FIELDS_SEPARATORS_MAX];
//	const char* seps[DELEGATE__FIELDS_SEPARATORS_MAX] = DELEGATE__FIELDS_SEPARATORS;
//
//
//	dele = (delegate_t*) delegate;
//	fn_local = "set_machine_plate_data()";
//
//	i = dele->number_of_machines;
//
//
//	/*
//	 *  AGENT__CONFIG__UNESCAPE_SEQUENCE          =  \;
//	 *  AGENT__CONFIG__UNESCAPE_SEQUENCE_LEN      =  2
//	 *  AGENT__CONFIG__UNESCAPE_REPLACEMENT_CHAR  =  ;
//	 */
//	escape_sequence = DELEGATE__UNESCAPE_SEQUENCE;
//	escape_sequence_len = DELEGATE__UNESCAPE_SEQUENCE_LEN;
//	c = DELEGATE__UNESCAPE_REPLACEMENT_CHAR;
//
//	rc = utils__libc__unescape_buffer((char*)value, value_len, escape_sequence, escape_sequence_len, c, &value_new_len);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -100, "utils__libc__unescape_buffer() returned %d", rc);
//		return -100;
//	}
//
//	for (i = 0; i < DELEGATE__FIELDS_SEPARATORS_MAX; i++)
//	{
//		seps_len[i] = strlen(seps[i]);
//	}
//
//
//	seps_count = DELEGATE__FIELDS_SEPARATORS_MAX;
//	tokens_max = DELEGATE__CONFIG__TOKENS_MAX;
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -200, "utils__libc__tokenize_string() returned %d", rc);
//		return -200;
//	}
//
//
//	if (token_count < 7)
//	{
//		utils__printf__error(&dele->pf, fn_local, -300, "token_count is %zu and it's out of range", token_count);
//		return -300;
//	}
//
//
//	/*
//	 * yes | no
//	 */
//	int_data = &dele->machine[i].config.feeder_present;
//
//	rc = utils__libc__write_1_or_0(int_data, tokens[0], tokens_len[1]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -400, "utils__libc__write_1_or_0() returned %d", rc);
//		return -400;
//	}
//
//
//	/*
//	 * feeder manufacturer
//	 */
//	b = dele->machine[dele->number_of_machines].config.feeder_manufacturer;
//	size = sizeof(dele->machine[dele->number_of_machines].config.feeder_manufacturer);
//
//	rc = utils__libc__write_string(b, size, tokens[1], tokens_len[1]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -500, "utils__libc__write_string() returned %d", rc);
//		return -500;
//	}
//
//	/*
//	 * feeder model
//	 */
//	b = dele->machine[dele->number_of_machines].config.feeder_model;
//	size = sizeof(dele->machine[dele->number_of_machines].config.feeder_model);
//
//	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -600, "feeder model - utils__libc__write_string() returned %d", rc);
//		return -600;
//	}
//
//
//	/*
//	 * feeder serial number
//	 */
//	b = dele->machine[dele->number_of_machines].config.feeder_serial_number;
//	size = sizeof(dele->machine[dele->number_of_machines].config.feeder_serial_number);
//
//	rc = utils__libc__write_string(b, size, tokens[2], tokens_len[2]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -600, "utils__libc__write_string() returned %d", rc);
//		return -600;
//	}
//
//	/*
//	 * cnc
//	 */
//	int_data = &dele->machine[dele->number_of_machines].config.cnc;
//
//	rc = utils__libc__write_1_or_0(int_data, tokens[3], tokens_len[3]);
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -700, "utils__libc__write_1_or_0() returned %d", rc);
//		return -700;
//	}
//
//	/*
//	 * year
//	 */
//	b = dele->machine[dele->number_of_machines].config.year;
//	size = sizeof(dele->machine[dele->number_of_machines].config.model);
//
//	rc = utils__libc__write_string(b, size, tokens[4], tokens_len[4]);
//
//	if (rc != 0)
//	{
//		utils__printf__error(&dele->pf, fn_local, -800, "utils__libc__write_string() returned %d", rc);
//		return -800;
//	}
//
//
//	return 0;
//}
//
//
//
//static int set_type(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*) delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.type;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.type);
//
//	rc = utils__libc__write_option(buffer, buffer_size, value, value_len, "CNC", 3, "NO CNC", 6);
//
//	return rc;
//}
//
//static int set_operating(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	int* data;
//	subagent_t* a;
//
//	a = (subagent_t*) delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.active;
//
//	rc = utils__libc__write_1_or_0(data, value, value_len);
//
//	return rc;
//
//}
//
//static int set_networked (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	int* data;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.networked;
//
//	rc = utils__libc__write_1_or_0(data, value, value_len);
//
//	return rc;
//
//}
//
//static int set_simulated (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	int* data;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.operating_mode;
//
//	rc = utils__libc__write_1_or_0(data, value, value_len);
//
//	return rc;
//}
//
//static int set_connection_timeout_seconds(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	size_t* data;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.connection_timeout_seconds;
//
//	rc = utils__libc__write_size_t(data, value, value_len);
//	if (rc != 0)
//	{
//		return -100;
//	}
//
//	if (dele->machine[dele->number_of_machines].config.connection_timeout_seconds == 0)
//	{
//		return -200;
//	}
//
//	return 0;
//
//}
//
//static int set_reconnection_attempts_time_interval_seconds(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	size_t* data;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.reconnection_attempts_time_interval_seconds;
//
//	rc = utils__libc__write_size_t(data, value, value_len);
//	if (rc != 0)
//	{
//		return -100;
//	}
//
//	if (dele->machine[dele->number_of_machines].config.reconnection_attempts_time_interval_seconds == 0)
//	{
//		return -200;
//	}
//
//	return 0;
//
//}
//
//static int set_no_response_timeout_seconds(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	size_t* data;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.no_response_timeout_seconds;
//
//	rc = utils__libc__write_size_t(data, value, value_len);
//	if (rc != 0)
//	{
//		return -100;
//	}
//
//	if (dele->machine[dele->number_of_machines].config.no_response_timeout_seconds == 0)
//	{
//		return -200;
//	}
//
//	return 0;
//
//}
//
//static int set_max_reconnection_attempts(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	size_t* data;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.max_reconnection_attempts;
//
//	rc = utils__libc__write_size_t(data, value, value_len);
//
//	return rc;
//
//}
//
//static int set_part_program_name_in_simulation_mode(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.part_program_name_in_simulation_mode;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.part_program_name_in_simulation_mode);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//
//}
//
//static int set_part_counter_initial_value_in_simulation_mode (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	size_t* data;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.part_counter_initial_value_in_simulation_mode;
//
//	rc = utils__libc__write_size_t(data, value, value_len);
//
//	return rc;
//
//}
//
//static int set_average_cycle_time_seconds_in_simulation_mode(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	double* data;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	data = &dele->machine[dele->number_of_machines].config.average_cycle_time_in_simulation_mode_seconds;
//
//	rc = utils__libc__write_double(data, value, value_len);
//
//	if (dele->machine[dele->number_of_machines].config.average_cycle_time_in_simulation_mode_seconds < 1)
//	{
//		return -100;
//	}
//
//	return rc;
//
//}
//
//static int set_manufacturer(void* delegate, const char* value, size_t value_len)
//{
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.manufacturer;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.manufacturer);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//
//}
//
//static int set_model(void* delegate, const char* value, size_t value_len)
//{
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.model;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.model);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_serial_number(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.serial_number;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.serial_number);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//
//}
//
//static int set_name(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.name;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.name);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_facility(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.facility;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.facility);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_department(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.department;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.department);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_cnc_name(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.cnc_name;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.cnc_name);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//
//}
//
//static int set_opc_ipv4_address (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_ipv4_address;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_ipv4_address);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_opc_ipv4_port(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_ipv4_port;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_ipv4_port);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return 0;
//}
//
//static int set_opc_user_name(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_user_name;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_user_name);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//
//}
//
//static int set_opc_password (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_password;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_password);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//
//}
//
//static int set_opc_connection_data (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	size_t i;
//	int* data_int;
//	size_t* data_sizet;
//	const char* seps[3] = { ",", " ", "\t" };
//	size_t seps_len[3];
//	char* tokens[16];
//	size_t tokens_len[16];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	int count_empty_tokens;
//	size_t j;
//	subagent_t* a;
//
//	a = (subagent_t*) delegate;
//
//
//	i = dele->number_of_machines;
//
//	for (j = 0; j < 3; j++)
//	{
//		seps_len[j] = strlen(seps[j]);
//	}
//
//
//	count_empty_tokens = 0;
//	seps_count = 3;
//	tokens_max = 16;
//
//	rc = utils__libc__tokenize_string(value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count, count_empty_tokens);
//	if (rc != 0)
//	{
//		return -100;
//	}
//
//	if (token_count < 6)
//	{
//		return -200;
//	}
//
//	/*
//	 * yes | no
//	 */
//	data_int = &dele->machine[i].config.cycle_time_fpc.do_estimation;
//
//	rc = utils__libc__write_1_or_0(data_int, tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		return -300;
//	}
//
//
//	/*
//	 * time to first estimation after boot in seconds - 0 wiil be set to 1
//	 */
//	data_sizet = &dele->machine[i].config.cycle_time_fpc.time_to_first_estimation_seconds;
//
//	rc = utils__libc__write_size_t(data_sizet, tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		return -400;
//	}
//
//	if (dele->machine[i].config.cycle_time_fpc.time_to_first_estimation_seconds == 0)
//	{
//		dele->machine[i].config.cycle_time_fpc.time_to_first_estimation_seconds = 1;
//	}
//
//
//
//	/*
//	 * time interval for estimations seconds - 0 wiil be set to 1
//	 */
//	data_sizet = &dele->machine[i].config.cycle_time_fpc.time_interval_for_estimations_seconds;
//
//	rc = utils__libc__write_size_t(data_sizet, tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		return -500;
//	}
//
//	if (dele->machine[i].config.cycle_time_fpc.time_interval_for_estimations_seconds == 0)
//	{
//		dele->machine[i].config.cycle_time_fpc.time_interval_for_estimations_seconds = 1;
//	}
//
//
//
//	/*
//	 * timeout before restarting an estimation in seconds - 0 wiil be set to 60
//	 */
//	data_sizet = &dele->machine[i].config.cycle_time_fpc.timeout_seconds;
//
//	rc = rc = utils__libc__write_size_t(data_sizet, tokens[3], tokens_len[3]);
//	if (rc != 0)
//	{
//		return -600;
//	}
//
//	if (dele->machine[i].config.cycle_time_fpc.timeout_seconds == 0)
//	{
//		dele->machine[i].config.cycle_time_fpc.timeout_seconds = 60;
//	}
//
//
//
//	/*
//	 * timeout before restarting an estimation in seconds - 0 wiil be set to 60
//	 */
//	data_sizet = &dele->machine[i].config.cycle_time_fpc.minium_acceptable_cycle_time_seconds;
//
//	rc = rc = utils__libc__write_size_t(data_sizet, tokens[4], tokens_len[4]);
//	if (rc != 0)
//	{
//		return -700;
//	}
//
//	if (dele->machine[i].config.cycle_time_fpc.minium_acceptable_cycle_time_seconds == 0)
//	{
//		dele->machine[i].config.cycle_time_fpc.timeout_seconds = 1;
//	}
//
//
//
//	/*
//	 * enable printf: yes | no
//	 */
//	data_int = &dele->machine[i].config.cycle_time_fpc.enable_printf;
//
//	rc = utils__libc__write_1_or_0(data_int, tokens[5], tokens_len[5]);
//	if (rc != 0)
//	{
//		return -800;
//	}
//
//	return 0;
//
//}
//
//static int set_opc_certificate_file (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_certificate_file;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_certificate_file);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//
//}
//
//static int set_opc_private_key_file (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_private_key_file;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_private_key_file);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_opc_part_counter_path(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_part_counter_path;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_part_counter_path);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_opc_cycle_time_path (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_cycle_time_path;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_cycle_time_path);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_opc_part_program_name_path(void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//	buffer = dele->machine[dele->number_of_machines].config.opc_part_program_name_path;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.opc_part_program_name_path);
//
//	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);
//
//	return rc;
//}
//
//static int set_part_program_name_filter (void* delegate, const char* value, size_t value_len)
//{
//
//	int rc;
//	size_t i;
//	int* data_int;
//	const char* seps[3] = {",", " ", "\t"};
//	size_t seps_len[3];
//	char* tokens[16];
//	size_t tokens_len[16];
//	size_t tokens_max;
//	size_t token_count;
//	size_t seps_count;
//	int count_empty_tokens;
//	size_t j;
//	char* buffer;
//	size_t buffer_size;
//	subagent_t* a;
//
//	a = (subagent_t*)delegate;
//
//
//	i = dele->number_of_machines;
//
//	for (j = 0; j < 3; j++)
//	{
//		seps_len[j] = strlen(seps[j]);	
//	}
//
//
//	count_empty_tokens = 0;
//	seps_count = 3;
//	tokens_max = 16;
//
//	rc = utils__libc__tokenize_string (value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count, count_empty_tokens);
//	if (rc != 0)
//	{
//		return -100;
//	}
//
//	if (token_count < 3)
//	{
//		return -200;
//	}
//
//	/*
//	 * yes | no
//	 */
//	data_int = &dele->machine[i].config.part_program_name_filter.do_filtering;
//
//	rc = utils__libc__write_1_or_0(data_int, tokens[0], tokens_len[0]);
//	if (rc != 0)
//	{
//		return -300;
//	}
//
//
//	/*
//	 * prefix
//	 */
//	buffer = dele->machine[dele->number_of_machines].config.part_program_name_filter.prefix;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.part_program_name_filter.prefix);
//
//	rc = utils__libc__write_string(buffer, buffer_size, tokens[1], tokens_len[1]);
//	if (rc != 0)
//	{
//		return -400;
//	}
//	
//	dele->machine[dele->number_of_machines].config.part_program_name_filter.prefix_len = strlen(buffer);
//
//
//	/*
//	 * suffix
//	 */
//	buffer = dele->machine[dele->number_of_machines].config.part_program_name_filter.suffix;
//	buffer_size = sizeof(dele->machine[dele->number_of_machines].config.part_program_name_filter.suffix);
//
//	rc = utils__libc__write_string(buffer, buffer_size, tokens[2], tokens_len[2]);
//	if (rc != 0)
//	{
//		return -500;
//	}
//
//	dele->machine[dele->number_of_machines].config.part_program_name_filter.suffix_len = strlen(buffer);
//
//	if ((dele->machine[dele->number_of_machines].config.part_program_name_filter.prefix_len == 0) && (dele->machine[dele->number_of_machines].config.part_program_name_filter.suffix_len == 0))
//	{
//		dele->machine[i].config.part_program_name_filter.do_filtering = 0;
//	}
//
//	return 0;
//
//}
//
//
//
//
//static int set_type(void* delegate, const char* value, size_t value_len);
//static int set_operating(void* delegate, const char* value, size_t value_len);
//static int set_networked(void* delegate, const char* value, size_t value_len);
//static int set_simulated(void* delegate, const char* value, size_t value_len);
//
//static int set_connection_timeout_seconds(void* delegate, const char* value, size_t value_len);
//static int set_reconnection_attempts_time_interval_seconds(void* delegate, const char* value, size_t value_len);
//static int set_max_reconnection_attempts(void* delegate, const char* value, size_t value_len);
//static int set_no_response_timeout_seconds(void* delegate, const char* value, size_t value_len);
//static int set_manufacturer(void* delegate, const char* value, size_t value_len);
//static int set_part_program_name_in_simulation_mode(void* delegate, const char* value, size_t value_len);
//static int set_part_counter_initial_value_in_simulation_mode(void* delegate, const char* value, size_t value_len);
//static int set_average_cycle_time_seconds_in_simulation_mode(void* delegate, const char* value, size_t value_len);
//
//static int set_model(void* delegate, const char* value, size_t value_len);
//static int set_serial_number(void* delegate, const char* value, size_t value_len);
//static int set_name(void* delegate, const char* value, size_t value_len);
//static int set_facility(void* delegate, const char* value, size_t value_len);
//static int set_department(void* delegate, const char* value, size_t value_len);
//
//static int set_cnc_name(void* delegate, const char* value, size_t value_len);
//
//static int set_opc_ipv4_address(void* delegate, const char* value, size_t value_len);
//static int set_opc_ipv4_port(void* delegate, const char* value, size_t value_len);
//static int set_opc_user_name(void* delegate, const char* value, size_t value_len);
//static int set_opc_password(void* delegate, const char* value, size_t value_len);
//static int set_opc_certificate_file(void* delegate, const char* value, size_t value_len);
//
//static int set_opc_connection_data(void* delegate, const char* value, size_t value_len);
//
//static int set_opc_private_key_file(void* delegate, const char* value, size_t value_len);
//static int set_opc_part_counter_path(void* delegate, const char* value, size_t value_len);
//static int set_opc_cycle_time_path(void* delegate, const char* value, size_t value_len);
//static int set_opc_part_program_name_path(void* delegate, const char* value, size_t value_len);
//static int set_part_program_name_filter(void* delegate, const char* value, size_t value_len);
//
//
//
//
//
//{"MANUFACTURER",                                    set_manufacturer                                     },
//{"MODEL",                                           set_model                                            },
//{"SERIAL NUMBER",                                   set_serial_number                                    },
//{"CNC",                                             set_type                                             },
//{"YEAR",                                            set_year                                             },//// // 
// 
// 
//{"NAME",                                            set_name                                             },
//{"FACILITY",                                        set_facility                                         },
//{"DEPARTMENT",                                      set_department                                       },
// 
//{"CNC NAME",                                        set_cnc_name                                         },
//
//
//{"TYPE",                                            set_type                                             },
//{"MANUFACTURER",                                    set_manufacturer                                     },
//{"MODEL",                                           set_model                                            },
//{"SERIAL NUMBER",                                   set_serial_number                                    },
//{"NAME",                                            set_name                                             },
//{"FACILITY",                                        set_facility                                         },
//{"DEPARTMENT",                                      set_department                                       },
//
//
//{"TYPE",                                            set_type                                             },
//{"MANUFACTURER",                                    set_manufacturer                                     },
//{"MODEL",                                           set_model                                            },
//{"SERIAL NUMBER",                                   set_serial_number                                    },
//{"NAME",                                            set_name                                             },
//{"FACILITY",                                        set_facility                                         },
//{"DEPARTMENT",                                      set_department                                       },
//
//
//
//{"TYPE",                                            set_type                                             },
//{"YEAR",                                            set_year                                             },// 
//{"MANUFACTURER",                                    set_manufacturer                                     },
//{"MODEL",                                           set_model                                            },
//{"SERIAL NUMBER",                                   set_serial_number                                    },
//{"NAME",                                            set_name                                             },
//{"FACILITY",                                        set_facility                                         },
//{"DEPARTMENT",                                      set_department                                       }
//
//
//
//
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
//
//
