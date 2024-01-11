#include "okuma_mt__private.h"


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
static int set_tcp_server_ipv4_address(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_tcp_server_ipv4_port(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_tcp_client_receive_buffer_size(const char* section_name, size_t section_name_len, const char* value, size_t value_len);
static int set_tcp_client_send_string(const char* section_name, size_t section_name_len, const char* value, size_t value_len);



static utils__cf__section_callback_t section;


static utils__cf__name_value_callback_t names_values[] =
{ 

  {"OKUMA-MT MACHINE",     "ID",                                              set_id                                               },
  {"OKUMA-MT MACHINE",     "OPERATING",                                       set_operating                                        },
  {"OKUMA-MT MACHINE",     "ONLINE",                                          set_online                                           },
  {"OKUMA-MT MACHINE",     "SIMULATION MODE",                                 set_simulation_mode                                  },
  {"OKUMA-MT MACHINE",     "CONNECTION TIMEOUT SECONDS",                      set_connection_timeout_seconds                       },
  {"OKUMA-MT MACHINE",     "RECONNECTION ATTEMPTS TIME INTERVAL SECONDS",     set_reconnection_attempts_time_interval_seconds      },
  {"OKUMA-MT MACHINE",     "MAX RECONNECTION ATTEMPTS",                       set_max_reconnection_attempts                        },
  {"OKUMA-MT MACHINE",     "NO RESPONSE TIMEOUT SECONDS",                     set_no_response_timeout_seconds                      },
  {"OKUMA-MT MACHINE",     "PART PROGRAM NAME IN SIMULATION MODE",            set_part_program_name_in_simulation_mode             },
  {"OKUMA-MT MACHINE",     "PART COUNTER INITIAL VALUE IN SIMULATION MODE",   set_part_counter_initial_value_in_simulation_mode    },
  {"OKUMA-MT MACHINE",     "AVERAGE CYCLE TIME SECONDS IN SIMULATION MODE",   set_average_cycle_time_seconds_in_simulation_mode    },
  {"OKUMA-MT MACHINE",     "MANUFACTURER",                                    set_manufacturer                                     },
  {"OKUMA-MT MACHINE",     "MODEL",                                           set_model                                            },
  {"OKUMA-MT MACHINE",     "SERIAL NUMBER",                                   set_serial_number                                    },
  {"OKUMA-MT MACHINE",     "NAME",                                            set_name                                             },
  {"OKUMA-MT MACHINE",     "FACILITY",                                        set_facility                                         },
  {"OKUMA-MT MACHINE",     "CNC NAME",                                        set_cnc_name                                         },
  {"OKUMA-MT MACHINE",     "TCP SERVER IP-V4 ADDRESS",                        set_tcp_server_ipv4_address                          },
  {"OKUMA-MT MACHINE",     "TCP SERVER IP-V4 PORT",                           set_tcp_server_ipv4_port                             },
  {"OKUMA-MT MACHINE",     "TCP CLIENT RECEIVE BUFFER SIZE",                  set_tcp_client_receive_buffer_size                   },
  {"OKUMA-MT MACHINE",     "TCP CLIENT SEND STRING",                          set_tcp_client_send_string                           }

};


static char* fn = "okuma_mt__private__load_configuration_file__machines()";

/*
 * No need to lock the thread in all of these functions because it hasn't started yet
 */

int okuma_mt__private__load_configuration_file__machines (void)
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
	 * Count the number of sections: [OKUMA-MT MACHINE]
	 */
	start_record = 1;
	rc = utils__cf__count_sections_from_file(&om->sdb, om->agent_configuration_file_name, om->machines_section_name, start_record, &section_count, &end_of_file);
	if (rc != 0)
	{
		printf("%s - error - utils__cf__count_sections_from_file() returned %d", fn, rc);
		return -100;
	}

	if (section_count == 0)
	{
		printf("%s - error - can't find [%s] sections in the configuration file\n", fn, om->machines_section_name);
		return -200;
	}


	/*
	 * Allocate memory for "section_count" machines
	 */
	size = sizeof(okuma_mt__machine_t) * section_count;

	om->machine = (okuma_mt__machine_t*) malloc(size);

	if (om->machine == NULL)
	{
		printf("%s - error - malloc() error\n", fn);
		return -300;
	}

	memset(om->machine, '\0', size);



	/*
	 * Set section data of the machines: [OKUMA-MT MACHINE]
	 */
	section.name = om->machines_section_name;
	section.function = found_section_name;
	machine_names_values_max = sizeof(names_values) / sizeof(utils__cf__name_value_callback_t);

	om->machine_count = 0;
	om->machine_count_flag = 0;

	done = 0;
	start_record = 1;
	do
	{

		rc = utils__cf__read_configuration_from_file(&om->sdb, om->agent_configuration_file_name, &section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		if (rc != 0)
		{
			if (end_of_file == 0)
			{
				printf("%s - error - utils__cf__read_configuration_from_file() returned %d\n", fn, rc);
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


	om->machine_count++;


	if (om->machine_count != section_count)
	{
		printf("%s - error - om->machine_count != section_count\n", fn);
		return -400;
	}



	if (om->machine_count > 1)
	{	

		/*
		 * Check for duplicate machines' ID
		 */
		for (i = 0; i < om->machine_count; i++)
		{
			for (j = i + 1; j < om->machine_count; j++)
			{
				if (om->machine[i].config.id == om->machine[j].config.id)
				{
					printf("%s - error - Duplicate id found - id = %d\n", fn, om->machine[i].config.id);
					return -500;
				}
			}
		}


		/*
		 * Check for potential buffer overflow
		 */
		for (i = 0; i < om->machine_count; i++)
		{

			len = strlen(om->machine[i].config.part_program_name_in_simulation_mode);

			if (len > sizeof(om->machine[i].part_program_name_simulated))
			{
				printf("%s - error - len > om->machine[%d].part_program_name_utf_8_simulated\n", fn, om->machine[i].config.id);
				return -600;
			}

			if (len > sizeof(om->machine[i].part_program_name_utf_8))
			{
				printf("%s - error - len > om->machine[%d].part_program_name_utf_8\n", fn, om->machine[i].config.id);
				return -700;
			}
		}
	}



	for (i = 0; i < om->machine_count; i++)
	{
		sprintf(om->machine[i].name_and_index, "%s %d", om->machines_section_name, i + 1);
		om->machine[i].name_and_index_len = strlen(om->machine[i].name_and_index);
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

	if (om->machine_count_flag == 0)
	{
		om->machine_count_flag = 1;
	}
	else
	{
		om->machine_count++;
	}

	return 0;
}

static int set_id (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.id;

	rc = utils__cf__write_int(data, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_operating(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.operating;

	rc = utils__sdb__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_online (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.online;

	rc = utils__sdb__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_simulation_mode (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.simulation_mode;

	rc = utils__sdb__write_yes_or_no(data, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_connection_timeout_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.connection_timeout_seconds;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (om->machine[om->machine_count].config.connection_timeout_seconds == 0)
	{
		return -200;
	}

	return 0;

}

static int set_reconnection_attempts_time_interval_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.reconnection_attempts_time_interval_seconds;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (om->machine[om->machine_count].config.reconnection_attempts_time_interval_seconds == 0)
	{
		return -200;
	}

	return 0;

}

static int set_no_response_timeout_seconds(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.no_response_timeout_seconds;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);
	if (rc != 0)
	{
		return -100;
	}

	if (om->machine[om->machine_count].config.no_response_timeout_seconds == 0)
	{
		return -200;
	}

	return 0;

}

static int set_max_reconnection_attempts(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.max_reconnection_attempts;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_part_program_name_in_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.part_program_name_in_simulation_mode;
	buffer_size = sizeof(om->machine[om->machine_count].config.part_program_name_in_simulation_mode);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_part_counter_initial_value_in_simulation_mode (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.part_counter_initial_value_in_simulation_mode;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_average_cycle_time_seconds_in_simulation_mode(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	double* data;

	data = &om->machine[om->machine_count].config.average_cycle_time_in_simulation_mode_seconds;

	rc = utils__cf__write_double(data, section_name, section_name_len, value, value_len);

	if (om->machine[om->machine_count].config.average_cycle_time_in_simulation_mode_seconds < 1)
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

	buffer = om->machine[om->machine_count].config.manufacturer;
	buffer_size = sizeof(om->machine[om->machine_count].config.manufacturer);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_model(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{
	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.model;
	buffer_size = sizeof(om->machine[om->machine_count].config.model);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_serial_number(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.serial_number;
	buffer_size = sizeof(om->machine[om->machine_count].config.serial_number);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.name;
	buffer_size = sizeof(om->machine[om->machine_count].config.name);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_facility(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.facility;
	buffer_size = sizeof(om->machine[om->machine_count].config.facility);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_cnc_name(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.cnc_name;
	buffer_size = sizeof(om->machine[om->machine_count].config.cnc_name);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;

}

static int set_tcp_server_ipv4_address (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.tcp_server_ipv4_address;
	buffer_size = sizeof(om->machine[om->machine_count].config.tcp_server_ipv4_address);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return rc;
}

static int set_tcp_server_ipv4_port(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;


	buffer = om->machine[om->machine_count].config.tcp_server_ipv4_port;
	buffer_size = sizeof(om->machine[om->machine_count].config.tcp_server_ipv4_port);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);

	return 0;
}

static int set_tcp_client_receive_buffer_size (const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.tcp_client_receive_buffer_size;

	rc = utils__cf__write_size_t(data, section_name, section_name_len, value, value_len);

	return rc;
}


static int set_tcp_client_send_string(const char* section_name, size_t section_name_len, const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;


	buffer = om->machine[om->machine_count].config.tcp_client_send_string;
	buffer_size = sizeof(om->machine[om->machine_count].config.tcp_client_send_string);

	rc = utils__cf__write_string(buffer, buffer_size, section_name, section_name_len, value, value_len);


	/*
	 * Convert "\r" into '\r'
	 */
	return 0;
}

