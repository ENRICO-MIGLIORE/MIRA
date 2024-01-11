#include "agent__siemens_open62541__private.h"


int agent__siemens_open62541__read_machine_part_program_name (int md)
{
	//UA_Variant value;
	//UA_NodeId nodeId;
	//UA_StatusCode retval;
	//char opc_node_path[SUBAGENT__CONFIG__MAX_PATH_SIZE];
	//size_t opc_node_path_len;
	//UA_String part_program_name;
	//size_t len;
	//const char* fn;


	//fn = "agent__siemens_open62541__read_machine_part_program_name()";


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

	//agent_so->subagent.machine[md].part_program_name_valid = 0;
	//

	//strcpy(opc_node_path, "/Channel/ProgramInfo/workPNameLong");   //strcpy(path, so->machine[md].config_2.opc_part_program_name_path);  // strcpy(path, "/Channel/ProgramInfo/workPNameLong")
	//opc_node_path_len = strlen(opc_node_path);
	//opc_node_path[opc_node_path_len] = '\0';

	///*
	// * Variants can hold scalar values and arrays of any type
	// */
	//UA_Variant_init(&value);

	//nodeId = UA_NODEID_STRING(2, (char*)opc_node_path);

	//retval = UA_Client_readValueAttribute(agent_so->machine[md].client, nodeId, &value);


	//if (!((retval == UA_STATUSCODE_GOOD) && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_STRING])))
	//{
	//	UA_Variant_clear(&value);
	//	return -400;
	//}

	//part_program_name = *(UA_String*)value.config_2;

	//len = part_program_name.length;

	//if (len == 0)
	//{
	//	UA_Variant_clear(&value);
	//	return -500;
	//}

	//if (len >= sizeof(agent_so->subagent.machine[md].part_program_name))
	//{
	//	len--;
	//}

	////	if (so->machine[md].config.part_program_name_filter.do_filtering == 1)
	////	{
	////		/*
	////		 * before filtering: "/_N_WKS_DIR/_N_XJ12MMW04_M_ZNP__2_WPD" 
	////		 * 
	////		 * prefix = "/_N_WKS_DIR/_N_"
	////		 * suffix = "__2_WPD
	////		 *
	////		 * after filtering:  "XJ12MMW04_M_ZNP"
	////		 */

	////		prefix = strstr(so->machine[md].part_program_name, so->machine[md].config.part_program_name_filter.prefix);
	////		if (prefix != NULL)
	////		{
	////			prefix += so->machine[md].config.part_program_name_filter.prefix_len;
	////			strcpy(so->machine[md].part_program_name_utf_8, prefix);
	////		}

	////		suffix = strstr(so->machine[md].part_program_name_utf_8, so->machine[md].config.part_program_name_filter.suffix);
	////		if (suffix != NULL)
	////		{
	////			*suffix = '\0';				
	////		}
	////	}
	////	else
	////	{
	////		strcpy(so->machine[md].part_program_name_utf_8, so->machine[md].part_program_name);
	////	}

	//memcpy(agent_so->subagent.machine[md].part_program_name, (const void *) part_program_name.config_2, len);
	//agent_so->subagent.machine[md].part_program_name[len] = '\0';


	//agent_so->subagent.machine[md].part_program_name_valid = 1;

	//UA_Variant_clear(&value);

	return 0;

}


//int agent__siemens_open62541__private__read_part_program_name__real(int md)
//{
//
//	UA_Variant value2;
//	UA_NodeId nodeId2;
//	UA_StatusCode retval;
//	UA_String s;
//	char* part_program_name;
//	char path[1024];
//	size_t path_len;
//	size_t len;
//	char* prefix;
//	char* suffix;
//
//
//
//	//if ((md < 0) || (md >= so->number_of_machines))
//	//{
//	//	return -100;
//	//}
//
//	//so->machine[md].part_program_name_valid = 0;
//
//	///*
//	// * Variants can hold scalar values and arrays of any type
//	// */
//	//UA_Variant_init(&value2);
//
//
//	//strcpy(path, so->machine[md].config.opc_part_program_name_path);    /* strcpy(path, "/Channel/ProgramInfo/workPNameLong"); */
//
//	//path_len = strlen(path);
//	//path[path_len] = '\0';
//
//	//nodeId2 = UA_NODEID_STRING(2, (char*)path);
//
//	//retval = UA_Client_readValueAttribute(so->machine[md].client, nodeId2, &value2);
//
//	//if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_STRING]))
//	//{		
//	//
//	//	s = *(UA_String*) value2.data;
//
//	//	len = (size_t) s.length;
//
//	//	if (len >= sizeof(so->machine[md].part_program_name))
//	//	{
//	//		UA_Variant_clear(&value2);    		/* Clean up */
//
//	//		return -200;
//	//	}
//
//
//	//	part_program_name = (char *) s.data;
//
//	//	memcpy(so->machine[md].part_program_name, (const void *) part_program_name, len);
//	//	so->machine[md].part_program_name[len] = '\0';
//
//	//	if (so->machine[md].config.part_program_name_filter.do_filtering == 1)
//	//	{
//	//		/*
//	//		 * before filtering: "/_N_WKS_DIR/_N_XJ12MMW04_M_ZNP__2_WPD" 
//	//		 * 
//	//		 * prefix = "/_N_WKS_DIR/_N_"
//	//		 * suffix = "__2_WPD
//	//		 *
//	//		 * after filtering:  "XJ12MMW04_M_ZNP"
//	//		 */
//
//	//		prefix = strstr(so->machine[md].part_program_name, so->machine[md].config.part_program_name_filter.prefix);
//	//		if (prefix != NULL)
//	//		{
//	//			prefix += so->machine[md].config.part_program_name_filter.prefix_len;
//	//			strcpy(so->machine[md].part_program_name_utf_8, prefix);
//	//		}
//
//	//		suffix = strstr(so->machine[md].part_program_name_utf_8, so->machine[md].config.part_program_name_filter.suffix);
//	//		if (suffix != NULL)
//	//		{
//	//			*suffix = '\0';				
//	//		}
//	//	}
//	//	else
//	//	{
//	//		strcpy(so->machine[md].part_program_name_utf_8, so->machine[md].part_program_name);
//	//	}
//	//	
//	//	so->machine[md].part_program_name_utf_8_len = strlen(so->machine[md].part_program_name_utf_8);
//
//	//	so->machine[md].part_program_name_valid = 1;
//
//	//	UA_Variant_clear(&value2);    		/* clean up */
//
//	//	return 0;
//	//}
//
//
//	return -300;
//
//}