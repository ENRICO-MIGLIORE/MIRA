#include "..\fggr.h"
#include <Fwlib64.h>






#define BUFF_SIZE     1024


int fgg__cnc__focas_get_program_code (unsigned short focas_handle, long prgnum, fgg__buffer_t *payload)
{


	    char buf[BUFF_SIZE+1] ;
        short ret ;
        long len_2 ;

		payload->len = 0;
		

        ret = cnc_upstart3( focas_handle, 0, prgnum, prgnum ) ;

        if ( ret ) return ( ret ) ;
        do {
                len_2 = BUFF_SIZE ;
				//ret = cnc_upload3( focas_handle, &len_2, (char *) &payload->data[payload->len]);
				ret = cnc_upload3( focas_handle, &len_2, buf);
			
                if ( ret == EW_BUFFER ) {
                        continue ;
                }
                if ( ret == EW_OK ) 
				{
					memcpy (&payload->data[payload->len],buf,len_2);
				    payload->len += len_2;
					if (payload->len >= 127900)
				    {
					    return -1;
				    }
                }
                if ( payload->data[payload->len - 1] == '%' ) {
                        break ;
                }
        } while (( ret == EW_OK ) || ( ret == EW_BUFFER ));

        ret = cnc_upend3( focas_handle ) ;


		
        return ( ret ) ;


}


