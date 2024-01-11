#include "agent__fanuc_focas__private.h"


//int agent__fanuc_focas__get_number_of_machines (int* number_of_machines)
//{
//	return 0;
//}



int agent__fanuc_focas__get_machine_id (int fd, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int rc;

	// Convert fd into 

	//rc = agency__private__get_machine_data(AGENCY__MACHINE_ID, md, buffer, buffer_size, buffer_len);

	// pthread_mutex_lock(&agency->agent[i].machine[j].thread_mutex);


	rc = sprintf(buffer, "%d", agent__fanuc_focas->machine[fd].config_2.id);

	if (rc < 0)
	{
		return -100;
	}

	return 0;


}