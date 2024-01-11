#include "okuma_mt__private.h"



int okuma_mt__private__read_alarm_status__real (int md)
{

	int rc;
	size_t len;
	char* p;

	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}

	om->machine[md].alarm_status_valid = 0;


	if (om->machine[md].data_stream_valid != 1)
	{
		return -200;
	}


	p = "EmergencyStop";
	len = strlen(p);

	rc = utils__xml__extract_inner_xml(om->machine[md].receive_buffer, om->machine[md].receive_buffer_len, p, len, om->machine[md].alarm_utf_8, sizeof(om->machine[md].alarm_utf_8), &om->machine[md].alarm_utf_8_len);
	if (rc != 0)
	{
		return -300;
	}



	/*
	 * emergency button: 
	 *                    if we read "ARMED" no alarm in progress
	 *                    if we read "TRIGGERED" alarm in progress
	 */	

	p = "ARMED";
	len = strlen(p);

	if (len == om->machine[md].alarm_utf_8_len)
	{
		rc = memcmp(om->machine[md].alarm_utf_8, p, om->machine[md].alarm_utf_8_len);
		if (rc == 0)
		{
			om->machine[md].alarm_status_valid = 1;
			om->machine[md].alarm_status = 0;
			return 0;
		}
	}


	p = "TRIGGERED";
	len = strlen(p);

	if (len == om->machine[md].alarm_utf_8_len)
	{
		rc = memcmp(om->machine[md].alarm_utf_8, p, om->machine[md].alarm_utf_8_len);
		if (rc == 0)
		{
			om->machine[md].alarm_status_valid = 1;
			om->machine[md].alarm_status = 1;
			return 0;
		}
	}

	return 0;

}