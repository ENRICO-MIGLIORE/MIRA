#include "mira__private.h"


int mira__get_buffer_size (size_t* buffer_size)
{


    if (mira == NULL)
    {
        return -100;
    }

    if (mira->started != 1)
    {
        return -200;
    }

    if (buffer_size == NULL)
    {
        return -300;
    }

    *buffer_size = mira->buffer_size;

    return 0;

}

