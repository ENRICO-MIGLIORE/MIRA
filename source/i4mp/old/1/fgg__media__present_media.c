#include "fgg__media.h"


#if 0
int fgg__media__present_media (size_t presentation_mode, fgg__buffer_t *value, size_t pairs_max, fgg__buffer_t *presentation_buffer)
{

	size_t max_len;
	int len;

	if (pairs_max != fgg__media->fields_max)
	{
		return -10;
	}

	len = 0;

	if (presentation_mode == 1)
	{
		max_len = value[5].len + value[6].len + value[7].len + 6;
		if (max_len >= FGG__CONFIG__BUFFER_SIZE)
		{
			return -20;
		}

		len = sprintf (presentation_buffer->data, "%s***%s***%s", value[5].data, value[6].data, value[7].data);
	
	}
	

	if (len <= 0)
	{
		return -30;
	}

	presentation_buffer->len = (size_t) len;

    /*
	 * The presentation_buffer is a zero terminated string
	 */

	return 0;

}

#endif








