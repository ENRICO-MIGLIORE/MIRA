#include "fp.h"


                           
                 
					

/*
* Version 1
*/
static fggr__map_t  fp__map__version_1[] = {{"PK-ID", 5, FGGR__FIELD_DEFAULT_VALUE, FGGR__FIELD_DEFAULT_VALUE_LEN,   FGGR__INTERNAL_FIELD,  FP__FIELD__PK_ID}, 
                                            {"FK-USERS--PK-ID ", 15,  "N1", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__FK_USERS__PK_ID},                                                            
                                            {"FK-MEDIA--PK-ID-1", 17,  "N2", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__FK_MEDIA__PK_ID_1},
                                            {"FK-MEDIA--PK-ID-2", 17,  "N3", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__FK_MEDIA__PK_ID_2},
                                            {"FK-BOM--PK-ID", 13,  "N4", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__FK_BOM__PK_ID},
                                            {"RK-CUSTOMERS--PK-ID", 19,  "N5", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__RK_CUSTOMERS_ID},	
                                            {"PART NUMBER", 11,  "N6", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__PART_NUMBER},
                                            {"DRAWING NUMBER", 14,  "N7", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__DRAWING_NUMBER}, 
                                            {"DRAWING NUMBER REVISION", 23,  "N8", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__DRAWING_NUMBER_REVISION}, 
                                            {"WEIGHT", 6,  "N9", 2,   FGGR__EXTERNAL_FIELD,  FP__FIELD__WEIGHT},
                                            {"DESCRIPTION", 11,  "N10", 3,   FGGR__EXTERNAL_FIELD,  FP__FIELD__DESCRIPTION}, 
                                            {"NOTE", 4,  "N11", 3,   FGGR__EXTERNAL_FIELD,  FP__FIELD__NOTE}};


void fp__map_html_form_names_to_sdb_names__version_1 (void)
{
	
	fp->component.map = fp__map__version_1;
	fp->component.map_len = sizeof (fp__map__version_1) / sizeof (fggr__map_t);
	fp->component.map_version = 1;
	
}


void fp__map_html_form_names_to_sdb_names (void)
{
	fp__map_html_form_names_to_sdb_names__version_1();
}



void fp__set_module_data (void)
{

	/*
	* Set module name
	*/

	//fp->module.name = "fp";

	/*
	* Set module name version: 1
	*/
	fp->component.map = fp__map__version_1;
	fp->component.map_len = sizeof (fp__map__version_1) / sizeof (fggr__map_t);
	fp->component.map_version = 1;

}




