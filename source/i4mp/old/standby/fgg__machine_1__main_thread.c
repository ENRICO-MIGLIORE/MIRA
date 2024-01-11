#include <stdio.h>
#include <stdlib.h>
#include "../fgg.h"



#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/plugin/securitypolicy.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/plugin/securitypolicy_default.h>
#include "../common.h"


int fgg__cnc__open62541_connect  (UA_Client *client, fgg__buffer_t* ip, fgg__buffer_t* port, fgg__buffer_t* username, fgg__buffer_t* password);
int fgg__cnc__open62541_clear_client  (UA_Client *client);
int fgg__cnc__open62541_get_machined_parts (UA_Client* client, fgg__buffer_t* path, size_t *count);
int fgg__cnc__open62541_get_emergency (UA_Client* client, fgg__buffer_t* path, size_t *state);
int fgg__cnc__open62541_get_time_of_cycle  (UA_Client* client, fgg__buffer_t* path, double *time);
int fgg__cnc__open62541_number_of_alarm (UA_Client* client, fgg__buffer_t* path, size_t *alarm);
int fgg__cnc__open62541_name_program_in_execution  (UA_Client* client, fgg__buffer_t* path, fgg__buffer_t *prog);
int fgg__cnc__open62541_get_state_machine (UA_Client* client, fgg__buffer_t* path, size_t *state);
int fgg__cnc__open62541_get_avanzamento_barra (UA_Client* client, fgg__buffer_t* path, size_t *avanzamento);
int fgg__cnc__enca_pscp_get_program_files (fgg__buffer_t* ip,  fgg__buffer_t* username, fgg__buffer_t* password, fgg__buffer_t* path_source, fgg__buffer_t* path_dest, size_t flag);






/*
 * CNC-1 = Settembre 2019 - Finotto
 */



#define CNC_1__INIT__STATE                         0
#define CNC_1__IS_IN_NETWORK__STATE                1
#define CNC_1__CONNECT                             2
#define CNC_1__RECONNECT                           3
#define CNC_1__READY__STATE                       10

#define CNC_1__MACHINE_DATA__STATE               110
#define CNC_1__PROGRAMS_NAME__STATE              111



#define CNC_PARAMETER_MACCHINA_IN_RETE            0           //se la macchina e' connessa in rete  (esempio le macchine vecchie non sono in rete = 0)
#define CNC_PARAMETER_IP_1                        1           //indirizzo ip dell'opc   o se e' una fanuc indirizzo ip del cn
#define CNC_PARAMETER_PORTA_IP_1                  2			  //numero di porta riferita al ip sopra
#define CNC_PARAMETER_USER_NAME_OPC               3			  //client login per OPC
#define CNC_PARAMETER_PASSWORD_OPC                4			  //password login per OCP
#define CNC_PARAMETER_IP_2                        5			  //ip per winscp
#define CNC_PARAMETER_PORTA_IP_2                  6			  //porta per winscp
#define CNC_PARAMETER_USER_NAME_WINSCP            7			  //user login per winscp
#define CNC_PARAMETER_PASSWORD_WINSCP             8			  //password login per winscp
#define CNC_PARAMETER_PERCORSO_PEZZI_ASSOLUTI     9			  
#define CNC_PARAMETER_PERCORSO_TEMPO_DI_CICLO     10
#define CNC_PARAMETER_PERCORSO_ALLARMI            11
#define CNC_PARAMETER_NOME_PROG_IN_ESECUZIONE     12
#define CNC_PARAMETER_STATO_MACCHINA              13
#define CNC_PARAMETER_AVANZAMENTO_BARRA           18
#define CNC_PARAMETER_FUNGO_EMERGENZA             19
#define CNC_PARAMETER_PERCORSO_WRKS_DIR_SRC       20
#define CNC_PARAMETER_PERCORSO_WRKS_DIR_DST       21



#define UTIMAC_MAX    2

int enca_psftp_init(void);


void tolocal(int argc, char *argv[]);

char *argv[128];
static char tmp_source_buff[512];
void pippo (int argc, char* argv[]);

