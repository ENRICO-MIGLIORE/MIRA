#include <open62541.h>
#include "carmelo__cncs.h"

int carmelo__cncs__open62541_get_machined_parts  (UA_Client* client, char* path, unsigned long path_len, unsigned long *count)
{

	UA_Variant value2; /* Variants can hold scalar values and arrays of any type */
	UA_NodeId nodeId2;
	UA_StatusCode retval;

	UA_Variant_init(&value2);

	path[path_len] = '\0';

	nodeId2 = UA_NODEID_STRING(2, (char *) path);

	retval = UA_Client_readValueAttribute(client, nodeId2, &value2);

	if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_INT32])) 
	{
		//printf("pezzi assoluti is: %i\n", *(UA_Int32*)value2.data);
		*count = *(unsigned long*)value2.data;

		/* Clean up */
		UA_Variant_clear(&value2);
		return 0;
	}

	return -1;

}


int carmelo__cncs__open62541_get_emergency  (UA_Client* client, char* path, unsigned long path_len, unsigned long *state)
{

	UA_Variant value2; /* Variants can hold scalar values and arrays of any type */
	UA_NodeId nodeId2;
	UA_StatusCode retval;
	//unsigned char pp;

	UA_Variant_init(&value2);

	path[path_len] = '\0';

	nodeId2 = UA_NODEID_STRING(2, (char *) path);
	retval = UA_Client_readValueAttribute(client, nodeId2, &value2);

	if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_UINT16])) 
	{
		//printf("pezzi assoluti is: %i\n", *(UA_Int32*)value2.data);
		//pp = *(UA_UInt16*)value2.data;
		*state = *(UA_UInt16*) value2.data;

		/* Clean up */
		UA_Variant_clear(&value2);
		return 0;
	}

	return -1;

}

