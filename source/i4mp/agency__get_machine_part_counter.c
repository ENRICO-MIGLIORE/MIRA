#include "agency_private.h"
 

int agency__get_machine_part_counter (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	int rc;

	rc = agency__private__get_machine_data(AGENCY__MACHINE_PART_COUNTER, md, buffer, buffer_size, buffer_len);

	return rc;


}
