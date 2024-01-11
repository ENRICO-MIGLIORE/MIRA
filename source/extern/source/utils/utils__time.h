#ifndef UTILS__TIME_H
#define UTILS__TIME_H


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>


/*
 * year_buffer_size, month_buffer_size, day_buffer_size, buffer_size must all be greater than UTILS__TIME__BUFFER_SIZE
 */

#define UTILS__TIME__BUFFER_SIZE    16


int utils__time__get_date (char *year_buffer, size_t year_buffer_size, size_t *year_buffer_len, char *month_buffer, size_t month_buffer_size, size_t *month_buffer_len, char *day_buffer, size_t day_buffer_size, size_t *day_buffer_len);
int utils__time__get_iso_date (char *buffer, size_t buffer_size, size_t *buffer_len);
int utils__time__get_iso_extended_date (char *buffer, size_t buffer_size, size_t *buffer_len);
int utils__time__get_iso_extended_time (char *buffer, size_t buffer_size, size_t *buffer_len);
int utils__time__get_integer_date (size_t *number, size_t *year, size_t *month, size_t *day);


#endif

