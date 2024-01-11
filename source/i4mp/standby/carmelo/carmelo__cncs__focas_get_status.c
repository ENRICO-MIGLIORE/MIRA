//#include "carmelo__cncs.h"
#include "..\fggr.h"
#include <Fwlib64.h>

#define CNC__FOCAS__ALARM__STATE             0x01
#define CNC__FOCAS__EMERGENCY__STATE         0x02
#define CNC__FOCAS__WARNING__STATE           0x04
#define CNC__FOCAS__STOP__STATE              0x08
#define CNC__FOCAS__RUN__STATE               0x10


int fgg__cnc__focas_get_status (unsigned short fd, unsigned long *state)
{
	short rc;


	ODBST2 statinfo_2;



	rc = cnc_statinfo2 (fd, &statinfo_2);//allarme warning run

	if(rc != 0)
	{
		return -1;
	}

	*state = 0x00;

	if(statinfo_2.alarm != 0)
	{
		*state |= CNC__FOCAS__ALARM__STATE;
	}

	if(statinfo_2.emergency != 0)
	{
		*state |= CNC__FOCAS__EMERGENCY__STATE;
	}

	if(statinfo_2.warning != 0)
	{
		//*state |= CNC__FOCAS__WARNING__STATE;  //abbiamo deciso di non guardare i warning
	}

	if(statinfo_2.run != 3)
	{
		*state |= CNC__FOCAS__STOP__STATE; //la macchina non e' in start
	}
	else
	{
		*state |= CNC__FOCAS__RUN__STATE; //per me a questo punto la macchina e' in start e in RUN
	}

	return rc;
}
