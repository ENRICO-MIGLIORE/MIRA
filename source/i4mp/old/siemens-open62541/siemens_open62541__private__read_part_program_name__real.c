#include "siemens_open62541__private.h"


int siemens_open62541__private__read_part_program_name__real (int md)
{

	//UA_Variant value2; /* Variants can hold scalar values and arrays of any type */
	//UA_NodeId nodeId2;
	//UA_StatusCode retval;
	//char path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
	//size_t path_len;
	//int rc;


	if ((md < 0) || (md >= so->machine_count))
	{
		return -1000;
	}

	so->machine[md].part_program_name_valid = 0;


	return 0;



	//UA_Variant_init(&value2);


	///*
	// * strcpy(path, "/Channel/Parameter/rpa[u1,90]");
	// */
	//strcpy(path, so->machine[md].config.opc_cycle_time_path);
	//path_len = strlen(path);


	//nodeId2 = UA_NODEID_STRING(2, path);

	//retval = UA_Client_readValueAttribute(so->machine[md].client, nodeId2, &value2);

	//if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_DOUBLE]))
	//{

	//	cycle_time = *(UA_Double*)value2.data;

	//	so->machine[md].cycle_time = cycle_time;
	//	sprintf(so->machine[md].cycle_time_utf_8, "%f", cycle_time);
	//	so->machine[md].cycle_time_utf_8_len = strlen(so->machine[md].cycle_time_utf_8);

	//	rc = utils__libc__trim_string(so->machine[md].cycle_time_utf_8, so->machine[md].cycle_time_utf_8_len, &buffer_new_len, '0');
	//	if (rc != 0)
	//	{
	//		return -200;
	//	}
	//	so->machine[md].cycle_time_utf_8[buffer_new_len] = '\0';
	//	so->machine[md].cycle_time_valid = 1;

	//	UA_Variant_clear(&value2);   /* Clean up */

	//	return 0;
	//}


	//

	//return -1000;

}

