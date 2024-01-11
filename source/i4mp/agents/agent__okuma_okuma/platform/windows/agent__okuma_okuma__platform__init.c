


//typedef struct
//{
//
//	const char* name;
//	const char* machine_section_name;
//
//	agent__start_t start;
//	agent__stop_t stop;
//	agent__connect_to_machine_t connect_to_machine;
//	agent__read_machine_data_t read_machine_part_counter;
//	agent__read_machine_data_t read_machine_cycle_time;
//	agent__read_machine_data_t read_machine_part_program_name;
//	agent__read_machine_data_t read_machine_data_stream;
//
//	//agent__disconnect_from_machine_t disconnect_from_machine;	
//
//} agent__okuma_okuma_t;
//
//
//
//static agent__okuma_okuma_t agent__okuma_okuma;


int agent__okuma_okuma__platform__init(void)
{
	return 0;
}



//int agent__okuma_okuma__platform__init (void)
//{
//	agent__okuma_okuma.name = "OKUMA-OKUMA";
//	agent__okuma_okuma.machine_section_name = "MACHINE OKUMA-OKUMA";
//
//	agent__okuma_okuma.start = agent__okuma_okuma__platform__start;
//	agent__okuma_okuma.stop = agent__okuma_okuma__platform__private__stop;
//
//	//agent__okuma_okuma__platform__private__stop,
//	//agent__okuma_okuma__platform__private__connect_to_machine,
//	//agent__okuma_okuma__platform__private__read_machine_part_counter,
//	//agent__okuma_okuma__platform__private__read_machine_cycle_time,
//	//agent__okuma_okuma__platform__private__read_machine_part_program_name,
//	//agent__okuma_okuma__platform__private__task__read_machine_data
//
//	return 0;
//}



int agent__okuma_okuma__platform__config(void)
{

	return 0;
}