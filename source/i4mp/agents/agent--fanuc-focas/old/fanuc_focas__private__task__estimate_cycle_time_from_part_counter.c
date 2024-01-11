#include "fanuc_focas__private.h"


#define ECTFPC__INIT                                     0
#define ECTFPC__WAIT                                     1
#define ECTFPC__TAKE_A_SNAPSHOT_OF_PART_COUNTER          2
#define ECTFPC__WAIT_FOR_PART_COUNTER_TO_CHANGE_1        3
#define ECTFPC__WAIT_FOR_PART_COUNTER_TO_CHANGE_2        4
#define ECTFPC__ERROR                                  900


static char* fn = "fanuc_focas__private__task__estimate_cycle_time_from_part_counter()";


void fanuc_focas__private__task__estimate_cycle_time_from_part_counter (void)
{

	int i;
	int j;
	int rc;
	int flag;
	size_t cycle_time_milliseconds;
	size_t ticks_start;
	size_t diff;
	

	for (i = 0; i < ff->machine_count; i++)
	{ 

		switch (ff->machine[i].cycle_time_fpc.task_state)
		{

		case ECTFPC__INIT:
			if ((ff->machine[i].config.simulated == 0) && (ff->machine[i].config.cycle_time_fpc.do_estimation == 1))
			{				
				
				ticks_start = ff->thread_ticks_milliseconds;

				if (ff->machine[i].cycle_time_fpc.first_time == 0)
				{
					ff->machine[i].cycle_time_fpc.first_time = 1;
					ff->machine[i].cycle_time_fpc.ticks_stop = ticks_start + (ff->machine[i].config.cycle_time_fpc.time_to_first_estimation_seconds * 1000);
				}
				else
				{
					ff->machine[i].cycle_time_fpc.ticks_stop = ticks_start + (ff->machine[i].config.cycle_time_fpc.time_interval_for_estimations_seconds * 1000);
				}
									
				ff->machine[i].cycle_time_fpc.task_state = ECTFPC__WAIT;
			}
			break;

		case ECTFPC__WAIT:
			if (ff->thread_ticks_milliseconds > ff->machine[i].cycle_time_fpc.ticks_stop)
			{
				if (ff->machine[i].config.cycle_time_fpc.enable_printf == 1)
				{
					utils__printf__info(&ff->pf, fn, 0, "machine %d - cycle time estimation started - step 1 of 3", i);
				}
				ff->machine[i].cycle_time_fpc.task_state = ECTFPC__TAKE_A_SNAPSHOT_OF_PART_COUNTER;
			}
			break;

		case ECTFPC__TAKE_A_SNAPSHOT_OF_PART_COUNTER:
			if (ff->machine[i].part_counter_valid == 0)
			{
				ff->machine[i].cycle_time_fpc.task_state = ECTFPC__ERROR;
				break;
			}

			/* 
			 * take a snapshot of the part counter
			 */
			strcpy(ff->machine[i].cycle_time_fpc.part_counter, ff->machine[i].part_counter_utf_8);
			ff->machine[i].cycle_time_fpc.task_state = ECTFPC__WAIT_FOR_PART_COUNTER_TO_CHANGE_1;
			break;

		case ECTFPC__WAIT_FOR_PART_COUNTER_TO_CHANGE_1:
			if (ff->machine[i].part_counter_valid == 0)
			{
				ff->machine[i].cycle_time_fpc.task_state = ECTFPC__ERROR;
				break;
			}
			
			rc = memcmp(ff->machine[i].cycle_time_fpc.part_counter, ff->machine[i].part_counter_utf_8, ff->machine[i].part_counter_utf_8_len);
			if (rc != 0)
			{

				strcpy(ff->machine[i].cycle_time_fpc.part_counter, ff->machine[i].part_counter_utf_8);

				ff->machine[i].cycle_time_fpc.ticks = ff->thread_ticks_milliseconds;
				ff->machine[i].cycle_time_fpc.ticks_timeout = ff->thread_ticks_milliseconds;


				ff->machine[i].cycle_time_fpc.in_progress = 1;

				if (ff->machine[i].config.cycle_time_fpc.enable_printf == 1)
				{
					utils__printf__info(&ff->pf, fn, 0, "machine %d - cycle time estimation in progress - step 2 of 3", i);
				}

				ff->machine[i].cycle_time_fpc.task_state = ECTFPC__WAIT_FOR_PART_COUNTER_TO_CHANGE_2;


			}
			
			break;

		case ECTFPC__WAIT_FOR_PART_COUNTER_TO_CHANGE_2:
			if (ff->machine[i].part_counter_valid == 0)
			{
				ff->machine[i].cycle_time_fpc.task_state = ECTFPC__ERROR;
				break;
			}
			
			rc = memcmp(ff->machine[i].cycle_time_fpc.part_counter, ff->machine[i].part_counter_utf_8, ff->machine[i].part_counter_utf_8_len);
			if (rc != 0)
			{
				if (ff->thread_ticks_milliseconds < ff->machine[i].cycle_time_fpc.ticks)
				{
					ff->machine[i].cycle_time_fpc.task_state = ECTFPC__ERROR;
					break;
				}							

				/*
				 * cycle time
				 */				
				cycle_time_milliseconds = ff->thread_ticks_milliseconds - ff->machine[i].cycle_time_fpc.ticks;

				if (cycle_time_milliseconds > (ff->machine[i].config.cycle_time_fpc.minium_acceptable_cycle_time_seconds * 1000))
				{
					ff->machine[i].cycle_time_fpc.cycle_time = (double)(cycle_time_milliseconds / 1000.0);
					ff->machine[i].cycle_time_fpc.valid = 1;

					if (ff->machine[i].config.cycle_time_fpc.enable_printf == 1)
					{
						utils__printf__info(&ff->pf, fn, 0, "machine %d - cycle time estimation ended - step 3 of 3", i);
						utils__printf__info(&ff->pf, fn, 0, "machine %d cycle time %f seconds", i, ff->machine[i].cycle_time_fpc.cycle_time);
					}

				}
				else
				{
					utils__printf__warning(&ff->pf, fn, 0, "machine %d cycle time estimation %f is smaller than configured %zu", i, (double)(cycle_time_milliseconds / 1000.0), ff->machine[i].config.cycle_time_fpc.minium_acceptable_cycle_time_seconds);
				}
																		
				ff->machine[i].cycle_time_fpc.in_progress = 0;
				ff->machine[i].cycle_time_fpc.task_state = ECTFPC__INIT;
			}
			
			break;

		case ECTFPC__ERROR:
			utils__printf__error(&ff->pf, fn, 0, "machine %d state machine went to ECTFPC__ERROR state", i);
			ff->machine[i].cycle_time_fpc.valid = 0;
			ff->machine[i].cycle_time_fpc.in_progress = 0;
			ff->machine[i].cycle_time_fpc.task_state = ECTFPC__INIT;
			break;

		default:
			utils__printf__error(&ff->pf, fn, 0, "machine %d state machine went to default state", i);
			ff->machine[i].cycle_time_fpc.valid = 0;
			ff->machine[i].cycle_time_fpc.in_progress = 0;			
			ff->machine[i].cycle_time_fpc.task_state = ECTFPC__INIT;
			break;
		}

		if (ff->machine[i].cycle_time_fpc.in_progress == 1)
		{
		
			if (ff->thread_ticks_milliseconds > ff->machine[i].cycle_time_fpc.ticks_timeout)
			{

				diff = ff->thread_ticks_milliseconds > ff->machine[i].cycle_time_fpc.ticks_timeout;

				if (diff > (ff->machine[i].config.cycle_time_fpc.timeout_seconds * 1000))
				{
					/*
					 * timeout
					 */
					utils__printf__error(&ff->pf, fn, 0, "machine %d timeout when estimating cycle time from part counter", i);

					ff->machine[i].cycle_time_fpc.task_state = ECTFPC__ERROR;
				}
			}
		}
	}



	/*
	 * when all machines quit estimating the cycle time, the thread can return to its normal sleep time
	 */
	flag = 0;
	for (j = 0; j < ff->machine_count; j++)
	{
		if (ff->machine[j].cycle_time_fpc.in_progress == 1)
		{
			flag = 1;
		}
	}

	if (flag == 1)
	{		                                     
		ff->thread_sleep_time_milliseconds = 1000;                                          /* set thread's sleep time to 1 second */
	}
	else
	{
		ff->thread_sleep_time_milliseconds = ff->config.thread_sleep_time_seconds * 1000;   /* restore thread's sleep time */
	}

}