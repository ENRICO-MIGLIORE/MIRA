#include <agency.h>


#define AGENCY__TEST_1__CONFIG_FILE_NAME       "D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\i4mp_config.txt"


//int agency__test_1(const char* config_file_name, const char* log_file_name, int enable_printf, int enable_log_file, int enable_table_layout_output, int test_cycles)

int agency__test_1 (const char* config_file_name)
{
	int rc;
	int number_of_machines;
	char buffer[AGENCY__BUFFER_SIZE];
	int i;
	size_t buffer_len;
	agency__config_t config;
	int fd;
	int test_cycles;


	rc = agency__init();
	if (rc != 0)
	{
		return -100;
	}

	memset(&config, 0, sizeof(config));
	config.file_name = config_file_name;   //config.file_name = AGENCY__TEST_1__CONFIG_FILE_NAME;
	config.buffer = NULL;
	config.buffer_len = 0;
 	rc = agency__config(&config);
	if (rc != 0)
	{
		return -200;
	}

	rc = agency__start();
	if (rc != 0)
	{
		return -300;
	}

	rc = agency__get_number_of_machines(&number_of_machines); 
	if (rc != 0)
	{
		return -400;
	}

	fd = 3;

	rc = agency__get_machine_id(fd, buffer, sizeof(buffer), &buffer_len);
	if (rc != 0)
	{
		return -500;
	}

	rc = agency__get_machine_name(fd, buffer, sizeof(buffer), &buffer_len);


	buffer_len = 0;  //to keep happy the compiler
	// number_of_machines = 0;

	test_cycles = 100;

	while (test_cycles > 0)
	{

		for (i = 0; i < number_of_machines; i++)
		{
		
			agency__sleep(1000);

		    rc = agency__get_machine_name(i, buffer, sizeof(buffer), &buffer_len);

			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("machine name = not available\n");
				}
				else
				{
					printf("machine name = %s\n", buffer);
				}
			}

			rc = agency__get_machine_part_counter(i, buffer, sizeof(buffer), &buffer_len);

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


			rc = agency__get_machine_cycle_time(i, buffer, sizeof(buffer), &buffer_len);

			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("cycle time = not available\n");
				}
				else
				{
					printf("cycle time = %s\n", buffer);
				}
			}

			rc = agency__get_machine_part_program_name(i, buffer, sizeof(buffer), &buffer_len);

			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("part program name = not available\n");
				}
				else
				{
					printf("part program name = %s\n", buffer);
				}
			}


			
			rc = agency__get_machine_status_run(i, buffer, sizeof(buffer), &buffer_len);
			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("status run = not available\n");
				}
				else
				{
					printf("status run = %s\n", buffer);
				}
			}


			rc = agency__get_machine_status_alarm(i, buffer, sizeof(buffer), &buffer_len);
			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("status alarm = not available\n");
				}
				else
				{
					printf("status alarm = %s\n", buffer);
				}
			}
			printf("*****************************\n");
			printf("*****************************\n");
			printf("*****************************\n\n");
		}

		

		test_cycles--;
	}

	


