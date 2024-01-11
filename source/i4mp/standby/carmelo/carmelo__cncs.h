#ifndef FGGR__CNC_H
#define FGGR__CNC_H

#include <utils__sdb.h>

typedef struct
{
	char data[4 * 1024];
	unsigned long len;

} fgg__buffer_t;


#define FGGR__CONFIG__SDB_RECORDS_MAX  1024
#define FGGR__CONFIG__SDB_BUFFER_SIZE  1024
#define FGGR__CONFIG__SDB_FIELDS_MAX     64



//#include "..\fggr.h"

#define FGGR__CNCS_PARAMETERS_MAX                          48
#define FGGR__CNCS_MACHINE_DATA_MAX                        64


#define CNC__FOCAS__ALARM__STATE             0x01
#define CNC__FOCAS__EMERGENCY__STATE         0x02
#define CNC__FOCAS__WARNING__STATE           0x04
#define CNC__FOCAS__STOP__STATE              0x08
#define CNC__FOCAS__RUN__STATE               0x10


#define   FGGR__CNCS__CMD__CONFIG                              0
#define   FGGR__CNCS__CMD__CONFIG_END                          1
#define   FGGR__CNCS__CMD__GET_MACHINE_DATA                    2
#define   FGGR__CNCS__CMD__GET_PROGRAMS_NAME                   3
#define   FGGR__CNCS__CMD__GET_PROGRAM                         4


//#define   FGGR__CNCS__CMD__GET_CONNECTION_STATUS             2
//#define   FGGR__CNCS__CMD__GET_ABSOLUTE_MACHINED_PARTS       3 
//#define   FGGR__CNCS__CMD__GET_PRODUCTION_STATUS             4
//#define   FGGR__CNCS__CMD__GET_ALARM_STATUS                  5



#define   FGGR__CNCS__CMD__FTP_DIR_LIST                      4 
#define   FGGR__CNCS__CMD__FTP_FILE_LIST                     5
#define   FGGR__CNCS__CMD__FTP_READ_FILE                     6 
#define   FGGR__CNCS__CMD__FTP_WRITE_FILE                    7 



#define   FGGR__CNCS__RESPONSE__OK         0
#define   FGGR__CNCS__RESPONSE__ERROR     -1


#define FGGR__CNCS__MACHINE_MAX                             20
#define FGGR__CNCS__MACHINE_CMD_MAX                        128
#define FGGR__CNCS__THREADS_PER_MACHINE                      2


#define FGGR__CNCS__PARAMETER_1_OFFSET                      12


typedef struct  
{
	fgg__buffer_t dir_path;

} fgg__cnc__config_t;




typedef struct 
{
	int command_status[FGGR__CNCS__MACHINE_CMD_MAX];
	int response[FGGR__CNCS__MACHINE_CMD_MAX];

} fgg__cncs__shell_t;

typedef struct
{

	fgg__buffer_t absolute_machine_part;
	fgg__buffer_t in_production;
	fgg__buffer_t in_alarm;
	fgg__buffer_t connect;
	fgg__buffer_t prog_in_exe;
	fgg__buffer_t cicle_time;
	fgg__buffer_t bar_feed;
	fgg__buffer_t instant_power;
	fgg__buffer_t average_power;


} fgg__cncs__live_data_t;



