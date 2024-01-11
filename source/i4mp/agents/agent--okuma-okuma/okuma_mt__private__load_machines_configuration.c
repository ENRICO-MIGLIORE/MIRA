#include "okuma_mt__private.h"


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

static int set_tcp_server_ipv4_address(const char* value, size_t value_len);
static int set_tcp_server_ipv4_port(const char* value, size_t value_len);
static int set_tcp_client_receive_buffer_size(const char* value, size_t value_len);
static int set_tcp_client_send_string(const char* value, size_t value_len);
static int set_tcp_enable_printf(const char* value, size_t value_len);



static int set_cycle_time_from_part_counter(const char* value, size_t value_len);


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

  {"TCP SERVER IP-V4 ADDRESS",                        set_tcp_server_ipv4_address                          },
  {"TCP SERVER IP-V4 PORT",                           set_tcp_server_ipv4_port                             },
  {"TCP CLIENT RECEIVE BUFFER SIZE",                  set_tcp_client_receive_buffer_size                   },
  {"TCP CLIENT SEND STRING",                          set_tcp_client_send_string                           },
  {"TCP CLIENT ENABLE PRINTF",                        set_tcp_enable_printf                                },


  {"CYCLE TIME FROM PART COUNTER",                    set_cycle_time_from_part_counter                     },

};


static char* fn = "okuma_mt__private__load_machines_configuration()";



