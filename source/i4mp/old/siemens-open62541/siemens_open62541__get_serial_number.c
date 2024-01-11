#include "siemens_open62541__private.h"


int siemens_open62541__get_serial_number (int md, char* buffer, size_t buffer_size, size_t* buffer_len)
{

	size_t buffer_size_min;
	int rc;


	buffer_size_min = SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256;

	pthread_mutex_lock(&so->pthread_mutex);

	rc = siemens_open62541__private__check_parameters_and_agent_status(md, buffer, buffer_size, buffer_size_min, buffer_len);

	if (rc == 0)
	{
		strcpy(buffer, so->machine[md].config.serial_number);
		*buffer_len = strlen(buffer);
	}
    
	pthread_mutex_unlock(&so->pthread_mutex);

	return rc;
}

//
//int siemens_open62541__private__check_parameters_and_agent_status_2(int md, char* buffer, size_t buffer_size, size_t len);
//
//
//int siemens_open62541__set_serial_number(int md, char* buffer, size_t buffer_len)
//{
//
//	size_t buffer_size;
//	int rc;
//
//	pthread_mutex_lock(&so->pthread_mutex);
//
//	/*
//	 * -1 is the room we need to safely terminate the string
//	 */
//	buffer_size = sizeof(so->machine[md].config.serial_number) - 1;
//
//	rc = siemens_open62541__private__check_parameters_and_agent_status_2(md, so->machine[md].config.serial_number, sizeof(so->machine[md].config.serial_number), buffer_len);
//	if (rc == 0)
//	{
//		strcpy(buffer, so->machine[md].config.serial_number);
//		memcpy(so->machine[md].config.serial_number, buffer, buffer_len);
//		so->machine[md].config.serial_number[buffer_len] = '\0';
//	}
//
//
//	pthread_mutex_unlock(&so->pthread_mutex);
//
//	return rc;
//}
//
//
//
//int siemens_open62541__private__check_parameters_and_agent_status_2(int md, char* buffer, size_t buffer_size, size_t len)
//{
//
//	if (so == NULL)
//	{
//		return -100;
//	}
//
//	if (so->configured != 1)
//	{
//		return -200;
//	}
//
//	if ((md >= so->machine_count) || (md < 0))
//	{
//		return -400;
//	}
//
//	if (buffer == NULL)
//	{
//		return -500;
//	}
//
//	if (buffer_size < SIEMENS_OPEN62541__CONFIG__BUFFER_SIZE_256)
//	{
//		return -700;
//	}
//
//
//	if (len + 1 > buffer_size)
//	{
//		return -700;
//	}
//
//	return 0;
//
//}