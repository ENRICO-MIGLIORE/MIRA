#include <open62541.h>
#include "carmelo__cncs.h"


int carmelo__cncs__open62541_get_time_of_cycle  (UA_Client* client, char* path, unsigned long path_len, double *time)
{

	UA_Variant value2; /* Variants can hold scalar values and arrays of any type */
	UA_NodeId nodeId2;
	UA_StatusCode retval;

	UA_Variant_init(&value2);

	path[path_len] = '\0';

	nodeId2 = UA_NODEID_STRING(2, (char *) path);
	retval = UA_Client_readValueAttribute(client, nodeId2, &value2);

	if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_DOUBLE])) 
	{
		*time = *(UA_Double*)value2.data;

		/* Clean up */
		UA_Variant_clear(&value2);
		return 0;
	}

	return -1;

}

