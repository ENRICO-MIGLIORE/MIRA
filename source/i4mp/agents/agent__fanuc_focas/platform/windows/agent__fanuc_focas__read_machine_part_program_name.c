#include "Fwlib64.h"



//#include "carmelo__cncs.h"


#include "agent__fanuc_focas__private.h"


int agent__fanuc_focas__read_alarm_status (unsigned short fd, unsigned long* state)
{
	short rc;


	ODBST2 statinfo_2;



	rc = cnc_statinfo2(fd, &statinfo_2);//allarme warning run

	if (rc != 0)
	{
		return -1;
	}

	*state = 0x00;

	if (statinfo_2.alarm != 0)
	{
		//*state |= CNC__FOCAS__ALARM__STATE;
	}

	if (statinfo_2.emergency != 0)
	{
		//*state |= CNC__FOCAS__EMERGENCY__STATE;
	}

	if (statinfo_2.warning != 0)
	{
		//*state |= CNC__FOCAS__WARNING__STATE;  //abbiamo deciso di non guardare i warning
	}

	if (statinfo_2.run != 3)
	{
		//*state |= CNC__FOCAS__STOP__STATE; //la macchina non e' in start
	}
	else
	{
		//*state |= CNC__FOCAS__RUN__STATE; //per me a questo punto la macchina e' in start e in RUN
	}

	return rc;
}




int agent__fanuc_focas__read_machine_part_program_name (fanuc_focas__machine_t* machine)
{

	short rc;
	size_t len;
	const char* fn;
	unsigned short focas_handle;
	//machine_t* machine;
	ODBEXEPRG part_program;


	fn = "agent__fanuc_focas__read_machine_part_program_name()";


	if (machine == NULL)
	{
		return -100;
	}

	//machine = (machine_t*)arg;

	if (machine->ext_unsigned_short_valid == 0)
	{
		return -100;
	}

	focas_handle = machine->ext_unsigned_short;

	machine->part_program_name_valid = 0;


	rc = cnc_exeprgname(focas_handle, &part_program);             //LEGGO il nome e il numero del programma in esecuzione

	if (rc != EW_OK)
	{
		return -300;
	}

	len = strlen(part_program.name);
	if (len >= sizeof(machine->part_program_name))
	{
		len--;
	}

	memcpy(machine->part_program_name, (const void*) part_program.name, len);
	machine->part_program_name[len] = '\0';
	machine->part_program_name_valid = 1;


	//memcpy(machine->part_program_name, (const void*) part_program.name, len);
	//machine->part_program_name[len] = '\0';


	return 0;

}



//int fgg__cnc__focas_get_number_program_in_execution(unsigned short fd, fgg__buffer_t* prog_in_execution)
//{
//	int rc;
//	unsigned long len;
//	ODBEXEPRG programm_in_execution;
//
//
//
//	rc = cnc_exeprgname(fd, &programm_in_execution);             //LEGGO il nome e il numero del programma in esecuzione
//
//	len = (unsigned long)strlen(programm_in_execution.name);
//
//	//rc |= fgg__util__write_buffer (prog_in_execution, (unsigned char *)programm_in_execution.name,  util_strlen_32 ((unsigned char *)programm_in_execution.name));
//	memcpy(prog_in_execution->data, (unsigned char*)programm_in_execution.name, len);
//	prog_in_execution->len = len;
//
//
//	return rc;
//}
