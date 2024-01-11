#include "agent__siemens_open62541__private.h"


//static UA_INLINE UA_ByteString load_file(const char* path);
//static UA_INLINE UA_ByteString load_file(const char* path, UA_ByteString* data);


int agent__siemens_open62541__connect_to_machine (int md)
{
	UA_ClientConfig* client_config;
	UA_StatusCode retval;
	UA_ByteString certificate;
	UA_ByteString privateKey;
	char opc_server_ipv4_url_endpoint[I4_AGENCY__CONFIG__MAX_PATH_SIZE];
	const char* opc_server_user_name;
	const char* opc_server_password;
	const char* opc_server_ipv4_address;
	const char* opc_server_ipv4_port;
	const char* opc_server_certificate_file;
	const char* opc_server_private_key_file;
	const char* fn;
	size_t file_size;
	int rc;
	char* certificate_buffer;
	char* private_key_buffer;


	fn = "agent__siemens_open62541__connect_to_machine()";

#if 0


	agent_so->subagent.machine[md].connection_status_valid = 1;
	agent_so->subagent.machine[md].connection_status = 0;

	
	if ((md < 0) || (md >= agent_so->number_of_machines))
	{
		//utils__printf__error(&so->subagent->pf, fn, -100, "machine descriptor md = %d - it's out of range", md);
		return -100;
	}


	agent_so->machine[md].client = UA_Client_new();
	
	if (agent_so->machine[md].client == NULL)
	{
		utils__printf__error(&agent_so->subagent.pf, fn, -200, "UA_Client_new() returned null - machine id = %d", md);
		return -200;
	}


	/*
	 * just for code readability
	 */
	opc_server_user_name = (const char*) agent_so->subagent.machine[md].config_2.opc_server_user_name;
	opc_server_password = (const char*) agent_so->subagent.machine[md].config_2.opc_server_password;
	opc_server_ipv4_address = (const char*) agent_so->subagent.machine[md].config_2.opc_server_ipv4_address;
	opc_server_ipv4_port = (const char*) agent_so->subagent.machine[md].config_2.opc_server_ipv4_port;
	opc_server_certificate_file = (const char*) agent_so->subagent.machine[md].config_2.opc_server_certificate_file;
	opc_server_private_key_file = (const char*) agent_so->subagent.machine[md].config_2.opc_server_private_key_file;

	strcpy(opc_server_ipv4_url_endpoint, "opc.tcp://");
	strcat(opc_server_ipv4_url_endpoint, opc_server_ipv4_address);
	strcat(opc_server_ipv4_url_endpoint, ":");
	strcat(opc_server_ipv4_url_endpoint, opc_server_ipv4_port);



	/*
	 * certificate = loadFile("D:\\PROGS\\prog-87--fggr\\deployment-examples\\example-1\\windows\\certificates\\server_cert.der");
	 * privateKey = loadFile("D:\\PROGS\\prog-87--fggr\\deployment-examples\\example-1\\windows\\certificates\\server_key.der");
	 */

	rc = utils__libc__get_file_size(opc_server_certificate_file, &file_size);
	if (rc != 0)
	{
		utils__printf__error(&agent_so->subagent.pf, fn, -200, "UA_Client_new() returned null - machine id = %d", agent_so->subagent.machine[md].config_2.id);
		return -200;
	}


	certificate_buffer = (char*)malloc(file_size);
	if (certificate_buffer == NULL)
	{
		utils__printf__error(&agent_so->subagent.pf, fn, -200, "UA_Client_new() returned null - machine id = %d", agent_so->subagent.machine[md].config_2.id);
		return -200;
	}


	rc = utils__libc__read_file(opc_server_certificate_file, certificate_buffer, file_size);
	if (rc != 0)
	{
		free((void *) certificate_buffer);
		utils__printf__error(&agent_so->subagent.pf, fn, -200, "UA_Client_new() returned null - machine id = %d", agent_so->subagent.machine[md].config_2.id);
		return -200;
	}

	certificate.length = file_size;
	certificate.config_2 = (UA_Byte*) certificate_buffer;


	rc = utils__libc__get_file_size(opc_server_private_key_file, &file_size);
	if (rc != 0)
	{
		free((void*)certificate_buffer);
		utils__printf__error(&agent_so->subagent.pf, fn, -200, "UA_Client_new() returned null - machine id = %d", agent_so->subagent.machine[md].config_2.id);
		return -200;
	}


	private_key_buffer = (char*)malloc(file_size);
	if (private_key_buffer == NULL)
	{
		free((void*)certificate_buffer);
		utils__printf__error(&agent_so->subagent.pf, fn, -200, "UA_Client_new() returned null - machine id = %d", agent_so->subagent.machine[md].config_2.id);
		return -200;
	}


	rc = utils__libc__read_file(opc_server_private_key_file, private_key_buffer, file_size);
	if (rc != 0)
	{
		free((void*)certificate_buffer);
		free((void*)private_key_buffer);
		utils__printf__error(&agent_so->subagent.pf, fn, -200, "UA_Client_new() returned null - machine id = %d", agent_so->subagent.machine[md].config_2.id);
		return -200;
	}


	privateKey.length = file_size;
	privateKey.config_2 = (UA_Byte*) private_key_buffer;





	//private_key_buffer
	//certificate = load_file(opc_server_certificate_file);
	//		
	//if (certificate.config_2 == NULL)  //if (certificate.data == NULL)
	//{
	//	UA_Client_delete(agent_so->machine[md].client);
	//	//utils__printf__error(&so->subagent->pf, fn, -300, "machine id %d - certificate not found", so->subagent->machine[md].config_2.id);
	//	return -300;
	//}



	//privateKey = load_file(opc_server_private_key_file);
	//if (privateKey.config_2 == NULL)  //if (privateKey.data == NULL)
	//{
	//	UA_Client_delete(agent_so->machine[md].client);
	//	//utils__printf__error(&so->subagent->pf, fn, -400, "machine id %d - private key not found", so->subagent->machine[md].config_2.id);
	//	return -400;
	//}






	//len = strlen(ipv4_url_endpoint);


	////opc_ipv4_addres_len = strlen(so->machine[md].config.opc_ipv4_address);

	//opc_ipv4_addres_len = strlen((const char*)agent_so->subagent.machine[md].config_2.opc_server_ipv4_address);

	//memcpy(&ipv4_url_endpoint[len], a_so->machine->machine_local[md].config_2.opc_ipv4_address, opc_ipv4_addres_len);

	//len_endpointurl += opc_ipv4_addres_len;



	//memcpy(&endpoint_ipv4_url[len_endpointurl], ":", 1);
	//len_endpointurl++;
	//opc_ipv4_port_len = strlen(a_so->machine->machine_local[md].config_2.opc_ipv4_port);
	//memcpy(&endpoint_ipv4_url[len_endpointurl], a_so->machine->machine_local[md].config_2.opc_ipv4_port, opc_ipv4_port_len);
	//len_endpointurl += opc_ipv4_port_len;
	//endpoint_ipv4_url[len_endpointurl] = '\0';



	client_config = UA_Client_getConfig(agent_so->machine[md].client);
	if (client_config == NULL)
	{
		UA_Client_delete(agent_so->machine[md].client);
		return -900;
	}


	client_config->securityMode = UA_MESSAGESECURITYMODE_NONE; ////////QUESTO MODIFICATO POI e' ANDATO PRIMA ERA UA_MESSAGESECURITYMODE_SIGNANDENCRYPT. La macchina vecchia andava anche questo
	client_config->securityPolicyUri = UA_String_fromChars("http://opcfoundation.org/UA/SecurityPolicy#None");

	retval = UA_ClientConfig_setDefaultEncryption(client_config, certificate, privateKey, NULL, 0, NULL, 0);
	if (retval != UA_STATUSCODE_GOOD)
	{
		UA_Client_delete(agent_so->machine[md].client);
		return -900;
	}

	//UA_ByteString_clear(&certificate);
	//UA_ByteString_clear(&privateKey);



	retval = UA_Client_connectUsername(agent_so->machine[md].client, (const char*) opc_server_ipv4_url_endpoint, opc_server_user_name, opc_server_password);

	if (retval != UA_STATUSCODE_GOOD)
	{
		UA_Client_delete(agent_so->machine[md].client);
		//utils__printf__info(&agent_so->subagent.pf, fn, 0, "UA_Client_connectUsername() returned %d - end point ipv4 %s", md, opc_server_ipv4_url_endpoint);
		//utils__printf__error(&so->subagent->pf, fn, -500, "UA_Client_connectUsername() returned %d for machine id %d", (int)retval, so->subagent->machine[md].config_2.id);
		return -500;
	}


	agent_so->subagent.machine[md].connection_status_valid = 1;
	agent_so->subagent.machine[md].connection_status = 1;
	
	utils__printf__info(&agent_so->subagent.pf, fn, 0, "agent connected to machine %s - machine id = %d", agent_so->subagent.machine[md].config_2.name, agent_so->subagent.machine[md].config_2.id);


#endif

	return 0;
}





