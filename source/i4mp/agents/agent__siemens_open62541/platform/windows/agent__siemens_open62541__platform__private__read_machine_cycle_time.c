#include <open62541.h>

#include <agency_private.h>


int agent__siemens_open62541__platform__private__read_machine_cycle_time (void* arg)
{
	
	UA_Variant value;
	UA_NodeId node_id;
	UA_StatusCode retval;	
	UA_Client* client;
	char opc_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t opc_node_path_len;
	const char* fn;
	machine_t* machine;


	fn = "agent__siemens_open62541__read_machine_cycle_time()";


	if (arg == NULL)
	{
		return -100;
	}

	machine = (machine_t*)arg;
	if (machine->ext_void_pointer_valid == 0)
	{
		return -200;
	}

	client = (UA_Client* )machine->ext_void_pointer;
	if (client == NULL)
	{
		return -300;
	}


	//machine->part_counter_valid = 0;
	machine->cycle_time_valid = 0;

	////strcpy(path, so->machine[md].config.opc_part_counter_path);  /* strcpy(path, "/Nck/State/aDbd[236]"); */
	//strcpy(opc_node_path, "/Nck/State/aDbd[236]");
	//opc_node_path_len = strlen(opc_node_path);
	//opc_node_path[opc_node_path_len] = '\0';

	//strcpy(opc_node_path, "/Channel/Parameter/rpa[u1,90]");
	strcpy(opc_node_path, machine->config_2.opc_ua_server_cycle_time_node_path);
	opc_node_path_len = strlen(opc_node_path);
	//opc_node_path[opc_node_path_len] = '\0';


	/*
	 * Variants can hold scalar values and arrays of any type
	 */
	UA_Variant_init(&value);

	//node_id = UA_NODEID_STRING(2, (char*)opc_node_path);   //utimac
	//node_id = UA_NODEID_STRING(1, (char*)opc_node_path);   //schutte
	node_id = UA_NODEID_STRING(machine->config_2.opc_ua_server_node_id, (char*)opc_node_path); //messo dentro al file di configurazione

	retval = UA_Client_readValueAttribute(client, node_id, &value);

	if (!((retval == UA_STATUSCODE_GOOD) && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE])))
	{
		UA_Variant_clear(&value);
		return -400;
	}

	machine->cycle_time_native = *(UA_Double*)value.config_2;
	sprintf(machine->cycle_time, "%.1f", machine->cycle_time_native);
	machine->cycle_time_valid = 1;

	UA_Variant_clear(&value);



	///*
	// * Variants can hold scalar values and arrays of any type
	// */
	//UA_Variant_init(&value);

	//node_id = UA_NODEID_STRING(2, (char*)opc_node_path);

	//retval = UA_Client_readValueAttribute(client, node_id, &value);
	//
	//if (!((retval == UA_STATUSCODE_GOOD) && (UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32]))))	
	//{
	//	UA_Variant_clear(&value);
	//	return -400;
	//}

	//machine->part_counter_native = *((int*)value.config_2);
	//sprintf(machine->part_counter, "%d", machine->part_counter_native);
	//machine->part_counter_valid = 1;

	//UA_Variant_clear(&value);

	return 0;

}


//int agent__siemens_open62541__platform__private__read_machine_cycle_time(int md)
//{
//	UA_Variant value;
//	UA_NodeId nodeId;
//	UA_StatusCode retval;
//	char opc_node_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
//	size_t opc_node_path_len;
//	double cycle_time;
//	const char* fn;
//
//
//	fn = "agent__siemens_open62541__platform__private__read_machine_cycle_time()";
//
//
//	if (agent_so == NULL)
//	{
//		return -100;
//	}
//
//	if (agent_so->started != 1)
//	{
//		return -200;
//	}
//
//	if ((md < 0) || (md >= agent_so->number_of_machines))
//	{
//		return -300;
//	}
//
//	agent_so->subagent.machine[md].cycle_time_valid = 0;
//
//
//	//strcpy(path, so->machine[md].config.opc_cycle_time_path);  //strcpy(path, "/Channel/Parameter/rpa[u1,90]");
//
//	strcpy(opc_node_path, "/Channel/Parameter/rpa[u1,90]");
//	opc_node_path_len = strlen(opc_node_path);
//	opc_node_path[opc_node_path_len] = '\0';
//
//	/*
//	 * Variants can hold scalar values and arrays of any type
//	 */
//	UA_Variant_init(&value);
//
//	nodeId = UA_NODEID_STRING(2, (char*)opc_node_path);
//
//	retval = UA_Client_readValueAttribute(agent_so->machine[md].client, nodeId, &value);
//
//
//	if (!((retval == UA_STATUSCODE_GOOD) && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_DOUBLE])))
//	{
//		UA_Variant_clear(&value);
//		return -400;
//	}
//
//	cycle_time = *(UA_Double*)value.config_2;
//
//	agent_so->subagent.machine[md].cycle_time_native = cycle_time;
//	sprintf(agent_so->subagent.machine[md].cycle_time, "%.1f", agent_so->subagent.machine[md].cycle_time_native);
//	agent_so->subagent.machine[md].cycle_time_valid = 1;
//
//	UA_Variant_clear(&value);
//
//	return 0;
//
//}
