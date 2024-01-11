#include "fanuc_focas__private.h"


int fanuc_focas__read_cycle_time__real (size_t machine_id)
{

	//UA_Variant value2; /* Variants can hold scalar values and arrays of any type */
	//UA_NodeId nodeId2;
	//UA_StatusCode retval;
	//size_t fd;
	//char path[FANUC_FOCAS__CONFIG__MAX_PATH_SIZE];
	//size_t path_len;
	//double cycle_time;
	//size_t buffer_new_len;
	//int rc;


	//rc = fanuc_focas__check_machine_id(machine_id);

	//if (rc != 0)
	//{
	//	return -100;
	//}


	//fd = machine_id - 1;

	//ff->machine[fd].cycle_time_valid = 0;



	//UA_Variant_init(&value2);


	///*
	// * strcpy(path, "/Channel/Parameter/rpa[u1,90]");
	// */
	//strcpy(path, ff->machine[fd].config.opc_cycle_time_path);
	//path_len = strlen(path);


	//nodeId2 = UA_NODEID_STRING(2, path);


	//retval = UA_Client_readValueAttribute(ff->machine[fd].client, nodeId2, &value2);

	//if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_DOUBLE]))
	//{

	//	cycle_time = *(UA_Double*)value2.data;

	//	ff->machine[fd].cycle_time = cycle_time;
	//	sprintf(ff->machine[fd].cycle_time_utf_8, "%f", cycle_time);
	//	ff->machine[fd].cycle_time_utf_8_len = strlen(ff->machine[fd].cycle_time_utf_8);

	//	rc = utils__libc__trim_string(ff->machine[fd].cycle_time_utf_8, ff->machine[fd].cycle_time_utf_8_len, &buffer_new_len, '0');
	//	if (rc != 0)
	//	{
	//		return -200;
	//	}
	//	ff->machine[fd].cycle_time_utf_8[buffer_new_len] = '\0';
	//	ff->machine[fd].cycle_time_valid = 1;

	//	UA_Variant_clear(&value2);   /* Clean up */

	//	return 0;
	//}

	return -1000;

}

