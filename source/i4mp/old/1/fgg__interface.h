#ifndef FGGR__INTERFACE_H
#define FGGR__INTERFACE_H


int fgg__interface__read_value (const unsigned char *id, unsigned long id_count, unsigned char *value, unsigned long value_size, unsigned long *value_count);
int fgg__interface__write_value (const unsigned char *id, unsigned long id_count, const unsigned char *value, unsigned long value_size, unsigned long value_count);
#endif