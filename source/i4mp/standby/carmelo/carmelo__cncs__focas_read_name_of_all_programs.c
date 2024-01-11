#include "..\fggr.h"
//#include "carmelo__cncs.h"
#include <Fwlib64.h>



int fgg__cnc__focas_read_name_of_all_programs (unsigned short focas_handle, fgg__buffer_t *buff)
{
	PRGDIR2 prg_totali[512];
	short i, num;
	short top = 0;
	short ret;
	unsigned char tmp_name[128];
	unsigned char tmp_buff[512];
	unsigned long len;

	/*QUESTO DO WHILE SOTTO FUNZIONA DA DIO MI DA TUTTI I PROGRAMMI IN MACCHINA */
	do {
		num = 512;
		ret = cnc_rdprogdir2( focas_handle, 2, &top, &num, prg_totali );
		if ( ret == EW_NUMBER ) 
		{
			return -1;
			break;
		}
		if ( ret ) {
			//printf( "ERROR: %d\n", ret );
			return -2;
			break;
		}

		memset (tmp_buff,'\0',sizeof(tmp_buff));

		for ( i = 0 ; i < num ; i++ ) 
		{
			sprintf((char *) tmp_name,"O%d&", prg_totali[i].number);
			strcat ((char *) tmp_buff , (const char *)tmp_name);

		}
		//fgg__util__write_buffer(buff,tmp_buff,util_strlen_32 (tmp_buff));
		len = (unsigned long) strlen((const char *) tmp_buff);
		memcpy (buff->data, tmp_buff, len );
		buff->len = len;
		top = prg_totali[num-1].number + 1;
	} while ( num >= 512 );
	/* NON TOCCARE QUESTO DO WHILE SOPRA */

	return 0;
}
