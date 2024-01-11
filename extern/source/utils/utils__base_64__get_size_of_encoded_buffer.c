#include <stddef.h>
  
  
size_t utils__base_64__get_size_of_encoded_buffer (size_t source_len)
{
	size_t size;

	size = (size_t) (4 * ((source_len + 2) / 3));

	return size;
}

