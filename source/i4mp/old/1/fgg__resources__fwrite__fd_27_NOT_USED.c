#include "fgg__resources.h"
#include "fgg__rm.h"
#include "fggr.h"
#include "fgg__rmw_ie.h"
#include "fgg__fp.h"
#include "fgg__fpw_ie.h"
#include "fgg__po__private.h"
#include "fgg__po.h"
#include "fgg__jo.h"


static char *fn = {"fgg__resources__fwrite__fd_27"};



static int fgg__resources__fwrite__fd_27___helper (unsigned long *index, unsigned long index_len, unsigned long *offset, utils__sdb_t *sdb)
{
	int rc;
	unsigned long index_tmp;
	unsigned long i;
	unsigned long j;
	int exit;
	char *p;
	char *p_2;
	int len_tmp_tmp;


	/* se non c'e l'utente esco */
	exit = 0;
	index_tmp = FGG__PO__FIELD__FK_USERS__PK_ID - FGGR__PRIVATE_FIELDS_MAX;
	for (j = 0; (j < sdb->pair_count) && (exit == 0); j++)
	{
		if (sdb->name_len[j] == fgg__po->module.names_map[index_tmp].form_field_name_len)
		{
			rc = memcmp(sdb->name[j], fgg__po->module.names_map[index_tmp].form_field_name, sdb->name_len[j]);
			if (rc == 0)
			{
				exit = 1;
			}
		}
	}

	if (exit == 0)
	{
		return -10;
	}

	/* cerco quelli richiesti */
	for (i = 0; i < index_len; i++)
	{
		index_tmp = offset[i] - FGGR__PRIVATE_FIELDS_MAX;

		exit = 0;

		for (j = 0; (j < sdb->pair_count) && (exit == 0); j++)
		{
			if (sdb->name_len[j] == fgg__po->module.names_map[index_tmp].form_field_name_len)
			{
				rc = memcmp(sdb->name[j], fgg__po->module.names_map[index_tmp].form_field_name, sdb->name_len[j]);
				if (rc == 0)
				{
					index[i] = j;
					exit = 1;
				}
			}
		}

		if (exit == 0)
		{
			return -20;
		}
	}


	/*cerco il primo spazio e tronco.  TRONCO I PK_ID VALUE   ESEMPIO:  value[0] = "3 - ENRICO MIGLIORE"    DIVENTA  value[0] = "3"  (IN REALTA' ACCORCIA SOLO LA LEN)  */
	for (i = 0; i < index_len; i++)
	{
		switch (offset[i])
		{

		case FGG__PO__FIELD__FK_USERS__PK_ID:        
		case FGG__PO__FIELD__FK_CUSTOMERS__PK_ID: 
		case FGG__PO__FIELD__FK_FP__PK_ID:        
		case FGG__PO__FIELD__FK_RM__PK_ID: 
		case FGG__PO__FIELD__FK_MACHINE__PK_ID:        
		case FGG__PO__FIELD__FK_PROGRAMS__PK_ID: 
		case FGG__PO__FIELD__FK_RMW__PK_ID:        

			p = sdb->value[index[i]]; 
			len_tmp_tmp = strlen(FGG__FORM_FIELD_SEPARATOR);
			p_2 = utils__libc__strstr(sdb->value[index[i]], sdb->value_len[index[i]],  FGG__FORM_FIELD_SEPARATOR, FGG__FORM_FIELD_SEPARATOR_LEN); 
			if (p_2 == NULL)
			{
				utils__printf(UTILS__ERROR, fn, -30, "utils__libc__strstr() returned NULL");
				return -30;
			}
			sdb->value_len[index[i]] = p_2 - p;
			break;

		}
	}

	return 0;

}


#define FK_USERS__PK_ID                          0
#define FK_CUSTOMERS__PK_ID                      1
#define FK_FP__PK_ID                             2
#define FK_RM__PK_ID                             3
#define JOB_STATUS                               4
#define CONNECTION_STATUS                        5
#define PARTS_TO_PRODUCE                         6                 
#define CYCLE_TIME                               7                       
#define PART_LENGTH                              8                      
#define RAW_PART_LENGTH                          9             
#define EXCERPT_LENGTH                          10                 
#define INTERNAL_JOB_NUMBER                     11             
#define CUSTOMER_ORDER                          12                
#define CUSTOMER_JOB                            13                
#define CUSTOMER_ORDER_DATE                     14              
#define CYCLE_TIME_READ_IN_MACHINE              15       
#define FK_RMW__PK_ID                           16                


