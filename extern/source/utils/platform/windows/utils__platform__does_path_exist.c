#include <direct.h>
#include <stdio.h>


/*
 * This program uses the _chdir function to verify that a given directory exists
 */


int utils__platform__does_path_exist (const char *dir_path)
{
	int rc;
	char buffer[1024];
	char *p;
	 

	/*
	 * 1 - Get the current directory of the process and store it in p
	 */
	p = _getcwd(buffer, sizeof(buffer));
	if (p == NULL)
	{
		return -10;
	}

	/*
	 * 2 - Change temporarily the current directory of the process. If we make it, the directory dir exists
	 */
    rc = _chdir((const char *) dir_path);
	if (rc != 0)
	{
		return -20;  /* The directory does not exist */
	}


	/*
	 * At this point, the directory dir exist
	 */


	/*
	 * 3 - Restore the original directory of the process
	 */
	rc = _chdir((const char *) buffer);
	if (rc != 0)
	{
		return -30;
	}


	return 0;

}


