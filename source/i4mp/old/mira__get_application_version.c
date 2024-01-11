#include "mira__private.h"


int mira__get_application_version (char* buffer, size_t buffer_size, size_t* buffer_len)
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

    len = strlen(mira->application_version);
    if (len >= buffer_size)
    {
        return -300;
    }

    strcpy(buffer, mira->application_version);

    *buffer_len = len;

    return 0;

}