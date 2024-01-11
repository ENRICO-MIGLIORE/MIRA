#include "../fgg.h"


#define CNC_1__INIT__STATE                        0
#define CNC_1__READY__STATE                       10

#define CNC_1__MACHINE_DATA__STATE               110
#define CNC_1__MACHINE_DATA_2__STATE             111




#define UTIMAC_MAX    2
static int state_helper[UTIMAC_MAX];
static char *name_program[UTIMAC_MAX];

void fgg__machine_1__simulator_helper_init (void)
{
	size_t i;

	for (i = 0; i < UTIMAC_MAX; i++)
	{

		state_helper[i] = 0;
	}

	name_program[0] = "E00129";
	name_program[1] = "E00129_BARENO_WPD_OK";
	
}


#define CYCLE_TIME 2  

void fgg__machine_1__simulator_helper_task (size_t index,unsigned long *pieces_machined, double *cycle_time, unsigned long *alarm, fgg__buffer_t *prog, unsigned long *state_machine, unsigned long *avanzamento, unsigned long *state_em)
{
	
	static timer_soft_sec_t timer[UTIMAC_MAX];
	static size_t tmp_alarm[UTIMAC_MAX];
	static size_t tmp_emergency[UTIMAC_MAX];
	int rc;

	


	switch (state_helper[index])
	{

	case 0:
		

		strcpy((char *)prog->data,  name_program[index]);

		prog->len = strlen ((char *)name_program[index]);
		*avanzamento = 0;
		//timer_soft_ms_start (&timer[index], 6000);
		timer_soft_sec_start (&timer[index], 6);
		state_helper[index] = 1;
		*pieces_machined = 6;
		*alarm = 0;
		break;

	case 1:

		//rc = timer_soft_ms_is_expired(&timer[index]);
		rc = timer_soft_sec_is_expired(&timer[index]);
		if (rc == 0)
		{	
			*avanzamento = 1;
			//timer_soft_ms_start (&timer[index], CYCLE_TIME);
			timer_soft_sec_start (&timer[index], CYCLE_TIME);
			*cycle_time = CYCLE_TIME;
			state_helper[index] = 2;
		}

		break;

	case 2:
		//rc = timer_soft_ms_is_expired(&timer[index]);
		rc = timer_soft_sec_is_expired(&timer[index]);
		if (rc == 0)
		{	
			*pieces_machined = *pieces_machined + 1;
			if (*pieces_machined > 0xFFFFFFFE)
			{
				*pieces_machined = 1000;
			}

			tmp_alarm[index]++;
			if (tmp_alarm[index] >= 10)
			{
				tmp_alarm[index] = 0;
				if (*alarm == 0)
				{
					*alarm = 1;
				}
				else
				{
					*alarm = 0;
				}

			}

			tmp_emergency[index]++;
			if (tmp_emergency[index] >= 10)
			{
				tmp_emergency[index] = 0;
				if (*state_em == 0)
				{
					*state_em = 1;
				}
				else
				{
					*state_em = 0;
				}

			}
		

			//timer_soft_ms_start (&timer[index], CYCLE_TIME);
			timer_soft_sec_start (&timer[index], CYCLE_TIME);
			state_helper[index] = 1;
		}
		break;



	default:
		state_helper[index] = 0;
		break;

	}

}




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




unsigned int __stdcall fgg__machine_1__simulator_thread (void *arg)
{
	static int state[UTIMAC_MAX];
	static double cycle_time[UTIMAC_MAX];
	unsigned long alarm[UTIMAC_MAX];
	unsigned long state_machine[UTIMAC_MAX];
	unsigned long avanzamento[UTIMAC_MAX];
	fgg__buffer_t prog[UTIMAC_MAX];
	static int index[UTIMAC_MAX] = {0, 4};
	int rc[UTIMAC_MAX];
	static unsigned long machine_is_connected[UTIMAC_MAX];
	int i;
	size_t buffer_size;
	static unsigned long pieces_machined[UTIMAC_MAX];
	unsigned long state_em[UTIMAC_MAX];
	static timer_soft_sec_t timer_ms_for_read_file[UTIMAC_MAX];


	
	while (fgg.cncs->machine[0].thread_status[1] == 0);


	while ((fgg.cncs->machine[0].thread_status[1] == 1) || (fgg.cncs->machine[0].thread_status[1] == 2))
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
					state[i] = CNC_1__CONNECT;
				}			
				break;

			case CNC_1__CONNECT:
				rc[i] = 0;

				if (rc[i] == 0)
				{

					//timer_soft_ms_start(&timer_ms_for_read_file[i], 10000 * (i + 1));
					timer_soft_sec_start(&timer_ms_for_read_file[i], 10 * (i + 1));
					state[i] = CNC_1__READY__STATE;
				}

				break;

			case CNC_1__RECONNECT:


				state[i] = CNC_1__CONNECT;


				break;	

			case CNC_1__READY__STATE:

				//if (timer_soft_ms_is_expired (&timer_ms_for_read_file[0]) == 0)
				if (timer_soft_sec_is_expired (&timer_ms_for_read_file[0]) == 0)
				{ 
					//leggo i file da scp

					&fgg.cncs->machine[index[0]].parameter[CNC_PARAMETER_PERCORSO_WRKS_DIR_DST];


					rc[i] = 0;
					fgg__machine_1__simulator_helper_task (i, &pieces_machined[i], &cycle_time[i], &alarm[i], &prog[i], 
						                                 &state_machine[i], &avanzamento[i], &state_em[i]);
				
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
				rc[i] = util__ultoa (machine_is_connected[i], fgg.cncs->machine[index[i]].live_data.connect.data, buffer_size, &fgg.cncs->machine[index[i]].live_data.connect.len);

				buffer_size = sizeof(fgg.cncs->machine[index[i]].live_data.absolute_machine_part.data);
				rc[i] = util__ultoa (pieces_machined[i], fgg.cncs->machine[index[i]].live_data.absolute_machine_part.data, buffer_size, &fgg.cncs->machine[index[i]].live_data.absolute_machine_part.len);

				buffer_size = sizeof(fgg.cncs->machine[index[i]].live_data.in_production.data);
				rc[i] = util__ultoa (state_machine[i], fgg.cncs->machine[index[i]].live_data.in_production.data, buffer_size, &fgg.cncs->machine[index[i]].live_data.in_production.len);

				buffer_size = sizeof(fgg.cncs->machine[index[i]].live_data.in_alarm.data);
				rc[i] = util__ultoa (alarm[i], fgg.cncs->machine[index[i]].live_data.in_alarm.data, buffer_size, &fgg.cncs->machine[index[i]].live_data.in_alarm.len);


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


				if (fgg.cncs->machine[index[i]].thread_status[1] == 2)
				{
					/*
					* Exit request from external application
					*/
					fgg.cncs->machine[index[i]].thread_status[1] = 3;
				}

			}

		}
		
	}

	return 0;
}



