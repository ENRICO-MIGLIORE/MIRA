#include <open62541.h>

#include <agency_private.h>


int agent__siemens_open62541__platform__private__read_machine_status_alarm (void* arg)
{

	UA_Variant value;
	UA_NodeId node_id;
	UA_StatusCode retval;
	UA_Client* client;
	char opc_node_path[AGENCY__CONFIG__MAX_PATH_SIZE];
	size_t opc_node_path_len;
	const char* fn;
	machine_t* machine;


	fn = "agent__siemens_open62541__read_machine_status_alarm()";


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


	machine->machine_status_alarm_valid = 0;


	strcpy(opc_node_path, machine->config_2.opc_ua_server_alarm_status_node_path);
	opc_node_path_len = strlen(opc_node_path);

	/*
	 * Variants can hold scalar values and arrays of any type
	 */
	UA_Variant_init(&value);

	node_id = UA_NODEID_STRING(machine->config_2.opc_ua_server_node_id, (char*)opc_node_path); //messo dentro al file di configurazione

	retval = UA_Client_readValueAttribute(client, node_id, &value);


	if (retval != UA_STATUSCODE_GOOD)
	{
		UA_Variant_clear(&value);
		return -400;
	}

	//carmelo
	if (strstr(value.type->typeName, "UInt16") != NULL)
	{
		machine->machine_status_alarm_native = *((unsigned short*)value.config_2);
	}
	else if (strstr(value.type->typeName, "UInt32") != NULL)
	{
		machine->machine_status_alarm_native = *((unsigned int*)value.config_2);
	}
	else
	{
		machine->machine_status_alarm_native = *((int*)value.config_2);
	}


	//mi sembra di ricordare che se la macchina e' in ALARM mandavo 0 a FGG. altrimenti != 0
	//SCHUTTE 31 e 32 sono in ALARM          Utimac:/Channel/State/acProg[u1,1]              Program status $AC_PROG 0=Reset 1=Stop 2=Run 3=Wait 4=Interrputed

	strcpy(machine->machine_status_alarm, "1"); //non sono in allarme

	if (machine->machine_status_alarm_native > 9)
	{
		//sono sullo schutte
		if ((machine->machine_status_alarm_native == 31) || (machine->machine_status_alarm_native == 32))
		{
			//sono in alarm
			strcpy(machine->machine_status_alarm, "0");
		}
	}
	else
	{
		//sono su utimac
		if ((machine->machine_status_alarm_native == 0) || (machine->machine_status_alarm_native == 1) || (machine->machine_status_alarm_native == 4))
		{
			//sono in alarm
			strcpy(machine->machine_status_alarm, "0");
		}
	}
	
	machine->machine_status_alarm_valid = 1;

	UA_Variant_clear(&value);



	return 0;

}
