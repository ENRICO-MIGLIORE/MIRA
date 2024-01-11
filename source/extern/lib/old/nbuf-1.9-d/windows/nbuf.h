#ifndef NBUF_H
#define NBUF_H

#include <stddef.h>
#include <string.h>

typedef struct
{
	size_t offset;
	size_t len;

} nbuf_token_t;

typedef struct
{
	size_t buffers_busy;
	size_t buffers_free;
	size_t alloc_count;
	size_t free_count;
	size_t chain_count;
	size_t error_on_alloc;
	size_t error_on_free;
	size_t error_on_chain;

} nbuf_stats_t;



#if 0
typedef struct
{
	char *data;
	size_t len;
	void *next;
	void *last;
	int busy;
	int child;

} nbuf_t;
#endif


typedef struct
{
	char *data;
	unsigned char len;
	void *next;
	void *last;
	int busy;
	int child;

} nbuf_1_t;


typedef struct
{
	char *data;
	unsigned short len;
	void *next;
	void *last;
	int busy;
	int child;

} nbuf_2_t;

typedef struct
{
	char *data;
	unsigned short len;
	void *next;
	void *last;
	int busy;
	int child;

} nbuf_3_t;

typedef struct
{
	//nbuf_t *buffer;
	//size_t buffers_max;
	//size_t data_size;
	//char *data;


	nbuf_1_t *buffer_1;
	size_t buffers_1_max;
	size_t data_1_size;
	char *data_1;

	nbuf_2_t *buffer_2;
	size_t buffers_2_max;
	size_t data_2_size;
	char *data_2;

	nbuf_3_t *buffer_3;
	size_t buffers_3_max;
	size_t data_3_size;
	char *data_3;

} nbuf__config_t;


int nbuf__init (void);
int nbuf__config (nbuf__config_t *conf);
//nbuf_t *nbuf__alloc (void);
//int nbuf__free (nbuf_t **b);
//int nbuf__chain (nbuf_t *b1, nbuf_t *b2);
//size_t nbuf__get_buffer_size (void);
//int nbuf__get_len (nbuf_t *b, size_t *len);
//int nbuf__get_buffer_chain_len (nbuf_t *b, size_t *chain_len);
//nbuf_t * nbuf__search(const nbuf_t *b, size_t start_offset, size_t stop_offset, const char *string, size_t string_len, size_t *string_offset);
//int nbuf__tokenize (const nbuf_t *b, size_t start_offset, size_t stop_offset, const char *seps, nbuf_token_t *token, size_t tokens_max, size_t *token_count);
//int nbuf_write (nbuf_t *b, const char *data, size_t len, size_t *len_written);
//nbuf_t * nbuf_read (nbuf_t *b, char *buffer, size_t offset, size_t buffer_size, size_t len_to_read, size_t *len_read);
//int nbuf__get_stats (nbuf_stats_t *stats);
//size_t nbuf__printf_buffer (nbuf_t *b);
//size_t nbuf__printf_buffer_chain (nbuf_t *b);



int nbuf__config_1 (nbuf__config_t *conf);
nbuf_1_t *nbuf__alloc_1 (void);
int nbuf__free_1 (nbuf_1_t **b);
int nbuf__chain_1 (nbuf_1_t *b1, nbuf_1_t *b2);
unsigned char nbuf__get_buffer_1_size (void);
int nbuf__get_len_1 (nbuf_1_t *b, size_t *len);
int nbuf__get_buffer_1_chain_len (nbuf_1_t *b, size_t *chain_len);
nbuf_1_t * nbuf__search_1 (const nbuf_1_t *b, size_t start_offset, size_t stop_offset, const char *string, size_t string_len, size_t *string_offset);
int nbuf__tokenize_1 (const nbuf_1_t *b, size_t start_offset, size_t stop_offset, const char *seps, nbuf_token_t *token, size_t tokens_max, size_t *token_count);
int nbuf_write_1 (nbuf_1_t *b, const char *data, size_t len, size_t *len_written);
nbuf_1_t * nbuf_read_1 (nbuf_1_t *b, char *buffer, size_t offset, size_t buffer_size, size_t len_to_read, size_t *len_read);
int nbuf__get_stats_1 (nbuf_stats_t *stats);
size_t nbuf__printf_buffer_1 (nbuf_1_t *b);
size_t nbuf__printf_buffer_1_chain (nbuf_1_t *b);


int nbuf__config_2 (nbuf__config_t *conf);
nbuf_2_t *nbuf__alloc_2 (void);
int nbuf__free_2 (nbuf_2_t **b);
int nbuf__chain_2 (nbuf_2_t *b1, nbuf_2_t *b2);
unsigned short nbuf__get_buffer_2_size (void);
int nbuf__get_len_2 (nbuf_2_t *b, size_t *len);
int nbuf__get_buffer_2_chain_len (nbuf_2_t *b, size_t *chain_len);
nbuf_2_t * nbuf__search_2 (const nbuf_2_t *b, size_t start_offset, size_t stop_offset, const char *string, size_t string_len, size_t *string_offset);
int nbuf__tokenize_2 (const nbuf_2_t *b, size_t start_offset, size_t stop_offset, const char *seps, nbuf_token_t *token, size_t tokens_max, size_t *token_count);
int nbuf_write_2 (nbuf_2_t *b, const char *data, size_t len, size_t *len_written);
nbuf_2_t * nbuf_read_2 (nbuf_2_t *b, char *buffer, size_t offset, size_t buffer_size, size_t len_to_read, size_t *len_read);
int nbuf__get_stats_2 (nbuf_stats_t *stats);
size_t nbuf__printf_buffer_2 (nbuf_2_t *b);
size_t nbuf__printf_buffer_2_chain (nbuf_2_t *b);



int nbuf__config_3 (nbuf__config_t *conf);
nbuf_3_t *nbuf__alloc_3 (void);
int nbuf__free_3 (nbuf_3_t **b);
int nbuf__chain_3 (nbuf_3_t *b1, nbuf_3_t *b2);
unsigned short nbuf__get_buffer_3_size (void);
int nbuf__get_len_3 (nbuf_3_t *b, size_t *len);
int nbuf__get_buffer_3_chain_len (nbuf_3_t *b, size_t *chain_len);
nbuf_3_t * nbuf__search_3 (const nbuf_3_t *b, size_t start_offset, size_t stop_offset, const char *string, size_t string_len, size_t *string_offset);
int nbuf__tokenize_3 (const nbuf_3_t *b, size_t start_offset, size_t stop_offset, const char *seps, nbuf_token_t *token, size_t tokens_max, size_t *token_count);
int nbuf_write_3 (nbuf_3_t *b, const char *data, size_t len, size_t *len_written);
nbuf_3_t * nbuf_read_3 (nbuf_3_t *b, char *buffer, size_t offset, size_t buffer_size, size_t len_to_read, size_t *len_read);
int nbuf__get_stats_3 (nbuf_stats_t *stats);
size_t nbuf__printf_buffer_3 (nbuf_3_t *b);
size_t nbuf__printf_buffer_3_chain (nbuf_3_t *b);

#endif
