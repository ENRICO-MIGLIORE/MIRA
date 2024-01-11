#include "fgg__media.h"

#if 0
void fgg__media__fill_media_names (fgg__buffer_t *name, int option)
{
	size_t i;


	i = 0;

	for (i = 0; i < FGG__COMMON__RECORD__PRIVATE_FIELDS; i++)
	{
		(void) fgg__util__strcpy_buffer (&name[i], fgg__media->field_names[i].data);
	}

	if (option == 0)
	{
		for (i = FGG__MEDIA__PK_ID__V1; i < fgg__media->fields_max; i++)
		{
			(void) fgg__util__strcpy_buffer (&name[i], fgg__media->field_names[i].data);
		}
	}

}
#endif









