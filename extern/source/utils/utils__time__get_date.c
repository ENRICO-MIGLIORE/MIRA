#include "utils__time.h"


int utils__time__get_date (char *year_buffer, size_t year_buffer_size, size_t *year_buffer_len, char *month_buffer, size_t month_buffer_size, size_t *month_buffer_len, char *day_buffer, size_t day_buffer_size, size_t *day_buffer_len)
{
	time_t current_time;
	struct tm *local_time;


	if ((year_buffer == NULL) || (month_buffer == NULL) || (day_buffer == NULL))
	{
		return -10;
	}

	if ((year_buffer_len == NULL) || (month_buffer_len == NULL) || (day_buffer_len == NULL))
	{
		return -20;
	}

	if ((year_buffer_size < UTILS__TIME__BUFFER_SIZE ) || (month_buffer_size < UTILS__TIME__BUFFER_SIZE) || (day_buffer_size < UTILS__TIME__BUFFER_SIZE))
	{
		return -30;
	}


	time(&current_time);

	local_time = localtime(&current_time);


	/*
	 * Year
	 */
	*year_buffer_len = strftime (year_buffer, year_buffer_size, "%Y", local_time);



	/*
	 * Month
	 */
	*month_buffer_len = strftime (month_buffer, month_buffer_size, "%m", local_time);



	/*
	 * Day
	 */
	*day_buffer_len = strftime (day_buffer, day_buffer_size, "%d", local_time);


	return 0;

}


