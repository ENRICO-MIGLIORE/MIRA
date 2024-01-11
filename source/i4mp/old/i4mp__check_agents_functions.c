#include "mira__private.h"


int i4mp__check_agents_functions (i4mp__agent_functions_t* functions, size_t agents_max)
{

	size_t i;
	i4mp__agent_functions_t* af;

	if (agents_max == 0)
	{
		return -100;
	}

	if (functions == NULL)
	{
		return -200;
	}


	af = functions;

	for (i = 0; i < agents_max; i++)
	{
	
		if (af->init == NULL)
		{
			return -300;
		}

		if (af->config == NULL)
		{
			return -400;
		}

		if (af->start == NULL)
		{
			return -500;
		}

		if ((af->get_machine_count == NULL) || (af->get_machine_count_name == NULL))
		{
			return -600;
		}

		//if ((af->get_communications_enabled_machine_id == NULL) || (af->get_communications_enabled_machine_id_name == NULL))
		//{
		//	return -800;
		//}

		if ((af->get_machine_brand == NULL) || (af->get_machine_brand_name == NULL))
		{
			return -900;
		}

		if ((af->get_machine_model == NULL) || (af->get_machine_model_name == NULL))
		{
			return -1000;
		}

		if ((af->get_machine_sn == NULL) || (af->get_machine_sn_name == NULL))
		{
			return -1100;
		}

		if ((af->get_machine_facility == NULL) || (af->get_machine_facility_name == NULL))
		{
			return -1200;
		}

		if ((af->get_machine_name == NULL) || (af->get_machine_name_name == NULL))
		{
			return -1300;
		}

		if ((af->get_connection_status == NULL) || (af->get_connection_status_name == NULL))
		{
			return -1400;
		}

		if ((af->get_part_counter == NULL) || (af->get_part_counter_name == NULL))
		{
			return -1500;
		}

		if ((af->get_cycle_time == NULL) || (af->get_cycle_time_name == NULL))
		{
			return -1600;
		}


		af++;

	}

	return 0;

}


