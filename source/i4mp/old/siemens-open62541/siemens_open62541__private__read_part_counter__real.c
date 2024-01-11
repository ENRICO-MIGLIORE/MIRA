#include "siemens_open62541__private.h"


int siemens_open62541__private__read_part_counter__real (int md)
{

	UA_Variant value2;
	UA_NodeId nodeId2;
	UA_StatusCode retval;
	long c;
	char path[128];
	size_t path_len;
	size_t part_counter_real;


	if ((md < 0) || (md >= so->machine_count))
	{
		return -1000;
	}

	so->machine[md].part_counter_valid = 0;

	/*
	 * Variants can hold scalar values and arrays of any type
	 */
	UA_Variant_init(&value2);

	//strcpy(path, "/Nck/State/aDbd[236]");


	strcpy(path, so->machine[md].config.opc_part_counter_path);


	path_len = strlen(path);

	path[path_len] = '\0';

	nodeId2 = UA_NODEID_STRING(2, (char*)path);

	
	retval = UA_Client_readValueAttribute(so->machine[md].client, nodeId2, &value2);

	if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_INT32]))
	{

		c = *((long*)value2.data);

		if (c < 0)
		{
			return -100;
		}

		part_counter_real = (size_t) c;

		/*
		 * Clean up
		 */
		UA_Variant_clear(&value2);


		so->machine[md].part_counter = part_counter_real;
		sprintf(so->machine[md].part_counter_utf_8, "%zu", part_counter_real);
		so->machine[md].part_counter_utf_8_len = strlen(so->machine[md].part_counter_utf_8);
		so->machine[md].part_counter_valid = 1;

		return 0;
	}

	

	return -200;

}
