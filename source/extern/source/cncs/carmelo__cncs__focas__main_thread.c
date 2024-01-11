#include <carmelo__cncs__open62541.h>
#include <carmelo__cncs.h>
#include <Fwlib32.h>


/*
* CNC-1 = Settembre 2019 - Finotto
*/



#define CNC_2__INIT__STATE                         0
#define CNC_2__IS_IN_NETWORK__STATE                1
#define CNC_2__CONNECT                             2
#define CNC_2__READY__STATE                       10

#define CNC_2__MACHINE_DATA__STATE               110
#define CNC_2__PROGRAMS_NAME__STATE              111
#define CNC_2__PROGRAM_READ__STATE               112





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




#define FANUC_MAX     3



unsigned int __stdcall carmelo__cncs__focas__main_thread (void *arg)
{
	int i;
	static int state[FANUC_MAX];
	int rc[FANUC_MAX];
	unsigned long buffer_size;
	static unsigned long pieces_machined[FANUC_MAX];
	static long machine_is_connected[FANUC_MAX];
	unsigned long live_status[FANUC_MAX];
	unsigned long in_production[FANUC_MAX];
	unsigned long in_alarm[FANUC_MAX];
	fgg__buffer_t prog_in_execution[FANUC_MAX];
	fgg__buffer_t programs_name[FANUC_MAX];
	long program_to_read;

	//char buff_prog[1280000];
	//unsigned long  len_prog;


	static unsigned short fd[FANUC_MAX];

	state[0] = 0;
	state[1] = 0;

	//while (carmelo__cncs->machine[1].thread_status[0] == 0);


	while ((carmelo__cncs->machine[2].thread_status[0] == 1) || (carmelo__cncs->machine[2].thread_status[0] == 2))
	{

		for (i = 0; i < FANUC_MAX; i++)
		{
			switch (state[i])
			{

			case CNC_2__INIT__STATE:
				if (carmelo__cncs->machine[2+i].configurated != 0)
				{
					state[i] = CNC_2__IS_IN_NETWORK__STATE;
				}			
				break;

			case CNC_2__IS_IN_NETWORK__STATE:
				if (carmelo__cncs->machine[2+i].data.value[CNC_PARAMETER_MACCHINA_IN_RETE][0] != '0')
				{ 
					state[i] = CNC_2__CONNECT;
				}

				break;

			case CNC_2__CONNECT:

				machine_is_connected[i] = 0;
				/*TENTO LA CONNESSIONE */
				rc[i] = fgg__cnc__focas_connect (carmelo__cncs->machine[2+i].data.value[CNC_PARAMETER_IP_1], carmelo__cncs->machine[2+i].data.value_len[CNC_PARAMETER_IP_1], carmelo__cncs->machine[2+i].data.value[CNC_PARAMETER_PORTA_IP_1],carmelo__cncs->machine[2+i].data.value_len[CNC_PARAMETER_PORTA_IP_1], &fd[i]);
				if (rc[i] == 0)
				{
					/* CONNESSIONE RIUSCITA */
					machine_is_connected[i] = 1;
					state[i] = CNC_2__READY__STATE;
				}
				
				break;

			case CNC_2__READY__STATE:

				if (machine_is_connected[i] == 1)
				{
					rc[i] = fgg__cnc__focas_get_machined_parts (fd[i], &pieces_machined[i]);

					machine_is_connected[i] = fgg__cnc__focas_is_connected (fd[i]);

					rc[i] = fgg__cnc__focas_get_status (fd[i], &live_status[i]);

					in_production[i] = 0;
					if (live_status[i] == CNC__FOCAS__RUN__STATE)
					{
						in_production[i] = 1;
					}

					in_alarm[i] = 0;
					if ((live_status[i] & CNC__FOCAS__ALARM__STATE) == CNC__FOCAS__ALARM__STATE)
					{
						in_alarm[i] = 1;
					}

					rc[i] = fgg__cnc__focas_get_number_program_in_execution (fd[i], &prog_in_execution[i]);

					
				}
				else
				{
					//non e' connessa in rete in questo momento
					
					pieces_machined[i] = 0;
					machine_is_connected[i] = 0;
					in_production[i] = 0;
					in_alarm[i] = 0;
					//fgg__util__write_buffer (&prog_in_execution[i], (unsigned char *) "-", 1);
					prog_in_execution[i].data[0] = '-';
					prog_in_execution[i].len = 1;



				}

				

				if (carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_MACHINE_DATA] == 1)
				{
					carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_MACHINE_DATA] = 2;
					state[i] = CNC_2__MACHINE_DATA__STATE;
				}
				else if (carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAMS_NAME] == 1)
				{
					carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAMS_NAME] = 2;
					state[i] = CNC_2__PROGRAMS_NAME__STATE;
				}
				else if (carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAM] == 1)
				{
					carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAM] = 2;
					state[i] = CNC_2__PROGRAM_READ__STATE;

				}
				else if (machine_is_connected[i] == 0)
				{
					state[i] = CNC_2__CONNECT;
				}
				break;

			case CNC_2__MACHINE_DATA__STATE:

				//buffer_size = sizeof(carmelo__cncs->machine[2+i].live_data.connect.data);
				//rc[i] = util_ultoa (machine_is_connected[i], carmelo__cncs->machine[2+i].live_data.connect.data, buffer_size, &carmelo__cncs->machine[2+i].live_data.connect.len);
				
				if (machine_is_connected[i] == 1)
				{
					strcpy (carmelo__cncs->machine[2+i].live_data.connect.data,"online");
					carmelo__cncs->machine[2+i].live_data.connect.len = strlen("online");
				}
				else
				{
					strcpy (carmelo__cncs->machine[2+i].live_data.connect.data,"offline");
					carmelo__cncs->machine[2+i].live_data.connect.len = strlen("offline");
				}
			
				
				carmelo__cncs->machine[2+i].live_data.absolute_machine_part.len = sprintf (carmelo__cncs->machine[2+i].live_data.absolute_machine_part.data, "%d", pieces_machined[i]);

				if (in_production[i] == 1)
				{
					strcpy (carmelo__cncs->machine[2+i].live_data.in_production.data,"RUN");
					carmelo__cncs->machine[2+i].live_data.in_production.len = strlen("RUN");
				}
				else
				{
					strcpy (carmelo__cncs->machine[2+i].live_data.in_production.data,"STOP");
					carmelo__cncs->machine[2+i].live_data.in_production.len = strlen("STOP");
				}
			

				if (in_alarm[i] == 1)
				{
					strcpy (carmelo__cncs->machine[2+i].live_data.in_alarm.data,"SI");
					carmelo__cncs->machine[2+i].live_data.in_alarm.len = strlen("SI");
				}
				else
				{
					strcpy (carmelo__cncs->machine[2+i].live_data.in_alarm.data,"NO");
					carmelo__cncs->machine[2+i].live_data.in_alarm.len = strlen("NO");
				}


				memcpy (&carmelo__cncs->machine[2+i].live_data.prog_in_exe, &prog_in_execution[i], sizeof (fgg__buffer_t));


				carmelo__cncs->machine[2+i].live_data.cicle_time.data[0] = '-';
				carmelo__cncs->machine[2+i].live_data.cicle_time.len = 1;

				carmelo__cncs->machine[2+i].live_data.bar_feed.data[0] = '-';
				carmelo__cncs->machine[2+i].live_data.bar_feed.len = 1;

				carmelo__cncs->machine[2+i].live_data.instant_power.data[0] = '-';
				carmelo__cncs->machine[2+i].live_data.instant_power.len = 1;

				carmelo__cncs->machine[2+i].live_data.average_power.data[0] = '-';
				carmelo__cncs->machine[2+i].live_data.average_power.len = 1;
					

				carmelo__cncs->machine[2+i].shell.response[FGGR__CNCS__CMD__GET_MACHINE_DATA] = 0;
				carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_MACHINE_DATA] = 3;


				state[i] = CNC_2__READY__STATE;

				break;

			case CNC_2__PROGRAMS_NAME__STATE:

				carmelo__cncs->machine[2+i].programs_name.data[0] = '-';
				carmelo__cncs->machine[2+i].programs_name.len = 1;

				if (machine_is_connected[i] == 0)
				{
					//macchina non connessa
					
					state[i] = CNC_2__CONNECT;
				}
				else
				{
					rc[i] = fgg__cnc__focas_read_name_of_all_programs (fd[i], &programs_name[i]);
					if (rc[i] == 0)
					{
						memcpy (&carmelo__cncs->machine[2+i].programs_name, &programs_name[i], sizeof(fgg__buffer_t));
					}
                    state[i] = CNC_2__READY__STATE;
					
				}

				carmelo__cncs->machine[2+i].shell.response[FGGR__CNCS__CMD__GET_PROGRAMS_NAME] = 0;
				carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAMS_NAME] = 3;



				break;

		 case CNC_2__PROGRAM_READ__STATE:

			  
			   
			    //carmelo__cncs->machine[2+i].payload->len = 0;
				carmelo__cncs->machine[2+i].shell.response[FGGR__CNCS__CMD__GET_PROGRAM] = 0;
