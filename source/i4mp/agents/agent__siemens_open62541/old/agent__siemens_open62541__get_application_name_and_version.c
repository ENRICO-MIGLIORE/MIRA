#include "siemens_open62541__private.h"


int agent__siemens_open62541__get_application_name_and_version (char* buffer, size_t buffer_size, size_t* buffer_len)
{

    size_t len;

    if (buffer == NULL)
    {
        return -100;
    }

    if (buffer_len == NULL)
    {
        return -200;
    }

    len = strlen(agent_so->application_name_and_version);

    if (len >= buffer_size)
    {
        return -300;
    }

    strcpy(buffer, agent_so->application_name_and_version);

    *buffer_len = len;

    return 0;

}
