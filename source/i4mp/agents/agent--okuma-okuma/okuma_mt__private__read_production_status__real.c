#include "okuma_mt__private.h"

/*
<EmergencyStop dataItemId = "Mestop" timestamp = "2017-06-26T02.37.23.3125000Z" name = "estop" sequence = "56"> ARMED</EmergencyStop>
Questa riga riporta lo stato del fungo di emergenza : Triggered = fungo premuto; Armed = fungo non premuto

<ControllerMode dataItemId = "Mpmode" timestamp = "2017-06-26T02.37.23.3125000Z" name = "pmode" sequence = "62">AUTOMATIC</ControllerMode>
Questa riga riporta la modalità operativa della macchina : AUTOMATIC = macchina in automatico, MANUAL = macchina in manuale, MDI = Manual data input

<Execution dataItemId = "Mpexecution" timestamp = "2017-06-26T03.29.23.828Z" name = "pexecution" sequence = "21422">ACTIVE</Execution>
Questa riga riporta lo stato esecutivo della macchina : STOPPED = interruzione volontaria della lavorazione(i.e.pulsante di fermo ciclo), ACTIVE = macchina in lavorazione(i.e.macchina che esegue un programma), INTERRUPTED = Ciclo di lavoro interrotto, READY = Macchina che ha concluso il ciclo di lavoro O macchina pronta per eseguire un nuovo programma

<Warning dataItemId = "Msystem" timestamp = "2017-06-26T03.29.26.750Z" name = "system" sequence = "21451" nativeCode = "4204" nativeSeverity = "4204" type = "SYSTEM">4204 ALARM_D  10000320 < / Warning >
Righe di questo tipo riportano i codici allarmi presenti sulla macchina, in questa riga viene riportato il codice allarme dello stop di emergenza ed il giustificativo alfanumerico relativo.Per ogni allarme presente sulla macchina verrà generata una riga del genere

<PartCount dataItemId = "Mppartcount" timestamp = "2017-06-26T02.51.52.265Z" name = "ppartcount" sequence = "3463">1 </PartCount >
Contapezzi sequenziale della macchina, questo valore viene azzerato al caricamento di un nuovo programma nella memoria e prosegue per valori interi all’esecuzione di comandi M30 / M02(ovvero alla fine del programma)

<Program dataItemId = "Mpprogram" timestamp = "2017-06-26T02.47.30.734Z" name = "pprogram" sequence = "1095" > MECSPE.MIN</Program>
Nome del programma caricato in memoria

*/

/*
 * <Execution dataItemId="Mpexecution" timestamp="2017-06-26T03.29.23.828Z" name="pexecution" sequence="21422">ACTIVE</Execution>  
 * 
 * machine states:
 *        ACTIVE = machine is working
 *        STOPPED = machine is not working, example stop cycle button was pressed by the operator*                                                          
 *        INTERRUPTED = cycle interrputed 
 *        READY = machine ended a working cycle and is ready to execute another one
 *
 * 
 */
int okuma_mt__private__read_production_status__real(int md)
{

	int rc;
	size_t len;
	char* p;

	if ((md < 0) || (md >= om->machine_count))
	{
		return -1000;
	}

	om->machine[md].production_status_valid = 0;


	if (om->machine[md].data_stream_valid != 1)
	{
		return -200;
	}

	p = "Execution";
	len = strlen(p);

	rc = utils__xml__extract_inner_xml(om->machine[md].receive_buffer, om->machine[md].receive_buffer_len, p, len, om->machine[md].alarm_utf_8, sizeof(om->machine[md].alarm_utf_8), &om->machine[md].alarm_utf_8_len);
	if (rc != 0)
	{
		return -300;
	}


	p = "ACTIVE";
	len = strlen(p);

	if (len == om->machine[md].alarm_utf_8_len)
	{
		rc = memcmp(om->machine[md].alarm_utf_8, p, om->machine[md].alarm_utf_8_len);
		if (rc == 0)
		{
			om->machine[md].production_status_valid = 1;
			om->machine[md].production_status = 1;
			return 0;
		}
	}

	return 0;

}