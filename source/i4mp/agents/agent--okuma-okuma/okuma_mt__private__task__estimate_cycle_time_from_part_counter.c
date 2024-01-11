#include "okuma_mt__private.h"


#define INIT                                     0
#define WAIT                                     1
#define TAKE_A_SNAPSHOT_OF_PART_COUNTER          2
#define WAIT_FOR_PART_COUNTER_TO_CHANGE_1        3
#define WAIT_FOR_PART_COUNTER_TO_CHANGE_2        4
#define PART_COUNTER_INVALID                   800
#define ERROR                                  900


static char* fn = "okuma_mt__private__task__estimate_cycle_time_from_part_counter()";


void okuma_mt__private__task__estimate_cycle_time_from_part_counter (void)
{

	int i; 
	int j;
	int rc;
	size_t cycle_time_milliseconds;
	size_t diff;
	

	for (i = 0; i < om->machine_count; i++)
	{ 

		switch (om->machine[i].cycle_time_fpc.task_state)
		{

		case INIT:
			if ((om->machine[i].config.simulated == 0) && (om->machine[i].config.cycle_time_fpc.do_estimation == 1))
			{				
				
				om->machine[i].cycle_time_fpc.ticks_start = om->thread_2_ticks_milliseconds;

				if (om->machine[i].cycle_time_fpc.first_time == 0)
				{
					om->machine[i].cycle_time_fpc.first_time = 1;
					om->machine[i].cycle_time_fpc.ticks_stop = om->machine[i].cycle_time_fpc.ticks_start + (om->machine[i].config.cycle_time_fpc.time_to_first_estimation_seconds * 1000);
				}
				else
				{
					om->machine[i].cycle_time_fpc.ticks_stop = om->machine[i].cycle_time_fpc.ticks_start + (om->machine[i].config.cycle_time_fpc.time_interval_for_estimations_seconds * 1000);
				}
									
				om->machine[i].cycle_time_fpc.task_state = WAIT;
			}
			break;

		case WAIT:
			if (om->thread_2_ticks_milliseconds > om->machine[i].cycle_time_fpc.ticks_stop)
			{
				if (om->machine[i].config.cycle_time_fpc.enable_printf == 1)
				{
					utils__printf__info(&om->pf, fn, 0, "machine id %d - cycle time estimation started - step 1 of 3", om->machine[i].config.id);
				}
				om->machine[i].cycle_time_fpc.in_progress = 1;
				om->machine[i].cycle_time_fpc.task_state = TAKE_A_SNAPSHOT_OF_PART_COUNTER;
			}
			break;

		case TAKE_A_SNAPSHOT_OF_PART_COUNTER:
			if (om->machine[i].part_counter_valid == 0)
			{
				if (om->machine[i].config.cycle_time_fpc.enable_printf == 1)
				{
					utils__printf__info(&om->pf, fn, 0, "machine id %d - from TAKE_A_SNAPSHOT_OF_PART_COUNTER to PART_COUNTER_INVALID", om->machine[i].config.id);
				}
				om->machine[i].cycle_time_fpc.task_state = PART_COUNTER_INVALID;
				break;
			}

			/* 
			 * take a snapshot of the part counter
			 */
			strcpy(om->machine[i].cycle_time_fpc.part_counter, om->machine[i].part_counter_utf_8);
			om->machine[i].cycle_time_fpc.task_state = WAIT_FOR_PART_COUNTER_TO_CHANGE_1;
			break;

		case WAIT_FOR_PART_COUNTER_TO_CHANGE_1:
			if (om->machine[i].part_counter_valid == 0)
			{
				if (om->machine[i].config.cycle_time_fpc.enable_printf == 1)
				{
					utils__printf__info(&om->pf, fn, 0, "machine id %d - from WAIT_FOR_PART_COUNTER_TO_CHANGE_1 to PART_COUNTER_INVALID", om->machine[i].config.id);
				}
				om->machine[i].cycle_time_fpc.task_state = PART_COUNTER_INVALID;
				break;
			}
			
			rc = memcmp(om->machine[i].cycle_time_fpc.part_counter, om->machine[i].part_counter_utf_8, om->machine[i].part_counter_utf_8_len);
			if (rc != 0)
			{

				strcpy(om->machine[i].cycle_time_fpc.part_counter, om->machine[i].part_counter_utf_8);

				om->machine[i].cycle_time_fpc.ticks = om->thread_2_ticks_milliseconds;
				om->machine[i].cycle_time_fpc.ticks_timeout = om->thread_2_ticks_milliseconds;
				

				if (om->machine[i].config.cycle_time_fpc.enable_printf == 1)
				{
					utils__printf__info(&om->pf, fn, 0, "machine id %d - cycle time estimation in progress - step 2 of 3", om->machine[i].config.id);
				}

				om->machine[i].cycle_time_fpc.task_state = WAIT_FOR_PART_COUNTER_TO_CHANGE_2;
			}
			
			break;

		case WAIT_FOR_PART_COUNTER_TO_CHANGE_2:
			if (om->machine[i].part_counter_valid == 0)
			{
				if (om->machine[i].config.cycle_time_fpc.enable_printf == 1)
				{
					utils__printf__info(&om->pf, fn, 0, "machine id %d - from WAIT_FOR_PART_COUNTER_TO_CHANGE_1 to PART_COUNTER_INVALID", om->machine[i].config.id);
				}
				om->machine[i].cycle_time_fpc.task_state = PART_COUNTER_INVALID;
				break;
			}
			
			rc = memcmp(om->machine[i].cycle_time_fpc.part_counter, om->machine[i].part_counter_utf_8, om->machine[i].part_counter_utf_8_len);
			if (rc != 0)
			{
				if (om->thread_2_ticks_milliseconds < om->machine[i].cycle_time_fpc.ticks)
				{
					utils__printf__error(&om->pf, fn, -100, "machine id %d - thread_2_ticks_milliseconds %zu < cycle_time_fpc.ticks %zu", om->machine[i].config.id, om->thread_2_ticks_milliseconds, om->machine[i].cycle_time_fpc.ticks);
					om->machine[i].cycle_time_fpc.task_state = ERROR;
					break;
				}							

				/*
				 * cycle time
				 */				
				cycle_time_milliseconds = om->thread_2_ticks_milliseconds - om->machine[i].cycle_time_fpc.ticks;

				if (cycle_time_milliseconds > (om->machine[i].config.cycle_time_fpc.minium_acceptable_cycle_time_seconds * 1000))
				{
					om->machine[i].cycle_time_fpc.cycle_time = (double)(cycle_time_milliseconds / 1000.0);
					om->machine[i].cycle_time_fpc.valid = 1;

					if (om->machine[i].config.cycle_time_fpc.enable_printf == 1)
					{
						utils__printf__info(&om->pf, fn, 0, "machine id %d - cycle time estimation ended - step 3 of 3", om->machine[i].config.id);
						utils__printf__info(&om->pf, fn, 0, "machine id %d - cycle time %f seconds", om->machine[i].config.id, om->machine[i].cycle_time_fpc.cycle_time);
					}
				}
				else
				{
					if (om->machine[i].config.cycle_time_fpc.enable_printf == 1)
					{					
					    utils__printf__warning(&om->pf, fn, 0, "machine id %d - cycle time estimation %f is smaller than configured %zu", om->machine[i].config.id, (double)(cycle_time_milliseconds / 1000.0), om->machine[i].config.cycle_time_fpc.minium_acceptable_cycle_time_seconds);
					}

					om->machine[i].cycle_time_fpc.valid = 0;
				}
																		
				om->machine[i].cycle_time_fpc.in_progress = 0;
				om->machine[i].cycle_time_fpc.task_state = INIT;
			}
			
			break;


		case PART_COUNTER_INVALID:		
			om->machine[i].cycle_time_fpc.valid = 0;
			om->machine[i].cycle_time_fpc.in_progress = 0;
			om->machine[i].cycle_time_fpc.task_state = INIT;
			break;

		case ERROR:
			utils__printf__error(&om->pf, fn, -200, "machine id %d - state machine went to ERROR - go to INIT", om->machine[i].config.id);
			om->machine[i].cycle_time_fpc.valid = 0;
			om->machine[i].cycle_time_fpc.in_progress = 0;
			om->machine[i].cycle_time_fpc.task_state = INIT;
			break;

		default:
			utils__printf__error(&om->pf, fn, -300, "machine id %d - state machine went to default: - go to INIT", om->machine[i].config.id);
			om->machine[i].cycle_time_fpc.valid = 0;
			om->machine[i].cycle_time_fpc.in_progress = 0;			
			om->machine[i].cycle_time_fpc.task_state = INIT;
			break;
		}

		if ((om->machine[i].cycle_time_fpc.in_progress == 1) && (om->thread_2_ticks_milliseconds > om->machine[i].cycle_time_fpc.ticks_start))
		{
		
			diff = om->thread_2_ticks_milliseconds - om->machine[i].cycle_time_fpc.ticks_start;

			if (diff > (om->machine[i].config.cycle_time_fpc.timeout_seconds * 1000))
			{
				/*
				 * timeout
				 */
				utils__printf__error(&om->pf, fn, -400, "machine id %d - timeout when estimating cycle time", om->machine[i].config.id);

				om->machine[i].cycle_time_fpc.task_state = ERROR;
			}
		}
	}



	/*
	 * when all machines quit estimating the cycle time, the thread can return to its normal sleep time
	 */
	om->cycle_time_estimation_from_part_counter_in_progress = 0;
	for (j = 0; j < om->machine_count; j++)
	{
		if (om->machine[j].cycle_time_fpc.in_progress == 1)
		{
			om->cycle_time_estimation_from_part_counter_in_progress = 1;
		}
	}

	//if (flag == 1)
	//{		                                     
	//	om->thread_2_sleep_time_milliseconds = 1000;                                          /* set thread's sleep time to 1 second */
	//}
	//else
	//{
	//	om->thread_2_sleep_time_milliseconds = om->config.thread_sleep_time_seconds * 1000;   /* restore thread's sleep time */
	//}

}