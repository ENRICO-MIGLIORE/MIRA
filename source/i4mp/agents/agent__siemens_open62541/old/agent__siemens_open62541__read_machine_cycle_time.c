#include "agent__siemens_open62541__private.h"


int agent__siemens_open62541__read_machine_cycle_time (int md)
{
	//UA_Variant value;
	//UA_NodeId nodeId;
	//UA_StatusCode retval;
	//char opc_node_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	//size_t opc_node_path_len;
	//double cycle_time;
	//const char* fn;


	//fn = "agent__siemens_open62541__read_machine_cycle_time()";


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

	//agent_so->subagent.machine[md].cycle_time_valid = 0;


	////strcpy(path, so->machine[md].config.opc_cycle_time_path);  //strcpy(path, "/Channel/Parameter/rpa[u1,90]");

	//strcpy(opc_node_path, "/Channel/Parameter/rpa[u1,90]");
	//opc_node_path_len = strlen(opc_node_path);
	//opc_node_path[opc_node_path_len] = '\0';

	///*
	// * Variants can hold scalar values and arrays of any type
	// */
	//UA_Variant_init(&value);

	//nodeId = UA_NODEID_STRING(2, (char*)opc_node_path);

	//retval = UA_Client_readValueAttribute(agent_so->machine[md].client, nodeId, &value);


	//if (!((retval == UA_STATUSCODE_GOOD) && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE])))
	//{
	//	UA_Variant_clear(&value);
	//	return -400;
	//}

	//cycle_time = *(UA_Double*)value.config_2;
	//
	//agent_so->subagent.machine[md].cycle_time_native = cycle_time;
	//sprintf(agent_so->subagent.machine[md].cycle_time, "%.1f", agent_so->subagent.machine[md].cycle_time_native);
	//agent_so->subagent.machine[md].cycle_time_valid = 1;

	//UA_Variant_clear(&value);

	return 0;

}


//int agent__siemens_open62541__private__read_cycle_time__real (int md)
//{
//
//	//UA_Variant value2; /* Variants can hold scalar values and arrays of any type */
//	//UA_NodeId nodeId2;
//	//UA_StatusCode retval;
//	//char path[SIEMENS_OPEN62541__CONFIG__MAX_PATH_SIZE];
//	//size_t path_len;
//	//double cycle_time;
//	//size_t buffer_new_len;
//	//int rc;
//
//
//	//if ((md < 0) || (md >= so->number_of_machines))
//	//{
//	//	return -1000;
//	//}
//
//
//	//so->machine[md].cycle_time_valid = 0;
//
//
//	///*
//	// * strcpy(path, "/Channel/Parameter/rpa[u1,90]");
//	// */
//	//strcpy(path, so->machine[md].config.opc_cycle_time_path);
//	//path_len = strlen(path);
//
//
//	//UA_Variant_init(&value2);
//
//	//nodeId2 = UA_NODEID_STRING(2, path);
//
//	//retval = UA_Client_readValueAttribute(so->machine[md].client, nodeId2, &value2);
//
//	//if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_DOUBLE]))
//	//{
//
//	//	cycle_time = *(UA_Double*)value2.data;
//
//	//	so->machine[md].cycle_time = cycle_time;
//	//	sprintf(so->machine[md].cycle_time_utf_8, "%.1f", cycle_time);
//	//	so->machine[md].cycle_time_utf_8_len = strlen(so->machine[md].cycle_time_utf_8);
//
//	//	rc = utils__libc__trim_string(so->machine[md].cycle_time_utf_8, so->machine[md].cycle_time_utf_8_len, &buffer_new_len, '0');
//	//	if (rc != 0)
//	//	{
//	//		return -200;
//	//	}
//
//
//	//	if (buffer_new_len == 0)
//	//	{
//	//		return -300;
//	//	}
//
//	//	/*
//	//	 *   transform 10.0 to 10
//	//	 */
//	//	if (so->machine[md].cycle_time_utf_8[buffer_new_len - 1] == '.')
//	//	{
//	//		buffer_new_len--;
//	//	}
//
//	//	so->machine[md].cycle_time_utf_8[buffer_new_len] = '\0';
//
//	//	so->machine[md].cycle_time_utf_8_len = buffer_new_len;
//
//	//	so->machine[md].cycle_time_valid = 1;
//
//
//	//	UA_Variant_clear(&value2);   /* Clean up */
//
//	//	return 0;
//	//}
//	//
//
//	return -1000;
//
//}

