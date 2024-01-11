

#include <open62541.h>

//#include "..\fgg__cncs_open62541.h"
#include "carmelo__cncs.h"


int carmelo__cncs__open62541_clear_client  (UA_Client *client)
{

	UA_Client_disconnect(client);
   	UA_Client_delete(client);

	return 0;	
}