/*
				if (machine_is_connected[i] == 0)
				{
					//macchina non connessa
					
					state[i] = CNC_2__CONNECT;
				}
				else
				{
					util_atoul (&carmelo__cncs->machine[2+i].prog_numeber_to_read.data[1] , carmelo__cncs->machine[2+i].prog_numeber_to_read.len-1, (unsigned long *) &program_to_read);

					rc[i] = fgg__cnc__focas_get_program_code(fd[i], program_to_read, carmelo__cncs->machine[2+i].payload);
					carmelo__cncs->machine[2+i].shell.response[FGGR__CNCS__CMD__GET_PROGRAM] = -1;
					if (rc[i] == 0)
					{
						//util_memcpy_32 (carmelo__cncs->machine[2+i].buff_prog, buff_prog, len_prog);
						//carmelo__cncs->machine[2+i].len_prog = len_prog;
                        carmelo__cncs->machine[2+i].shell.response[FGGR__CNCS__CMD__GET_PROGRAM] = 0;
					}
                    state[i] = CNC_2__READY__STATE;
					
				}
				*/
				
				carmelo__cncs->machine[2+i].shell.command_status[FGGR__CNCS__CMD__GET_PROGRAM] = 3;
				state[i] = CNC_2__READY__STATE;


				break;


			default:

				break;
			}


			if (carmelo__cncs->machine[1].thread_status[0] == 2)
			{
				/*
				* Exit request from external application
				*/
				carmelo__cncs->machine[1].thread_status[0] = 3;
			}
		}

	}


	return 0;

}

