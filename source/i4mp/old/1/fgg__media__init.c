#include "fgg__media.h"


#if 0


static fgg__buffer_t field_names[FGG__MEDIA__PAIRS_MAX_V1] = {{"R-ID", 4}, {"R-VERSION", 9}, {"R-ACTIVE", 8}, {"R-DATE", 6},
                                                             {"R-TIME", 6}, {"PK-ID", 5}, {"FILE NAME", 9}, {"COMMENTS", 8}};


fgg__media_t *fgg__media;


int fgg__media__init (void)
{
	size_t i;
	size_t limit;

	fgg__media = (fgg__media_t *) malloc (sizeof (fgg__media_t));

	if (fgg__media == NULL)
	{
		return -10;
	}

	memset (fgg__media, '\0', sizeof (fgg__media_t));

	limit = sizeof (field_names) / sizeof (fgg__buffer_t);


	for (i = 0; i < limit; i++)
	{
		memcpy (fgg__media->field_names[i].data, &field_names[i], sizeof (fgg__buffer_t));
	}

	fgg__media->fields_max = FGG__MEDIA__PAIRS_MAX_V1;

	return 0;
}






#endif
 