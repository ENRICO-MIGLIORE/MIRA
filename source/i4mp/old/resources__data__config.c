
#include "boa_2.h"
#include "resources.h"


 static char *fn = "resources__data__config()";

#define FGGR__RESOURCES_MAX                    109


fgg__resources__data__t resources[FGGR__RESOURCES_MAX];
static char raw_materials_load[2048];
static char *url_bad_responce = "bad_responce.html";


int resources__data__config (void)
{
	int rc;
	fgg__resources__config_t conf;
	
	memset(resources, 0, sizeof(resources));

	resources[0].read_only = 1;
	//resources[0].name = "machine/1/status";
	resources[0].name = "machine";
	resources[0].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[0].value = "-";
	resources[0].len = 1;
	resources[0].size = 0;

	resources[1].read_only = 1;
	resources[1].name = "machine/1/alarm";
	resources[1].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[1].value = "SI";
	resources[1].len = strlen("SI");
	resources[1].size = resources[1].len;

	resources[2].read_only = 1;
	resources[2].name = "machine/1/job_name";
	resources[2].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[2].value = "non lo so";
	resources[2].len = strlen("non lo so");
	resources[2].size = resources[2].len;

	resources[3].read_only = 1;
	resources[3].name = "machine/1/job_completion";
	resources[3].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[3].value = "non lo so";
	resources[3].len = strlen("non lo so");
	resources[3].size = resources[2].len;

	resources[4].read_only = 1;
	resources[4].name = "machine/1/average_power";
	resources[4].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[4].value = "non lo so";
	resources[4].len = strlen("non lo so");
	resources[4].size = resources[2].len;

	resources[5].read_only = 1;
	resources[5].name = "machine/1/bar_feed";
	resources[5].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[5].value = "non lo so";
	resources[5].len = strlen("non lo so");
	resources[5].size = resources[2].len;
	

	resources[6].read_only = 1;
	resources[6].name = "machine/1/machined_parts";
	resources[6].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[6].value = "272568";
	resources[6].len = strlen("272568");
	resources[6].size = resources[0].len;

	resources[7].read_only = 1;
	resources[7].name = "machine/1/program_name";
	resources[7].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[7].value = "non lo so";
	resources[7].len = strlen("non lo so");
	resources[7].size = resources[2].len;

	resources[8].read_only = 1;
	resources[8].name = "machine/1/cycle_time";
	resources[8].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[8].value = "0 sec";
	resources[8].len = strlen("0 sec");
	resources[8].size = resources[2].len;

	resources[9].read_only = 1;
	resources[9].name = "machine/1/instant_power";
	resources[9].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[9].value = "non lo so";
	resources[9].len = strlen("non lo so");
	resources[9].size = resources[2].len;

	resources[10].read_only = 0;
	resources[10].name = "raw_materials__load"; //e' il form del caricamento materia prima
	resources[10].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[10].value = raw_materials_load;
	resources[10].url_responce = "rm__inventory.html";
	resources[10].len = 0;
	resources[10].size = sizeof(raw_materials_load);

	resources[11].read_only = 1;
	resources[11].name = "users__get_users";
	resources[11].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[11].value = "0";
	resources[11].len = strlen("0");
	resources[11].size = resources[2].len;

	resources[12].read_only = 1;
	resources[12].name = "suppliers__get_suppliers";
	resources[12].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[12].value = "0";
	resources[12].len = strlen("0");
	resources[12].size = resources[2].len;

	resources[13].read_only = 1;
	resources[13].name = "rm__get_rm";
	resources[13].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[13].value = "0";
	resources[13].len = strlen("0");
	resources[13].size = resources[2].len; 

	resources[14].read_only = 1;
	resources[14].name = "xxxxxxxxxxx"; 
	resources[14].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[14].value = "0";
	resources[14].len = strlen("0");
	resources[14].size = resources[2].len;
	

	resources[15].read_only = 1;
	resources[15].name = "rm_iet__get_rm_iet";  //   rm_iet__get_rm_iet
	resources[15].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[15].value = "0";
	resources[15].len = strlen("0");
	resources[15].size = resources[2].len;


	resources[16].read_only = 0;
	resources[16].name = "rm__update_rm_ie"; //e' il form della rettifica inventariale materia prima
	//resources[16].name = "inventario_rm.html";
	resources[16].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[16].value = raw_materials_load;
	resources[16].url_responce = "rm__inventory.html";
	resources[16].len = 0;
	resources[16].size = sizeof(raw_materials_load);


	resources[17].read_only = 0;
	resources[17].name = "xxxxxxxx"; //restituisce l'elenco di tutti i fp con cliente e peso
	resources[17].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[17].value = "0";
	resources[17].len = strlen("0");
	resources[17].size = resources[2].len;


	resources[18].read_only = 0;
	resources[18].name = "fp__get_fp"; //get_fp
	resources[18].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[18].value = "0";
	resources[18].len = strlen("0");
	resources[18].size = resources[2].len;

	resources[19].read_only = 0;
	resources[19].name = "po__get_po"; //get_jobs
	resources[19].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[19].value = "0";
	resources[19].len = strlen("0");
	resources[19].size = resources[2].len;

	resources[20].read_only = 0;
	resources[20].name = "fp__load"; //e' il form del caricamento dei prodotti finiti
	resources[20].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[20].value = raw_materials_load;
	//resources[20].url_responce = "inventario_fp.html";
	resources[20].url_responce = "etichetta.pdf";
	resources[20].len = 0;
	resources[20].size = sizeof(raw_materials_load);

	resources[21].read_only = 0;
	resources[21].name = "fp__get_inventory_table";     //restituisce il numero di pezzi di un fp in magazzino
	resources[21].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[21].value = "0";
	resources[21].len = strlen("0");
	resources[21].size = resources[2].len;

	resources[22].read_only = 0;
	resources[22].name = "fp__update_fp_ie"; //e' il form della retifica inventariale prodotti finiti
	resources[22].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[22].value = raw_materials_load;
	resources[22].url_responce = "fp__inventory.html";
	resources[22].len = 0;
	resources[22].size = sizeof(raw_materials_load); 

	resources[23].read_only = 0;
	resources[23].name = "fp_iet__get_fp_iet";
	resources[23].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[23].value = "0";
	resources[23].len = strlen("0");
	resources[23].size = resources[2].len; 

	resources[24].read_only = 0;
	resources[24].name = "fp__create_new_fp"; //e' il form che crea un prodotto finito
	resources[24].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[24].value = raw_materials_load;
	resources[24].url_responce = "fp__inventory.html";
	resources[24].len = 0;
	resources[24].size = sizeof(raw_materials_load);

	resources[25].read_only = 0;
	resources[25].name = "fp__update_fp"; //e' il form che modifica un prodotto finito
	resources[25].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[25].value = raw_materials_load;
	resources[25].url_responce = "fp__inventory.html";
	resources[25].len = 0;
	resources[25].size = sizeof(raw_materials_load);

	resources[26].read_only = 0;
	resources[26].name = "fp__get_fp_all_fields"; //get 1 fp con tutti i campi
	resources[26].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[26].value = "0";
	resources[26].len = strlen("0");
	resources[26].size = resources[2].len;

	resources[27].read_only = 0;
	resources[27].name = "xxxxxxxxxxxxxxx"; 
	resources[27].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[27].value = raw_materials_load;
	resources[27].url_responce = "index.html";
	resources[27].len = 0;
	resources[27].size = sizeof(raw_materials_load);

	resources[28].read_only = 0;
	resources[28].name = "customers__get_customers"; //get customers
	resources[28].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[28].value = "0";
	resources[28].len = strlen("0");
	resources[28].size = resources[2].len; 
	
	resources[29].read_only = 0;
	resources[29].name = "xxxxxxxxxxxx";
	resources[29].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[29].value = "0";
	resources[29].len = strlen("0");
	resources[29].size = resources[2].len;

	resources[30].read_only = 0;
	resources[30].name = "xxxxxxxxxxxxxxxxxxxxxxxxxx"; 
	resources[30].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[30].value = "0";
	resources[30].len = strlen("0");
	resources[30].url_responce = "index.html";  //STRANISSIMO MA MI E' ENTRATA COME POST QUESTO FD (30) E PER PARARE UN BUG HO DOVUTO METTERGLI UNA URIRESPONSE
	resources[30].size = resources[2].len;

	resources[31].read_only = 0;
	resources[31].name = "po__close_po"; //e' il form chiusura dei po
	resources[31].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[31].value = raw_materials_load;
	resources[31].url_responce = "index.html";
	resources[31].len = 0;
	resources[31].size = sizeof(raw_materials_load);

	resources[32].read_only = 0;
	resources[32].name = "po__get_po_by_customer_and_year_close"; //risponde con i po di un determinato anno che sono stati chiusi
	resources[32].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[32].value = "0";
	resources[32].len = strlen("0");
	resources[32].size = resources[2].len;

	resources[33].read_only = 0;
	resources[33].name = "po__get_po_by_customer_and_year_open"; //get_jobs_open le po aperte di un certo anno e di un certo customer
	resources[33].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[33].value = "0";
	resources[33].len = strlen("0");
	resources[33].size = resources[2].len;

	resources[34].read_only = 0;
	resources[34].name = "po__update_po"; //e' il form che modifica una job
	resources[34].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[34].value = raw_materials_load;
	resources[34].url_responce = "po__update_po.html";
	resources[34].len = 0;
	resources[34].size = sizeof(raw_materials_load);

	resources[35].read_only = 0;
	resources[35].name = "po__get_po_all_fields"; //restituisce tutti ma proprio tutti i campi di una job!
	resources[35].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[35].value = "0";
	resources[35].len = strlen("0");
	resources[35].size = resources[2].len;

	resources[36].read_only = 0;
	resources[36].name = "get_fp_ie_production"; //restituisce l'elenco di tutti i movimenti per produzione di un determinato anno
	resources[36].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[36].value = "0";
	resources[36].len = strlen("0");
	resources[36].size = resources[2].len;

	resources[37].read_only = 0;
	resources[37].name = "ristampa_etichette_post"; //e' il bottone per ristampare un etichetta di produzione da attaccare sul sacco
	resources[37].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[37].value = raw_materials_load;
	resources[37].url_responce = "etichetta.pdf";
	resources[37].len = 0;
	resources[37].size = sizeof(raw_materials_load);
	
	resources[38].read_only = 0;
	resources[38].name = "rm__get_rm_by_supplier"; //restituisce l'elenco di tutti i rm di un determinato fornitore  rm__get_rm_by_supplier
	resources[38].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[38].value = "0";
	resources[38].len = strlen("0");
	resources[38].size = resources[2].len;

	resources[39].read_only = 0;
	resources[39].name = "fp__get_for_this_client"; //restituisce l'elenco di tutti i fp di un determinato cliente
	resources[39].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[39].value = "0";
	resources[39].len = strlen("0");
	resources[39].size = resources[2].len;


	resources[40].read_only = 0;
	resources[40].name = "ship__create_new"; //e' il form che crea una nuova spedizione
	resources[40].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[40].value = raw_materials_load;
	resources[40].url_responce = "shipp__create_new.html";
	resources[40].len = 0;
	resources[40].size = sizeof(raw_materials_load);

	resources[41].read_only = 0;
	resources[41].name = "xxxxxxxx"; //restituisce l'elenco di tutti i fp con cliente e peso
	resources[41].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[41].value = "0";
	resources[41].len = strlen("0");
	resources[41].size = resources[2].len;

	resources[42].read_only = 0;
	resources[42].name = "ship__get_shipping_by_year_customer"; //restituisce l'elenco di tutte le spedizioni di un anno dato
	resources[42].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[42].value = "0";
	resources[42].len = strlen("0");
	resources[42].size = resources[2].len;

	resources[43].read_only = 0;
	resources[43].name = "get_all_fp_with_time_weight_by_client"; //restituisce l'elenco di tutti gli fp indicando i tempi e i pesi partendo da un cliente
	resources[43].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[43].value = "0";
	resources[43].len = strlen("0");
	resources[43].size = resources[2].len;

	resources[44].read_only = 0;
	resources[44].name = "po__reopen_po"; //riapre un po
	resources[44].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[44].value = raw_materials_load;
	resources[44].len = 0;
	resources[44].size = sizeof(raw_materials_load);
	
	resources[45].read_only = 0;
	resources[45].name = "jo__get_jo_all_fields"; //restituisce una commessa    get_commesse_all_fields      jo__get_jo_all_fields
	resources[45].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[45].value = "0";
	resources[45].len = strlen("0");
	resources[45].size = resources[2].len;

	resources[46].read_only = 0;
	resources[46].name = "xxxxxxxxxxxxxxxx"; 
	resources[46].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[46].value = "0";
	resources[46].len = strlen("0");
	resources[46].size = resources[2].len;

	resources[47].read_only = 0;
	resources[47].name = "xxxxxxxxxxxxxxx"; 
	resources[47].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[47].value = raw_materials_load;
	resources[47].url_responce = "odp_view.html";
	resources[47].len = 128;
	resources[47].size = sizeof(raw_materials_load);

	resources[48].read_only = 0;
	resources[48].name = "po__get_po_progress"; //restituisce la % di avanzamento produzione di un ODP
	resources[48].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[48].value = "0";
	resources[48].len = strlen("0");
	resources[48].size = resources[2].len;

	resources[49].read_only = 0;
	resources[49].name = "xxxxxxxxxxxxxxxxxxxxx"; 
	resources[49].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[49].value = "0";
	resources[49].len = strlen("0");
	resources[49].size = resources[2].len;


	resources[50].read_only = 0;
	resources[50].name = "jo__new_job"; //e' il form crea_nuova_commessa
	resources[50].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[50].value = raw_materials_load;
	resources[50].url_responce = "index.html";
	resources[50].len = 0;
	resources[50].size = sizeof(raw_materials_load);

	resources[51].read_only = 0;   
	resources[51].name = "xxxxxxxxxxxxxxxxxxxxxxxxx"; 
	resources[51].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[51].value = "0";
	resources[51].len = strlen("0");
	resources[51].size = resources[2].len;

	resources[52].read_only = 0;   
	resources[52].name = "jo__get_jo_by_customer_and_year_open"; //restituisce le jo di un certo cliente in un certo anno aperte
	resources[52].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[52].value = "0";
	resources[52].len = strlen("0");
	resources[52].size = resources[2].len; 

	resources[53].read_only = 0;
	resources[53].name = "xxxxxxxxxxxxxxxx"; 
	resources[53].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[53].value = "0";
	resources[53].len = strlen("0");
	resources[53].size = resources[2].len; 
	

	resources[54].read_only = 0;
	resources[54].name = "jo__close_jo"; //e' il form chiudi_commessa
	resources[54].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[54].value = raw_materials_load;
	resources[54].url_responce = "jobs_get_open_jo.html";
	resources[54].len = 0;
	resources[54].size = sizeof(raw_materials_load);

	resources[55].read_only = 0;
	resources[55].name = "jo__open_jo"; //e' il form riapri_commessa
	resources[55].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[55].value = raw_materials_load;
	resources[55].url_responce = "jobs_get_close_jo.html";
	resources[55].len = 0;
	resources[55].size = sizeof(raw_materials_load);

	resources[56].read_only = 0;
	resources[56].name = "jo__update_jo"; //e' il form modifica_commessa
	resources[56].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[56].value = raw_materials_load;
	resources[56].url_responce = "jobs_get_open_jo.html";
	resources[56].len = 0;
	resources[56].size = sizeof(raw_materials_load);

	resources[57].read_only = 0;
	resources[57].name = "warehouse__get_warehouse"; //restituisce i magazzini
	resources[57].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[57].value = "0";
	resources[57].len = strlen("0");
	resources[57].size = resources[2].len; 

	resources[58].read_only = 0;
	resources[58].name = "get_lang"; //restituisce la lingua   1 ita   2 english
	resources[58].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[58].value = "0";
	resources[58].len = strlen("0");
	resources[58].size = resources[2].len; 

	resources[59].read_only = 0;
	resources[59].name = "set_lang";
	resources[59].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[59].value = raw_materials_load;
	resources[59].url_responce = "index.html";
	resources[59].len = 0;
	resources[59].size = sizeof(raw_materials_load);


	resources[60].read_only = 0;
	resources[60].name = "rm__get_weight_rm_in_rmw"; //restituisce il peso di un materiale dentro un magazzino
	resources[60].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[60].value = "0";
	resources[60].len = strlen("0");
	resources[60].size = resources[2].len; 

	resources[61].read_only = 0;
	//resources[61].name = "get_fiscal_years"; //restituisce la lista degli anni nel file fiscal-data.txt
	resources[61].name = "sfy_filter__get_fiscal_years"; //restituisce la lista degli anni nel file fiscal-data.txt
	resources[61].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[61].value = "0";
	resources[61].len = strlen("0");
	resources[61].size = resources[2].len; 


	/*
	 * Return the number of users
	 */
	resources[62].read_only = 0;
	resources[62].name = "get_user_count"; 
	resources[62].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[62].value = "0";
	resources[62].len = strlen("0");
	resources[62].size = resources[2].len; 

	/*
	 * Return the number of users
	 */
	resources[63].read_only = 0;
	resources[63].name = "users__get_count"; 
	resources[63].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[63].value = "0";
	resources[63].len = strlen("0");
	resources[63].size = resources[2].len; 

	/*
	 * Return the number of users
	 */
	resources[64].read_only = 0;
	resources[64].name = "sfy_filter__get_count";   
	resources[64].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[64].value = "0";
	resources[64].len = strlen("0");
	resources[64].size = resources[2].len; 

	/*
	 * Return the number of jobs
	 */
	resources[65].read_only = 0;
	resources[65].name = "po__get_count"; 
	resources[65].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[65].value = "0";
	resources[65].len = strlen("0");
	resources[65].size = resources[2].len;

	/*
	 * Return the number of customer
	 */
	resources[66].read_only = 0;
	resources[66].name = "customers__get_count"; 
	resources[66].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[66].value = "0";
	resources[66].len = strlen("0");
	resources[66].size = resources[2].len; 


	/*
	 * Return the number of fp
	 */
	resources[67].read_only = 0;
	resources[67].name = "fp__get_count"; 
	resources[67].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[67].value = "0";
	resources[67].len = strlen("0");
	resources[67].size = resources[2].len; 

	/*
	 * 
	 */
	resources[68].read_only = 0;
	resources[68].name = "fp__get_count_by_customer"; 
	resources[68].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[68].value = "0";
	resources[68].len = strlen("0");
	resources[68].size = resources[2].len; 


	/*
	 * Return the number of rm
	 */
	resources[69].read_only = 0;
	resources[69].name = "rm__get_count"; 
	resources[69].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[69].value = "0";
	resources[69].len = strlen("0");
	resources[69].size = resources[2].len; 

	/*
	 * Return the number of warehouse
	 */
	resources[70].read_only = 0;
	resources[70].name = "warehouse__get_count"; 
	resources[70].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[70].value = "0";
	resources[70].len = strlen("0");
	resources[70].size = resources[2].len; 


	
    /*
	 * Return the po by customer and year
	 */
	resources[71].read_only = 0;
	resources[71].name = "po__get_po_by_customer_and_year"; 
	resources[71].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[71].value = "0";
	resources[71].len = strlen("0");
	resources[71].size = resources[2].len; 

	 /*
	 * Return the po count by customer and year
	 */
	resources[72].read_only = 0;
	resources[72].name = "po__get_po_count_by_customer_and_year"; 
	resources[72].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[72].value = "0";
	resources[72].len = strlen("0");
	resources[72].size = resources[2].len; 
	 
	/*
	 * Return the rm_by_pk_id
	 */
	resources[73].read_only = 0;
	resources[73].name = "rm__get_rm_by_pk_id"; 
	resources[73].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[73].value = "0";
	resources[73].len = strlen("0");
	resources[73].size = resources[2].len; 

	/*
	 * Return the warehouse__get_warehouse_by_pk_id
	 */
	resources[74].read_only = 0;
	resources[74].name = "warehouse__get_warehouse_by_pk_id"; 
	resources[74].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[74].value = "0";
	resources[74].len = strlen("0");
	resources[74].size = resources[2].len; 

	/*
	 * Return the fp__get_fp_by_pk_id
	 */
	resources[75].read_only = 0;
	resources[75].name = "fp__get_fp_by_pk_id"; 
	resources[75].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[75].value = "0";
	resources[75].len = strlen("0");
	resources[75].size = resources[2].len; 


	
	/*
	 * Return the rm__sdb__select_active_rm_count_from_rm_by_supplier
	 */
	resources[76].read_only = 0;
	resources[76].name = "rm__get_count_from_rm_by_supplier"; 
	resources[76].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[76].value = "0";
	resources[76].len = strlen("0");
	resources[76].size = resources[2].len; 

	/*
	 * Return the suppliers__get_count
	 */
	resources[77].read_only = 0;
	resources[77].name = "suppliers__get_count"; 
	resources[77].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[77].value = "0";
	resources[77].len = strlen("0");
	resources[77].size = resources[2].len; 


	resources[78].read_only = 0;
	resources[78].name = "suppliers__get_supplier_by_rm_pkid"; 
	resources[78].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[78].value = "0";
	resources[78].len = strlen("0");
	resources[78].size = resources[2].len; 

	resources[79].read_only = 0;
	resources[79].name = "machines__get_machines"; 
	resources[79].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[79].value = "0";
	resources[79].len = strlen("0");
	resources[79].size = resources[2].len; 

	resources[80].read_only = 0;
	resources[80].name = "machines__get_count"; 
	resources[80].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[80].value = "0";
	resources[80].len = strlen("0");
	resources[80].size = resources[2].len; 

	resources[81].read_only = 0;
	resources[81].name = "machines__get_machines_by_pk_id"; 
	resources[81].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[81].value = "0";
	resources[81].len = strlen("0");
	resources[81].size = resources[2].len; 

	resources[82].read_only = 0;
	resources[82].name = "*.html"; 
	resources[82].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[82].value = "0";
	resources[82].len = strlen("0");
	resources[82].size = resources[2].len; 

	resources[83].read_only = 0;
	resources[83].name = "jo__get_jo_count_by_customer_and_year_open"; 
	resources[83].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[83].value = "0";
	resources[83].len = strlen("0");
	resources[83].size = resources[2].len; 
	
	resources[84].read_only = 0;
	resources[84].name = "rm_section__get_count"; 
	resources[84].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[84].value = "0";
	resources[84].len = strlen("0");
	resources[84].size = resources[2].len; 

	resources[85].read_only = 0;
	resources[85].name = "rm_section__get_rm_sections"; 
	resources[85].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[85].value = "0";
	resources[85].len = strlen("0");
	resources[85].size = resources[2].len; 

	resources[86].read_only = 0;
	resources[86].name = "rm_dimension__get_rm_dimensions"; 
	resources[86].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[86].value = "0";
	resources[86].len = strlen("0");
	resources[86].size = resources[2].len; 

	resources[87].read_only = 0;
	resources[87].name = "rm_material__get_rm_materials"; 
	resources[87].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[87].value = "0";
	resources[87].len = strlen("0");
	resources[87].size = resources[2].len; 

	resources[88].read_only = 0;
	resources[88].name = "rm__get_count_from_rm_by_supplier_sec_dim_mat"; 
	resources[88].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[88].value = "0";
	resources[88].len = strlen("0");
	resources[88].size = resources[2].len; 

	resources[89].read_only = 0;
	resources[89].name = "rm__get_rm_by_supplier_sect_dim_mat"; 
	resources[89].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[89].value = "0";
	resources[89].len = strlen("0");
	resources[89].size = resources[2].len; 

	resources[90].read_only = 0;
	resources[90].name = "rm_iet__get_rm_iet_count"; 
	resources[90].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[90].value = "0";
	resources[90].len = strlen("0");
	resources[90].size = resources[2].len; 
	
	resources[91].read_only = 0;
	resources[91].name = "jo__get_jo_count_by_customer_and_year_close"; 
	resources[91].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[91].value = "0";
	resources[91].len = strlen("0");
	resources[91].size = resources[2].len; 

	resources[92].read_only = 0;   
	resources[92].name = "jo__get_jo_by_customer_and_year_close"; //restituisce le jo di un certo cliente in un certo anno aperte
	resources[92].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[92].value = "0";
	resources[92].len = strlen("0");
	resources[92].size = resources[2].len; 

	 /*
	 * Return the po count by customer and year
	 */
	resources[93].read_only = 0;
	resources[93].name = "po__get_po_count_by_customer_and_year_open"; 
	resources[93].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[93].value = "0";
	resources[93].len = strlen("0");
	resources[93].size = resources[2].len; 
		
	resources[94].read_only = 0;
	resources[94].name = "po__get_po_count_by_customer_and_year_close"; 
	resources[94].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[94].value = "0";
	resources[94].len = strlen("0");
	resources[94].size = resources[2].len; 

	resources[95].read_only = 0;
	resources[95].name = "fp_iet__get_fp_iet_count"; 
	resources[95].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[95].value = "0";
	resources[95].len = strlen("0");
	resources[95].size = resources[2].len; 


	resources[96].read_only = 0;
	resources[96].name = "ship__get_count_shipping_by_year_customer"; 
	resources[96].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[96].value = "0";
	resources[96].len = strlen("0");
	resources[96].size = resources[2].len;
	

	resources[97].read_only = 0;
	resources[97].name = "ship__get_count_shipping_by_year_fp"; 
	resources[97].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[97].value = "0";
	resources[97].len = strlen("0");
	resources[97].size = resources[2].len;

	resources[98].read_only = 0;
	resources[98].name = "ship__get_shipping_by_year_fp"; //restituisce l'elenco di tutte le spedizioni di un anno e di un fp
	resources[98].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[98].value = "0";
	resources[98].len = strlen("0");
	resources[98].size = resources[2].len;

	resources[99].read_only = 0;
	resources[99].name = "mf__get_mf"; 
	resources[99].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[99].value = "0";
	resources[99].len = strlen("0");
	resources[99].size = resources[2].len;

	resources[100].read_only = 0;
	resources[100].name = "mf__get_count_mf_active";
	resources[100].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[100].value = "0";
	resources[100].len = strlen("0");
	resources[100].size = resources[2].len;


	resources[101].read_only = 0;
	resources[101].name = "machines__create_new";
	resources[101].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[101].value = raw_materials_load;
	resources[101].url_responce = "machines.html";
	resources[101].len = 0;
	resources[101].size = sizeof(raw_materials_load);

	resources[102].read_only = 0;
	resources[102].name = "machines__update";
	resources[102].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[102].value = raw_materials_load;
	resources[102].url_responce = "machines.html";
	resources[102].len = 0;
	resources[102].size = sizeof(raw_materials_load);

	resources[103].read_only = 0;
	resources[103].name = "mf__get_mf_by_pk_id";
	resources[103].mime_type = BOA_2__MIME_TYPE__TEXT_PLAIN;
	resources[103].value = "0";
	resources[103].len = strlen("0");
	resources[103].size = resources[2].len;

	resources[104].read_only = 0;
	resources[104].name = "users__create_new";
	resources[104].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[104].value = raw_materials_load;
	resources[104].url_responce = "index.html";
	resources[104].len = 0;
	resources[104].size = sizeof(raw_materials_load);

	resources[105].read_only = 0;
	resources[105].name = "rmw__create_new";
	resources[105].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[105].value = raw_materials_load;
	resources[105].url_responce = "index.html";
	resources[105].len = 0;
	resources[105].size = sizeof(raw_materials_load);

	resources[106].read_only = 0;
	resources[106].name = "mf__create_new";
	resources[106].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[106].value = raw_materials_load;
	resources[106].url_responce = "index.html";
	resources[106].len = 0;
	resources[106].size = sizeof(raw_materials_load);
	
	resources[107].read_only = 0;
	resources[107].name = "customers__create_new";
	resources[107].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[107].value = raw_materials_load;
	resources[107].url_responce = "index.html";
	resources[107].len = 0;
	resources[107].size = sizeof(raw_materials_load);

	resources[108].read_only = 0;
	resources[108].name = "suppliers__create_new";
	resources[108].mime_type = BOA_2__MIME_TYPE__TEXT_HTML;
	resources[108].value = raw_materials_load;
	resources[108].url_responce = "index.html";
	resources[108].len = 0;
	resources[108].size = sizeof(raw_materials_load);

	conf.resource = &resources[0];
	conf.resources_max = sizeof (resources) / sizeof (fgg__resources__data__t);
	conf.cluster_size = 16;
	conf.url_bad_responce = url_bad_responce;

	rc = resources__config ();
	if (rc != 0)
	{
		utils__printf__error(&fggr->pf, fn, -10, "resources__config() returned %d", rc);
		return -10;
	}


	return 0;
}


