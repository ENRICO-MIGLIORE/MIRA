#include "agent__fanuc_focas__private.h"


static const char* agent__fanuc_focas_name = "AGENT FANUC-FOCAS";
static const char* agent__fanuc_focas_version = "1.1";


agent__fanuc_focas_t *agent__fanuc_focas = NULL;


int agent__fanuc_focas__init (void)
{

	const char* fn;

	fn = "agent__fanuc_focas__init()";

	/*
	 * allocate the structure
	 */
	agent__fanuc_focas = (agent__fanuc_focas_t *) malloc(sizeof(agent__fanuc_focas_t));
	if (agent__fanuc_focas == NULL)
	{
		utils__printf__error(NULL, fn, -100, "malloc() error");
		return -100;
	}

	memset(agent__fanuc_focas, '\0', sizeof(agent__fanuc_focas_t));

	agent__fanuc_focas->name = agent__fanuc_focas_name;
	agent__fanuc_focas->version = agent__fanuc_focas_version;


	return 0;
}


