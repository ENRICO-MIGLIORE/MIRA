#include <agency_private.h>


int agent__okuma_okuma__platform__private__connect_to_machine (void *arg)
{
	// questa funzione e' una finta connessione. In realta' non connette un bel niente perche' l'okuma non ha il concetto di connessione

	const char* fn;
	int len;
	int rc;
	machine_t* machine;
	int buffer_size;
	

	fn = "agent__okuma_okuma__connect_to_machine()";

	if (arg == NULL)
	{
		return -100;
	}
	machine = (machine_t*)arg;

	machine->connection_status_valid = 0;
	machine->connection_status = 0;



	utils__printf__info(&machine->pf, fn, 0, "agent connected to machine %s (id = % d)", machine->config_2.name, machine->config_2.id);


	return 0;
}


