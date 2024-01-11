#include "fgg__po.h"
#include "fgg__rm.h"
#include "fgg__rmw_ie.h"
#include "fgg__rmw_ie__private.h"
#include "fgg__fpw_ie__private.h"
#include "fgg__fpw_ie.h"


/*
* Insert data into the databse from a shipping document
*/

 
static char *fn = "fgg__fpw_ie__1__positive_adjustment__production()";




int fgg__fpw_ie__1__positive_adjustment__production(utils__sdb_t *sdb, utils__sdb_t *sdb_out, unsigned long *id_out, unsigned long *year_out,unsigned long fk__jobs__pk_id, unsigned long fk__jobs__pk_year, unsigned long bag_count, unsigned long parts_in_a_bag, unsigned long lang)
{

	int rc;
	unsigned long id;
	unsigned long tid;
	unsigned long year;
	int active;
	unsigned long fk__rm__pk_id;
	double part_length;
	double cut_length;
	double total_length;
	double base_area;
	double specific_weight;
	double volume;
	double total_weight;
	//unsigned long bag_count;
	unsigned long part_count;
	//unsigned long parts_in_a_bag;
	int snapshot;
	unsigned long i;
	int exit;
	char *tmp_name;
	unsigned long tmp_name_len;
	unsigned long tmp_len;
	char tmp_data[64];


	if (sdb_out == NULL)
	{
		utils__printf(UTILS__ERROR, fn, -90, "sdb_out NULL");
		return -90;
	}

	utils__sdb__clear_sdb (sdb_out);

	rc = fgg__fpw_ie__make_new_id_year_tid (&year, &id, &tid);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -40, "fgg__fpw_ie__make_new_id_year_tid() returned %d - year %d - id %d - tid %d", rc, year, id, tid);
		return -40;
	}


	*id_out = id;
	*year_out = year;

	//faccio la select della jobs per prendermi il fp e dopo mi servira' per calcolare il peso!
	rc = fgg__po__sdb__select_po_from_po (fk__jobs__pk_id, fk__jobs__pk_year, &fgg__fpw_ie->sdb, &active, 0, lang);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -90, "fgg__po__db__select_job_from_jobs() returned %d", rc);
		return -90;
	}

	/* aggiungo in append al sdb che mi viene passato la FGG__FPW_IE__FIELD__RK_FP_PK_ID dell FP, perche' da javascript non arriva, ma e' frutto di una selec di una JOB */
	//N5
	tmp_name = fgg__fpw_ie->module.names_map[FGG__FPW_IE__FIELD__RK_FP_PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name;
	tmp_name_len = fgg__fpw_ie->module.names_map[FGG__FPW_IE__FIELD__RK_FP_PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name_len;

	rc = utils__sdb__write_pair_to_sdb (sdb, tmp_name, tmp_name_len, fgg__fpw_ie->sdb.value[FGG__PO__FIELD__FK_FP__PK_ID], fgg__fpw_ie->sdb.value_len[FGG__PO__FIELD__FK_FP__PK_ID], UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}

	tmp_name = fgg__fpw_ie->module.names_map[FGG__FPW_IE__FIELD__FK_FPW_IET_PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name;
	tmp_name_len = fgg__fpw_ie->module.names_map[FGG__FPW_IE__FIELD__FK_FPW_IET_PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name_len;

	rc = utils__sdb__write_pair_to_sdb (sdb, tmp_name, tmp_name_len, "1" ,1 , UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}
	
	active = FGGR__RECORD_ACTIVE;
	
	rc = fgg__fpw_ie__sdb__insert_inventory_entry_into_fpw_ie(id, year, tid, sdb, active);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -180, "fgg__fpw_ie__sdb__insert_inventory_entry_into_fpw_ie() returned %d - year %d - id %d - tid %d - values_max %d", rc, year, id, tid, active);
		return -180;
	}


	/*
	 * Calculate the weight     Perche' non faccio la select dell fp visto che ho l'id e prendo il peso dell'fp?
	 */
	
	part_count = bag_count * parts_in_a_bag;

	
	rc = utils__libc__atoul (fgg__fpw_ie->sdb.value[FGG__PO__FIELD__FK_RM__PK_ID], fgg__fpw_ie->sdb.value_len[FGG__PO__FIELD__FK_RM__PK_ID], &fk__rm__pk_id);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -210, "utils__libc__atoul() returned %d", rc);
		return -210;
	}



	tmp_name = fgg__rmw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_RMW__PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name;
	tmp_name_len = fgg__rmw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_RMW__PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name_len;
	rc = utils__sdb__write_pair_to_sdb (sdb_out, tmp_name, tmp_name_len, fgg__fpw_ie->sdb.value[FGG__PO__FIELD__FK_RMW__PK_ID], fgg__fpw_ie->sdb.value_len[FGG__PO__FIELD__FK_RMW__PK_ID], UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}

	rc = utils__libc__atod (fgg__fpw_ie->sdb.value[FGG__PO__FIELD__PART_LENGTH], fgg__fpw_ie->sdb.value_len[FGG__PO__FIELD__PART_LENGTH],&part_length);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -230, "utils__libc__atod() returned %d", rc);
		return -230;
	}

	rc = utils__libc__atod (fgg__fpw_ie->sdb.value[FGG__PO__FIELD__RAW_PART_LENGTH], fgg__fpw_ie->sdb.value_len[FGG__PO__FIELD__RAW_PART_LENGTH],&cut_length);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -240, "utils__libc__atod() returned %d", rc);
		return -240;
	}

	total_length = part_length + cut_length;

	rc = fgg__rm__sdb__select_rm_from_rm (fk__rm__pk_id, &fgg__fpw_ie->sdb, &active, lang);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -250, "fgg__rm__sdb__select_rm_from_rm() returned %d", rc);
		return -250;
	}
	
	
	rc = utils__libc__atod (fgg__fpw_ie->sdb.value[FGG__RM__FIELD__BASE_AREA], fgg__fpw_ie->sdb.value_len[FGG__RM__FIELD__BASE_AREA],&base_area);    /* BASE AREA is mm^2 */
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -260, "utils__libc__atod() returned %d", rc);
		return -260;
	}

	rc = utils__libc__atod (fgg__fpw_ie->sdb.value[FGG__RM__FIELD__SPECIFIC_WEIGHT], fgg__fpw_ie->sdb.value_len[FGG__RM__FIELD__SPECIFIC_WEIGHT],&specific_weight);   /* SPECIFIC WEIGHT is g/cm^3 */
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -270, "utils__libc__atod() returned %d", rc);
		return -270;
	}


	volume = (base_area * total_length) / 1000000;     

	total_weight = volume * specific_weight;

	total_weight = total_weight * part_count;

	tmp_len = sprintf (tmp_data, "%lu", fk__rm__pk_id);
	tmp_name = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_RM__PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name;
	tmp_name_len = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_RM__PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name_len;
	rc = utils__sdb__write_pair_to_sdb (sdb_out, tmp_name, tmp_name_len, tmp_data, tmp_len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}

	
	tmp_len = sprintf (tmp_data, "%f", total_weight);
	tmp_name = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__WEIGHT - FGGR__PRIVATE_FIELDS_MAX].form_field_name;
	tmp_name_len = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__WEIGHT - FGGR__PRIVATE_FIELDS_MAX].form_field_name_len;
	rc = utils__sdb__write_pair_to_sdb (sdb_out, tmp_name, tmp_name_len, tmp_data, tmp_len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}


	tmp_len = sprintf (tmp_data, "%lu", fk__jobs__pk_id);
	tmp_name = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_JOBS__PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name;
	tmp_name_len = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_JOBS__PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name_len;
	rc = utils__sdb__write_pair_to_sdb (sdb_out, tmp_name, tmp_name_len, tmp_data, tmp_len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}


	tmp_len = sprintf (tmp_data, "%lu", fk__jobs__pk_year);
	tmp_name = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_JOBS__PK_YEAR - FGGR__PRIVATE_FIELDS_MAX].form_field_name;
	tmp_name_len = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_JOBS__PK_YEAR - FGGR__PRIVATE_FIELDS_MAX].form_field_name_len;
	rc = utils__sdb__write_pair_to_sdb (sdb_out, tmp_name, tmp_name_len, tmp_data, tmp_len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}


	tmp_name = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_RMW_IET__PK_ID - FGGR__PRIVATE_FIELDS_MAX].form_field_name;
	tmp_name_len = fgg__fpw_ie->module.names_map[FGG__RMW_IE__FIELD__FK_JOBS__PK_YEAR - FGGR__PRIVATE_FIELDS_MAX].form_field_name_len;
	rc = utils__sdb__write_pair_to_sdb (sdb_out, tmp_name, tmp_name_len, "3", 1, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}

	return 0;
}






















