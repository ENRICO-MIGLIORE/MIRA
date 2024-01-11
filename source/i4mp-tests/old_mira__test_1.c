#include <siemens_open62541.h>

#include <mira.h>


#define MIRA_TEST_1__AGENTS_MAX   1


int mira__test_1 (const char* config_file_name, const char* log_file_name, int enable_printf, int enable_log_file, int enable_table_layout_output, int test_cycles)
{
	int rc;
	int i;
	int j;
	int machine_count;
	mira__config_t mira_config;
	mira__agent_t mira__agent[MIRA_TEST_1__AGENTS_MAX];
	size_t buffer_size;
	size_t buffer_len;
	char* buffer;

	/*
	 * init
	 */
	rc = mira__init();
	if (rc != 0)
	{
		printf("mira__test_1() - error - mira__init() returned %d\n", rc);
		return -100;
	}
	

	/*
	 * config
	 */
	memset(mira__agent, 0, sizeof(mira__agent));
	i = 0;

	mira__agent[i].name = siemens_open62541__get_agent_name();

	mira__agent[i].type = siemens_open62541__get_agent_type();
	mira__agent[i].config_file_name = config_file_name;
	mira__agent[i].config_buffer = NULL;
	mira__agent[i].config_buffer_len = 0;
	
	mira__agent[i].buffer_size = siemens_open62541__get_agent_buffer_size();

	mira__agent[i].init = agent__siemens_open62541__init;
	mira__agent[i].config = agent__siemens_open62541__config;
	mira__agent[i].start = agent__siemens_open62541__start;

	mira__agent[i].get_total_number_of_machines = siemens_open62541__get_machine_count;

	mira__agent[i].get_machine_id = siemens_open62541__get_machine_id;
	mira__agent[i].get_machine_manufacturer = siemens_open62541__get_manufacturer;
	mira__agent[i].get_machine_model = agent__siemens_open62541__get_machine_model;
	mira__agent[i].get_serial_number = siemens_open62541__get_serial_number;
	mira__agent[i].get_machine_name = agent__siemens_open62541__get_machine_name;
	mira__agent[i].get_machine_facility = siemens_open62541__get_facility;
	mira__agent[i].get_machine_department = siemens_open62541__get_department;
	mira__agent[i].get_machine_cnc_name = agent__siemens_open62541__get_machine_cnc_name;

	mira__agent[i].get_networked_status = siemens_open62541__get_networked_status;
	mira__agent[i].get_simulated_status = siemens_open62541__get_simulated_status;
	mira__agent[i].get_operating_status = siemens_open62541__get_operating_status;

	mira__agent[i].get_connection_status = siemens_open62541__get_connection_status;
	mira__agent[i].get_alarm_status = agent__siemens_open62541__get_alarm_status;
	mira__agent[i].get_production_status = siemens_open62541__get_production_status;
	mira__agent[i].get_machine_part_counter = agent__siemens_open62541__get_machine_part_counter;
	mira__agent[i].get_machine_cycle_time = siemens_open62541__get_cycle_time;
	mira__agent[i].get_machine_part_program_name = siemens_open62541__get_machine_part_program_name;

	i++;

	memset(&mira_config, 0, sizeof(mira_config));

	mira_config.agent = &mira__agent[0];
	mira_config.agents_max = i;
	mira_config.log_file_name = log_file_name;
	mira_config.enable_printf = enable_printf;
	mira_config.enable_log_file = enable_log_file;
	mira_config.enable_table_layout_output = enable_table_layout_output;

	rc = mira__config(&mira_config);
	if (rc != 0)
	{
		printf("mira__test_1() - error - mira__config() returned %d\n", rc);
		return -200;
	}


	rc = mira__start();
	if (rc != 0)
	{
		printf("mira__test_1() - error - mira__start() returned %d\n", rc);
		return -300;
	}


	rc = mira__get_buffer_size(&buffer_size);
	if (rc != 0)
	{
		printf("mira__test_1() - error - mira__get_buffer_size() returned %d\n", rc);
		return -400;

	}

	buffer = malloc(buffer_size);
	if (buffer == NULL)
	{
		printf("mira__test_1() - error - malloc() returned null\n");
		return -500;
	}


	/*
	 * print agents' data
	 */
	(void) mira__print_agents();





	rc = mira__get_total_number_of_machines(buffer, buffer_size, &buffer_len);
	if (rc != 0)
	{
		printf("i4mp__test_2() - error - mira__get_machine_count() returned %d\n", rc);
		return -1000;
	}



	machine_count = atoi(buffer);
	if (machine_count == 0)
	{
		printf("i4mp__test_2() - info - machine_count = %d - test ended\n", machine_count);
		return 0;
	}


	if (machine_count <= 0)
	{
		printf("i4mp__test_2() - error - machine_count = %d\n", machine_count);
		return -300;
	}


	for (j = 0; j < test_cycles; j++)
	{

		for (i = 0; i < machine_count; i++)
		{

			printf("\n--------------------------------------------------------------------------------\n");

			rc = mira__get_machine_id(i, buffer, buffer_size, &buffer_len);

			rc = mira__get_machine_name(i, buffer, buffer_size, &buffer_len);

			printf("machine %d - query %d of %d\n\n", i, j + 1, test_cycles);

			
			rc = mira__get_machine_part_counter(i, buffer, buffer_size, &buffer_len);

			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("part counter = not available\n");
				}
				else
				{
					printf("part counter = %s\n", buffer);
				}
			}



			rc = mira__get_machine_cycle_time(i, buffer, buffer_size, &buffer_len);
			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("cycle time = not available\n");
				}
				else
				{
					printf("cycle time = %s seconds\n", buffer);
				}
			}


			rc = mira__get_machine_part_program_name(i, buffer, buffer_size, &buffer_len);
			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("part program name = not available\n");
				}
				else
				{
					printf("part program name = \"%s\"\n", buffer);
				}
			}

			printf("--------------------------------------------------------------------------------\n");
		}

		mira__sleep(5000);
	}

	while (1);