#if 0
	rc = mira__init();
	if (rc != 0)
	{
		printf("mira__test_1() - error - mira__init() returned %d\n", rc);
		return -100;
	}
	

	memset(mira_agent, 0, sizeof(mira_agent));
	i = 0;

	mira_agent[i].init = agent__siemens_open62541__init;
	mira_agent[i].config = agent__siemens_open62541__config;
	mira_agent[i].start = agent__siemens_open62541__start;

	mira_agent[i].get_agent_buffer_size = agent__siemens_open62541__get_agent_buffer_size;
	mira_agent[i].get_agent_name = agent__siemens_open62541__get_agent_name;
	mira_agent[i].get_agent_total_number_of_machines = agent__siemens_open62541__get_agent_number_of_machines;


	//mira_agent[i].get_machine_data = agent__siemens_open62541__get_machine_data;


	mira_agent[i].get_machine_id = agent__siemens_open62541__get_machine_id;
	mira_agent[i].get_machine_agent_name = agent__siemens_open62541__get_machine_agent_name;

	//mira_agent[i].get_machine_manufacturer = agent__siemens_open62541__get_machine_manufacturer;
	//mira_agent[i].get_machine_model = agent__siemens_open62541__get_machine_model;
	//mira_agent[i].get_machine_serial_number = agent__siemens_open62541__get_machine_serial_number;
	//mira_agent[i].get_machine_manufacture_year = agent__siemens_open62541__get_machine_manufacture_year;

	//mira_agent[i].get_machine_organization = agent__siemens_open62541__get_machine_organization;
	//mira_agent[i].get_machine_facility = agent__siemens_open62541__get_machine_facility;
	//mira_agent[i].get_machine_department = agent__siemens_open62541__get_machine_department;
	mira_agent[i].get_machine_name = agent__siemens_open62541__get_machine_name;



	mira_agent[i].get_machine_networked_status = agent__siemens_open62541__get_machine_networked_status;
	mira_agent[i].get_machine_run_mode_status = agent__siemens_open62541__get_machine_run_mode_status;
	//mira_agent[i].get_machine_active_status = agent__siemens_open62541__get_machine_active_status;


	mira_agent[i].get_machine_connection_status = agent__siemens_open62541__get_machine_connection_status;
	mira_agent[i].get_machine_alarm_status = agent__siemens_open62541__get_machine_alarm_status;
	
	
	
	//mira_agent[i].get_machine_cnc_name = agent__siemens_open62541__get_machine_cnc_name;


	mira_agent[i].get_machine_production_status = agent__siemens_open62541__get_machine_production_status;
	mira_agent[i].get_machine_part_counter = agent__siemens_open62541__get_machine_part_counter;
	mira_agent[i].get_machine_cycle_time = agent__siemens_open62541__get_machine_cycle_time;
	mira_agent[i].get_machine_part_program_name = agent__siemens_open62541__get_machine_part_program_name;

	mira_agent[i].config_file_name = config_file_name;
	mira_agent[i].config_buffer = NULL;
	mira_agent[i].config_buffer_len = 0;

	i++;

	memset(&mira_config, 0, sizeof(mira_config));

	mira_config.i4_agency = &mira_agent[0];
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


	/*
	 * if we get here, the mira framework has started
	 */



	rc = mira__get_buffer_size(&buffer_size);
	if (rc != 0)
	{
		printf("mira__test_1() - error - mira__get_buffer_size() returned %d\n", rc);
		return -400;

	}

	if (buffer_size < 2)
	{
		printf("mira__test_1() - buffer size is zero\n");
	}


	buffer = malloc(buffer_size);
	if (buffer == NULL)
	{
		printf("mira__test_1() - error - malloc() returned null\n");
		return -500;
	}


	/*
	 * print agency' data
	 */
	(void) mira__print_agents();



	rc = mira__get_number_of_machines(&number_of_machines);
	if (rc != 0)
	{
		printf("i4mp__test_2() - error - mira__get_machine_count() returned %d\n", rc);
		return -1000;
	}


	if (number_of_machines == 0)
	{
		printf("i4mp__test_2() - info - machine_count = %d - test ended\n", number_of_machines);
		return 0;
	}


	mira__sleep(1000);



	/*
	 * Get config data
	 */
	for (i = 0; i < number_of_machines; i++)
	{


		/*
		 * machine data
		 */
		//rc = mira__get_machine_data(i, buffer, buffer_size, &buffer_len, MIRA__MACHINE_ID);
		//if (rc == 0)
		//{
		//	if (buffer_len < sizeof(machine_id))
		//	{
		//		strcpy(machine_id, buffer);
		//	}
		//}
		//else
		//{
		//	strcpy(machine_id, "-");
		//}

		/*
		 * machine id
		 */
		rc = mira__get_machine_id(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			if (buffer_len < sizeof(machine_id))
			{
				strcpy(machine_id, buffer);
			}
		}
		else
		{
			strcpy(machine_id, "-");
		}


		/*
		 * machine mira_agent name
		 */
		rc = mira__get_machine_agent_name(i, buffer, buffer_size, &buffer_len);
		if (rc == 0)
		{
			if (buffer_len < sizeof(machine_agent_name))
			{
				strcpy(machine_agent_name, buffer);
			}			
		}
		else
		{
			strcpy(machine_agent_name, "-");
		}

		///*
		// * machine manufacturing data
		// */
		//rc = mira__get_machine_manufacturer(i, buffer, buffer_size, &buffer_len);
		//if (rc != 0)
		//{
		//	strcpy(buffer, "-");
		//}
		//printf("mira_agent = %s - machine id = %s - manufacturer = %s\n", machine_agent_name, machine_id, buffer);


		//rc = mira__get_machine_model(i, buffer, buffer_size, &buffer_len);
		//if (rc != 0)
		//{
		//	strcpy(buffer, "-");
		//}
		//printf("mira_agent = %s - machine id = %s - model = %s\n", machine_agent_name, machine_id, buffer);


		//rc = mira__get_machine_serial_number(i, buffer, buffer_size, &buffer_len);
		//if (rc != 0)
		//{
		//	strcpy(buffer, "-");
		//}
		//printf("mira_agent = %s - machine id = %s - serial number = %s\n", machine_agent_name, machine_id, buffer);


		//rc = mira__get_machine_manufacture_year(i, buffer, buffer_size, &buffer_len);
		//if (rc != 0)
		//{
		//	strcpy(buffer, "-");
		//}
		//printf("mira_agent = %s - machine id = %s - manufacture year = %s\n", machine_agent_name, machine_id, buffer);



		///*
		// * machine location data
		// */
		//rc = mira__get_machine_organization(i, buffer, buffer_size, &buffer_len);
		//if (rc != 0)
		//{
		//	strcpy(buffer, "-");
		//}
		//printf("mira_agent = %s - machine id = %s - organization = %s\n", machine_agent_name, machine_id, buffer);

		//rc = mira__get_machine_facility(i, buffer, buffer_size, &buffer_len);
		//if (rc != 0)
		//{
		//	strcpy(buffer, "-");
		//}
		//printf("mira_agent = %s - machine id = %s - facility = %s\n", machine_agent_name, machine_id, buffer);

		//rc = mira__get_machine_department(i, buffer, buffer_size, &buffer_len);
		//if (rc != 0)
		//{
		//	strcpy(buffer, "-");
		//}
		//printf("mira_agent = %s - machine id = %s - department = %s\n", machine_agent_name, machine_id, buffer);

		//rc = mira__get_machine_name(i, buffer, buffer_size, &buffer_len);
		//if (rc != 0)
		//{
		//	strcpy(buffer, "-");
		//}
		//printf("mira_agent = %s - machine id = %s - name = %s\n", machine_agent_name, machine_id, buffer);


		/*
		 * machine operating mode data
		 */
		rc = mira__get_machine_networked_status(i, buffer, buffer_size, &buffer_len);
		if (rc != 0)
		{
			strcpy(buffer, "-");
		}
		printf("mira_agent = %s - machine id = %s - networked status = %s\n", machine_agent_name, machine_id, buffer);


		rc = mira__get_machine_run_mode_status(i, buffer, buffer_size, &buffer_len);
		if (rc != 0)
		{
			printf("mira_agent = %s - machine id = %s - run mode = -\n", machine_agent_name, machine_id);
		}
		else
		{

			if (buffer[0] == '1')
			{
				printf("mira_agent = %s - machine id = %s - run mode = run\n", machine_agent_name, machine_id);
			}
			else
			{
				printf("mira_agent = %s - machine id = %s - run mode = simulation\n", machine_agent_name, machine_id);
			}
		}

	}

	while (1);


	/*
     * Get config data
     */
	for (i = 0; i < number_of_machines; i++)
	{
		rc = mira__get_machine_id(i, buffer, buffer_size, &buffer_len);

		if (rc == 0)
		{
			if ((buffer_len == 1) && (buffer[0] == '-'))
			{
				printf("machine id = not available\n");
			}
			else
			{
				printf("machine id = %s\n", buffer);
			}
		}
		else
		{
			printf("machine id = error\n");
		}

	}

	printf("--------------------------------------------------------------------------------\n");

	for (j = 0; j < test_cycles; j++)
	{
		for (i = 0; i < number_of_machines; i++)
		{

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
			else
			{
				printf("unexpected part counter = error\n");
			}

			mira__sleep(1000);

			rc = mira__get_machine_cycle_time(i, buffer, buffer_size, &buffer_len);

			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("cycle time = not available\n");
				}
				else
				{
					printf("cycle time = %s\n", buffer);
				}
			}
			else
			{
				printf("cycle time = error\n");
			}

			mira__sleep(1000);


			rc = mira__get_machine_part_program_name(i, buffer, buffer_size, &buffer_len);

			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("part program name = not available\n");
				}
				else
				{
					printf("part program name = %s\n", buffer);
				}

			}
			else
			{
				printf("part program name = error\n");
			}

			mira__sleep(1000);
		}
	}

	while (1);


	/*
	 * Get live data
	 */
	for (j = 0; j < test_cycles; j++)
	{

		for (i = 0; i < number_of_machines; i++)
		{

			mira__sleep(1000);

			rc = mira__get_machine_connection_status(i, buffer, buffer_size, &buffer_len);

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
					printf("mira__get_machine_connection_status() unexpected error\n");
				}
			}
			else
			{
				printf("mira__get_connection_status() returned error %d\n", rc);
			}

			rc = mira__get_machine_alarm_status(i, buffer, buffer_size, &buffer_len);

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
					printf("alarm = not available\n");
				}
				else
				{
					printf("mira__get_machine_alarm_status() unexpected error\n");
				}
			}
			else
			{
				printf("mira__get_machine_alarm_status() returned error %d\n", rc);
			}


			printf("--------------------------------------------------------------------------------\n");



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
			else
			{
				printf("unexpected part counter = error\n");
			}

			rc = mira__get_machine_cycle_time (i, buffer, buffer_size, &buffer_len);

			if (rc == 0)
			{
				if ((buffer_len == 1) && (buffer[0] == '-'))
				{
					printf("cycle time = not available\n");
				}
				else
				{
					printf("cycle time = %s\n", buffer);
				}
			}
			else
			{
				printf("cycle time = error\n");
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
					printf("part program name = %s\n", buffer);
				}

			}
			else
			{
				printf("part program name = error\n");
			}
		}		
	}

	while (1);


#endif

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
				//		printf("machine %d - machine in active\n", i);
				//	}
				//	else
				//	{
				//		printf("machine %d - machine is not active\n", i);
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








