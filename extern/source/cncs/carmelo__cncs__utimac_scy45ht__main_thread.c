

#include "carmelo__cncs__open62541.h"
#include "carmelo__cncs.h"





#define CNC_1__IS_IN_NETWORK__STATE                0
#define CNC_1__CONNECT                             1
#define CNC_1__RECONNECT                           2
#define CNC_1__READY__STATE                       10

#define CNC_1__MACHINE_DATA__STATE               110
#define CNC_1__PROGRAMS_NAME__STATE              111



#define CNC_PARAMETER_MACCHINA_IN_RETE            12          //se la macchina e' connessa in rete  (esempio le macchine vecchie non sono in rete = 0)
#define CNC_PARAMETER_IP_1                        13           //indirizzo ip dell'opc   o se e' una fanuc indirizzo ip del cn
#define CNC_PARAMETER_PORTA_IP_1                  14			  //numero di porta riferita al ip sopra
#define CNC_PARAMETER_USER_NAME_OPC               15			  //client login per OPC
#define CNC_PARAMETER_PASSWORD_OPC                16			  //password login per OCP
#define CNC_PARAMETER_IP_2                        17			  //ip per winscp
#define CNC_PARAMETER_PORTA_IP_2                  18			  //porta per winscp
#define CNC_PARAMETER_USER_NAME_WINSCP            19			  //user login per winscp
#define CNC_PARAMETER_PASSWORD_WINSCP             21			  //password login per winscp
#define CNC_PARAMETER_PERCORSO_PEZZI_ASSOLUTI     21			  
#define CNC_PARAMETER_PERCORSO_TEMPO_DI_CICLO     22
#define CNC_PARAMETER_PERCORSO_ALLARMI            23
#define CNC_PARAMETER_NOME_PROG_IN_ESECUZIONE     24
#define CNC_PARAMETER_STATO_MACCHINA              25
#define CNC_PARAMETER_AVANZAMENTO_BARRA           26
#define CNC_PARAMETER_FUNGO_EMERGENZA             27
#define CNC_PARAMETER_PERCORSO_WRKS_DIR_SRC       28
#define CNC_PARAMETER_PERCORSO_WRKS_DIR_DST       29
#define CNC_PARAMETER_PERCORSO_INSTANT_POWER      30
#define CNC_PARAMETER_PERCORSO_AVERAGE_POWER      31



#define UTIMAC_MAX    2

int enca_psftp_init(void);


void tolocal(int argc, char *argv[]);

char *argv[128];
static char tmp_source_buff[512];
void pippo (int argc, char* argv[]);

static UA_Client *client3[UTIMAC_MAX];


