#include <open62541.h>

#include <agency_private.h>


int agent__siemens_open62541__platform__private__read_machine_part_counter (void* arg)
{
	
	UA_Variant value;
	UA_NodeId node_id;
	UA_StatusCode retval;	
	UA_Client* client;
	char opc_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t opc_node_path_len;
	const char* fn;
	machine_t* machine;


	fn = "agent__siemens_open62541__read_machine_part_counter()";


	if (arg == NULL)
	{
		return -100;
	}

	machine = (machine_t*)arg;
	if (machine->ext_void_pointer_valid == 0)
	{
		return -200;
	}

	client = (UA_Client*)machine->ext_void_pointer;
	if (client == NULL)
	{
		return -300;
	}


	machine->part_counter_valid = 0;    //agent_so->subagent.machine[md].part_counter_valid = 0;    //so->machine[md].part_counter_valid = 0;

	
	strcpy(opc_node_path, machine->config_2.opc_ua_server_part_counter_node_path);  /* strcpy(path, "/Nck/State/aDbd[236]"); */
	opc_node_path_len = strlen(opc_node_path);
	//opc_node_path[opc_node_path_len] = '\0';

	/*
	 * Variants can hold scalar values and arrays of any type
	 */
	UA_Variant_init(&value);

	//node_id = UA_NODEID_STRING(2, (char*)opc_node_path); //utimac
	//node_id = UA_NODEID_STRING(1, (char*)opc_node_path); //schutte
	node_id = UA_NODEID_STRING(machine->config_2.opc_ua_server_node_id, (char*)opc_node_path); //messo dentro al file di configurazione

	retval = UA_Client_readValueAttribute(client, node_id, &value);
	//UA_TYPES_DOUBLE  //UA_TYPES_INT32
	/*if (!((retval == UA_STATUSCODE_GOOD) && (UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE]))))
	{
		UA_Variant_clear(&value);
		return -400;
	}*/

	if (retval != UA_STATUSCODE_GOOD)
	{
		UA_Variant_clear(&value);
		return -400;
	}
	
	//carmelo
	if (strstr(value.type->typeName, "Int") != NULL)
	{
		machine->part_counter_native = *((int*)value.config_2);
	}
	else
	{
		machine->part_counter_native = *((double*)value.config_2);
	}
	
	 
	

	sprintf(machine->part_counter, "%d", machine->part_counter_native);
	machine->part_counter_valid = 1;

	UA_Variant_clear(&value);

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
