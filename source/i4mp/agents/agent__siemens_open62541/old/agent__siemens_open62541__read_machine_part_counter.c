#include "agent__siemens_open62541__private.h"


int agent__siemens_open62541__read_machine_part_counter (int md)
{
	//UA_Variant value;
	//UA_NodeId nodeId;
	//UA_StatusCode retval;	
	//char opc_node_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	//size_t opc_node_path_len;
	//int part_counter;
	//const char* fn;


	//fn = "agent__siemens_open62541__read_machine_part_counter()";


	//if (agent_so == NULL)
	//{
	//	return -100;
	//}

	//if (agent_so->started != 1)
	//{
	//	return -200;
	//}

	//if ((md < 0) || (md >= agent_so->number_of_machines))
	//{
	//	return -300;
	//}

	//agent_so->subagent.machine[md].part_counter_valid = 0;    //so->machine[md].part_counter_valid = 0;
	//

	////strcpy(path, so->machine[md].config.opc_part_counter_path);  /* strcpy(path, "/Nck/State/aDbd[236]"); */

	//strcpy(opc_node_path, "/Nck/State/aDbd[236]");
	//opc_node_path_len = strlen(opc_node_path);
	//opc_node_path[opc_node_path_len] = '\0';

	///*
	// * Variants can hold scalar values and arrays of any type
	// */
	//UA_Variant_init(&value);

	//nodeId = UA_NODEID_STRING(2, (char*)opc_node_path);
	//
	//retval = UA_Client_readValueAttribute(agent_so->machine[md].client, nodeId, &value);


	////if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32]))
	//if (!((retval == UA_STATUSCODE_GOOD) && (UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32]))))	
	//{
	//	UA_Variant_clear(&value);
	//	return -400;
	//}

	//part_counter = *((int*)value.config_2);


	//agent_so->subagent.machine[md].part_counter_native = part_counter;
	//
	//
	//sprintf(agent_so->subagent.machine[md].part_counter, "%d", agent_so->subagent.machine[md].part_counter_native);
	////*buffer_len = strlen(buffer);

	////so->machine[md].part_counter = part_counter;
	////sprintf(so->machine[md].part_counter_utf_8, "%zu", part_counter);
	////so->machine[md].part_counter_utf_8_len = strlen(so->machine[md].part_counter_utf_8);

	//agent_so->subagent.machine[md].part_counter_valid = 1;

	//UA_Variant_clear(&value);

	return 0;

}


//int agent__siemens_open62541__private__read_part_counter__real (int md)
//{
//
//	UA_Variant value2;
//	UA_NodeId nodeId2;
//	UA_StatusCode retval;
//	long config_2;
//	char path[1024];
//	size_t path_len;
//	size_t part_counter;
//	char* fn;
//
//
//	fn = "siemens_open62541__private__read_part_counter__real()";
//
//
//	//if ((md < 0) || (md >= so->number_of_machines))
//	//{
//	//	return -100;
//	//}
//
//	//
//	//so->machine[md].part_counter_valid = 0;
//
//	//strcpy(path, so->machine[md].config.opc_part_counter_path);  /* strcpy(path, "/Nck/State/aDbd[236]"); */
//	//path_len = strlen(path);
//	//path[path_len] = '\0';
//
//	///*
//	// * Variants can hold scalar values and arrays of any type
//	// */
//	//UA_Variant_init(&value2);
//
//	//nodeId2 = UA_NODEID_STRING(2, (char*)path);
//	//
//	//retval = UA_Client_readValueAttribute(so->machine[md].client, nodeId2, &value2);
//
//	//if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_INT32]))	
//	//{
//
//	//	data = *((long*)value2.data);
//
//	//	UA_Variant_clear(&value2);
//
//	//	if (data < 0)
//	//	{
//	//		return -200;
//	//	}
//
//	//	part_counter = (size_t) data;
//
//	//	so->machine[md].part_counter = part_counter;
//	//	sprintf(so->machine[md].part_counter_utf_8, "%zu", part_counter);
//	//	so->machine[md].part_counter_utf_8_len = strlen(so->machine[md].part_counter_utf_8);
//
//	//	so->machine[md].part_counter_valid = 1;
//
//	//	return 0;
//	//}
//
//	
//
//	return -300;
//
//}