//int utils__libc__load_file (const char* file_name, char* buffer, size_t *buffer_size)
//{
//
//	FILE* f;
//	long file_size;
//	size_t len;
//	UA_ByteString fileContents = UA_STRING_NULL;
//
//	f = fopen(path, "rb");
//	if (f == NULL)
//	{
//		return -100;
//	}
//	
//	fseek(f, 0, SEEK_END);     /* Get the file length, allocate the data and read */
//
//	file_size = ftell(f);
//
//	if (file_size < 0)
//	{
//
//	}
//
//	//fileContents.length = (size_t) ftell(f);
//	fileContents.length = (size_t) file_size;
//
//	//fileContents.config_2 = (UA_Byte*)UA_malloc(fileContents.length * sizeof(UA_Byte));
//	fileContents.config_2 = (UA_Byte*)malloc(file_size);
//
//	if (fileContents.config_2 == NULL)
//	{
//		fclose(f);
//		return -1000;
//	}
//
//	fseek(f, 0, SEEK_SET);
//
//	len = fread(fileContents.config_2, 1, fileContents.length, f);
//
//	if (len != fileContents.length)
//	{
//		UA_ByteString_clear(&fileContents);
//	}
//
//
//	if (fileContents.config_2)
//	{
//		fseek(f, 0, SEEK_SET);
//
//		size_t read = fread(fileContents.config_2, sizeof(UA_Byte), fileContents.length, fp);
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
//	fclose(f);
//
//	//free((void*)fileContents.config_2);
//
//	//return fileContents;
//	return 0;
//
//}



//static UA_INLINE UA_ByteString load_file(const char* path, UA_ByteString *data)
//{
//
//	UA_ByteString fileContents = UA_STRING_NULL;
//
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
//	//fileContents.config_2 = (UA_Byte*)UA_malloc(fileContents.length * sizeof(UA_Byte));
//	fileContents.config_2 = (UA_Byte*) malloc(fileContents.length * sizeof(UA_Byte));
//
//	if (fileContents.config_2)
//	{
//		fseek(fp, 0, SEEK_SET);
//
//		size_t read = fread(fileContents.config_2, sizeof(UA_Byte), fileContents.length, fp);
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
//	//free((void*)fileContents.config_2);
//
//	return fileContents;
//
//}
