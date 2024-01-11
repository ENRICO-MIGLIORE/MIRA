#include "siemens_open62541__private.h"


static int found_agent_section(const char* section_name, size_t section_name_len);

static int set_id(const char* value, size_t value_len);
static int set_type(const char* value, size_t value_len);
static int set_operating(const char* value, size_t value_len);
static int set_networked(const char* value, size_t value_len);
static int set_simulated(const char* value, size_t value_len);

static int set_connection_timeout_seconds(const char* value, size_t value_len);
static int set_reconnection_attempts_time_interval_seconds(const char* value, size_t value_len);
static int set_max_reconnection_attempts(const char* value, size_t value_len);
static int set_no_response_timeout_seconds(const char* value, size_t value_len);
static int set_manufacturer(const char* value, size_t value_len);
static int set_part_program_name_in_simulation_mode(const char* value, size_t value_len);
static int set_part_counter_initial_value_in_simulation_mode(const char* value, size_t value_len);
static int set_average_cycle_time_seconds_in_simulation_mode(const char* value, size_t value_len);

static int set_model(const char* value, size_t value_len);
static int set_serial_number(const char* value, size_t value_len);
static int set_name(const char* value, size_t value_len);
static int set_facility(const char* value, size_t value_len);
static int set_department(const char* value, size_t value_len);

static int set_cnc_name(const char* value, size_t value_len);

static int set_opc_ipv4_address(const char* value, size_t value_len);
static int set_opc_ipv4_port(const char* value, size_t value_len);
static int set_opc_user_name(const char* value, size_t value_len);
static int set_opc_password(const char* value, size_t value_len);
static int set_opc_certificate_file(const char* value, size_t value_len);
static int set_opc_private_key_file(const char* value, size_t value_len);
static int set_opc_part_counter_path(const char* value, size_t value_len);
static int set_opc_cycle_time_path(const char* value, size_t value_len);
static int set_opc_part_program_name_path(const char* value, size_t value_len);
static int set_part_program_name_filter(const char* value, size_t value_len);




static utils__sdb__section_callback_t section;


static utils__sdb__value_callback_t names_values[] =
{ 

  {"ID",                                              set_id                                               },
  {"TYPE",                                            set_type                                             },
  {"OPERATING",                                       set_operating                                        },
  {"NETWORKED",                                       set_networked                                        },
  {"SIMULATED",                                       set_simulated                                        },

  {"CONNECTION TIMEOUT SECONDS",                      set_connection_timeout_seconds                       },
  {"RECONNECTION ATTEMPTS TIME INTERVAL SECONDS",     set_reconnection_attempts_time_interval_seconds      },
  {"MAX RECONNECTION ATTEMPTS",                       set_max_reconnection_attempts                        },
  {"NO RESPONSE TIMEOUT SECONDS",                     set_no_response_timeout_seconds                      },
  {"PART PROGRAM NAME IN SIMULATION MODE",            set_part_program_name_in_simulation_mode             },
  {"PART COUNTER INITIAL VALUE IN SIMULATION MODE",   set_part_counter_initial_value_in_simulation_mode    },
  {"AVERAGE CYCLE TIME SECONDS IN SIMULATION MODE",   set_average_cycle_time_seconds_in_simulation_mode    },

  {"MANUFACTURER",                                    set_manufacturer                                     },
  {"MODEL",                                           set_model                                            },
  {"SERIAL NUMBER",                                   set_serial_number                                    },
  {"NAME",                                            set_name                                             },
  {"FACILITY",                                        set_facility                                         },
  {"DEPARTMENT",                                      set_department                                       },

  {"CNC NAME",                                        set_cnc_name                                         },

  {"OPC IP-V4 ADDRESS",                               set_opc_ipv4_address                                 },
  {"OPC IP-V4 PORT",                                  set_opc_ipv4_port                                    },
  {"OPC USER NAME",                                   set_opc_user_name                                    },
  {"OPC PASSWORD",                                    set_opc_password                                     },
  {"OPC CERTIFICATE FILE",                            set_opc_certificate_file                             },
  {"OPC PRIVATE KEY FILE",                            set_opc_private_key_file                             },
  {"OPC PART COUNTER PATH",                           set_opc_part_counter_path                            },
  {"OPC CYCLE TIME PATH",                             set_opc_cycle_time_path                              },
  {"OPC PART PROGRAM NAME PATH",                      set_opc_part_program_name_path                       },
  {"PART PROGRAM NAME FILTER",                        set_part_program_name_filter                         }


};


static char* fn = "siemens_open62541__private__load_machines_configuration()";

/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */

