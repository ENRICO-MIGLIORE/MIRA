#include "../fgg__app.h"
#include "../fgg__jobs.h"
#include "../fgg__customers.h"
#include "../fgg__causals.h"
#include "../fgg__log.h"
#include "../fgg__materials.h"
#include "../fgg__parts.h"
#include "../fgg__programs.h"
#include "../fgg__storages_fp.h"
#include "../fgg__storages_rm.h"
#include "../fgg__warehouses_fp.h"
#include "../fgg__warehouses_rm.h"
#include "../fgg__shipping_addresses.h"
#include "../fgg__suppliers.h"
#include "../fgg__users.h"

#include "fgg__machine_1.h"

#include "../fgg.h"


int fgg__load (void)
{

	int rc;
	size_t len;
	fgg__app__config_t app_config;
	fgg__log__config_t log_config;
	fgg__jobs__config_t jobs_config;
	fgg__material__config_t materials_config;
	fgg__customer__config_t customers_config;
	fgg__supplier__config_t suppliers_config;
	fgg__user__config_t users_config;
	fgg__cnc__config_t cncs_config;	
	fgg__part__config_t parts_config;
	fgg__shipping_address__config_t shipping_address_config;
	fgg__warehouse_fp__config_t warehouse_fp_config;
	fgg__warehouse_rm__config_t warehouse_rm_config;
	fgg__causal__config_t causal_config;
	fgg__storage_fp__config_t storages_fp_config;
	fgg__storage_rm__config_t storages_rm_config;
	fgg__program__config_t programs_config;
	fgg__machine_1__config_t machine_1__config;

	fgg__buffer_t app_error;

	/*
	 * APP
	 */
	app_config.pluto = 0;
	rc = fgg__app__config (&app_config);
	if (rc != 0)
	{
		return -10;
	}

	/*
	 * LOG
	 */
	memcpy (&log_config.dir_path, &fgg__app->log_file_path, sizeof(fgg__buffer_t));

	rc |= fgg__log__config (&log_config);


	/*
	 * JOBS
	 */
	memcpy (&jobs_config.dir_path, &fgg__app->db_path, sizeof(fgg__buffer_t));

	len = strlen ("jobs");
	memcpy (&jobs_config.dir_path.data[jobs_config.dir_path.len], "jobs", len);
	jobs_config.dir_path.len += len;
	rc |= fgg__jobs__config (&jobs_config);
	

	/*
	* PARTS
	*/
	memcpy (parts_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	parts_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&parts_config.dir_path.data[parts_config.dir_path.len], "parts", 5);
	parts_config.dir_path.len += 5;
	rc |= fgg__parts__config (&parts_config);


	/*
	* MATERIALS
	*/
	memcpy (materials_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	materials_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&materials_config.dir_path.data[materials_config.dir_path.len], "materials", 9);
	materials_config.dir_path.len += 9;

	rc |= fgg__materials__config (&materials_config);


	/*
	* CUSTOMERS
	*/	
	memcpy (customers_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	customers_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&customers_config.dir_path.data[customers_config.dir_path.len], "customers", 9);
	customers_config.dir_path.len += 9;

	rc |= fgg__customers__config (&customers_config);

	/*
	* CAUSALS
	*/	
	memcpy (causal_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	causal_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&causal_config.dir_path.data[causal_config.dir_path.len], "causals", 7);
	causal_config.dir_path.len += 7;
	rc |= fgg__causals__config (&causal_config);

	/*
	 * SUPPLIERS
	 */	
	memcpy (suppliers_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	suppliers_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&suppliers_config.dir_path.data[suppliers_config.dir_path.len], "suppliers", 9);
	suppliers_config.dir_path.len += 9;
	rc |= fgg__suppliers__config (&suppliers_config);


	/*
	 * USERS
	 */
	memcpy (users_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	users_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&users_config.dir_path.data[users_config.dir_path.len], "users", 5);
	users_config.dir_path.len += 5;
	
	rc |= fgg__users__config (&users_config);




	/*
	 * SHIPPING ADDRESS
	 */
	memcpy (shipping_address_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	shipping_address_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&shipping_address_config.dir_path.data[shipping_address_config.dir_path.len], "shipping-addresses", 18);
	shipping_address_config.dir_path.len += 18;
	rc |= fgg__shipping_addresses__config (&shipping_address_config);

	/*
	 * STORAGES-FP
	 */
	memcpy (storages_fp_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	storages_fp_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&storages_fp_config.dir_path.data[storages_fp_config.dir_path.len], "storages-fp", 11);
	storages_fp_config.dir_path.len += 11;
	rc |= fgg__storages_fp__config (&storages_fp_config);

	/*
	 * STORAGES-RM
	 */
	memcpy (storages_rm_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	storages_rm_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&storages_rm_config.dir_path.data[storages_rm_config.dir_path.len], "storages-rm", 11);
	storages_rm_config.dir_path.len += 11;
	rc |= fgg__storages_rm__config (&storages_rm_config);

	/*
	 * WAREHOUSES-FP
	 */
	memcpy (warehouse_fp_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	warehouse_fp_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&warehouse_fp_config.dir_path.data[warehouse_fp_config.dir_path.len], "warehouses-fp", 13);
	warehouse_fp_config.dir_path.len += 13;
	rc |= fgg__warehouses_fp__config (&warehouse_fp_config);

	/*
	 * WAREHOUSES-RM
	 */
	memcpy (warehouse_rm_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	warehouse_rm_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&warehouse_rm_config.dir_path.data[warehouse_rm_config.dir_path.len], "warehouses-rm", 13);
	warehouse_rm_config.dir_path.len += 13;
	rc |= fgg__warehouses_rm__config (&warehouse_rm_config);

	/*
	 * HTML
	 */
	//fgg__util__copy_buffer (&html_config.dir_path, &fgg__app->html_site_path);
	//rc |= fgg__html__config (&html_config);

	/*
	 * CNC
	 */	
	memcpy (cncs_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	cncs_config.dir_path.len = fgg__app->db_path.len;
	memcpy (&cncs_config.dir_path.data[cncs_config.dir_path.len], "cncs", 4);
	cncs_config.dir_path.len += 4;
	rc |= fgg__machines__config (&cncs_config);


	/*
	 * PROGRAMS
	 */
	memcpy (programs_config.dir_path.data, fgg__app->db_path.data, fgg__app->db_path.len);
	programs_config.dir_path.len = fgg__app->db_path.len;

	len = strlen("programs");
	memcpy (&programs_config.dir_path.data[programs_config.dir_path.len], "programs", len);
	programs_config.dir_path.len += len;
	rc |= fgg__programs__config (&programs_config);


	if (rc != 0)
	{		
		//EK fgg__log__write (FGG__LOG__ERROR, &fgg_lang.app_error->word[FGG__LANG__APP__CONFIG_ERROR]);

		rc = fgg__util__strcpy_buffer (&app_error, "config() ended with an error");
		fgg__log__write (FGG__LOG__ERROR, &app_error);
		return  -10;
	}

	machine_1__config.dir_path.data[0] = '\0';
	machine_1__config.dir_path.len = 0;
    rc |= fgg__machine_1__config (&machine_1__config);

	return 0;
}


