#include "agency_private.h"
 

int agency__get_machine_part_program_name (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int rc;

	rc = agency__private__get_machine_data(AGENCY__MACHINE_PART_PROGRAM_NAME, md, buffer, buffer_size, buffer_len);


	//pthread_mutex_lock(&agency->agent[i].machine[j].thread_mutex);

	return rc;


}