#if 0
int fgg__fpw_ie__1__positive_adjustment__production_working (fgg__fpw_ie__data_in_t *data_in, fgg__fpw_ie__data_out_t *data_out)
{
	int rc;
	unsigned long id;
	unsigned long tid;
	unsigned long year;
	unsigned long active;

	unsigned long fk__jobs__pk_id;
	unsigned long fk__rm__pk_id;
	unsigned long fk__jobs__pk_year;
	double part_length;
	double cut_length;
	double total_length;
	double base_area;
	double specific_weight;
	double volume;
	double total_weight;
	unsigned long bag_count;
	unsigned long part_count;
	unsigned long parts_in_a_bag;


#if 0
	rc = utils__sdb__clear_sdb (&fgg__fpw_ie->tmp_1_data);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -10, "utils__sdb__clear_sdb() returned %d", rc);
		return -10;
	}


	/*
	 * FK-USER - Offset = 0
	 */
	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__FK_USERS_PK_ID].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__FK_USERS_PK_ID].len, data_in->user_id.data, data_in->user_id.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -20, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -20;
	}

	/*
	 * Offset = 1
	 */
	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__FK_FPW_IET_PK_ID].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__FK_FPW_IET_PK_ID].len,  "1", 1, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -30, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -30;
	}

	rc = fgg__fpw_ie__make_new_id_year_tid (&year, &id, &tid);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -40, "fgg__fpw_ie__make_new_id_year_tid() returned %d - year %d - id %d - tid %d", rc, year, id, tid);
		return -40;
	}

	data_out->fp_ie_id = id;
	data_out->fp_ie_year = year;


	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__FK_JOBS_PK_ID].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__FK_JOBS_PK_ID].len, data_in->jobs_id.data, data_in->jobs_id.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -50, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -50;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__FK_JOBS_PK_YEAR].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__FK_JOBS_PK_YEAR].len,  data_in->jobs_year.data, data_in->jobs_year.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -60, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -60;
	}



	//faccio la select della jobs per prendermi il fp e dopo mi servira' per calcolare il peso!


	rc = utils__libc__atoul (data_in->jobs_id.data, data_in->jobs_id.len, &fk__jobs__pk_id);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -70, "utils__libc__atoul() returned %d - fk__jobs__pk_id %d", rc, fk__jobs__pk_id);
		return -70;
	}


	rc = utils__libc__atoul (data_in->jobs_year.data, data_in->jobs_year.len, &fk__jobs__pk_year);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -80, "utils__libc__atoul() returned %d - fk__jobs__pk_year %d", rc, fk__jobs__pk_year);
		return -80;
	}

	rc = fgg__po__db__select_job_from_jobs (fk__jobs__pk_id, fk__jobs__pk_year, &fgg__fpw_ie->data, &active, 0, NULL ,0);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -90, "fgg__po__db__select_job_from_jobs() returned %d", rc);
		return -90;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__RK_FP_PK_ID].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__RK_FP_PK_ID].len, fgg__fpw_ie->data.value[FGG__PO__FK_FP__PK_ID__V1], fgg__fpw_ie->data.value_len[FGG__PO__FK_FP__PK_ID__V1], UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -100, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -100;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__BAGS_QUANTITY].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__BAGS_QUANTITY].len, data_in->bags_quantity.data, data_in->bags_quantity.len, UTILS__SDB__UTF_8__ENCODING);	
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -110, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -110;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__QUANTITY_PER_BAG].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__QUANTITY_PER_BAG].len, data_in->quantity_per_bag.data, data_in->quantity_per_bag.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -120, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -120;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__REFERENCE_1].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__REFERENCE_1].len, data_in->reference_1.data, data_in->reference_1.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -130, "fgutils__sdb__write_pair_to_sdbg__jobs__db__select_job_from_jobs() returned %d", rc);
		return -130;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__REFERENCE_2].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__REFERENCE_2].len, data_in->reference_2.data, data_in->reference_2.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -140, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -140;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__REFERENCE_3].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__REFERENCE_3].len, data_in->reference_3.data, data_in->reference_3.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -150, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -150;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__REFERENCE_4].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__REFERENCE_4].len, data_in->reference_4.data, data_in->reference_4.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -160, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -160;
	}

	rc = utils__sdb__write_pair_to_sdb (&fgg__fpw_ie->tmp_1_data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__NOTE].data, fgg__fpw_ie->field_names[FGG__FPW_IE__FIELD__NOTE].len, data_in->note.data, data_in->note.len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -170, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -170;
	}

	/*
	* values_max = 12;
	*/
	
	active = FGGR__RECORD_ACTIVE;
	rc = fgg__fpw_ie__sdb__insert_inventory_entry_into_fpw_ie (id, year, tid, &fgg__fpw_ie->tmp_1_data, acrive);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -180, "fgg__fpw_ie__db__insert_inventory_entry_into_fpw_ie() returned %d - year %d - id %d - tid %d - values_max %d", rc, year, id, tid, active);
		return -180;
	}


	/*
	 * Calculate the weight
	 */
	


	rc = utils__libc__atoul (data_in->bags_quantity.data, data_in->bags_quantity.len, &bag_count);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -190, "utils__libc__atoul() returned %d", rc);
		return -190;
	}

	rc = utils__libc__atoul (data_in->quantity_per_bag.data, data_in->quantity_per_bag.len, &parts_in_a_bag);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -200, "utils__libc__atoul() returned %d", rc);
		return -200;
	}

	part_count = bag_count * parts_in_a_bag;

	
	rc = utils__libc__atoul (fgg__fpw_ie->data.value[FGG__PO__FK_RM__PK_ID__V1], fgg__fpw_ie->data.value_len[FGG__PO__FK_RM__PK_ID__V1], &fk__rm__pk_id);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -210, "utils__libc__atoul() returned %d", rc);
		return -210;
	}

	
	rc = utils__libc__copy_buffer (data_out->rmw_id.data, sizeof(data_out->rmw_id.data), &data_out->rmw_id.len, fgg__fpw_ie->data.value[FGG__PO__FK_RMW__PK_ID__V1], fgg__fpw_ie->data.value_len[FGG__PO__FK_RMW__PK_ID__V1]);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -220, "utils__libc__copy_buffer() returned %d", rc);
		return -220;
	}

	rc = utils__libc__atod (fgg__fpw_ie->data.value[FGG__PO__PART_LENGTH__V1], fgg__fpw_ie->data.value_len[FGG__PO__PART_LENGTH__V1],&part_length);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -230, "utils__libc__atod() returned %d", rc);
		return -230;
	}

	rc = utils__libc__atod (fgg__fpw_ie->data.value[FGG__PO__RAW_PART_LENGTH__V1], fgg__fpw_ie->data.value_len[FGG__PO__RAW_PART_LENGTH__V1],&cut_length);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -240, "utils__libc__atod() returned %d", rc);
		return -240;
	}

	total_length = part_length + cut_length;

	rc = fgg__rm__sdb__select_rm_from_rm (fk__rm__pk_id, &fgg__fpw_ie->data, &active);
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -250, "fgg__rm__sdb__select_rm_from_rm() returned %d", rc);
		return -250;
	}
	
	
	rc = utils__libc__atod (fgg__fpw_ie->data.value[FGG__RM__FIELD__BASE_AREA], fgg__fpw_ie->data.value_len[FGG__RM__FIELD__BASE_AREA],&base_area);    /* BASE AREA is mm^2 */
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -260, "utils__libc__atod() returned %d", rc);
		return -260;
	}

	rc = utils__libc__atod (fgg__fpw_ie->data.value[FGG__RM__FIELD__SPECIFIC_WEIGHT], fgg__fpw_ie->data.value_len[FGG__RM__FIELD__SPECIFIC_WEIGHT],&specific_weight);   /* SPECIFIC WEIGHT is g/cm^3 */
	if (rc != 0)
	{
		utils__printf(FGGR__ERROR, fn, -270, "utils__libc__atod() returned %d", rc);
		return -270;
	}


	volume = (base_area * total_length) / 1000000;     

	total_weight = volume * specific_weight;

	total_weight = total_weight * part_count;

	data_out->rm_id.len = sprintf (data_out->rm_id.data, "%lu", fk__rm__pk_id);
	data_out->weight.len = sprintf (data_out->weight.data, "%f", total_weight);
	data_out->jobs_id.len = sprintf (data_out->jobs_id.data, "%lu", fk__jobs__pk_id);
	data_out->jobs_year.len = sprintf (data_out->jobs_year.data, "%lu", fk__jobs__pk_year);

#endif
	return 0;
}
#endif










