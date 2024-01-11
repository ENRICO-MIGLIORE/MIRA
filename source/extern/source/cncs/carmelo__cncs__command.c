//#include <windows.h>
#include <process.h>

#include "..\fggr.h"

//#include "..\fgg__cncs_open62541.h"
#include "carmelo__cncs.h"
#include "timer_soft_sec.h"



//int fgg__cncs__is_command_ended (int fd, int cmd, int *response, unsigned long *arg_count, fgg__buffer_t *arg, unsigned long args_max, fgg__payload_t *payload, unsigned long* payload_count)
int fgg__cncs__is_command_ended (int fd, int cmd, int *response, utils__sdb_t *data)
{
	int rc;

	unsigned long language_iso_639_1_code_len;
	char language_iso_639_1_code[UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	language_iso_639_1_code[0] = 'i';
	language_iso_639_1_code[1] = 't';
	language_iso_639_1_code_len = 2;

	if ((fd <= 0) || (fd > FGGR__CNCS__MACHINE_MAX))
	{
		return -10;
	}

	fd--;


	rc = 1;

	if (carmelo__cncs->machine[fd].shell.command_status[cmd] != 3)
	{
		/*
		* Command is in progress
		*/
		return 1;
	}

	switch (cmd)
	{

	case FGGR__CNCS__CMD__CONFIG:
		rc = 0;

		*response = FGGR__CNCS__RESPONSE__OK;
		break;

	case FGGR__CNCS__CMD__CONFIG_END:
		rc = 0;

		*response = FGGR__CNCS__RESPONSE__OK;
		break;

	case FGGR__CNCS__CMD__GET_MACHINE_DATA:

		if (carmelo__cncs->machine[fd].shell.command_status[cmd] == 3)
		{
			*response = carmelo__cncs->machine[fd].shell.response[cmd];
			

			rc = utils__sdb__clear_sdb(data);
			if (rc != 0)
			{
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

			rc = utils__sdb__write_pair_to_sdb(data, "connessione", strlen("connessione"), carmelo__cncs->machine[fd].live_data.connect.data, carmelo__cncs->machine[fd].live_data.connect.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

		    rc = utils__sdb__write_pair_to_sdb(data, "status", strlen("status"), carmelo__cncs->machine[fd].live_data.in_production.data, carmelo__cncs->machine[fd].live_data.in_production.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
		    if (rc != 0)
		 	{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

		    rc = utils__sdb__write_pair_to_sdb(data, "in_alarm", strlen("in_alarm"), carmelo__cncs->machine[fd].live_data.in_alarm.data, carmelo__cncs->machine[fd].live_data.in_alarm.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

		    rc = utils__sdb__write_pair_to_sdb(data, "absolute_machine_part", strlen("absolute_machine_part"), carmelo__cncs->machine[fd].live_data.absolute_machine_part.data, carmelo__cncs->machine[fd].live_data.absolute_machine_part.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

			rc = utils__sdb__write_pair_to_sdb(data, "prog_in_exe", strlen("prog_in_exe"), carmelo__cncs->machine[fd].live_data.prog_in_exe.data, carmelo__cncs->machine[fd].live_data.prog_in_exe.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

			rc = utils__sdb__write_pair_to_sdb(data, "cicle_time", strlen("cicle_time"), carmelo__cncs->machine[fd].live_data.cicle_time.data, carmelo__cncs->machine[fd].live_data.cicle_time.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

			rc = utils__sdb__write_pair_to_sdb(data, "bar_feed", strlen("bar_feed"), carmelo__cncs->machine[fd].live_data.bar_feed.data, carmelo__cncs->machine[fd].live_data.bar_feed.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

			rc = utils__sdb__write_pair_to_sdb(data, "instant_power", strlen("instant_power"), carmelo__cncs->machine[fd].live_data.instant_power.data, carmelo__cncs->machine[fd].live_data.instant_power.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}

			rc = utils__sdb__write_pair_to_sdb(data, "average_power", strlen("average_power"), carmelo__cncs->machine[fd].live_data.average_power.data, carmelo__cncs->machine[fd].live_data.average_power.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				rc = utils__sdb__clear_sdb(data);
				carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
				return -1000;
			}


			carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
			rc = 0;
		}
		break;



	case FGGR__CNCS__CMD__GET_PROGRAMS_NAME:

		if (carmelo__cncs->machine[fd].shell.command_status[cmd] == 3)
		{
			*response = carmelo__cncs->machine[fd].shell.response[cmd];
			
			
			rc = utils__sdb__clear_sdb(data);
			if (rc != 0)
			{
				return -1000;
			}

			rc = utils__sdb__write_pair_to_sdb(data, "programs_name", strlen("programs_name"), carmelo__cncs->machine[fd].programs_name.data, carmelo__cncs->machine[fd].programs_name.len, UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				return -1000;
			}
		
			carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
			rc = 0;
		}
		break;


    case FGGR__CNCS__CMD__GET_PROGRAM:

		if (carmelo__cncs->machine[fd].shell.command_status[cmd] == 3)
		{
			*response = carmelo__cncs->machine[fd].shell.response[cmd];
			
		

			//fgg__util__copy_payload (payload, const fgg__payload_t *source) (payload->data, &carmelo__cncs->machine[fd].buff_prog, 
			//argc++;

			

			carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
			rc = 0;
		}
		break;


	default:
		return -1000;
		break;
	}

	return rc;

}



static char *fn = "fgg__cncs__command()";

int fgg__cncs__command (int fd, int cmd, utils__sdb_t *data_sdb, unsigned long sequence,  fgg__buffer_t *payload)
{
	int rc;
	unsigned long i;

	unsigned long language_iso_639_1_code_len;
	char language_iso_639_1_code[UTILS__LANGUAGE_ISO_639_1__CODE_LEN];

	language_iso_639_1_code[0] = 'i';
	language_iso_639_1_code[1] = 't';
	language_iso_639_1_code_len = 2;


	if ((fd <= 0) || (fd > FGGR__CNCS__MACHINE_MAX))
	{
		return -10;
	}

	fd--;

	if (carmelo__cncs->machine[fd].shell.command_status[cmd] != 0)
	{
		/*
		 * Command is in progress
		 */
		return 1;
	}

	if ((carmelo__cncs->machine[fd].configurated == 0) && (cmd != FGGR__CNCS__CMD__CONFIG) && (cmd != FGGR__CNCS__CMD__CONFIG_END))
	{
		return -11;
	}

	rc = -1000;


	
	switch (cmd)
	{

	case FGGR__CNCS__CMD__CONFIG:

		if (data_sdb == NULL)
	    {
		     utils__printf__error(&fggr->pf, fn, -10, "data_sdb == NULL");
		     return -10;
	    }

	    if (data_sdb->num_fields < 42)
	    {
		    utils__printf__error(&fggr->pf, fn, -20, "data_sdb->num_fields < 2, data_sdb->num_fields %d", data_sdb->num_fields);
		    return -20;
	    }

		for (i = 0; i < data_sdb->num_fields; i++)
		{
		    rc = utils__sdb__write_pair_to_sdb(&carmelo__cncs->machine[fd].data, data_sdb->name[i], data_sdb->name_len[i], data_sdb->value[i], data_sdb->value_len[i], UTILS__SDB__ENCODING__UTF_8, language_iso_639_1_code, language_iso_639_1_code_len);
			if (rc != 0)
			{
				utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__write_pair_to_sdb() return %d", rc);
		    return -20;
			}
		}

		carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
		carmelo__cncs->machine[fd].shell.response[cmd] = 0;
		rc = 0;	
		break;

	case FGGR__CNCS__CMD__CONFIG_END:		
		carmelo__cncs->machine[fd].configurated = 1;
		carmelo__cncs->machine[fd].shell.command_status[cmd] = 0;
		carmelo__cncs->machine[fd].shell.response[cmd] = 0;
		rc = 0;
		break;

	case FGGR__CNCS__CMD__GET_MACHINE_DATA:
		carmelo__cncs->machine[fd].shell.command_status[cmd] = 1;
		rc = 0;
		break;

	case FGGR__CNCS__CMD__GET_PROGRAMS_NAME:
		carmelo__cncs->machine[fd].shell.command_status[cmd] = 1;
		rc = 0;
		break;

    case FGGR__CNCS__CMD__GET_PROGRAM:

		/*if (argc != 1)
		{
			return -2;
		}
		fgg__util__copy_buffer (&carmelo__cncs->machine[fd].prog_numeber_to_read, arg);
		carmelo__cncs->machine[fd].payload = payload;*/
		
		carmelo__cncs->machine[fd].shell.command_status[cmd] = 1;
		rc = 0;
		break;


	default:
		return -10;
		break;

	}


	return rc;
}

