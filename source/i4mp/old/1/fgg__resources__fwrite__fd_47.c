#include "fgg__resources.h"
#include "fgg__rm.h"
#include "fggr.h"
#include "fgg__rmw_ie.h"
#include "fgg__fp.h"
#include "fgg__fpw_ie.h"
#include "fgg__po.h"
#include "fgg__jo.h"


static char *fn = {"fgg__resources__fwrite__fd_44"};

int fgg__resources__fwrite__fd_47 (utils__sdb_t *data_sdb)
{
	int rc;

	/*
	 * Prepara id&year di un odp che e' associato alla commessa
	 */
	if (data_sdb == NULL)
	{
		utils__printf(UTILS__ERROR, fn, -10, "data_sdb == NULL");
		return -10;
	}

	if (data_sdb->pair_count < 1)
	{
		utils__printf(UTILS__ERROR, fn, -20, "data_sdb->pair_count < 1, data_sdb->pair_count %d", data_sdb->pair_count);
		return -20;
	}

	rc = utils__sdb__clear_sdb (&fgg__resources.data); 
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -30, "utils__sdb__clear_sdb() returned %d", rc);
		return -30;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__resources.data, data_sdb->name[0], data_sdb->name_len[0], data_sdb->value[0], data_sdb->value_len[0], UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -40, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -40;
	}


	return 0;
}



#if 0
int fgg__resources__fwrite__fd_47 (utils__sdb_t *data_sdb)
{
	int rc;

	/*
	 * Prepara id&year di un odp che e' associato alla commessa
	 */
	if (data_sdb == NULL)
	{
		utils__printf(FGGR__ERROR, fn, -10, "data_sdb == NULL");
		return -10;
	}

	if (data_sdb->pair_count < 1)
	{
		utils__printf(FGGR__ERROR, fn, -20, "data_sdb->pair_count < 1, data_sdb->pair_count %d", data_sdb->pair_count);
		return -20;
	}

	rc = utils__sdb__clear_sdb (&fgg__resources.data); 
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -30, "utils__sdb__clear_sdb() returned %d", rc);
		return -30;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__resources.data, data_sdb->name[0], data_sdb->name_len[0], data_sdb->value[0], data_sdb->value_len[0], UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -40, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -40;
	}


	return 0;
}
#endif