unsigned int __stdcall fgg__machine_1__main_thread (void *arg)
{
	static int state[UTIMAC_MAX];
	static double cycle_time[UTIMAC_MAX];
	size_t alarm[UTIMAC_MAX];
	size_t state_machine[UTIMAC_MAX];
	size_t avanzamento[UTIMAC_MAX];
	fgg__buffer_t prog[UTIMAC_MAX];
	static int index[UTIMAC_MAX] = {0, 4};
	int rc[UTIMAC_MAX];
	static UA_Client *client3[UTIMAC_MAX];
	static size_t machine_is_connected[UTIMAC_MAX];
	int i;
	size_t buffer_size;
	static size_t pieces_machined[UTIMAC_MAX];
	size_t state_em;
	static timer_soft_sec_t timer_ms_for_read_file[UTIMAC_MAX];
	


	while (fgg.cncs->machine[0].thread_status[0] == 0);


	while ((fgg.cncs->machine[0].thread_status[0] == 1) || (fgg.cncs->machine[0].thread_status[0] == 2))
	{

		for (i = 0; i < UTIMAC_MAX; i++)
		{
			switch (state[i])
			{

			case CNC_1__INIT__STATE:
				if (fgg.cncs->machine[index[i]].configurated != 0)
				{
					state[i] = CNC_1__IS_IN_NETWORK__STATE;
				}			
				break;

			case CNC_1__IS_IN_NETWORK__STATE:
				if (fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_MACCHINA_IN_RETE].data[0] != '0')
				{
					if (i == 0)
					{
						enca_psftp_init();
					}
					
					client3[i] = UA_Client_new();

					state[i] = CNC_1__CONNECT;
				}			
				break;

			case CNC_1__CONNECT:
				/*EK rc[i] = fgg__cnc__open62541_connect  (client3[i], &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_IP_1], 
					                                              &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_PORTA_IP_1],
					                                              &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_USER_NAME_OPC], 
																  &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_PASSWORD_OPC]);*/

				if (rc[i] == 0)
				{
					
					//timer_soft_ms_start(&timer_ms_for_read_file[i], 10000 * (i + 1));
					timer_soft_sec_start(&timer_ms_for_read_file[i], 10 * (i + 1));
					state[i] = CNC_1__READY__STATE;
				}

				break;

			case CNC_1__RECONNECT:
				//EK fgg__cnc__open62541_clear_client  (client3[i]);

				client3[i] = UA_Client_new();

				state[i] = CNC_1__CONNECT;


				break;	

			case CNC_1__READY__STATE:

				//if (timer_soft_ms_is_expired (&timer_ms_for_read_file[0]) == 0)
				if (timer_soft_sec_is_expired (&timer_ms_for_read_file[0]) == 0)
				{ 
					//leggo i file da scp
					/*EK fgg__cnc__enca_pscp_get_program_files (&fgg.cncs->machine[index[0]].parameter[CNC_PARAMETER_IP_2],  
						                                   &fgg.cncs->machine[index[0]].parameter[CNC_PARAMETER_USER_NAME_WINSCP], 
														   &fgg.cncs->machine[index[0]].parameter[CNC_PARAMETER_PASSWORD_WINSCP], 
														   &fgg.cncs->machine[index[0]].parameter[CNC_PARAMETER_PERCORSO_WRKS_DIR_SRC], 
														   &fgg.cncs->machine[index[0]].parameter[CNC_PARAMETER_PERCORSO_WRKS_DIR_DST], 
														   1);*/

					//timer_soft_ms_start (&timer_ms_for_read_file[0], 9900000 * (i + 1));
					//timer_soft_ms_start (&timer_ms_for_read_file[1], 10000);

					timer_soft_sec_start (&timer_ms_for_read_file[0], 9900 * (i + 1));
					timer_soft_sec_start (&timer_ms_for_read_file[1], 10);
				}

				//if (timer_soft_ms_is_expired (&timer_ms_for_read_file[1]) == 0)
				if (timer_soft_sec_is_expired (&timer_ms_for_read_file[1]) == 0)
				{ 
					//timer_soft_ms_start (&timer_ms_for_read_file[1], 12000 * (i + 1));
					timer_soft_sec_start (&timer_ms_for_read_file[1], 12 * (i + 1));

					tmp_source_buff[0] = '\0';
					strcpy (tmp_source_buff,"manufact@192.168.1.52:/nckfs/_N_WKS_DIR");
				    argv[0] = tmp_source_buff;
			        argv[1] = "..\\ciao";
			        pippo (2, argv);
				}

				pieces_machined[i] = 0;
				cycle_time[i] = 0;
				state_machine[i] = 0;
				alarm[i] = 0;


				rc[i] = 0;

				//EK rc[i] |= fgg__cnc__open62541_get_machined_parts  (client3[i],  &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_PERCORSO_PEZZI_ASSOLUTI], &pieces_machined[i]);

				//EK rc[i] |= fgg__cnc__open62541_get_time_of_cycle  (client3[i],  &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_PERCORSO_TEMPO_DI_CICLO], &cycle_time[i]);

				//EK rc[i] |= fgg__cnc__open62541_number_of_alarm  (client3[i], &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_PERCORSO_ALLARMI], &alarm[i]);

				//EK rc[i] |= fgg__cnc__open62541_name_program_in_execution  (client3[i], &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_NOME_PROG_IN_ESECUZIONE], &prog[i]); 

				//EK rc[i] |= fgg__cnc__open62541_get_state_machine  (client3[i], &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_STATO_MACCHINA], &state_machine[i]); 

				//EK rc[i] |= fgg__cnc__open62541_get_avanzamento_barra (client3[i], &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_AVANZAMENTO_BARRA], &avanzamento[i]); 

				//EK rc[i] |= fgg__cnc__open62541_get_emergency  (client3[i], &fgg.cncs->machine[index[i]].parameter[CNC_PARAMETER_FUNGO_EMERGENZA], &state_em);


				machine_is_connected[i] = 1;
				if (rc[i] != 0)
				{
					machine_is_connected[i] = 0;
				}

				if ((avanzamento[i] == 1) && ((state_machine[i] == 2) || (state_machine[i] == 3)))   //condizione controllata al telefono con faggion : state deve essere o 2 o 3 (2=Run 3=Wait) && avanzamento_barra = 1
				{
					state_machine[i] = 1;
				}
				else
				{
					state_machine[i] = 0;
				}


				if (fgg.cncs->machine[index[i]].shell.command_status[FGG__CNCS__CMD__GET_MACHINE_DATA] == 1)
				{
					fgg.cncs->machine[index[i]].shell.command_status[FGG__CNCS__CMD__GET_MACHINE_DATA] = 2;
					state[i] = CNC_1__MACHINE_DATA__STATE;
				}
				else if (fgg.cncs->machine[index[i]].shell.command_status[FGG__CNCS__CMD__GET_PROGRAMS_NAME] == 1)
				{
					fgg.cncs->machine[index[i]].shell.command_status[FGG__CNCS__CMD__GET_PROGRAMS_NAME] = 2;
					state[i] = CNC_1__PROGRAMS_NAME__STATE;
				}
				else if (machine_is_connected[i] == 0)
				{
					state[i] = CNC_1__RECONNECT;
				}

				break;

			case CNC_1__MACHINE_DATA__STATE:

				buffer_size = sizeof(fgg.cncs->machine[index[i]].live_data.connect.data);
				rc[i] = util__ultoa (machine_is_connected[i], fgg.cncs->machine[index[i]].live_data.connect.data, buffer_size,  &fgg.cncs->machine[index[i]].live_data.connect.len);

				buffer_size = sizeof(fgg.cncs->machine[index[i]].live_data.absolute_machine_part.data);
				rc[i] = util__ultoa (pieces_machined[i], fgg.cncs->machine[index[i]].live_data.absolute_machine_part.data, buffer_size,  &fgg.cncs->machine[index[i]].live_data.absolute_machine_part.len);

				buffer_size = sizeof(fgg.cncs->machine[index[i]].live_data.in_production.data);
				rc[i] = util__ultoa (state_machine[i], fgg.cncs->machine[index[i]].live_data.in_production.data, buffer_size,  &fgg.cncs->machine[index[i]].live_data.in_production.len);

				buffer_size = sizeof(fgg.cncs->machine[index[i]].live_data.in_alarm.data);
				rc[i] = util__ultoa (alarm[i], fgg.cncs->machine[index[i]].live_data.in_alarm.data, buffer_size,  &fgg.cncs->machine[index[i]].live_data.in_alarm.len);


				memcpy (&fgg.cncs->machine[index[i]].live_data.prog_in_exe, &prog[i], sizeof(fgg__buffer_t));

				fgg.cncs->machine[index[i]].shell.response[FGG__CNCS__CMD__GET_MACHINE_DATA] = 0;
				fgg.cncs->machine[index[i]].shell.command_status[FGG__CNCS__CMD__GET_MACHINE_DATA] = 3;
				state[i] = CNC_1__READY__STATE;

				break;

			case CNC_1__PROGRAMS_NAME__STATE:

				rc[i] = fgg__util__write_buffer (&fgg.cncs->machine[index[i]].programs_name , "-", 1);

				if (machine_is_connected == 0)
				{
					//macchina non connessa

					state[i] = CNC_1__RECONNECT;
				}
				else
				{

					state[i] = CNC_1__READY__STATE;

				}

				fgg.cncs->machine[index[i]].shell.response[FGG__CNCS__CMD__GET_PROGRAMS_NAME] = 0;
				fgg.cncs->machine[index[i]].shell.command_status[FGG__CNCS__CMD__GET_PROGRAMS_NAME] = 3;



				break;


			default:

				break;
			}


			if (fgg.cncs->machine[index[i]].thread_status[0] == 2)
			{
				/*
				* Exit request from external application
				*/
				fgg.cncs->machine[index[i]].thread_status[0] = 3;
			}

		}

	}
	return 0;

}