#if 0

	/*
	 * Get config data
	 */
	for (i = 0; i < machine_count; i++)
	{

		printf("machine_local %d config config_2\n\n", i);


		// rc = fanuc_focas__get_id(0, buffer, buffer_size, &buffer_len);

		rc = i4mp__get_id(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("id = \"%s\"\n", buffer);
		}
		else
		{
			printf("mira__get_machine_id() returned error %d\n", rc);
		}

		rc = i4mp__get_type(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("type = \"%s\"\n", buffer);
		}
		else
		{
			printf("i4mp__get_type() returned error %d\n", rc);
		}

		rc = i4mp__get_networked_status(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			if (buffer[0] == '1')
			{
				printf("machine_local is networked\n");
			}
			else
			{
				printf("machine_local is not networked\n");
			}
		}
		else
		{
			printf("i4mp__get_networked_status() returned error %d\n", rc);
		}

		rc = i4mp__get_simulated_status(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			if (buffer[0] == '1')
			{
				printf("machine_local is simulated\n");
			}
			else
			{
				printf("machine_local is in run mode\n");
			}
		}
		else
		{
			printf("i4mp__get_simulated_status() returned error %d\n", rc);
		}


		rc = i4mp__get_operating_status(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			if (buffer[0] == '1')
			{
				printf("machine_local is operating\n");
			}
			else
			{
				printf("machine_local is not operating\n");
			}
		}
		else
		{
			printf("i4mp__get_simulated_status() returned error %d\n", rc);
		}


		rc = i4mp__get_manufacturer(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("manufacturer = \"%s\"\n", buffer);
		}
		else
		{
			printf("i4mp__get_manufacturer() returned error %d\n", rc);
		}

		rc = i4mp__get_model(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("model = \"%s\"\n", buffer);
		}
		else
		{
			printf("i4mp__get_model() returned error %d\n", rc);
		}

		rc = i4mp__get_serial_number(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("serial_number = \"%s\"\n", buffer);
		}
		else
		{
			printf("i4mp__get_serial_number() returned error %d\n", rc);
		}

		rc = i4mp__get_name(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("name = \"%s\"\n", buffer);
		}

		rc = i4mp__get_facility(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("facility = \"%s\"\n", buffer);
		}

		rc = i4mp__get_department(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("department = \"%s\"\n", buffer);
		}


		rc = i4mp__get_cnc_name(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			printf("cnc name = \"%s\"\n", buffer);
		}

		if (i < machine_count)
		{
			printf("--------------------------------------------------------------------------------\n");
		}

		printf("\n");
	}


	/*
	 * Get live data
	 */
	for (j = 0; j < test_times; j++)
	{

		for (i = 0; i < machine_count; i++)
		{

			printf("--------------------------------------------------------------------------------\n");
			printf("machine_local %d live config_2 - query %d of %d\n\n", i, j + 1, test_times);


			rc = i4mp__get_networked_status(i, buffer, buffer_size, &buffer_len);

			if ((rc == 0) && (buffer_len == 1) && (buffer[0] == '1'))
			{

				rc = i4mp__get_name(i, buffer, buffer_size, &buffer_len);
				if (rc == 0)
				{
					printf("name = \"%s\"\n", buffer);
				}
				else
				{
					printf("i4mp__get_name() returned error %d\n", rc);
				}

				rc = i4mp__get_simulated_status(i, buffer, buffer_size, &buffer_len);
				if (rc == 0)
				{
					if (buffer[0] == '1')
					{
						printf("mode = simulation\n");
					}
					else
					{
						printf("mode = run\n");
					}
				}
				else
				{
					printf("i4mp__get_simulated_status() returned error %d\n", rc);
				}

				rc = i4mp__get_connection_status(i, buffer, buffer_size, &buffer_len);
				if ((rc == 0) && (buffer_len == 1))
				{
					if (buffer[0] == '0')
					{
						printf("connection = no\n");
					}
					else if (buffer[0] == '1')
					{
						printf("connection = yes\n");
					}
					else if (buffer[0] == '-')
					{
						printf("connection = not available\n");
					}
					else
					{
						printf("i4mp__get_connection_status() unexpected error\n");
					}
				}
				else
				{
					printf("i4mp__get_connection_status() returned error %d\n", rc);
				}

				rc = i4mp__get_production_status(i, buffer, buffer_size, &buffer_len);
				if ((rc == 0) && (buffer_len == 1))
				{
					if (buffer[0] == '0')
					{
						printf("production = no\n");
					}
					else if (buffer[0] == '1')
					{
						printf("production = yes\n");
					}
					else if (buffer[0] == '-')
					{
						printf("production = not available\n");
					}
					else
					{
						printf("i4mp__get_production_status() unexpected error\n");
					}
				}
				else
				{
					printf("i4mp__get_production_status() returned error %d\n", rc);
				}

				rc = i4mp__get_alarm_status(i, buffer, buffer_size, &buffer_len);
				if ((rc == 0) && (buffer_len == 1))
				{
					if (buffer[0] == '0')
					{
						printf("alarm = no\n");
					}
					else if (buffer[0] == '1')
					{
						printf("alarm = yes\n");
					}
					else if (buffer[0] == '-')
					{
						printf("alarm: not available\n");
					}
					else
					{
						printf("i4mp__get_alarm_status() unexpected error\n");
					}
				}
				else
				{
					printf("i4mp__get_alarm_status() returned error %d\n", rc);
				}


				rc = i4mp__get_part_counter(i, buffer, buffer_size, &buffer_len);
				if (rc == 0)
				{
					if ((buffer_len == 1) && (buffer[0] == '-'))
					{
						printf("part counter = not available\n");
					}
					else
					{
						printf("part counter = %s\n", buffer);
					}

				}
				else
				{
					printf("mira__get_part_counter() returned error %d\n", rc);
				}


				rc = i4mp__get_cycle_time(i, buffer, buffer_size, &buffer_len);
				if (rc == 0)
				{
					if ((buffer_len == 1) && (buffer[0] == '-'))
					{
						printf("cycle time = not available\n");
					}
					else
					{
						printf("cycle time = %s seconds\n", buffer);
					}
				}
				else
				{
					printf("i4mp__get_cycle_time() returned error %d\n", rc);
				}


				rc = i4mp__get_part_program_name(i, buffer, buffer_size, &buffer_len);
				if (rc == 0)
				{
					if ((buffer_len == 1) && (buffer[0] == '-'))
					{
						printf("part program name = not available\n");
					}
					else
					{
						printf("part program name = \"%s\"\n", buffer);
					}
				}


				//rc = i4mp__get_operating_status(i, buffer, buffer_size, &buffer_len);
				//if (rc == 0)
				//{
				//	if (buffer[0] == '1')
				//	{
				//		printf("machine %d - machine in operating\n", i);
				//	}
				//	else
				//	{
				//		printf("machine %d - machine is not operating\n", i);
				//	}
				//}
				//else
				//{
				//	printf("i4mp__get_operating_status() returned error %d\n", rc);
				//}


				printf("\n");

			}

		}


		i4mp__sleep_milliseconds(10000);

	}

#endif

	return rc;

}








