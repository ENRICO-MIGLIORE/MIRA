#include "machine.h"


int subagent__read_part_counter__real (subagent__machine_t* machine, int md)
{

	//UA_Variant value2;
	//UA_NodeId nodeId2;
	//UA_StatusCode retval;
	//long data;
	//char path[1024];
	//size_t path_len;
	//size_t part_counter;


	//if ((md < 0) || (md >= so->machine_count))
	//{
	//	return -100;
	//}

	//
	//so->machine[md].part_counter_valid = 0;

	//strcpy(path, so->machine[md].config.opc_part_counter_path);  /* strcpy(path, "/Nck/State/aDbd[236]"); */
	//path_len = strlen(path);
	//path[path_len] = '\0';

	///*
	// * Variants can hold scalar values and arrays of any type
	// */
	//UA_Variant_init(&value2);

	//nodeId2 = UA_NODEID_STRING(2, (char*)path);
	//
	//retval = UA_Client_readValueAttribute(so->machine[md].client, nodeId2, &value2);

	//if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_INT32]))	
	//{

	//	data = *((long*)value2.data);

	//	UA_Variant_clear(&value2);

	//	if (data < 0)
	//	{
	//		return -200;
	//	}

	//	part_counter = (size_t) data;

	//	so->machine[md].part_counter = part_counter;
	//	sprintf(so->machine[md].part_counter_utf_8, "%zu", part_counter);
	//	so->machine[md].part_counter_utf_8_len = strlen(so->machine[md].part_counter_utf_8);

	//	so->machine[md].part_counter_valid = 1;

	//	return 0;
	//}

	

	return -300;

}
