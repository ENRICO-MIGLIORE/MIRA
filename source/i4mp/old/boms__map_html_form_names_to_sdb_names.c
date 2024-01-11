#include "boms.h"

 

/*
 * Version 1
 */
fggr__map_t  boms__map__version_1[] = {{"PK-ID", 5, FGGR__FIELD_DEFAULT_VALUE, FGGR__FIELD_DEFAULT_VALUE_LEN,   FGGR__INTERNAL_FIELD,  CUSTOMERS__FIELD__PK_ID}, 
{"VAT ID", 6,  "N1", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__VAT_ID}, 
{"NAME", 4,  "N2", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__NAME}, 
{"ADDRESS", 7,  "N3", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__ADDRESS}, 
{"HOUSE NUMBER", 12,  "N4", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__HOUSE_NUMBER}, 
{"CITY", 4,  "N5", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__CITY}, 
{"ZIP CODE", 8,  "N6", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__ZIP_CODE}, 
{"COUNTY", 6,  "N7", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__COUNTY}, 
{"STATE", 5,  "N8", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__NATION}, 
{"NATION", 6,  "N9", 2,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__NATION}, 
{"COMMENT", 7,  "N10", 3,   FGGR__EXTERNAL_FIELD,  CUSTOMERS__FIELD__NOTE}};



void boms__map_html_form_names_to_sdb_names__version_1 (void)
{
	
	boms->component.map = boms__map__version_1;
	boms->component.map_len = sizeof (boms__map__version_1) / sizeof (fggr__map_t);
	boms->component.map_version = 1;
	
}


void boms__map_html_form_names_to_sdb_names (void)
{
	boms__map_html_form_names_to_sdb_names__version_1();
}

