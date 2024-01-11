#include "utils__time.h"


#define UTILS__TIME__LOCAL_BUFFER_SIZE    32

/*
 *  size_t number;
 *  size_t year;
 *  size_t month;
 *  size_t day;
 *  int rc;
 *
 *  rc = utils__time__get_integer_date (&number, &year, &month, &day);
 *
 *
 */

int utils__time__get_integer_date (size_t *number, size_t *year, size_t *month, size_t *day)
{
	time_t current_time;
	struct tm *local_time;
	char buffer[UTILS__TIME__LOCAL_BUFFER_SIZE];
	size_t buffer_len;
	int n;
	int y;
	int m;
	int d;


	if ((number == NULL) || (year == NULL) || (month == NULL) || (day == NULL))
	{
		return -10;
	}

	time(&current_time);

	local_time = localtime(&current_time);

	/*
	 * Year
	 */
	buffer_len = strftime (buffer, sizeof(buffer), "%Y", local_time);
	
	y = atoi(buffer);
	if (y >= 0)
	{
		*year = y;
	}
	else
	{
		return -20;
	}


	/*
	 * Month
	 */
	buffer_len = strftime (buffer, sizeof(buffer), "%m", local_time);
	
	m = atoi(buffer);
	if (m >= 0)
	{
		*month = m;
	}
	else
	{
		return -30;
	}

	/*
	 * Day
	 */
	buffer_len = strftime (buffer, sizeof(buffer), "%d", local_time);
	
	d = atoi(buffer);
	if (d >= 0)
	{
		*day = d;
	}
	else
	{
		return -40;
	}


    /*
	 * ISO:  "20170421"
	 */
	buffer_len = strftime (buffer, sizeof(buffer), "%Y%m%d", local_time);

	n = atoi(buffer);
	if (n >= 0)
	{
		*number = n;
	}
	else
	{
		return -50;
	}

	return 0;
}



