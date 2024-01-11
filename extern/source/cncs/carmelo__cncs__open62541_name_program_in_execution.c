#include <open62541.h>
#include "carmelo__cncs.h"

int carmelo__cncs__open62541_name_program_in_execution  (UA_Client* client,char* path, unsigned long path_len, fgg__buffer_t *prog)
{

	UA_Variant value2; /* Variants can hold scalar values and arrays of any type */
	UA_NodeId nodeId2;
	UA_StatusCode retval;
	UA_String aa;

	UA_Variant_init(&value2);

	path[path_len] = '\0';

	nodeId2 = UA_NODEID_STRING(2, (char *) path);
	retval = UA_Client_readValueAttribute(client, nodeId2, &value2);

	if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value2, &UA_TYPES[UA_TYPES_STRING])) 
	{
		aa = *(UA_String*)value2.data;

		prog->len = (unsigned long) aa.length;

		memcpy (prog->data, (unsigned char *) aa.data, prog->len);

		/* Clean up */
		UA_Variant_clear(&value2);

		return 0;
	}

	return -1;
}

