#include <stdio.h>


int todo (void)
{

	printf("todo() - 1 - Il BOA o l'FGG toglie i backslash al percorso del file di configurazione e quindi Carmelo deve forzarlo a mano in MySQL\n");
	printf("todo() - 1 - valori di default: abbandoniamo il trattino '-' e pubblichiamo i campi vuoti - E' piu' facile da gestire - nessuno deve popolare i campi dei db con trattini '-'\n");
	printf("todo() - 1 - okuma_mt__private__load_machines_configuration() - convert printf() in utils__printf() - done = NO\n");
	printf("todo() - 2 - utils__libc__write_string() - many functions have return 0 instead of return rc\n");	
	printf("todo() - 3 - add machine_local subsystem\n");
	printf("todo() - 4 - okuma_mt__platform__private__task__read_machine_data_stream() - if the machine_local is not operated it does not have to be queried\n");
	printf("todo() - 5 - okuma_mt__private__read_part_program_name__real() - \"Program\" must arrive from the configuration\n");
	printf("todo() - 6 - okuma_mt__private__read_part_counter__real() - \"PartCount\" must arrive from the configuration\n");
	printf("todo() - 7 - application:  machine_local count = 0 - test\n");
	printf("todo() - 8 - machines:  machine_local count = 0 - test\n");
	printf("todo() - 9.1 - okuma_mt__platform__private__task__read_machine_data_stream() may last more than 1 second, when recv() blocks\n");
	printf("todo() - 9.2 - okuma_mt__private__task__estimate_cycle_time_from_part_counter() deve proseguire solo quando la recv() e' durata meno di un secondo e quando il contapezzi si e' incrementato di 1\n");
	printf("todo() - 9.3 - se il contapezzi si blocca, devo restartare il conteggio\n");
	printf("todo() - 10 - suffix utf_8 is no good for resources\n");
	printf("todo() - 11 - okuma part counter:  cronometra il codice tra connect() e recv() e deve durare meno di un secondo. se non accade il conteggio del tempo deve ripartire\n");
	printf("todo() - 12 - okuma connection monitor task - controllare le sezioni critiche\n");
	printf("todo() - 13 - okuma connection monitor task - deve andare in esecuzione con il thread principale e il tempo deve tenere conto dell'esecuzione ogni 5 secondi\n");
	printf("todo() - 14 - tutte le property devono essere come config_2: cambiabili in tempo reale -> deve avvenire il restart dell'agent mediante stop()\n");
	printf("todo() - 15 - se stacco il cavo tutte le config_2 devono andare in NOT AVAILABLE e le socket() devono ripartire mediante stop() e restart() \n");
	printf("todo() - 16 - l'Okuma va in timeout quando gli chiedo di valutare il tempo di ciclo la seconda volta dopo 180 secondi\n");
	printf("todo() - 17 - Siemens - Se il Client non si connette non riprova e l'agent ritorna '-' su tutte le query\n");
	printf("todo() - 18 - Siemens - Ogni tanto la macchina sembra non rispondere\n");
	printf("todo() - 19 - CSS grid: mettere 12 colonne e riscrivere tutte le CSS grid areas in modo da avere 24 colonne, cioe' 12 di contenuti e 12 di spacing 1. Questo permette di avere omogeneita' in tutto il sito e poterlo rendere responsive su cellulare con un approccio unico per tutte le pagine\n");

	return 0;

}








