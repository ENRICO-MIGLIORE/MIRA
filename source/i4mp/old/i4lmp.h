#ifndef I4MP_H
#define I4MP_H


#include <stddef.h>


#include "i4mp__machine_agent.h"



int i4mp__entry(int argc, char* argv[], i4mp__machine_agent_t* mp, size_t machine_proxy_count);

int i4mp__get_machine_count (size_t* count);
int i4mp__get_communications_enabled_machine_count(size_t* count);

int i4mp__get_connection_status(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_part_counter(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_cycle_time(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_machine_brand(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_machine_model(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_machine_sn(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_machine_name(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);
int i4mp__get_machine_facility(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len);

char* i4mp__get_application_version(void);

#endif
