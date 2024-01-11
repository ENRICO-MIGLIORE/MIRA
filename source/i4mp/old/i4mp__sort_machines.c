#include <siemens_open62541.h>
#include <fanuc_focas.h>

#include "mira__private.h"


int i4mp__sort_machines (void)
{
	size_t i;
	size_t swap_id;
	size_t swap_group;
	char* swap_agent_name;
	int swap_occurred;
	size_t tmp_1;
	size_t tmp_2;
	
	/*
	 * Simple ordering algorithm. Order by the following decimal number:  (id * 10) + group
	 * 
	 *  id     group              (id * 10) + group
	 *  -------------------------------------------------
	 *  3      2                  3 * 10  +  2  =  32
	 *  2      1                  2 * 10  +  1  =  21
	 *  1      2                  1 * 10  +  2  =  12
	 *  2      2                  2 * 10  +  2  =  22
	 *  1      1                  1 * 10  +  1  =  11
	 *  3      1                  3 * 10  +  1  =  31
	 *  4      1                  4 * 10  +  1  =  41
	 *  
	 */
	do
	{
		swap_occurred = 0;

		for (i = 0; i < i4mp->machine_count - 1; i++)
		{
			//tmp_1 = (i4mp->machine[i].id * 10) + i4mp->machine[i].agent_fd;
			//tmp_2 = (i4mp->machine[i + 1].id * 10) + i4mp->machine[i + 1].agent_fd;

			//if (tmp_2 < tmp_1)
			//{
			//	swap_id = i4mp->machine[i].id;
			//	i4mp->machine[i].id = i4mp->machine[i + 1].id;
			//	i4mp->machine[i + 1].id = swap_id;

			//	swap_group = i4mp->machine[i].agent_fd;
			//	i4mp->machine[i].agent_fd = i4mp->machine[i + 1].agent_fd;
			//	i4mp->machine[i + 1].agent_fd = swap_group;

			//	swap_agent_name = (char *) i4mp->machine[i].agent_name;
			//	i4mp->machine[i].agent_name = i4mp->machine[i + 1].agent_name;
			//	i4mp->machine[i + 1].agent_name = swap_agent_name;

				swap_occurred = 1;
			//}
		}
	}
	while (swap_occurred == 1);



	return 0;

}
