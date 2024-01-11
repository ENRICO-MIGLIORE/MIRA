//#include "..\fgg__cncs_open62541.h"
#include "carmelo__cncs.h"
#include "..\fggr.h"


carmelo__cncs_t *carmelo__cncs;


int carmelo__cncs__init  (void)
{
	int rc;
	int i;
	utils__sdb__config_t sdb_config;
    static char *fn = "carmelo__cncs__init()";


	carmelo__cncs = (carmelo__cncs_t *) malloc(sizeof(carmelo__cncs_t));

	if (carmelo__cncs == NULL)
	{
		utils__printf__error(&fggr->pf, fn, -10, "malloc() error");
		return -10;
	}

	memset (carmelo__cncs, '\0', sizeof (carmelo__cncs_t));



	for (i = 0; i < FGGR__CNCS__MACHINE_MAX; i++)
	{
		sdb_config.buffer = carmelo__cncs->machine[i].buffer;
		sdb_config.buffer_size = sizeof(carmelo__cncs->machine[i].buffer);
		sdb_config.name = carmelo__cncs->machine[i].name;
		sdb_config.name_len = carmelo__cncs->machine[i].name_len;
		sdb_config.value = carmelo__cncs->machine[i].value;
		sdb_config.value_len = carmelo__cncs->machine[i].value_len;
		sdb_config.encoding = carmelo__cncs->machine[i].encoding;
		sdb_config.fields_max = FGGR__CONFIG__SDB_FIELDS_MAX;

		rc = utils__sdb__config_sdb (&carmelo__cncs->machine[i].data, &sdb_config);
		if (rc != 0)
		{
			utils__printf__error(&fggr->pf, fn, -20, "utils__sdb__config_sdb() returned %d", rc);
			return -20;
		}

		sdb_config.buffer = carmelo__cncs->machine[i].buffer_value_cnc;
		sdb_config.buffer_size = sizeof(carmelo__cncs->machine[i].buffer_value_cnc);
		sdb_config.name = carmelo__cncs->machine[i].name_value_cnc;
		sdb_config.name_len = carmelo__cncs->machine[i].name_len_value_cnc;
		sdb_config.value = carmelo__cncs->machine[i].value_value_cnc;
		sdb_config.value_len = carmelo__cncs->machine[i].value_len_value_cnc;
		sdb_config.encoding = carmelo__cncs->machine[i].encoding_value_cnc;
		sdb_config.fields_max = FGGR__CONFIG__SDB_FIELDS_MAX;

		rc = utils__sdb__config_sdb (&carmelo__cncs->machine[i].data_value_cnc, &sdb_config);
		if (rc != 0)
		{
			utils__printf__error(&fggr->pf, fn, -30, "utils__sdb__config_sdb() returned %d", rc);
			return -30;
		}
	}
	
	return 0;
}






