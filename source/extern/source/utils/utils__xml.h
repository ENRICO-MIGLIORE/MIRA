#ifndef UTILS__XML_H
#define UTILS__XML_H


#include <stddef.h>


int utils__xml__extract_inner_xml(const char* xml_document, size_t xml_document_len, const char* name, size_t name_len, char* value, size_t value_size, size_t* value_len);


#endif
