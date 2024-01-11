#include "fggr.h"
#include "fgg__programs.h"


static char *fn = "fgg__programs__present_program()";


int fgg__programs__present_program (unsigned long presentation_mode, utils__sdb_t *sdb, char *buffer, unsigned long buffer_size, unsigned long *buffer_len)
{

	int rc;
	unsigned long pair_count;
	char *name[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long name_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *value[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long value_len[FGGR__CONFIG__SDB_FIELDS_MAX];


	pair_count = 3;
	name[0] = fggr->javascript__field_names[5];
	name[1] = fggr->javascript__field_names[6];
	name[2] = fggr->javascript__field_names[8];
	

	name_len[0] = fggr->javascript__field_names_len[5];
	name_len[1] = fggr->javascript__field_names_len[6];
	name_len[2] = fggr->javascript__field_names_len[8];
		

	value[0] = sdb->value[5];
	value[1] = sdb->value[6];
	value[2] = sdb->value[8];
		

	value_len[0] = sdb->value_len[5];
	value_len[1] = sdb->value_len[6];
	value_len[2] = sdb->value_len[8];
	
	


	rc = fgg__format_js_buffer (presentation_mode, buffer, buffer_size, buffer_len, &name[0], name_len, pair_count, &value[0], value_len);

	return rc;
}


