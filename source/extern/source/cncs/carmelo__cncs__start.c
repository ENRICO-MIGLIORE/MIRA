 #include "..\fggr.h"
#include "carmelo__cncs.h"
 


int carmelo__cncs__start (void)
{
	int rc;

	FILE* f;
	fgg__buffer_t file_name;
    static char *fn = "fgg__customers__start()";
	char luca[256];

	//rc = utils__platform__make_absolute_file_name (carmelo__cncs->dir_path.data, "\\", "carmelo", "cncs", "--", ".txt", file_name.data, sizeof(file_name.data), &file_name.len);
	strcpy(carmelo__cncs->dir_path.data, "C:\\Users\\Admin\\Desktop\\PROGS\\PROG-75--FGGR\\documentation\\project-1\\deployment-base\\sdb\\cncs");

	
	rc = utils__platform__make_absolute_file_name(carmelo__cncs->dir_path.data, "carmelo", "cncs", "--", ".txt", file_name.data, sizeof(file_name.data), &file_name.len);
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -10, "utils__platform__make_absolute_file_name() returned %d", rc);
		return -10;
	}

	f = fopen(&file_name.data[0], "rb");
	if (f == NULL)
	{
		utils__printf__error(&fggr->pf, fn, -20, "Can't open file %s", file_name.data);
		return -20;
	}



	fclose(f);
	

	return 0;
}