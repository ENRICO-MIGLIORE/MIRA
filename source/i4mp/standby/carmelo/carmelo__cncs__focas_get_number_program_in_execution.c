#include "..\fggr.h"
#include <Fwlib64.h>





int fgg__cnc__focas_get_number_program_in_execution (unsigned short fd, fgg__buffer_t *prog_in_execution)
{
	int rc;
	unsigned long len;
	ODBEXEPRG programm_in_execution;



	rc = cnc_exeprgname(fd,  &programm_in_execution);             //LEGGO il nome e il numero del programma in esecuzione

	len = (unsigned long) strlen (programm_in_execution.name);

	//rc |= fgg__util__write_buffer (prog_in_execution, (unsigned char *)programm_in_execution.name,  util_strlen_32 ((unsigned char *)programm_in_execution.name));
	memcpy (prog_in_execution->data, (unsigned char *)programm_in_execution.name, len);
	prog_in_execution->len = len;

	
	     
	

	return rc;
}
