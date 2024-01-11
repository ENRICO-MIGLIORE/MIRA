#include "siemens_open62541__private.h"


static int found_section_name(const char* section_name, size_t section_name_len);

static int set_id(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_operating(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_online(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_connection_timeout_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_reconnection_attempts_time_interval_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_max_reconnection_attempts(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_no_response_timeout_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_manufacturer(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_part_program_name_in_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_part_counter_initial_value_in_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_average_cycle_time_seconds_in_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_model(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_serial_number(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_facility(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_cnc_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_opc_ipv4_address(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_opc_ipv4_port(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_opc_user_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_opc_password(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_opc_certificate_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_opc_private_key_file(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_opc_part_counter_path(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_opc_cycle_time_path(const char* section_name, size_t section_name_len, const char* value, size_t value_len);


static utils__cf__section_callback_t section;


static utils__cf__name_value_callback_t names_values[] =
{ 

  {"SIEMENS-OPEN62541 MACHINE",     "ID",                                              set_id                                               },
  {"SIEMENS-OPEN62541 MACHINE",     "OPERATING",                                       set_operating                                        },
  {"SIEMENS-OPEN62541 MACHINE",     "ONLINE",                                          set_online                                           },
  {"SIEMENS-OPEN62541 MACHINE",     "SIMULATION MODE",                                 set_simulation_mode                                  },
  {"SIEMENS-OPEN62541 MACHINE",     "CONNECTION TIMEOUT SECONDS",                      set_connection_timeout_seconds                       },
  {"SIEMENS-OPEN62541 MACHINE",     "RECONNECTION ATTEMPTS TIME INTERVAL SECONDS",     set_reconnection_attempts_time_interval_seconds      },
  {"SIEMENS-OPEN62541 MACHINE",     "MAX RECONNECTION ATTEMPTS",                       set_max_reconnection_attempts                        },
  {"SIEMENS-OPEN62541 MACHINE",     "NO RESPONSE TIMEOUT SECONDS",                     set_no_response_timeout_seconds                      },
  {"SIEMENS-OPEN62541 MACHINE",     "PART PROGRAM NAME IN SIMULATION MODE",            set_part_program_name_in_simulation_mode             },
  {"SIEMENS-OPEN62541 MACHINE",     "PART COUNTER INITIAL VALUE IN SIMULATION MODE",   set_part_counter_initial_value_in_simulation_mode    },
  {"SIEMENS-OPEN62541 MACHINE",     "AVERAGE CYCLE TIME SECONDS IN SIMULATION MODE",   set_average_cycle_time_seconds_in_simulation_mode    },
  {"SIEMENS-OPEN62541 MACHINE",     "MANUFACTURER",                                    set_manufacturer                                     },
  {"SIEMENS-OPEN62541 MACHINE",     "MODEL",                                           set_model                                            },
  {"SIEMENS-OPEN62541 MACHINE",     "SERIAL NUMBER",                                   set_serial_number                                    },
  {"SIEMENS-OPEN62541 MACHINE",     "NAME",                                            set_name                                             },
  {"SIEMENS-OPEN62541 MACHINE",     "FACILITY",                                        set_facility                                         },
  {"SIEMENS-OPEN62541 MACHINE",     "CNC NAME",                                        set_cnc_name                                         },
  {"SIEMENS-OPEN62541 MACHINE",     "OPC IP-V4 ADDRESS",                               set_opc_ipv4_address                                 },
  {"SIEMENS-OPEN62541 MACHINE",     "OPC IP-V4 PORT",                                  set_opc_ipv4_port                                    },
  {"SIEMENS-OPEN62541 MACHINE",     "OPC USER NAME",                                   set_opc_user_name                                    },
  {"SIEMENS-OPEN62541 MACHINE",     "OPC PASSWORD",                                    set_opc_password                                     },
  {"SIEMENS-OPEN62541 MACHINE",     "OPC CERTIFICATE FILE",                            set_opc_certificate_file                             },
  {"SIEMENS-OPEN62541 MACHINE",     "OPC PRIVATE KEY FILE",                            set_opc_private_key_file                             },
  {"SIEMENS-OPEN62541 MACHINE",     "OPC PART COUNTER PATH",                           set_opc_part_counter_path                            },
  {"SIEMENS-OPEN62541 MACHINE",     "OPC CYCLE TIME PATH",                             set_opc_cycle_time_path                              }
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


	/*
	 * Count the number of sections: [SIEMENS-OPEN62541 MACHINE]
	 */
	start_record = 1;

	if (so->config_mode == 0)
	{
		rc = utils__cf__count_sections_from_file(&so->sdb, so->agent_configuration_file_name, so->machines_section_name, start_record, &section_count, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__cf__count_sections_from_file() returned %d", fn, rc);
			return -100;
		}
	}
	else
	{
		rc = utils__cf__count_sections_from_buffer(&so->sdb, so->agent_configuration_file_name, so->machines_section_name, start_record, &section_count, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__cf__count_sections_from_buffer() returned %d", fn, rc);
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
	size = sizeof(siemens_open62541__private_machine_t) * section_count;

	so->machine = (siemens_open62541__private_machine_t*) malloc(size);

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
	section.function = found_section_name;
	machine_names_values_max = sizeof(names_values) / sizeof(utils__cf__name_value_callback_t);

	so->machine_count = 0;
	so->machine_count_flag = 0;

	done = 0;
	start_record = 1;
	do
	{
		if (so->config_mode == 0)
		{
			rc = utils__cf__read_configuration_from_file(&so->sdb, so->agent_configuration_file_name, &section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		else
		{
			rc = utils__cf__read_configuration_from_buffer(&so->sdb, so->agent_configuration_file_name, &section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		
		if (rc != 0)
		{
			if (end_of_file == 0)
			{
				if (so->config_mode)
				{
					printf("%s - error - utils__cf__read_configuration_file() returned %d\n", fn, rc);

				}
				else
				{
					printf("%s - error - utils__cf__read_configuration_from_buffer() returned %d\n", fn, rc);
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

static int found_section_name (const char* section_name, size_t section_name_len)
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

static int set_id (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->machine[so->machine_count].config.id;

	rc = utils__cf__write_int(data, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_operating(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->machine[so->machine_count].config.operating;

	rc = utils__cf__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;

}


static int set_online (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->machine[so->machine_count].config.online;

	rc = utils__cf__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_simulation_mode (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &so->machine[so->machine_count].config.simulation_mode;

	rc = utils__cf__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_connection_timeout_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.connection_timeout_seconds;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);
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

static int set_reconnection_attempts_time_interval_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.reconnection_attempts_time_interval_seconds;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);
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

static int set_no_response_timeout_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.no_response_timeout_seconds;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);
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

static int set_max_reconnection_attempts(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.max_reconnection_attempts;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_part_program_name_in_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.part_program_name_in_simulation_mode;
	buffer_size = sizeof(so->machine[so->machine_count].config.part_program_name_in_simulation_mode);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_part_counter_initial_value_in_simulation_mode (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &so->machine[so->machine_count].config.part_counter_initial_value_in_simulation_mode;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_average_cycle_time_seconds_in_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	double* data;

	data = &so->machine[so->machine_count].config.average_cycle_time_in_simulation_mode_seconds;

	rc = utils__cf__write_double(data, section_name, section_name_len, value, value_len);

	if (so->machine[so->machine_count].config.average_cycle_time_in_simulation_mode_seconds < 1)
	{
		return -100;
	}

	return rc;

}


static int set_manufacturer(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{
	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.manufacturer;
	buffer_size = sizeof(so->machine[so->machine_count].config.manufacturer);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_model(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{
	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.model;
	buffer_size = sizeof(so->machine[so->machine_count].config.model);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_serial_number(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.serial_number;
	buffer_size = sizeof(so->machine[so->machine_count].config.serial_number);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.name;
	buffer_size = sizeof(so->machine[so->machine_count].config.name);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_facility(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.facility;
	buffer_size = sizeof(so->machine[so->machine_count].config.facility);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_cnc_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.cnc_name;
	buffer_size = sizeof(so->machine[so->machine_count].config.cnc_name);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_opc_ipv4_address (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_ipv4_address;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_ipv4_address);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_opc_ipv4_port(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;


	buffer = so->machine[so->machine_count].config.opc_ipv4_port;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_ipv4_port);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return 0;
}

static int set_opc_user_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_user_name;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_user_name);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_opc_password (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_password;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_password);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_opc_certificate_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_certificate_file;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_certificate_file);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_opc_private_key_file (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_private_key_file;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_private_key_file);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_opc_part_counter_path(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_part_counter_path;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_part_counter_path);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_opc_cycle_time_path (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = so->machine[so->machine_count].config.opc_cycle_time_path;
	buffer_size = sizeof(so->machine[so->machine_count].config.opc_cycle_time_path);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}


