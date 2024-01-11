#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*
 * -c = configuration file
 * -n = number of machine queries
 */

#define argv_1     "-f"
#define argv_2     "D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\i4mp_config.txt"
#define argv_3     "-l"
#define argv_4     "D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\i4mp_log.txt"
#define argv_5     "-n"
#define argv_6     "1000"
#define argv_7     "-b"
#define argv_8     "65536"
#define argv_9     "1"
#define argv_10    "1"
#define argv_11    "1"



int agency__test_1(const char* config_file_name);


int main (int argc, char* argv[])
{


	int rc;

	if (argc < 3)
	{
		return;
	}


	rc = strcmp(argv[1], "-f");
	if (rc != 0)
	{
		return -100;
	}


	rc = agency__test_1((const char*)argv[2]);

	if (rc == 0)
	{
		printf("main() - agency__test_1() completed without errors - press enter to end the application");
	}
	else
	{
		printf("main() - agency__test_1() returned on error %d - press enter to end the application", rc);
	}


	return 0;

}



extern int todo(void);

extern int utils__libc__tokenize_string(const char* buffer, size_t buffer_len, const char** seps, size_t* seps_len, size_t seps_count, char** tokens, size_t* tokens_len, size_t tokens_max, size_t* token_count);
extern int utils__libc__print_tokens(char** tokens, size_t* tokens_len, size_t token_count);
extern int utils__libc__unescape_buffer(char* buffer, size_t buffer_len, const char* escape_sequence, size_t escape_sequence_len, char c, size_t* buffer_new_len);
extern int utils__libc__trim_tokens(char** tokens, size_t* tokens_len, size_t tokens_max, char c);



#include <math.h>


