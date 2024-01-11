#include "agent.h"


int agent__private__read_alarm_status (agent_t *agent, int md)
{

	if ((md < 0) || (md >= agent->machine_count))
	{
		return -1000;
	}

	agent->machine[md].alarm_status_valid = 1;
	agent->machine[md].alarm_status = 0;
	
	return 0;

}