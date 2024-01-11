#include "fggr.h"
#include "fgg__programs.h"


static char *fn = "fgg__programs__init()";


/* 04-09-2020   MODULO COMMESSE controllato e messo in fase con la SDB2 */


fgg__programs_t *fgg__programs;

int fgg__programs__init (void)
{

	fgg__programs = (fgg__programs_t *) malloc(sizeof(fgg__programs_t));

	if (fgg__programs == NULL)
	{
		utils__printf__error(&fggr->pf, fn, -10, "malloc() error");
		return -10;
	}

	return 0;

}



