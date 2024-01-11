#ifndef UTILS__PLATFORM_H
#define UTILS__PLATFORM_H

#include <stddef.h>

int utils__platform__create_path (const char *dir_path);
int utils__platform__does_path_exist (const char *dir_path);
int utils__platform__create_directory_by_dir_name (char *dir_path, const char *dir_name);
int utils__platform__build_fully_qualified_file_name (char *buffer, size_t buffer_size, const char *path, const char *file_name);
int utils__platform__make_absolute_file_name (const char *path, const char *name_prefix, const char *name, const char *name_separator, const char *file_extension, char *file_name, size_t file_name_size, size_t *file_name_len);
int utils__platform__does_file_exist (const char *file_name);
int utils__platform__create_empty_file (const char *file_name);
int utils__platform__empty_file (const char *file_name);
int utils__platform__remove_file (const char *file_name);
int utils__platform__touch_file (const char *file_name);
void utils__platform__sleep (size_t milliseconds);
int utils__platform__get_path_separator (char *path_separator, size_t path_separator_size);

#endif