//unsigned int __stdcall  fgg__machine_utimac_scy45ht__main_thread (void *arg)
//{
//	static int state[UTIMAC_MAX];
//	static double cycle_time[UTIMAC_MAX];
//	static double instant_power[UTIMAC_MAX];
//	static double average_power[UTIMAC_MAX];
//	static unsigned long alarm[UTIMAC_MAX];
//	static unsigned long state_machine[UTIMAC_MAX];
//	static unsigned long avanzamento[UTIMAC_MAX];
//	static fgg__buffer_t prog[UTIMAC_MAX];
//	//static int index[UTIMAC_MAX] = {0, 4};
//	static int index[UTIMAC_MAX] = {0,1};
//	int rc[UTIMAC_MAX];
//
//	
//	static unsigned long machine_is_connected[UTIMAC_MAX];
//	int i;
//	static unsigned long pieces_machined[UTIMAC_MAX];
//	static unsigned long state_em;
//	//static timer_soft_ms_t timer_ms_for_read_file[UTIMAC_MAX];
//	
//
//	while (carmelo__cncs->machine[0].thread_status[0] == 0);
//
//
//	while ((carmelo__cncs->machine[0].thread_status[0] == 1) || (carmelo__cncs->machine[0].thread_status[0] == 2))
//	{
//	
//		for (i = 0; i < UTIMAC_MAX; i++)
//		{
//			switch (state[i])
//			{
//
//		
//			case CNC_1__IS_IN_NETWORK__STATE:
//				if (carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_MACCHINA_IN_RETE][0] != '0')
//				{
//					//if 0 temporaneo perche' in realta' funziona tutto al 22-02-2020
//#if 0  
//					if 0 temporaneo perche' in realta' funziona tutto al 22-02-2020
//					if (i == 0)
//					{
//						enca_psftp_init();
//					}
//#endif					
//					state[i] = CNC_1__CONNECT;
//				}			
//				break;
//
//			case CNC_1__CONNECT:
//
//				client3[i] = UA_Client_new();
//
//				rc[i] = carmelo__cncs__open62541_connect  (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_IP_1], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_IP_1], 
//					                                              carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_PORTA_IP_1], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_PORTA_IP_1],
//					                                              carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_USER_NAME_OPC],carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_USER_NAME_OPC], 
//  																  carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_PASSWORD_OPC], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_PASSWORD_OPC]);
//
//				if (rc[i] == 0)
//				{
//					
//					//timer_soft_ms_start(&timer_ms_for_read_file[i], 10000 * (i + 1));
//					state[i] = CNC_1__READY__STATE;
//				    break;
//				}
//				carmelo__cncs__open62541_clear_client  (client3[i]);
//
//
//				break;
//
//			case CNC_1__RECONNECT:
//				//carmelo__cncs__open62541_clear_client  (client3[i]);
//
//				
//				state[i] = CNC_1__CONNECT;
//
//
//				break;	
//
//			case CNC_1__READY__STATE:
//
//									//if 0 temporaneo perche' in realta' funziona tutto al 22-02-2020
//#if 0 
//				
//				if 0 temporaneo perche' in realta' funziona tutto al 22-02-2020
//				if (timer_soft_ms_is_expired (&timer_ms_for_read_file[0]) == 0)
//				{ 
//
//					//leggo i file da scp
//					fgg__cnc__enca_pscp_get_program_files (&carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_IP_2],  
//						                                   &carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_USER_NAME_WINSCP], 
//														   &carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_PASSWORD_WINSCP], 
//														   &carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_PERCORSO_WRKS_DIR_SRC], 
//														   &carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_PERCORSO_WRKS_DIR_DST], 
//														   1);
//
//					timer_soft_ms_start (&timer_ms_for_read_file[0], 9900000 * (i + 1));
//					timer_soft_ms_start (&timer_ms_for_read_file[1], 10000);
//				}
//
//				if (timer_soft_ms_is_expired (&timer_ms_for_read_file[1]) == 0)
//				{ 
//					timer_soft_ms_start (&timer_ms_for_read_file[1], 12000 * (i + 1));
//
//
//					
//					tmp_source_buff[0] = '\0';
//					strcpy (tmp_source_buff,"manufact@192.168.1.52:/nckfs/_N_WKS_DIR");
//				    argv[0] = tmp_source_buff;
//			        argv[1] = "..\\22-02-2020";
//			        pippo (2, argv);
//
//				}
//#endif
//				pieces_machined[i] = 0;
//				cycle_time[i] = 0;
//				state_machine[i] = 0;
//				alarm[i] = 0;
//
//
//				rc[i] = 0;
//				rc[i] |= carmelo__cncs__open62541_get_machined_parts  (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_PERCORSO_PEZZI_ASSOLUTI], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_PERCORSO_PEZZI_ASSOLUTI], &pieces_machined[i]);
//
//				rc[i] |= carmelo__cncs__open62541_get_time_of_cycle  (client3[i],  carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_PERCORSO_TEMPO_DI_CICLO], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_PERCORSO_TEMPO_DI_CICLO], &cycle_time[i]);
//
//				rc[i] |= carmelo__cncs__open62541_number_of_alarm  (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_PERCORSO_ALLARMI], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_PERCORSO_ALLARMI], &alarm[i]);
//
//				rc[i] |= carmelo__cncs__open62541_name_program_in_execution  (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_NOME_PROG_IN_ESECUZIONE], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_NOME_PROG_IN_ESECUZIONE], &prog[i]); 
//
//				rc[i] |= carmelo__cncs__open62541_get_state_machine  (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_STATO_MACCHINA], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_STATO_MACCHINA], &state_machine[i]); 
//
//				rc[i] |= carmelo__cncs__open62541_get_avanzamento_barra (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_AVANZAMENTO_BARRA], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_AVANZAMENTO_BARRA], &avanzamento[i]); 
//
//				rc[i] |= carmelo__cncs__open62541_get_emergency  (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_FUNGO_EMERGENZA], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_FUNGO_EMERGENZA], &state_em);
//
//				rc[i] |= carmelo__cncs__open62541_get_instant_power  (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_PERCORSO_INSTANT_POWER], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_PERCORSO_INSTANT_POWER], &instant_power[i]);
//
//				rc[i] |= carmelo__cncs__open62541_get_average_power  (client3[i], carmelo__cncs->machine[index[i]].data.value[CNC_PARAMETER_PERCORSO_AVERAGE_POWER], carmelo__cncs->machine[index[i]].data.value_len[CNC_PARAMETER_PERCORSO_AVERAGE_POWER], &average_power[i]);
//
//
//				machine_is_connected[i] = 1;
//				if (rc[i] != 0)
//				{
//					machine_is_connected[i] = 0;
//				}
//
//				if ((avanzamento[i] == 1) && ((state_machine[i] == 2) || (state_machine[i] == 3)))   //condizione controllata al telefono con faggion : state deve essere o 2 o 3 (2=Run 3=Wait) && avanzamento_barra = 1
//				{
//					state_machine[i] = 1;
//				}
//				else
//				{
//					state_machine[i] = 0;
//				}
//
//
//				if (carmelo__cncs->machine[index[i]].shell.command_status[FGGR__CNCS__CMD__GET_MACHINE_DATA] == 1)
//				{
//					carmelo__cncs->machine[index[i]].shell.command_status[FGGR__CNCS__CMD__GET_MACHINE_DATA] = 2;
//					state[i] = CNC_1__MACHINE_DATA__STATE;
//				}
//			
//				/*else if (carmelo__cncs->machine[index[i]].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAMS_NAME] == 1)
//				{
//					carmelo__cncs->machine[index[i]].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAMS_NAME] = 2;
//					state[i] = CNC_1__PROGRAMS_NAME__STATE;
//				}*/
//				else if (machine_is_connected[i] == 0)
//				{
//					state[i] = CNC_1__RECONNECT;
//				}
//
//				break;
//
//			case CNC_1__MACHINE_DATA__STATE:
//
//				
//				if (machine_is_connected[i] == 1)
//				{
//					strcpy (carmelo__cncs->machine[index[i]].live_data.connect.data,"online");
//					carmelo__cncs->machine[index[i]].live_data.connect.len = strlen("online");
//				}
//				else
//				{
//					strcpy (carmelo__cncs->machine[index[i]].live_data.connect.data,"offline");
//					carmelo__cncs->machine[index[i]].live_data.connect.len = strlen("offline");
//				}
//
//
//
//
//				(void) ultoa (pieces_machined[i], carmelo__cncs->machine[index[i]].live_data.absolute_machine_part.data, 10);
//				carmelo__cncs->machine[index[i]].live_data.absolute_machine_part.len = strlen (carmelo__cncs->machine[index[i]].live_data.absolute_machine_part.data);
//
//
//				carmelo__cncs->machine[index[i]].live_data.cicle_time.len = sprintf(carmelo__cncs->machine[index[i]].live_data.cicle_time.data,"%.2f sec",cycle_time[i]);
//				
//
//
//
//				if (state_machine[i] == 1)
//				{
//					strcpy (carmelo__cncs->machine[index[i]].live_data.in_production.data,"RUN");
//					carmelo__cncs->machine[index[i]].live_data.in_production.len = 3;
//				}
//				else
//				{
//					strcpy (carmelo__cncs->machine[index[i]].live_data.in_production.data,"STOP");
//					carmelo__cncs->machine[index[i]].live_data.in_production.len = 4;
//				}
//
//
//
//
//				if (alarm[i] > 0)
//				{
//					strcpy (carmelo__cncs->machine[index[i]].live_data.in_alarm.data,"SI");
//				}
//				else
//				{
//					strcpy (carmelo__cncs->machine[index[i]].live_data.in_alarm.data,"NO");
//				}
//				carmelo__cncs->machine[index[i]].live_data.in_alarm.len = 2;
//
//
//				if (avanzamento[i] > 0)
//				{
//					strcpy (carmelo__cncs->machine[index[i]].live_data.bar_feed.data,"SI");
//				}
//				else
//				{
//					strcpy (carmelo__cncs->machine[index[i]].live_data.bar_feed.data,"NO");
//				}
//				carmelo__cncs->machine[index[i]].live_data.bar_feed.len = 2;
//
//
//
//				memcpy(carmelo__cncs->machine[index[i]].live_data.prog_in_exe.data, prog[i].data, prog[i].len);
//				carmelo__cncs->machine[index[i]].live_data.prog_in_exe.len = prog[i].len;
//
//
//				carmelo__cncs->machine[index[i]].live_data.instant_power.len = sprintf(carmelo__cncs->machine[index[i]].live_data.instant_power.data,"%.2f KWatt",instant_power[i]);
//
//				carmelo__cncs->machine[index[i]].live_data.average_power.len = sprintf(carmelo__cncs->machine[index[i]].live_data.average_power.data,"%.2f Kwatt",average_power[i]);
//			
//				/*buffer_size = sizeof(carmelo__cncs->machine[index[i]].live_data.in_production.data);
//				rc[i] = util_ultoa (state_machine[i], carmelo__cncs->machine[index[i]].live_data.in_production.data, buffer_size, &carmelo__cncs->machine[index[i]].live_data.in_production.len);
//
//				buffer_size = sizeof(carmelo__cncs->machine[index[i]].live_data.in_alarm.data);
//				rc[i] = util_ultoa (alarm[i], carmelo__cncs->machine[index[i]].live_data.in_alarm.data, buffer_size, &carmelo__cncs->machine[index[i]].live_data.in_alarm.len);
//
//
//				fgg__util__copy_buffer (&carmelo__cncs->machine[index[i]].live_data.prog_in_exe, &prog[i]);*/
//
//				carmelo__cncs->machine[index[i]].shell.response[FGGR__CNCS__CMD__GET_MACHINE_DATA] = 0;
//				carmelo__cncs->machine[index[i]].shell.command_status[FGGR__CNCS__CMD__GET_MACHINE_DATA] = 3;
//				state[i] = CNC_1__READY__STATE;
//
//				break;
//
//			case CNC_1__PROGRAMS_NAME__STATE:
//
//				/*rc[i] = fgg__util__write_buffer (&carmelo__cncs->machine[index[i]].programs_name , (unsigned char *) "-", 1);
//
//				if (machine_is_connected == 0)
//				{
//					//macchina non connessa
//
//					state[i] = CNC_1__RECONNECT;
//				}
//				else
//				{
//
//					state[i] = CNC_1__READY__STATE;
//
//				}
//
//				carmelo__cncs->machine[index[i]].shell.response[FGGR__CNCS__CMD__GET_PROGRAMS_NAME] = 0;
//				carmelo__cncs->machine[index[i]].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAMS_NAME] = 3;*/
//
//
//
//				break;
//
//
//			default:
//
//				break;
//			}
//
//
//            if (carmelo__cncs->machine[index[i]].thread_status[0] == 2)
//			{
//				/*
//				* Exit request from external application
//				*/
//				carmelo__cncs->machine[index[i]].thread_status[0] = 3;
//			}
//
//		}
//
//	}
//	return 0;
//
//}
//








