#ifndef FGG__CNC_OPEN62541_H
#define FGG__CNC_OPEN62541_H

//#include <..\fggr.h>
#include <open62541.h>
//#include <open62541/client_config_default.h>
//#include <open62541/client_highlevel.h>
//#include <open62541/plugin/log_stdout.h>
//#include <open62541/plugin/securitypolicy.h>
//#include <open62541/server.h>
//#include <open62541/server_config_default.h>
//#include <open62541/plugin/securitypolicy_default.h>
//#include <open62541/plugin/common.h> 



int carmelo__cncs__open62541_connect  (UA_Client *client, char* ip, unsigned long ip_len, char* port,  unsigned long port_len, char* username,  unsigned long username_len, char* password, unsigned long password_len);
int carmelo__cncs__open62541_clear_client  (UA_Client *client);
int carmelo__cncs__open62541_get_machined_parts  (UA_Client* client, char* path, unsigned long path_len, unsigned long *count);
//int carmelo__cncs__open62541_get_emergency  (UA_Client* client, char* path, unsigned long path_len, unsigned long *state);
//int carmelo__cncs__open62541_get_time_of_cycle  (UA_Client* client, char* path, unsigned long path_len, double *time);
//int carmelo__cncs__open62541_number_of_alarm  (UA_Client* client, char* path, unsigned long path_len, unsigned long *alarm);
//int carmelo__cncs__open62541_name_program_in_execution  (UA_Client* client, char* path, unsigned long path_len, fgg__buffer_t *prog);
//int carmelo__cncs__open62541_get_state_machine  (UA_Client* client, char* path, unsigned long path_len, unsigned long *state);
//int carmelo__cncs__open62541_get_avanzamento_barra  (UA_Client* client, char* path, unsigned long path_len, unsigned long *avanzamento);
//int carmelo__cncs__enca_pscp_get_program_files (fgg__buffer_t* ip,  fgg__buffer_t* username, fgg__buffer_t* password, fgg__buffer_t* path_source, fgg__buffer_t* path_dest, size_t flag);
//int carmelo__cncs__open62541_get_instant_power  (UA_Client* client, char* path, unsigned long path_len, double *instant_power);
//int carmelo__cncs__open62541_get_average_power  (UA_Client* client, char* path, unsigned long path_len, double *avarage_power);




#endif