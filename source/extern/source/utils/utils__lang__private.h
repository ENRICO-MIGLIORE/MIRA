#ifndef UTILS__LANG__PRIVATE_H
#define UTILS__LANG__PRIVATE_H


typedef struct  
{
	utils__lang__config_t config;
	int configured;

} utils__lang__t;


extern utils__lang__t lang;


#endif