int siemens_open62541__private__load_machines_configuration(void)
{

	int rc;
	int i;
	int j;
	size_t record_number;
	size_t start_record;
	size_t machine_names_values_max;
	int done;
	size_t section_count;
	size_t size;
	int end_of_file;
	size_t len;
	void* p;

	p = NULL;


	/*
	 * Count the number of sections: [SIEMENS-OPEN62541 MACHINE]
	 */
	start_record = 1;

	if (so->config_mode == 0)
	{
		rc = utils__sdb__count_sections_from_file(&so->sdb, so->agent_configuration_file_name, so->machines_section_name, start_record, &section_count, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__sdb__count_sections_from_file() returned %d", fn, rc);
			return -100;
		}
	}
	else
	{
		rc = utils__sdb__count_sections_from_buffer(&so->sdb, so->agent_configuration_file_name, so->machines_section_name, start_record, &section_count, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__sdb__count_sections_from_buffer() returned %d", fn, rc);
			return -100;
		}
	}

	if (section_count == 0)
	{
		printf("%s - error - can't find [%s] sections in the configuration file\n", fn, so->machines_section_name);
		return -200;
	}


	/*
	 * Allocate memory for the machines
	 */
	size = sizeof(siemens_open62541__machine_t) * section_count;

	so->machine = (siemens_open62541__machine_t*) malloc(size);

	if (so->machine == NULL)
	{
		printf("%s - error - malloc() error\n", fn);
		return -300;
	}

	memset(so->machine, '\0', size);



	/*
	 * Set section data of the machines: [SIEMENS-OPEN62541 MACHINE]
	 */
	section.name = so->machines_section_name;
	section.function = found_agent_section;
	machine_names_values_max = sizeof(names_values) / sizeof(utils__sdb__value_callback_t);

	so->machine_count = 0;
	so->machine_count_flag = 0;

	done = 0;
	start_record = 1;
	do
	{
		if (so->config_mode == 0)
		{
			rc = utils__sdb__read_configuration_from_file(p, &so->sdb, so->agent_configuration_file_name, &section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		else
		{
			rc = utils__sdb__read_configuration_from_buffer(p, &so->sdb, so->agent_configuration_file_name, &section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		
		if (rc != 0)
		{
			if (end_of_file == 0)
			{
				if (so->config_mode)
				{
					printf("%s - error - utils__sdb__read_configuration_file() returned %d\n", fn, rc);

				}
				else
				{
					printf("%s - error - utils__sdb__read_configuration_from_buffer() returned %d\n", fn, rc);
				}
				return -400;
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


	so->machine_count++;


	if (so->machine_count != section_count)
	{
		printf("%s - error - so->machine_count != section_count\n", fn);
		return -400;
	}



	if (so->machine_count > 1)
	{	

		/*
		 * Check for duplicate machines' ID
		 */
		for (i = 0; i < so->machine_count; i++)
		{
			for (j = i + 1; j < so->machine_count; j++)
			{
				if (so->machine[i].config.id == so->machine[j].config.id)
				{
					printf("%s - error - Duplicate id found - id = %d\n", fn, so->machine[i].config.id);
					return -500;
				}
			}
		}


		/*
		 * Check for potential buffer overflow
		 */
		for (i = 0; i < so->machine_count; i++)
		{

			len = strlen(so->machine[i].config.part_program_name_in_simulation_mode);

			if (len > sizeof(so->machine[i].part_program_name_simulated))
			{
				printf("%s - error - len > so->machine[%d].part_program_name_utf_8_simulated\n", fn, so->machine[i].config.id);
				return -600;
			}

			if (len > sizeof(so->machine[i].part_program_name_utf_8))
			{
				printf("%s - error - len > so->machine[%d].part_program_name_utf_8\n", fn, so->machine[i].config.id);
				return -700;
			}
		}
	}



	for (i = 0; i < so->machine_count; i++)
	{
		sprintf(so->machine[i].name_and_index, "%s %d", so->machines_section_name, i + 1);
		so->machine[i].name_and_index_len = strlen(so->machine[i].name_and_index);
	}

	return 0;
}

static int found_agent_section (const char* section_name, size_t section_name_len)
{

	if (section_name == NULL)
	{
		return -100;
	}

	if (section_name_len > UTILS__SDB__SECTION_NAME_SIZE)
	{
		return -200;
	}

	if (so->machine_count_flag == 0)
	{
		so->machine_count_flag = 1;
	}
	else
	{
		so->machine_count++;
	}

	return 0;
}

static int set_id (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->machine[so->machine_count].config.id;

	rc = utils__libc__write_int(data, value, value_len);

	return rc;
}

static int set_type(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.type;
	buffer_size = sizeof(so->machine[so->machine_count].config.type);

	rc = utils__libc__write_option(buffer, buffer_size, value, value_len, "CNC", 3, "NO CNC", 6);

	return rc;
}

static int set_operating(const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->machine[so->machine_count].config.operating;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

static int set_networked (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->machine[so->machine_count].config.networked;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

static int set_simulated (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->machine[so->machine_count].config.simulated;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;
}

static int set_connection_timeout_seconds(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.connection_timeout_seconds;

	rc = utils__libc__write_size_t(data, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (so->machine[so->machine_count].config.connection_timeout_seconds == 0)
	{
		return -200;
	}

	return 0;

}

static int set_reconnection_attempts_time_interval_seconds(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.reconnection_attempts_time_interval_seconds;

	rc = utils__libc__write_size_t(data, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (so->machine[so->machine_count].config.reconnection_attempts_time_interval_seconds == 0)
	{
		return -200;
	}

	return 0;

}

static int set_no_response_timeout_seconds(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.no_response_timeout_seconds;

	rc = utils__libc__write_size_t(data, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (so->machine[so->machine_count].config.no_response_timeout_seconds == 0)
	{
		return -200;
	}

	return 0;

}

static int set_max_reconnection_attempts(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.max_reconnection_attempts;

	rc = utils__libc__write_size_t(data, value, value_len);

	return rc;

}

static int set_part_program_name_in_simulation_mode(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.part_program_name_in_simulation_mode;
	buffer_size = sizeof(so->machine[so->machine_count].config.part_program_name_in_simulation_mode);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_part_counter_initial_value_in_simulation_mode (const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.part_counter_initial_value_in_simulation_mode;

	rc = utils__libc__write_size_t(data, value, value_len);

	return rc;

}

static int set_average_cycle_time_seconds_in_simulation_mode(const char* value, size_t value_len)
{

	int rc;
	double* data;

	data = &so->machine[so->machine_count].config.average_cycle_time_in_simulation_mode_seconds;

	rc = utils__libc__write_double(data, value, value_len);

	if (so->machine[so->machine_count].config.average_cycle_time_in_simulation_mode_seconds < 1)
	{
		return -100;
	}

	return rc;

}


static int set_manufacturer(const char* value, size_t value_len)
{
	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.manufacturer;
	buffer_size = sizeof(so->machine[so->machine_count].config.manufacturer);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_model(const char* value, size_t value_len)
{
	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.model;
	buffer_size = sizeof(so->machine[so->machine_count].config.model);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_serial_number(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.serial_number;
	buffer_size = sizeof(so->machine[so->machine_count].config.serial_number);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_name(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.name;
	buffer_size = sizeof(so->machine[so->machine_count].config.name);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_facility(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.facility;
	buffer_size = sizeof(so->machine[so->machine_count].config.facility);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_department(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.department;
	buffer_size = sizeof(so->machine[so->machine_count].config.department);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}



static int set_cnc_name(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.cnc_name;
	buffer_size = sizeof(so->machine[so->machine_count].config.cnc_name);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_opc_ipv4_address (const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_ipv4_address;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_ipv4_address);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_opc_ipv4_port(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;


	buffer = so->machine[so->machine_count].config.opc_ipv4_port;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_ipv4_port);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return 0;
}

static int set_opc_user_name(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_user_name;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_user_name);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_opc_password (const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_password;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_password);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_opc_certificate_file (const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_certificate_file;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_certificate_file);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_opc_private_key_file (const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_private_key_file;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_private_key_file);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_opc_part_counter_path(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_part_counter_path;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_part_counter_path);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_opc_cycle_time_path (const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_cycle_time_path;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_cycle_time_path);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}


static int set_opc_part_program_name_path(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_part_program_name_path;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_part_program_name_path);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}


static int set_part_program_name_filter (const char* value, size_t value_len)
{

	int rc;
	size_t i;
	int* data_int;
	const char* seps[3] = {",", " ", "\t"};
	size_t seps_len[3];
	char* tokens[16];
	size_t tokens_len[16];
	size_t tokens_max;
	size_t token_count;
	size_t seps_count;
	int count_empty_tokens;
	size_t j;
	char* buffer;
	size_t buffer_size;


	i = so->machine_count;

	for (j = 0; j < 3; j++)
	{
		seps_len[j] = strlen(seps[j]);	
	}


	count_empty_tokens = 0;
	seps_count = 3;
	tokens_max = 16;

	rc = utils__libc__tokenize_string (value, value_len, seps, &seps_len[0], seps_count, &tokens[0], tokens_len, tokens_max, &token_count, count_empty_tokens);
	if (rc != 0)
	{
		return -100;
	}

	if (token_count < 3)
	{
		return -200;
	}

	/*
	 * yes | no
	 */
	data_int = &so->machine[i].config.part_program_name_filter.do_filtering;

	rc = utils__libc__write_yes_or_no(data_int, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		return -300;
	}


	/*
	 * prefix
	 */
	buffer = so->machine[so->machine_count].config.part_program_name_filter.prefix;
	buffer_size = sizeof(so->machine[so->machine_count].config.part_program_name_filter.prefix);

	rc = utils__libc__write_string(buffer, buffer_size, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		return -400;
	}
	
	so->machine[so->machine_count].config.part_program_name_filter.prefix_len = strlen(buffer);


	/*
	 * suffix
	 */
	buffer = so->machine[so->machine_count].config.part_program_name_filter.suffix;
	buffer_size = sizeof(so->machine[so->machine_count].config.part_program_name_filter.suffix);

	rc = utils__libc__write_string(buffer, buffer_size, tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		return -500;
	}

	so->machine[so->machine_count].config.part_program_name_filter.suffix_len = strlen(buffer);

	if ((so->machine[so->machine_count].config.part_program_name_filter.prefix_len == 0) && (so->machine[so->machine_count].config.part_program_name_filter.suffix_len == 0))
	{
		so->machine[i].config.part_program_name_filter.do_filtering = 0;
	}

	return 0;

}
