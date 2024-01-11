
#include <open62541.h>

//#include "fgg__cncs_open62541.h"
#include "carmelo__cncs.h"


static UA_INLINE UA_ByteString loadFile(const char* const path) {
	UA_ByteString fileContents = UA_STRING_NULL;

	/* Open the file */
	FILE* fp = fopen(path, "rb");
	if (!fp) {
		errno = 0; /* We read errno also from the tcp layer... */
		return fileContents;
	}

	/* Get the file length, allocate the data and read */
	fseek(fp, 0, SEEK_END);
	fileContents.length = (size_t)ftell(fp);
	fileContents.data = (UA_Byte*)UA_malloc(fileContents.length * sizeof(UA_Byte));
	if (fileContents.data) {
		fseek(fp, 0, SEEK_SET);
		size_t read = fread(fileContents.data, sizeof(UA_Byte), fileContents.length, fp);
		if (read != fileContents.length)
			UA_ByteString_clear(&fileContents);
	}
	else {
		fileContents.length = 0;
	}
	fclose(fp);

	return fileContents;
}




int carmelo__cncs__open62541_connect  (UA_Client *client, char* ip, unsigned long ip_len, char* port,  unsigned long port_len, char* username,  unsigned long username_len, char* password, unsigned long password_len)
{

	UA_ClientConfig* config;
	UA_StatusCode retval;



	char endpoint_url[256];
	unsigned long len_endpointurl;





	UA_ByteString certificate = loadFile("D:\\PROGS\\prog-87--fggr\\deployment-examples\\example-1\\windows\\certificates\\server_cert.der"); 
	UA_ByteString privateKey = loadFile("D:\\PROGS\\prog-87--fggr\\deployment-examples\\example-1\\windows\\certificates\\server_key.der");

	strcpy (endpoint_url, "opc.tcp://" );
	len_endpointurl = strlen(endpoint_url);

	memcpy (&endpoint_url[len_endpointurl], ip, ip_len);
	len_endpointurl += ip_len;

	memcpy (&endpoint_url[len_endpointurl], ":", 1);
	len_endpointurl++;

	memcpy (&endpoint_url[len_endpointurl], port, port_len);
	len_endpointurl += port_len;

	endpoint_url[len_endpointurl] = '\0';



	//client = UA_Client_new();
	config = UA_Client_getConfig(client);


	config->securityMode = UA_MESSAGESECURITYMODE_NONE; ////////QUESTO MODIFICATO POI e' ANDATO PRIMA ERA UA_MESSAGESECURITYMODE_SIGNANDENCRYPT. Con lamacchina vecchia andava anche questo
	config->securityPolicyUri = UA_String_fromChars("http://opcfoundation.org/UA/SecurityPolicy#None");

	UA_ClientConfig_setDefaultEncryption(config, certificate, privateKey, NULL, 0, NULL, 0);

	UA_ByteString_clear(&certificate);
	UA_ByteString_clear(&privateKey);

	username[username_len] = '\0';

	password[password_len] = '\0';


	retval = UA_Client_connectUsername(client, (const char *) endpoint_url,(const char *)  username,(const char *)  password);


	if (retval != UA_STATUSCODE_GOOD)
	{
		UA_Client_delete(client);
		return -1;
	}

	return 0;

}

