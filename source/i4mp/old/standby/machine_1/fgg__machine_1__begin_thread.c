#include <Windows.h>
#include <process.h>

#include "../../fgg.h"


#include "fgg__machine_1.h"


void fgg__machine_1__simulator_helper_init (void);


int fgg__machine__1__begin_thread (size_t index)
{
	static HANDLE h_thread[2];
	static unsigned int thread_id[2];

	if (index > 2)
	{
		return -10;
	}

	if (fgg.cncs->machine[0].configurated == 0)
	{
		return -11;
	}

	if (fgg.cncs->machine[0].thread_status[index] != 0)
	{
		return -12;
	}

	if (index == 0)
	{		
		h_thread[index] = (HANDLE) _beginthreadex (NULL, 0, &fgg__machine_1__main_thread, NULL, 0, &thread_id[0]);
	}
	else
	{
		fgg__machine_1__simulator_helper_init ();
		h_thread[index] = (HANDLE) _beginthreadex (NULL, 0, &fgg__machine_1__simulator_thread, NULL, 0, &thread_id[1]);
	}

	

	if (h_thread[index] == 0)
	{
		return -20;
	}

	fgg.cncs->machine[0].thread_status[index] = 1;

	return 0;
}