int okuma_mt__private__load_machines_configuration(void)
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
	 * Count the number of sections: [OKUMA-MT MACHINE]
	 */
	start_record = 1;

	if (om->config_mode == 0)
	{
		rc = utils__sdb__count_sections_from_file(&om->sdb, om->agent_configuration_file_name, om->machines_section_name, start_record, &section_count, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__sdb__count_sections_from_file() returned %d", fn, rc);
			return -100;
		}
	}
	else
	{
		rc = utils__sdb__count_sections_from_buffer(&om->sdb, om->agent_configuration_file_name, om->machines_section_name, start_record, &section_count, &end_of_file);
		if (rc != 0)
		{
			printf("%s - error - utils__sdb__count_sections_from_buffer() returned %d", fn, rc);
			return -100;
		}
	}

	if (section_count == 0)
	{
		printf("%s - error - can't find [%s] sections in the configuration file\n", fn, om->machines_section_name);
		return -200;
	}


	/*
	 * Allocate memory for the machines
	 */
	size = sizeof(okuma_mt__machine_t) * section_count;

	om->machine = (okuma_mt__machine_t*)malloc(size);

	if (om->machine == NULL)
	{
		printf("%s - error - malloc() error\n", fn);
		return -300;
	}

	memset(om->machine, '\0', size);



	/*
	 * Set section data of the machines: [SIEMENS-OPEN62541 MACHINE]
	 */
	section.name = om->machines_section_name;
	section.function = found_agent_section;
	machine_names_values_max = sizeof(names_values) / sizeof(utils__sdb__value_callback_t);

	om->machine_count = 0;
	om->machine_count_flag = 0;

	done = 0;
	start_record = 1;
	do
	{
		if (om->config_mode == 0)
		{
			rc = utils__sdb__read_configuration_from_file(p, &om->sdb, om->agent_configuration_file_name, &section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}
		else
		{
			rc = utils__sdb__read_configuration_from_buffer(p, &om->sdb, om->agent_configuration_file_name, &section, names_values, machine_names_values_max, start_record, &record_number, &end_of_file);
		}

		if (rc != 0)
		{
			if (end_of_file == 0)
			{
				if (om->config_mode)
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

	} while (done == 0);


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
		//sprintf(om->machine[i].name_and_index, "%s %d", om->machines_section_name, i + 1);
		//om->machine[i].name_and_index_len = strlen(om->machine[i].name_and_index);
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

static int set_id (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.id;

	rc = utils__libc__write_int(data, value, value_len);

	return rc;
}

static int set_type(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.type;
	buffer_size = sizeof(om->machine[om->machine_count].config.type);

	rc = utils__libc__write_option(buffer, buffer_size, value, value_len, "CNC", 3, "NO CNC", 6);
	
	return rc;
}

static int set_operating(const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.operating;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

static int set_networked (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.networked;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

static int set_simulated (const char* value, size_t value_len)
{

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.simulated;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;
}

static int set_connection_timeout_seconds(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.connection_timeout_seconds;

	rc = utils__libc__write_size_t(data, value, value_len);
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

static int set_reconnection_attempts_time_interval_seconds(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.reconnection_attempts_time_interval_seconds;

	rc = utils__libc__write_size_t(data, value, value_len);
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

static int set_no_response_timeout_seconds(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.no_response_timeout_seconds;

	rc = utils__libc__write_size_t(data, value, value_len);
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

static int set_max_reconnection_attempts(const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.max_reconnection_attempts;

	rc = utils__libc__write_size_t(data, value, value_len);

	return rc;

}

static int set_part_program_name_in_simulation_mode(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.part_program_name_in_simulation_mode;
	buffer_size = sizeof(om->machine[om->machine_count].config.part_program_name_in_simulation_mode);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_part_counter_initial_value_in_simulation_mode (const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.part_counter_initial_value_in_simulation_mode;

	rc = utils__libc__write_size_t(data, value, value_len);

	return rc;

}

static int set_average_cycle_time_seconds_in_simulation_mode(const char* value, size_t value_len)
{

	int rc;
	double* data;

	data = &om->machine[om->machine_count].config.average_cycle_time_in_simulation_mode_seconds;

	rc = utils__libc__write_double(data, value, value_len);

	if (om->machine[om->machine_count].config.average_cycle_time_in_simulation_mode_seconds < 1)
	{
		return -100;
	}

	return rc;

}


static int set_cycle_time_from_part_counter (const char* value, size_t value_len)
{

	int rc;
	size_t i;
	int* data_int;
	size_t* data_sizet;
	const char* seps[3] = {",", " ", "\t"};
	size_t seps_len[3];
	char* tokens[16];
	size_t tokens_len[16];
	size_t tokens_max;
	size_t token_count;
	size_t seps_count;
	int count_empty_tokens;
	size_t j;


	i = om->machine_count;

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

	if (token_count < 6)
	{
		return -200;
	}

	/*
	 * yes | no
	 */
	data_int = &om->machine[i].config.cycle_time_fpc.do_estimation;

	rc = utils__libc__write_yes_or_no(data_int, tokens[0], tokens_len[0]);
	if (rc != 0)
	{
		return -300;
	}

	
	/*
	 * time to first estimation after boot in seconds - 0 wiil be set to 1
	 */
	data_sizet = &om->machine[i].config.cycle_time_fpc.time_to_first_estimation_seconds;

	rc = utils__libc__write_size_t(data_sizet, tokens[1], tokens_len[1]);
	if (rc != 0)
	{
		return -400;
	}

	if (om->machine[i].config.cycle_time_fpc.time_to_first_estimation_seconds == 0)
	{
		om->machine[i].config.cycle_time_fpc.time_to_first_estimation_seconds = 1;
	}



	/*
	 * time interval for estimations seconds - 0 wiil be set to 1
	 */
	data_sizet = &om->machine[i].config.cycle_time_fpc.time_interval_for_estimations_seconds;

	rc = utils__libc__write_size_t(data_sizet, tokens[2], tokens_len[2]);
	if (rc != 0)
	{
		return -500;
	}

	if (om->machine[i].config.cycle_time_fpc.time_interval_for_estimations_seconds == 0)
	{
		om->machine[i].config.cycle_time_fpc.time_interval_for_estimations_seconds = 1;
	}



	/*
	 * timeout before restarting an estimation in seconds - 0 wiil be set to 60
	 */
	data_sizet = &om->machine[i].config.cycle_time_fpc.timeout_seconds;

	rc = rc = utils__libc__write_size_t(data_sizet, tokens[3], tokens_len[3]);
	if (rc != 0)
	{
		return -600;
	}

	if (om->machine[i].config.cycle_time_fpc.timeout_seconds == 0)
	{
		om->machine[i].config.cycle_time_fpc.timeout_seconds = 60;
	}



	/*
	 * timeout before restarting an estimation in seconds - 0 wiil be set to 60
	 */
	data_sizet = &om->machine[i].config.cycle_time_fpc.minium_acceptable_cycle_time_seconds;

	rc = rc = utils__libc__write_size_t(data_sizet, tokens[4], tokens_len[4]);
	if (rc != 0)
	{
		return -700;
	}

	if (om->machine[i].config.cycle_time_fpc.minium_acceptable_cycle_time_seconds == 0)
	{
		om->machine[i].config.cycle_time_fpc.timeout_seconds = 1;
	}

	

	/*
	 * enable printf: yes | no
	 */
	data_int = &om->machine[i].config.cycle_time_fpc.enable_printf;

	rc = utils__libc__write_yes_or_no(data_int, tokens[5], tokens_len[5]);
	if (rc != 0)
	{
		return -800;
	}

	return 0;

}


static int set_manufacturer(const char* value, size_t value_len)
{
	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.manufacturer;
	buffer_size = sizeof(om->machine[om->machine_count].config.manufacturer);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_model(const char* value, size_t value_len)
{
	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.model;
	buffer_size = sizeof(om->machine[om->machine_count].config.model);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_serial_number(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.serial_number;
	buffer_size = sizeof(om->machine[om->machine_count].config.serial_number);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_name(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.name;
	buffer_size = sizeof(om->machine[om->machine_count].config.name);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_facility(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.facility;
	buffer_size = sizeof(om->machine[om->machine_count].config.facility);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}


static int set_department(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.department;
	buffer_size = sizeof(om->machine[om->machine_count].config.department);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}


static int set_cnc_name(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.cnc_name;
	buffer_size = sizeof(om->machine[om->machine_count].config.cnc_name);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;

}

static int set_tcp_server_ipv4_address (const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;

	buffer = om->machine[om->machine_count].config.tcp_server_ipv4_address;
	buffer_size = sizeof(om->machine[om->machine_count].config.tcp_server_ipv4_address);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_tcp_server_ipv4_port(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;


	buffer = om->machine[om->machine_count].config.tcp_server_ipv4_port;
	buffer_size = sizeof(om->machine[om->machine_count].config.tcp_server_ipv4_port);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);

	return rc;
}

static int set_tcp_client_receive_buffer_size (const char* value, size_t value_len)
{

	int rc;
	size_t* data;

	data = &om->machine[om->machine_count].config.tcp_client_receive_buffer_size;

	rc = utils__libc__write_size_t(data, value, value_len);

	return rc;
}


static int set_tcp_client_send_string(const char* value, size_t value_len)
{

	int rc;
	char* buffer;
	size_t buffer_size;


	buffer = om->machine[om->machine_count].config.tcp_client_send_string;
	buffer_size = sizeof(om->machine[om->machine_count].config.tcp_client_send_string);

	rc = utils__libc__write_string(buffer, buffer_size, value, value_len);


	/*
	 * Convert "\r" into '\r'
	 */
	return rc;
}

static int set_tcp_enable_printf (const char* value, size_t value_len)
{

	/*
	 * enable printf: yes | no
	 */

	int rc;
	int* data;

	data = &om->machine[om->machine_count].config.tcp_client_enable_printf;

	rc = utils__libc__write_yes_or_no(data, value, value_len);

	return rc;

}

