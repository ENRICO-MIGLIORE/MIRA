#include <agency_private.h>



int agent__okuma_okuma__read_machine_part_counter (void* arg)
{
	
	const char* fn;
	machine_t* machine;
	char* p;
	int len;
	int rc;


	fn = "agent__okuma_okuma__read_machine_part_counter()";


	if (arg == NULL)
	{
		return -100;
	}
#if 0
	machine = (machine_t*)arg;
	


	machine->part_counter_valid = 0;    //agent_so->subagent.machine[md].part_counter_valid = 0;    //so->machine[md].part_counter_valid = 0;

	if (machine->ext_data_stream_valid != 1)
	{
		return -200;
	}
	
	
	//p = "PartCount";
	p = "Program"; 
	len = strlen(p);
	
	rc = utils__xml__extract_inner_xml(machine->ext_receive_buffer, machine->ext_receive_buffer_len, p, len, machine->part_counter, sizeof(machine->part_counter), &machine->part_counter_len);
	if (rc != 0)
	{
		return -300;
	}
	
	

	machine->part_counter_valid = 1; 


#endif

	return 0;

}