typedef struct
{
	int configurated;
	int thread_status[FGGR__CNCS__THREADS_PER_MACHINE];
	//fgg__buffer_t parameter[48];
	
	utils__sdb_t data;
	char buffer[FGGR__CONFIG__SDB_BUFFER_SIZE];
	unsigned long name_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *name[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long value_len[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *value[FGGR__CONFIG__SDB_FIELDS_MAX];
	int encoding[FGGR__CONFIG__SDB_FIELDS_MAX];



	utils__sdb_t data_value_cnc;
	char buffer_value_cnc[FGGR__CONFIG__SDB_BUFFER_SIZE];
	unsigned long name_len_value_cnc[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *name_value_cnc[FGGR__CONFIG__SDB_FIELDS_MAX];
	unsigned long value_len_value_cnc[FGGR__CONFIG__SDB_FIELDS_MAX];
	char *value_value_cnc[FGGR__CONFIG__SDB_FIELDS_MAX];
	int encoding_value_cnc[FGGR__CONFIG__SDB_FIELDS_MAX];

	fgg__cncs__shell_t shell;
	//timer_soft_sec_t timer;
	fgg__cncs__live_data_t live_data;
	fgg__buffer_t programs_name;

	fgg__buffer_t prog_numeber_to_read;

	//fgg__payload_t *payload;
	unsigned char get_data;

} fgg__cncs__machine_t;


typedef struct 
{
	fgg__cnc__config_t config;
	fgg__cncs__machine_t machine[FGGR__CNCS__MACHINE_MAX];
	unsigned long num_machines;

	fgg__buffer_t dir_path;

	unsigned long record_index[FGGR__CONFIG__SDB_RECORDS_MAX];

}  carmelo__cncs_t;



extern carmelo__cncs_t *carmelo__cncs;
//extern fgg__buffer_t fgg__machine_utimac_scy45ht__live_data[FGGR__CNCS_MACHINE_DATA_MAX];

//extern fgg__buffer_t fgg__machine_star__75__live_data[FGGR__CNCS_MACHINE_DATA_MAX];



unsigned int __stdcall fgg__machine_utimac_scy45ht__main_thread (void *arg);
unsigned int __stdcall carmelo__cncs__focas__main_thread (void *arg);
int carmelo__cncs__init (void);
int carmelo__cncs__start (void);
//int fgg__cncs__db__select_cnc_from_cncs (size_t id, fgg__buffer_t *name, fgg__buffer_t *value, size_t pairs_max, size_t *pairs_read, int *active);
int carmelo__cncs__db__select_cnc_from_cncs(unsigned long id, utils__sdb_t *data, int *active, const char *ascii_7_bit_characters_to_escape, unsigned long ascii_7_bit_characters_to_escape_len, unsigned long lang);
int fgg__cncs__command (int fd, int cmd, utils__sdb_t *data_sdb, unsigned long sequence,  fgg__buffer_t *payload);
int fgg__cncs__is_command_ended (int fd, int cmd, int *response, utils__sdb_t *data);
int carmelo__cncs__db__select_count_from_cncs(unsigned long *count);


int fgg__machines__init (void);
int fgg__machines__config (fgg__cnc__config_t *config);
int fgg__machines__start (void);
int fgg__machines__stop (void);
//void fgg__cncs__task (void);


int fgg__machines__command (int fd, int cmd, fgg__buffer_t *arg, size_t argc, size_t sequence,  fgg__buffer_t *payload);
int fgg__machines__is_command_ended (int fd, int cmd, int *response, size_t *arg_count, fgg__buffer_t *arg, size_t args_max);

int fgg__machines__get_cnc (fgg__buffer_t *id, fgg__buffer_t *name, fgg__buffer_t *value, size_t nv_count, size_t *nv_found, int *cnc_active);
int fgg__machines__get_cnc_count (size_t *count);
int fgg__machines__select_cnc_from_cncs (size_t id, fgg__buffer_t *name, fgg__buffer_t *value, size_t pairs_max, size_t *pairs_read, int *active);
int fgg__machines__present_cnc (fgg__buffer_t *name, fgg__buffer_t *value, size_t pairs_max, fgg__buffer_t *buf);


int fgg__machine_1__init (void);
int fgg__machine__1__begin_thread (size_t index);
int fgg__machine_1__end_thread (size_t index);
unsigned int __stdcall fgg__machine_1__main_thread (void *arg);
unsigned int __stdcall fgg__machine_1__simulator_thread (void *arg);



int fgg__cncs__2__init (void);
int fgg__machine_2__begin_thread (size_t index);
int fgg__cncs__2__end_thread (size_t index);
unsigned int __stdcall fgg__machine_2__main_thread (void *arg);
unsigned int __stdcall fgg__machine_2__simulator_thread (void *arg);




int fgg__cnc__focas_get_machined_parts (unsigned short fd, unsigned long *count);
int fgg__cnc__focas_get_number_program_in_execution (unsigned short fd, fgg__buffer_t *prog_in_execution);
int fgg__cnc__focas_get_program_code(unsigned short focas_handle, long prgnum, fgg__buffer_t *payload);
int fgg__cnc__focas_get_status (unsigned short fd, unsigned long *state);
int fgg__cnc__focas_is_connected (unsigned short fd);
int fgg__cnc__focas_read_name_of_all_programs (unsigned short focas_handle, fgg__buffer_t *buff);

int fgg__cnc__focas_connect (char* ip, char ip_len, char* port, char port_len, unsigned short *fd);


#endif