int fgg__resources__fwrite__fd_27(utils__sdb_t *data_sdb)
{
	/*
	* E' la funziona che crea un odp
	*/
	int rc;
	unsigned long id;
	unsigned long year;
	unsigned long index[FGG__CONFIG__SDB_FIELDS_MAX];
	unsigned long offset[FGG__CONFIG__SDB_FIELDS_MAX];
	char tmp_buf_value[64];
	unsigned long tmp_buf_value_len;
	unsigned long tmp_index;
	char *p;
	char *p_2;
	unsigned long id_commessa;
	unsigned long year_commessa;
	unsigned long tmp_len;	
	unsigned long tmp_buf_name_len;
	char tmp_buf_name[64];


	if (data_sdb == NULL)
	{
		utils__printf(UTILS__ERROR, fn, -10, "data_sdb == NULL");
		return -10;
	}
                        
	offset[FK_USERS__PK_ID] = FGG__PO__FIELD__FK_USERS__PK_ID;                   
	offset[FK_CUSTOMERS__PK_ID] = FGG__PO__FIELD__FK_CUSTOMERS__PK_ID;               
	offset[FK_FP__PK_ID] = FGG__PO__FIELD__FK_FP__PK_ID;                      
	offset[FK_RM__PK_ID] = FGG__PO__FIELD__FK_RM__PK_ID;                                     
	offset[JOB_STATUS] = FGG__PO__FIELD__JOB_STATUS;                        
	offset[CONNECTION_STATUS] = FGG__PO__FIELD__CONNECTION_STATUS;                 
	offset[PARTS_TO_PRODUCE] = FGG__PO__FIELD__PARTS_TO_PRODUCE;                  
	offset[CYCLE_TIME] = FGG__PO__FIELD__CYCLE_TIME;                        
	offset[PART_LENGTH] = FGG__PO__FIELD__PART_LENGTH;                       
	offset[RAW_PART_LENGTH] = FGG__PO__FIELD__RAW_PART_LENGTH;                   
	offset[EXCERPT_LENGTH] = FGG__PO__FIELD__EXCERPT_LENGTH;                                                
	offset[INTERNAL_JOB_NUMBER] = FGG__PO__FIELD__INTERNAL_JOB_NUMBER;               
	offset[CUSTOMER_ORDER] = FGG__PO__FIELD__CUSTOMER_ORDER;                    
	offset[CUSTOMER_JOB] = FGG__PO__FIELD__CUSTOMER_JOB;                      
	offset[CUSTOMER_ORDER_DATE] = FGG__PO__FIELD__CUSTOMER_ORDER_DATE;               
	offset[CYCLE_TIME_READ_IN_MACHINE] = FGG__PO__FIELD__CYCLE_TIME_READ_IN_MACHINE;        
	offset[FK_RMW__PK_ID] = FGG__PO__FIELD__FK_RMW__PK_ID;                     

	rc = fgg__resources__fwrite__fd_27___helper (index, 17, offset, data_sdb);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -180, "fgg__resources__fwrite__fd_24___helper() returned %d", rc);
		return -180;
	}
	
	rc = fgg__po__make_new_po_id_and_year(&year, &id);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -120, "fgg__po__make_new_job_id_and_year() returned %d", rc);
		return -120;
	}

	rc = fgg__po__sdb__insert_po_into_po(id, year, data_sdb);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -150, "fgg__po__db__insert_job_into_jobs() returned %d - id %d - year %d", rc, id, year);
		return -150;
	}


	//ROW 1 .. ROW 16 row_to_update nel sdb delle JOB
	rc = utils__sdb__clear_sdb (&fgg__resources.data);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -160, "utils__sdb__clear_sdb() returned %d", rc);
		return -160;
	}


	

	tmp_index = FGG__PO__FIELD__FK_USERS__PK_ID - FGGR__PRIVATE_FIELDS_MAX;

	rc = utils__sdb__write_pair_to_sdb(&fgg__resources.data, fgg__po->module.names_map[tmp_index].form_field_name, fgg__po->module.names_map[tmp_index].form_field_name_len, data_sdb->value[index[FK_USERS__PK_ID]], data_sdb->value_len[index[FK_USERS__PK_ID]], UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -170, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -170;
	}


	p = data_sdb->value[index[FK_FP__PK_ID]];
	p_2 = utils__libc__strnchr(data_sdb->value[index[FK_FP__PK_ID]], data_sdb->value_len[index[FK_FP__PK_ID]], '$');//Finished product id  $ ROW x
	if (p_2 == NULL)
	{
		utils__printf(UTILS__ERROR, fn, -90, "utils__libc__strnchr() returned NULL");
		return -90;
	}
	tmp_len = data_sdb->value_len[index[FK_FP__PK_ID]];
	data_sdb->value_len[index[FK_FP__PK_ID]] = p_2 - p;

	tmp_len = tmp_len - data_sdb->value_len[index[FK_FP__PK_ID]] - 1;
	p_2++;
	tmp_buf_name_len = sprintf(tmp_buf_name,"%.*s",tmp_len, p_2 );
	tmp_buf_value_len = sprintf(tmp_buf_value, "%d-%d" ,id, year); //odp

	rc = utils__sdb__write_pair_to_sdb(&fgg__resources.data, tmp_buf_name, tmp_buf_name_len, tmp_buf_value, tmp_buf_value_len, UTILS__SDB__UTF_8__ENCODING);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -180, "utils__sdb__write_pair_to_sdb() returned %d", rc);
		return -180;
	}
	

	p = data_sdb->value[index[INTERNAL_JOB_NUMBER]];
	p_2 = utils__libc__strnchr(data_sdb->value[2], data_sdb->value_len[2], '-'); //id-year commessa interna
	if (p_2 == NULL)
	{
		utils__printf(UTILS__ERROR, fn, -60, "utils__libc__strnchr() returned NULL");
		return -60;
	}

	tmp_len = p_2 - p;

	rc = utils__libc__atoul (data_sdb->value[index[INTERNAL_JOB_NUMBER]], tmp_len, &id_commessa);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -70, "utils__libc__atoul() returned %d", rc);
		return -70;
	}

	p_2++;
	tmp_len = data_sdb->value_len[index[INTERNAL_JOB_NUMBER]] - tmp_len - 1;
	rc = utils__libc__atoul (data_sdb->value[2], tmp_len, &year_commessa);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -70, "utils__libc__atoul() returned %d", rc);
		return -70;
	}


	rc = fgg__jo__sdb__update_row_jo  (id_commessa, year_commessa, &fgg__resources.data, SDB__DEFAULT_READ_LANG);
	if (rc != 0)
	{
		utils__printf(UTILS__ERROR, fn, -190, "fgg__jo__sdb__update_row_jo() returned %d", rc);
		return -190;
	}




	return 0;
}

