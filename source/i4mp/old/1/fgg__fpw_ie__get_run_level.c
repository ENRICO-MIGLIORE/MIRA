#include "fgg__fpw_ie.h"


unsigned long fgg__fpw_ie__get_run_level (void)
{
	//if ((fgg__fpw_ie->task_1_run_level == fgg__fpw_ie->task_1_run_level_requested) && (fgg__fpw_ie->task_2_run_level == fgg__fpw_ie->task_2_run_level_requested))
	//{
	//	fgg__fpw_ie->module_run_level = fgg__fpw_ie->task_1_run_level_requested;
	//}

	if (fgg__fpw_ie->task_2_run_level == fgg__fpw_ie->task_2_run_level_requested)
	{
		fgg__fpw_ie->module_run_level = fgg__fpw_ie->task_1_run_level_requested;
	}

	return fgg__fpw_ie->module_run_level;
}

