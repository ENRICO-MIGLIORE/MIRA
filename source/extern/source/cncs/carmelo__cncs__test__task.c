#include <process.h>


#include "carmelo__cncs__open62541.h"
#include "carmelo__cncs.h"
#include "timer_soft_sec.h"


#include "..\fggr.h"


static char *fn = "test_machine_cnc()";



int fgg__cncs__1__begin_thread (unsigned long index)
{
	static HANDLE h_thread[2];
	static unsigned int thread_id[2];

	if (index > 2)
	{
		return -10;
	}

	if (carmelo__cncs->machine[0].configurated == 0)
	{
		return -11;
	}

	if (carmelo__cncs->machine[0].thread_status[index] != 0)
	{
		return -12;
	}

	if (index == 0)
	{

		h_thread[index] = (HANDLE) _beginthreadex (NULL, 0, &fgg__machine_utimac_scy45ht__main_thread, NULL, 0, &thread_id[0]);
	}
	else
	{
		//h_thread[index] = (HANDLE) _beginthreadex (NULL, 0, &fgg__cncs__1__simulator_thread, NULL, 0, &thread_id[1]);
	}


	//h_thread[index] = 0; //in test
	if (h_thread[index] == 0)
	{
		return -20;
	}

	carmelo__cncs->machine[0].thread_status[index] = 1;

	return 0;
}





int fgg__cncs__2__begin_thread (unsigned long index)
{
	static HANDLE h_thread[2];
	static unsigned int thread_id[2];

	if (index > 2)
	{
		return -10;
	}

	if (carmelo__cncs->machine[2].configurated == 0)
	{
		return -11;
	}

	if (carmelo__cncs->machine[2].thread_status[index] != 0)
	{
		return -12;
	}

	if (index == 0)
	{
		h_thread[index] = (HANDLE) _beginthreadex (NULL, 0, &carmelo__cncs__focas__main_thread, NULL, 0, &thread_id[0]);
	}
	else
	{
		;
	}



	if (h_thread[index] == 0)
	{
		return -20;
	}

	carmelo__cncs->machine[2].thread_status[index] = 1;

	return 0;
}


//fgg__buffer_t fgg__machine_utimac_scy45ht__live_data[FGGR__CNCS_MACHINE_DATA_MAX];

//fgg__buffer_t fgg__machine_star__75__live_data[FGGR__CNCS_MACHINE_DATA_MAX];

fgg__buffer_t fgg__machines__live_data[FGGR__CNCS_MACHINE_DATA_MAX];

utils__sdb_t db_data;
char db_buffer[FGGR__CONFIG__SDB_BUFFER_SIZE];
unsigned long db_name_len[FGGR__CONFIG__SDB_FIELDS_MAX];
char *db_name[FGGR__CONFIG__SDB_FIELDS_MAX];
unsigned long db_value_len[FGGR__CONFIG__SDB_FIELDS_MAX];
char *db_value[FGGR__CONFIG__SDB_FIELDS_MAX];
int db_encoding[FGGR__CONFIG__SDB_FIELDS_MAX];