void fgg__machine_utimac_scy45ht__main_thread_2(void)
{
	static int state[UTIMAC_MAX];
	static double cycle_time[UTIMAC_MAX];
	static double instant_power[UTIMAC_MAX];
	static double average_power[UTIMAC_MAX];
	static unsigned long alarm[UTIMAC_MAX];
	static unsigned long state_machine[UTIMAC_MAX];
	static unsigned long avanzamento[UTIMAC_MAX];
	static fgg__buffer_t prog[UTIMAC_MAX];
	//static int index[UTIMAC_MAX] = {0, 4};
	static int index[UTIMAC_MAX] = { 0,1 };
	int rc[UTIMAC_MAX];


	static unsigned long machine_is_connected[UTIMAC_MAX];
	int i;
	static unsigned long pieces_machined[UTIMAC_MAX];
	static unsigned long state_em;
	//static timer_soft_ms_t timer_ms_for_read_file[UTIMAC_MAX];

	char ip[32];
	char port[32];
	char user[32];
	char pass[32];
	char contapezzi[64];
	static unsigned long pieces_machined_old[UTIMAC_MAX];

	strcpy(ip, "192.168.1.102");
	strcpy(port, "4840");
	strcpy(user, "OpcUaClient");
	strcpy(pass, "SUNRISE");
	strcpy(contapezzi, "/Nck/State/aDbd[236]");
	
	i = 0;
	state[i] = 0;

	while (1)
	{
		switch (state[i])
		{

		case 0:

			client3[i] = UA_Client_new();

			rc[i] = carmelo__cncs__open62541_connect(client3[i], ip, strlen(ip),
				port, 4,
				user, strlen(user),
				pass, strlen(pass));

			if (rc[i] == 0)
			{

				//timer_soft_ms_start(&timer_ms_for_read_file[i], 10000 * (i + 1));
				state[i] = CNC_1__READY__STATE;
				break;
			}
			carmelo__cncs__open62541_clear_client(client3[i]);


			break;

		case CNC_1__RECONNECT:
			//carmelo__cncs__open62541_clear_client  (client3[i]);


			state[i] = CNC_1__CONNECT;


			break;

		case CNC_1__READY__STATE:

			//if 0 temporaneo perche' in realta' funziona tutto al 22-02-2020
#if 0 

			if 0 temporaneo perche' in realta' funziona tutto al 22 - 02 - 2020
				if (timer_soft_ms_is_expired(&timer_ms_for_read_file[0]) == 0)
				{

					//leggo i file da scp
					fgg__cnc__enca_pscp_get_program_files(&carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_IP_2],
						&carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_USER_NAME_WINSCP],
						&carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_PASSWORD_WINSCP],
						&carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_PERCORSO_WRKS_DIR_SRC],
						&carmelo__cncs->machine[index[0]].parameter[CNC_PARAMETER_PERCORSO_WRKS_DIR_DST],
						1);

					timer_soft_ms_start(&timer_ms_for_read_file[0], 9900000 * (i + 1));
					timer_soft_ms_start(&timer_ms_for_read_file[1], 10000);
				}

			if (timer_soft_ms_is_expired(&timer_ms_for_read_file[1]) == 0)
			{
				timer_soft_ms_start(&timer_ms_for_read_file[1], 12000 * (i + 1));



				tmp_source_buff[0] = '\0';
				strcpy(tmp_source_buff, "manufact@192.168.1.52:/nckfs/_N_WKS_DIR");
				argv[0] = tmp_source_buff;
				argv[1] = "..\\22-02-2020";
				pippo(2, argv);

			}
#endif
			pieces_machined[i] = 0;
			cycle_time[i] = 0;
			state_machine[i] = 0;
			alarm[i] = 0;


			rc[i] = 0;
			rc[i] |= carmelo__cncs__open62541_get_machined_parts(client3[i], contapezzi, strlen(contapezzi), &pieces_machined[i]);

			if (pieces_machined_old[i] != pieces_machined[i])
			{
				printf("%d\r\n", pieces_machined[i]);
				pieces_machined_old[i] = pieces_machined[i];
			}

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



			break;


		}

	}

}