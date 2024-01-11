#ifndef I4MP__MACHINE_PROXY_H
#define I4MP__MACHINE_PROXY_H


#include <stddef.h>


typedef int (*i4mp__machine_proxy__init_t) (int argc, char* argv[]);
typedef int (*i4mp__machine_proxy__config_t) (void);
typedef int (*i4mp__machine_proxy__start_t) (void);


typedef struct
{
	i4mp__machine_proxy__init_t init;
	i4mp__machine_proxy__config_t config;
	i4mp__machine_proxy__start_t start;

} i4mp__machine_proxy_t;


#endif
