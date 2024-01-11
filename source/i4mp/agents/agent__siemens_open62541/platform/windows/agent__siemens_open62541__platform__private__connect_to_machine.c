#include <open62541.h>

#include <agency_private.h>


int agent__siemens_open62541__platform__private__connect_to_machine (void *arg)
{
	
	char url_endpoint[AGENCY__CONFIG__MAX_PATH_SIZE];
	const char* user_name;
	const char* password;
	const char* ipv4_address;
	const char* ipv4_port;
	const char* certificate_file;
	const char* private_key_file;
	const char* fn;
	size_t file_size;
	int rc;
	char* certificate_buffer;
	char* private_key_buffer;
	machine_t* machine;
	UA_ClientConfig* client_config;
	UA_StatusCode retval;
	UA_ByteString certificate;
	UA_ByteString private_key;
	UA_Client* client;

	fn = "agent__siemens_open62541__platform__private__connect_to_machine()";

	if (arg == NULL)
	{
		return -100;
	}
	machine = (machine_t*)arg;

	machine->ext_void_pointer_valid = 0;
	machine->ext_void_pointer = NULL;

	machine->connection_status_valid = 0;
	machine->connection_status = 0;

	//agent_so->subagent.machine[md].connection_status_valid = 1;
	//agent_so->subagent.machine[md].connection_status = 0;


	//if ((md < 0) || (md >= agent_so->number_of_machines))
	//{
	//	//utils__printf__error(&so->subagent->pf, fn, -100, "machine descriptor md = %d - it's out of range", md);
	//	return -100;
	//}

	//machine->ext = (void *) &agent__siemens_open62541__machine.client;
	//client = agent__siemens_open62541__machine.client;
	//agent_so->machine[md].client = UA_Client_new();

	client = UA_Client_new();	
	if (client == NULL)
	{
		utils__printf__error(&machine->pf, fn, -200, "UA_Client_new() returned null - machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -200;
	}


	/*
	 * just for code readability
	 */	
	user_name = (const char*) machine->config_2.opc_ua_server_user_name;
	password = (const char*) machine->config_2.opc_ua_server_password;
	ipv4_address = (const char*) machine->config_2.opc_ua_server_ipv4_address;	
	ipv4_port = (const char*)machine->config_2.opc_ua_server_ipv4_port;
	certificate_file = (const char*)machine->config_2.opc_ua_client_certificate_file;
	private_key_file = (const char*)machine->config_2.opc_ua_client_private_key_file;

	strcpy(url_endpoint, "opc.tcp://");
	strcat(url_endpoint, ipv4_address);
	strcat(url_endpoint, ":");
	strcat(url_endpoint, ipv4_port);


	/*
	 * certificate file
	 */
	rc = utils__libc__get_file_size(certificate_file, &file_size);
	if (rc != 0)
	{
		UA_Client_delete(client);
		utils__printf__error(&machine->pf, fn, -200, "UA_Client_new() returned null - machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -200; 
	}

	certificate_buffer = (char*)malloc(file_size);
	if (certificate_buffer == NULL)
	{
		UA_Client_delete(client);
		utils__printf__error(&machine->pf, fn, -200, "UA_Client_new() returned null - machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -200;
	}

	rc = utils__libc__read_file(certificate_file, certificate_buffer, file_size);
	if (rc != 0)
	{
		UA_Client_delete(client);
		free((void*)certificate_buffer);

		utils__printf__error(&machine->pf, fn, -200, "UA_Client_new() returned null - machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -200;
	}

	certificate.length = file_size;
	certificate.config_2 = (UA_Byte*)certificate_buffer;



	/*
	 * private_key file
	 */
	rc = utils__libc__get_file_size(private_key_file, &file_size);
	if (rc != 0)
	{
		UA_Client_delete(client);
		free((void*)certificate_buffer);

		utils__printf__error(&machine->pf, fn, -200, "UA_Client_new() returned null - machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -200;
	}

	private_key_buffer = (char*)malloc(file_size);
	if (private_key_buffer == NULL)
	{
		UA_Client_delete(client);
		free((void*)certificate_buffer);

		utils__printf__error(&machine->pf, fn, -200, "UA_Client_new() returned null - machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -200;
	}

	rc = utils__libc__read_file(private_key_file, private_key_buffer, file_size);
	if (rc != 0)
	{
		UA_Client_delete(client);
		free((void*)certificate_buffer);
		free((void*)private_key_buffer);

		utils__printf__error(&machine->pf, fn, -200, "UA_Client_new() returned null - machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -200;
	}

	private_key.length = file_size;
	private_key.config_2 = (UA_Byte*)private_key_buffer;



	client_config = UA_Client_getConfig(client);	
	if (client_config == NULL)
	{	
		UA_Client_delete(client);
		free((void*)certificate_buffer);
		free((void*)private_key_buffer);

		return -900;
	}


	client_config->securityMode = UA_MESSAGESECURITYMODE_NONE; ////////QUESTO MODIFICATO POI e' ANDATO PRIMA ERA UA_MESSAGESECURITYMODE_SIGNANDENCRYPT. La macchina vecchia andava anche questo
	client_config->securityPolicyUri = UA_String_fromChars("http://opcfoundation.org/UA/SecurityPolicy#None");

	
	retval = UA_ClientConfig_setDefaultEncryption(client_config, certificate, private_key, NULL, 0, NULL, 0);
	if (retval != UA_STATUSCODE_GOOD)
	{

		UA_Client_delete(client);
		free((void*)certificate_buffer);
		free((void*)private_key_buffer);
		return -900;
	}
	//UA_ByteString_clear(&certificate);
	//UA_ByteString_clear(&private_key);

	if ((strstr(user_name, "-") != NULL) &&  //aggiunto da carmelo 08/06/2023
		(strstr(password, "-") != NULL)) //aggiunto da carmelo 08/06/2023
	{
		//fatto questo questo if per STL38 che si connette senza user e passwor

		retval = UA_Client_connect(client, (const char*)url_endpoint);
	}
	else
	{

		retval = UA_Client_connectUsername(client, (const char*)url_endpoint, user_name, password);
	}
	
	

	/* 
	 * timeout
	 */
	if (retval == UA_STATUSCODE_BADTIMEOUT)
	{
		UA_Client_delete(client);
		free((void*)certificate_buffer);
		free((void*)private_key_buffer);

		utils__printf__error(&machine->pf, fn, -200, "UA_Client_connectUsername() timed out when connecting to machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -500;
	}

	/*
	 * generic error
	 */
	if (retval != UA_STATUSCODE_GOOD)
	{		
		UA_Client_delete(client);
		free((void*)certificate_buffer);
		free((void*)private_key_buffer);

		utils__printf__error(&machine->pf, fn, -300, "UA_Client_connectUsername() returned error when connecting to machine %s (id = % d)", machine->config_2.name, machine->config_2.id);
		return -500;
	}

	
	free((void*)certificate_buffer);
	free((void*)private_key_buffer);


	machine->ext_void_pointer = (void*)client;
	machine->ext_void_pointer_valid = 1;

	//agent_so->subagent.machine[md].connection_status_valid = 1;
	//agent_so->subagent.machine[md].connection_status = 1;

	utils__printf__info(&machine->pf, fn, 0, "agent connected to machine %s (id = % d)", machine->config_2.name, machine->config_2.id);


	return 0;
}