int main_old (int argc, char* argv[])
{
	int rc;
	int c;
	int test_cycles;
	char* argv_local[16];
	int enable_printf;
	int enable_log_file;
	int enable_table_layout_output;
	char *buffer_2;
	char* seps[] = { "+", "@@@" };
	size_t buffer_2_len;
	size_t seps_len[2];
	size_t seps_count;
	char* tokens[16];
	size_t tokens_len[16];
	size_t tokens_max;
	size_t token_count;
	char buffer_3[256];
	size_t buffer_3_len;
	size_t buffer_new_len;
	const char* escape_sequence;
	size_t escape_sequence_len;
	char ch;

	double d;
	double e;

	
	//int i;

	//d = 0.0;  // 2,71828

	//for (i = 0; i < 50; i++)
	//{
	//	e = exp((double)(-i));

	//	d += e;
	//}
	//
	//e = 1 / (1 - exp(-1));

	//tokens[0] = " ABC ";
	//tokens_len[0] = strlen(tokens[0]);

	//tokens[1] = " EFG";
	//tokens_len[1] = strlen(tokens[1]);

	//tokens[2] = "HIL ";
	//tokens_len[2] = strlen(tokens[2]);

	//tokens[3] = " ";
	//tokens_len[3] = strlen(tokens[3]);

	//tokens[4] = " Z";
	//tokens_len[4] = strlen(tokens[4]);

	//tokens[5] = " Hello World! ";
	//tokens_len[5] = strlen(tokens[5]);

	//tokens[6] = "";
	//tokens_len[6] = strlen(tokens[6]);


	//tokens_max = 7;
	//rc = utils__libc__trim_tokens(tokens, tokens_len, tokens_max, ' ');

	//rc = utils__libc__print_tokens(tokens, tokens_len, tokens_max);


	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao ";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A ";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@@";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@";
	//buffer_2 = "@@CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@";
	//buffer_2 = "++CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @";
	//buffer_2 = "+@+CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @+";
	//buffer_2 = "@@+@+++CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @++";
	//buffer_2 = "@@";
	//buffer_2 = "";
	//buffer_2 = "+";
	//buffer_2 = "++";
	//buffer_2 = "+A+";
	//buffer_2 = "+@@@++@@@+++@@@";
	//buffer_2_len = strlen(buffer_2);
	//seps_len[0] = strlen(seps[0]);
	//seps_len[1] = strlen(seps[1]);
	//seps_count = sizeof(seps) / sizeof(char*);
	//tokens_max = sizeof(tokens) / sizeof(char*);




	//rc = utils__libc__tokenize_string(buffer_2, buffer_2_len, seps, seps_len, seps_count, tokens, tokens_len, tokens_max, &token_count);



	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao ";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A ";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@@";
	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@";
	//buffer_2 = "@@CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@";
	//buffer_2 = "++CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @";
	//buffer_2 = "+@+CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @+";
	//buffer_2 = "@@+@+++CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @++";
	//buffer_2 = "@@";
	//buffer_2 = "";
	//buffer_2 = "+";
	//buffer_2 = "++";
	//buffer_2 = "+A+";
	//buffer_2 = "+@@@++@@@+++@@@";
	//buffer_2_len = strlen(buffer_2);
	//seps_len[0] = strlen(seps[0]);
	//seps_len[1] = strlen(seps[1]);
	//seps_count = sizeof(seps) / sizeof(char*);
	//tokens_max = sizeof(tokens) / sizeof(char*);

	


	//rc = utils__libc__tokenize_string(buffer_2, buffer_2_len, seps, seps_len, seps_count, tokens, tokens_len, tokens_max, &token_count);

	//rc = utils__libc__print_tokens(tokens, tokens_len, token_count);



    //strcpy(buffer_3, "Hello !s World");
	//strcpy(buffer_3, "Hello !s World!");
	//strcpy(buffer_3, "!");
	//strcpy(buffer_3, "");
	//strcpy(buffer_3, "s");
	//strcpy(buffer_3, "!s");
	//strcpy(buffer_3, "!!");
	//strcpy(buffer_3, "!a");
	//strcpy(buffer_3, "!!s");
	//strcpy(buffer_3, "!!!s");
	//strcpy(buffer_3, "!!!!");
	//strcpy(buffer_3, "!!!!!");
	//strcpy(buffer_3, " YES; YES; D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\log\\i4mp_log.txt; 60; YES; SIEMENS-OPEN62541; YES; 5; NO; 0\\;99");
	//strcpy(buffer_3, " YES; YES; D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\log\\i4mp_log.txt; 60; YES; SIEMENS-OPEN62541; YES; 5; NO; 0\99");
	//strcpy(buffer_3, " YES; YES; D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\log\\i4mp_log.txt; 60; YES; SIEMENS-OPEN62541; YES; 5; NO; 0\\\\99");
	//strcpy(buffer_3, " YES; YES; D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\log\\i4mp_log.txt; 60; YES; SIEMENS-OPEN62541; YES; 5; NO; 0;;;99");
	//strcpy(buffer_3, " YES; YES; D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\log\\i4mp_log.txt; 60; YES; SIEMENS-OPEN62541; YES; 5; NO; 0=99");
	//strcpy(buffer_3, "\\;YES; YES; D:\\PROGS\\prog-97--i4mp\\deployment-examples\\project-1--windows\\example-1\\log\\i4mp_log.txt; 60; YES; SIEMENS-OPEN62541; YES; 5; NO; 0=99");


	
	//buffer_3_len = strlen(buffer_3);

	//printf("\"%.*s\"\n", (int)buffer_3_len, buffer_3);

	//escape_sequence = "!s;";
	//escape_sequence_len = 2;
	//ch = ';';

	//rc = utils__libc__unescape_buffer(buffer_3, buffer_3_len, escape_sequence, escape_sequence_len, ch, &buffer_new_len);
	//if (rc == 0)
	//{
	//	printf("\"%.*s\"\n", (int)buffer_new_len, buffer_3);
	//}


	//buffer_2 = "CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@";
	//buffer_2 = "@@CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @@";
	//buffer_2 = "++CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @";
	//buffer_2 = "+@+CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @+";
	//buffer_2 = "@@+@+++CIAO @@@ com+e stai * io bene @@@ grazie  ciao ?? ciao +A @++";



	return 0;

}







