#include "agent.h"

//
//static UA_INLINE UA_ByteString siemens_open62541__load_file(const char* path);
//
//
//static char* fn = "siemens_open62541__private__connect_to_machine__real()";


int agent__private__connect_to_machine(agent_t* agent, int md)
{
//	UA_ClientConfig* config;
//	UA_StatusCode retval;
//	UA_ByteString certificate;
//	UA_ByteString privateKey;
//	size_t opc_ipv4_addres_len;
//	size_t opc_ipv4_port_len;
//	char endpoint_ipv4_url[128];
//	size_t len_endpointurl;
//
//
//	if ((md > so->machine_count) || (md < 0))
//	{
//		return -100;
//	}
//
//
//	so->machine[md].client = UA_Client_new();
//
//	if (so->machine[md].client == NULL)
//	{
//		utils__printf__error(&so->pf, fn, -200, "UA_Client_new() returned NULL for machine id %d", so->machine[md].config.id);
//		return -200;
//	}
//
//	/*
//	 * certificate = loadFile("D:\\PROGS\\prog-87--fggr\\deployment-examples\\example-1\\windows\\certificates\\server_cert.der");
//	 * privateKey = loadFile("D:\\PROGS\\prog-87--fggr\\deployment-examples\\example-1\\windows\\certificates\\server_key.der");
//	 */
//
//	certificate = siemens_open62541__load_file((const char*)so->machine[md].config.opc_certificate_file);
//	if (certificate.data == NULL)
//	{
//		UA_Client_delete(so->machine[md].client);
//		utils__printf__error(&so->pf, fn, -300, "certificate not found for machine id %d", so->machine[md].config.id);
//		return -300;
//	}
//
//	privateKey = siemens_open62541__load_file((const char*)so->machine[md].config.opc_private_key_file);
//	if (privateKey.data == NULL)
//	{
//		UA_Client_delete(so->machine[md].client);
//		utils__printf__error(&so->pf, fn, -400, "private key not found for machine id %d", so->machine[md].config.id);
//		return -400;
//	}
//
//	strcpy(endpoint_ipv4_url, "opc.tcp://");
//	len_endpointurl = strlen(endpoint_ipv4_url);
//
//
//	opc_ipv4_addres_len = strlen(so->machine[md].config.opc_ipv4_address);
//	memcpy(&endpoint_ipv4_url[len_endpointurl], so->machine[md].config.opc_ipv4_address, opc_ipv4_addres_len);
//	len_endpointurl += opc_ipv4_addres_len;
//
//	memcpy(&endpoint_ipv4_url[len_endpointurl], ":", 1);
//	len_endpointurl++;
//
//	opc_ipv4_port_len = strlen(so->machine[md].config.opc_ipv4_port);
//	memcpy(&endpoint_ipv4_url[len_endpointurl], so->machine[md].config.opc_ipv4_port, opc_ipv4_port_len);
//	len_endpointurl += opc_ipv4_port_len;
//
//	endpoint_ipv4_url[len_endpointurl] = '\0';
//
//
//	config = UA_Client_getConfig(so->machine[md].client);
//
//	config->securityMode = UA_MESSAGESECURITYMODE_NONE; ////////QUESTO MODIFICATO POI e' ANDATO PRIMA ERA UA_MESSAGESECURITYMODE_SIGNANDENCRYPT. Con lamacchina vecchia andava anche questo
//	config->securityPolicyUri = UA_String_fromChars("http://opcfoundation.org/UA/SecurityPolicy#None");
//
//	UA_ClientConfig_setDefaultEncryption(config, certificate, privateKey, NULL, 0, NULL, 0);
//
//	UA_ByteString_clear(&certificate);
//	UA_ByteString_clear(&privateKey);
//
//
//	utils__printf__info(&so->pf, fn, 0, "machine id %d - end point ipv4 %s", md, endpoint_ipv4_url);
//
//
//	retval = UA_Client_connectUsername(so->machine[md].client, (const char*)endpoint_ipv4_url, (const char*)so->machine[md].config.opc_user_name, (const char*)so->machine[md].config.opc_password);
//
//	if (retval != UA_STATUSCODE_GOOD)
//	{
//		UA_Client_delete(so->machine[md].client);
//		utils__printf__error(&so->pf, fn, -500, "UA_Client_connectUsername() returned %d for machine id %d", (int)retval, so->machine[md].config.id);
//		return -500;
//	}
//
//
//	so->machine[md].connection_status = 1;
//	
//	utils__printf__info(&so->pf, fn, 0, "agent connected to \"%s(%d)\" in run mode", so->machine[md].config.name, so->machine[md].config.id);
//
//	return 0;

	int rc;

	rc = agent->connect_to_machine(md);

	return rc;
}


//
//
//
//
//static UA_INLINE UA_ByteString siemens_open62541__load_file(const char* path)
//{
//	UA_ByteString fileContents = UA_STRING_NULL;
//
//	/* Open the file */
//	FILE* fp = fopen(path, "rb");
//	if (!fp)
//	{
//		errno = 0;                        /* We read errno also from the tcp layer... */
//		return fileContents;
//	}
//
//	/* Get the file length, allocate the data and read */
//	fseek(fp, 0, SEEK_END);
//
//	fileContents.length = (size_t)ftell(fp);
//
//	fileContents.data = (UA_Byte*)UA_malloc(fileContents.length * sizeof(UA_Byte));
//
//	if (fileContents.data)
//	{
//		fseek(fp, 0, SEEK_SET);
//
//		size_t read = fread(fileContents.data, sizeof(UA_Byte), fileContents.length, fp);
//
//		if (read != fileContents.length)
//		{
//			UA_ByteString_clear(&fileContents);
//		}
//	}
//	else
//	{
//		fileContents.length = 0;
//	}
//
//	fclose(fp);
//
//	return fileContents;
//
//}