void carmelo__cncs__test_task (void)
{
	static int state = 0;
	static timer_soft_sec_t timer;
	static unsigned long cnc_count;
	//static timer_soft_ms_t timer[CNC_MACHINES_MAX];
	unsigned long i;
	int rc;
	static fgg__buffer_t programs_name;
	static fgg__buffer_t prog_in_exe[1];
	//unsigned long found;
	int active;
	int response;
	unsigned long count;
	//static fgg__payload_t paylaod;
	utils__sdb__config_t sdb_config;
	unsigned long language_iso_639_1_code_len;
	char language_iso_639_1_code[UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	language_iso_639_1_code[0] = 'i';
	language_iso_639_1_code[1] = 't';
	language_iso_639_1_code_len = 2;

	switch (state)
	{

	case 0:	

		sdb_config.buffer = db_buffer;
		sdb_config.buffer_size = sizeof(db_buffer);
		sdb_config.name = db_name;
		sdb_config.name_len = db_name_len;
		sdb_config.value = db_value;
		sdb_config.value_len = db_value_len;
		sdb_config.encoding = db_encoding;
		sdb_config.fields_max = FGGR__CONFIG__SDB_FIELDS_MAX;

		rc = utils__sdb__config_sdb (&db_data, &sdb_config);
		if (rc != 0)
		{
			utils__printf__error(&fggr->pf, fn, -30, "utils__sdb__config_sdb() returned %d", rc);
			state = 900;
		}
		state = 1;
		break;

	case 1:

		rc = carmelo__cncs__db__select_count_from_cncs(&count);
		if (rc != 0)
		{
			state = 900;
			break;
		}


		for (i = 1; i <= count; i++)
		{
			carmelo__cncs->machine_count = count;
			rc = carmelo__cncs__db__select_cnc_from_cncs (i, &db_data, &active, NULL, 0, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				state = 900;
				break;
			}


			rc = fgg__cncs__command (i, FGGR__CNCS__CMD__CONFIG,  &db_data, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}

			(void) fgg__cncs__command (i, FGGR__CNCS__CMD__CONFIG_END, NULL, 0, NULL);
			if (rc != 0)
			{
				state = 900;
				break;
			}
		}


		rc = fgg__cncs__1__begin_thread (0);

		////da decommentare rc = fgg__cncs__2__begin_thread (0);

		state = 3;

		break;

	case 3:


		timer_soft_sec_start(&timer, 5);
		state = 4;

		break;

	case 4:
		if (timer_soft_sec_is_expired(&timer) != 0)
		{
			return;
		}


		rc = fgg__cncs__command (1, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

		if (rc != 0)
		{
			state = 900;
			break;
		}		


		rc = fgg__cncs__command (2, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);
		if (rc != 0)
		{
			state = 900;
			break;
		}	

		rc = fgg__cncs__command (3, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);
		if (rc != 0)
		{
			state = 900;
			break;
		}	

		rc = fgg__cncs__command (4, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);
		if (rc != 0)
		{
			state = 900;
			break;
		}	

		rc = fgg__cncs__command (5, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);
		if (rc != 0)
		{
			state = 900;
			break;
		}	
		state = 5;
		break;

	case 5:
		//args_out_max = (sizeof (fgg__machine_utimac_scy45ht__live_data) / sizeof (fgg__buffer_t));

		rc = fgg__cncs__is_command_ended (1, FGGR__CNCS__CMD__GET_MACHINE_DATA, &response, &carmelo__cncs->machine[0].data_value_cnc);

		if (rc == 0)
		{
			rc = fgg__cncs__command (1, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}		
		}	

		rc = fgg__cncs__is_command_ended (2, FGGR__CNCS__CMD__GET_MACHINE_DATA, &response, &carmelo__cncs->machine[1].data_value_cnc);

		if (rc == 0)
		{
			rc = fgg__cncs__command (2, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}		
		}	


		rc = fgg__cncs__is_command_ended (3, FGGR__CNCS__CMD__GET_MACHINE_DATA, &response, &carmelo__cncs->machine[2].data_value_cnc);

		if (rc == 0)
		{
			rc = fgg__cncs__command (3, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}		
		}
		else if (rc < 0)
		{
			rc = fgg__cncs__command (3, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}	
		}



		rc = fgg__cncs__is_command_ended (4, FGGR__CNCS__CMD__GET_MACHINE_DATA, &response, &carmelo__cncs->machine[3].data_value_cnc);

		if (rc == 0)
		{
			rc = fgg__cncs__command (4, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}		
		}	
		else if (rc < 0)
		{
			rc = fgg__cncs__command (4, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}	
		}


		rc = fgg__cncs__is_command_ended (5, FGGR__CNCS__CMD__GET_MACHINE_DATA, &response, &carmelo__cncs->machine[4].data_value_cnc);

		if (rc == 0)
		{
			rc = fgg__cncs__command (5, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}		
		}
		else if (rc < 0)
		{
			rc = fgg__cncs__command (5, FGGR__CNCS__CMD__GET_MACHINE_DATA, NULL, 0, NULL);

			if (rc != 0)
			{
				state = 900;
				break;
			}	
		}

		state = 6;
		break;

	case 6:


		timer_soft_sec_start(&timer, 5);
		state = 7;

		break;

	case 7:
		if (timer_soft_sec_is_expired(&timer) != 0)
		{
			return;
		}
		state = 5;
		break;
		/*	case 6:
		rc = fgg__cncs__command (fd_index, FGGR__CNCS__CMD__GET_PROGRAMS_NAME, NULL, 0, 0, NULL);

		if (rc == 0)
		{
		state[k] = 7;
		}		
		break;

		case 7:


		rc = fgg__cncs__is_command_ended (fd_index, FGGR__CNCS__CMD__GET_PROGRAMS_NAME, &response, &args_out_count, &programs_name, 1);
		if (rc == 0)
		{
		if (response == 0)
		{

		fgg__util__print_buffer (&programs_name);	

		printf("---------------\r\n");
		timer_soft_ms_start(&timer, 1000);

		state = 8;

		}
		else
		{
		state[k] = 3;
		}			
		}	
		break;

		case 8:

		rc = fgg__cncs__command (fd_index, FGGR__CNCS__CMD__GET_PROGRAM, &prog_in_exe[k], 1, 0, &paylaod);

		if (rc == 0)
		{
		state = 9;
		}		
		break;

		case 9:


		rc = fgg__cncs__is_command_ended (fd_index, FGGR__CNCS__CMD__GET_PROGRAM, &response, &args_out_count, &programs_name, 1);
		if (rc == 0)
		{
		if (response == 0)
		{

		fgg__util__print_payload (&paylaod);	

		printf("---------------\r\n");
		timer_soft_ms_start(&timer, 1000);

		state = 3;

		}	
		break;
		*/
	case 100:		
		state = 100;
		break;

	case 900:
		state = 900;
		break;

	default:
		state = 0;
		break;
	}

}














