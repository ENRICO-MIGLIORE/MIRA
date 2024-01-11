#ifndef FANUC_FOCAS_H
#define FANUC_FOCAS_H


extern int fanuc_focas__init (int argc, char *argv[]);
extern int fanuc_focas__config (void);
extern int fanuc_focas__start (void);
extern char* fanuc_focas__get_version(void);


extern int fanuc_focas__get_machine_count (size_t* total_number_of_machines);
extern int fanuc_focas__get_communications_enabled_machine_count(size_t* count);
extern int fanuc_focas__get_communications_enabled_machine_id(size_t* machine_id, size_t total_number_of_machines);
extern int fanuc_focas__get_connection_status(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len, int mode);
extern int fanuc_focas__get_part_counter(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len, int mode);
extern int fanuc_focas__get_cycle_time(size_t machine_id, char* buffer, size_t buffer_size, size_t* buffer_len, int mode);


#endif
