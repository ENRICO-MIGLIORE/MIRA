#include "fgg__fpw_ie.h"



void fgg__fpw_ie__set_run_level (unsigned long run_level)
{

	fgg__fpw_ie->task_1_run_level_request = 1;
	fgg__fpw_ie->task_2_run_level_request = 1;

	fgg__fpw_ie->task_1_run_level_requested = run_level;
	fgg__fpw_ie->task_2_run_level_requested = run_level;

}