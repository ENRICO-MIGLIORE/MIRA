#ifndef BOA_2__H
#define BOA_2__H

#include <boa_2__toolchain.h>

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include <nbuf.h>
#include <text.h>


#define BOA_2__STATE__NOT_READY          			                  0
#define BOA_2__STATE__READY          			                      1


#define BOA_2__MIN_NBUF_SIZE          			                      8
#define BOA_2__NBUF_1_SIZE_MIN          			                  8


#define BOA_2__LOG_MESSAGE__ARG3_SIZE          			             32

#define BOA_2__LOG_MESSAGE__INFO          			                  0
#define BOA_2__LOG_MESSAGE__WARNING          			              1
#define BOA_2__LOG_MESSAGE__ERROR          			                  2


#define BOA_2__REQUEST__CONNECTION_KEEP_CLOSE			              0
#define BOA_2__REQUEST__CONNECTION_KEEP_ALIVE			              1


#define BOA_2__MIME_TYPE__TEXT_HTML          			              0
#define BOA_2__MIME_TYPE__APPLICATION_PDF          			          1
#define BOA_2__MIME_TYPE__APPLICATION_OCTET_STREAM          	      2
#define BOA_2__MIME_TYPE__TEXT_PLAIN          	                      3
#define BOA_2__MIME_TYPE__IMAGE_JPEG          	                      4
#define BOA_2__MIME_TYPE__TEXT_CSS          	                      5
#define BOA_2__MIME_TYPE__IMAGE_PNG          	                      6
#define BOA_2__MIME_TYPE__IMAGE_GIF          	                      7
#define BOA_2__MIME_TYPE__IMAGE_SVG_XML          	                  8

#define BOA_2__MIME_TYPES_MAX          			                      9


#define BOA_2__REQUEST__GET                                                     10
#define BOA_2__REQUEST__POST__MULTIPART__HEADER_AND_CHUNK_OF_PAYLOAD            20
#define BOA_2__REQUEST__POST__MULTIPART__CHUNK_OF_PAYLOAD                       30
#define BOA_2__REQUEST__POST__MULTIPART__LAST_CHUNK_OF_PAYLOAD                  40

#define BOA_2__POST__URL_ENCODED_CHUNKED__1                                    50
#define BOA_2__POST__URL_ENCODED_CHUNKED__2                                    60
#define BOA_2__POST__URL_ENCODED_CHUNKED__3                                    70
#define BOA_2__POST__URL_ENCODED_COMPLETE                                      80


#define BOA_2__RESPONSE_TYPE__ERROR                                                  -1



#define BOA_2__REQUEST_HEADERS_MAX                     5


#define BOA_2__RESPONSE_HEADER_SET_COOKIE              0
#define BOA_2__RESPONSE_HEADER_SERVER                  1
#define BOA_2__RESPONSE_HEADER_CONNECTION              2
#define BOA_2__RESPONSE_HEADER_CONTENT_LENGTH          3
#define BOA_2__RESPONSE_HEADER_CONTENT_TYPE            4
#define BOA_2__RESPONSE_HEADER_CONTENT_ENDCODING       5
#define BOA_2__RESPONSE_HEADER_CONTENT_DATE            6

#define BOA_2__RESPONSE_HEADERS_MAX                    7






typedef struct
{
	char *data;
	size_t len;

} boa_2__buffer_t;



typedef struct
{
	int level; /* INFO WARNING ERROR */
	int type;  
	char *text;  
	unsigned int time;
	int argc;
	unsigned long arg_1;
	unsigned long arg_2;
    char arg_3[32];

} boa_2__log_message_t;


typedef struct
{
	boa_2__log_message_t *body;
	unsigned short head;
	unsigned short tail;
	unsigned short count;
	unsigned short size;

} boa_2__log_message_queue_t;




typedef struct
{
	int state;
	signed char rc;
	void *file;

} boa_2__application_t;


typedef struct
{
	size_t retained_len;
	size_t boundary_offset;
	size_t boundary_len;
	size_t boundary_index;
	nbuf_3_t *header_nbuf;

} boa_2__request_post_multipart_t;


typedef struct
{
	char method;
	char type;
	nbuf_2_t *uri_nbuf;
	nbuf_1_t *header__host_nbuf;
	nbuf_1_t *header__connection_nbuf;
	nbuf_1_t *header__content_length_nbuf;
	nbuf_2_t *header__content_type__boundary_nbuf;
	nbuf_2_t *header__cookie_nbuf;
	nbuf_3_t *body_nbuf;
	unsigned char header_count;	
	signed char header_name_winner;
	size_t header_value_total_len;
	unsigned short content_length;
	unsigned short content_length_index;
	
	size_t fd;

	signed char *header_name_flag;
	signed char *header_host_name_winner_flag;
	signed char header_host_winner_index;

	size_t residual;

	boa_2__request_post_multipart_t post_multipart;
	size_t atomic_cnt;

	unsigned char content_type_index;
	unsigned char content_type_state;

} boa_2__request_t;


typedef struct
{

	nbuf_3_t *body_nbuf;
	unsigned char mime_type;
	char *uri_responce;
	size_t page_offset;
	size_t page_current;

} boa_2__response_t;


typedef struct
{
	boa_2__request_t request;
	boa_2__response_t response;
	size_t fd;

} boa_2__connection_data_t;


typedef struct 
{
	size_t *body;
	size_t size;     
	size_t head;     
	size_t tail;     
	size_t count;    

} boa2__request_queue_t;

typedef struct 
{
	size_t *body;
	size_t size;     
	size_t head;     
	size_t tail;     
	size_t count;    

} boa2__response_queue_t;


typedef struct
{
	boa_2__socket_fd socket_fd;
	unsigned short ip_v4_port;
	unsigned long ip_v4_address;

	int parser_state;

	unsigned short uri_len;
	nbuf_3_t *recv_nbuf;
	int close_request;
	time_t time;

	unsigned char request__header__current_name_len;
	unsigned short request__hacker__header_value_len;


	size_t request__header__host_name_count;
	unsigned char request__header__name_found;
	unsigned char request__header__index;
	unsigned char protocol_count;
	boa_2__connection_data_t data;

    signed char vhost_fd;

} boa_2__connection_t;

typedef struct
{
	int opened;
	boa_2__buffer_t name;

	boa2__request_queue_t request_queue;
	int semaphore;
	int rc;
	int server_rc;
	unsigned int time;
	size_t data_fd;
	boa_2__connection_data_t *data;

} boa_2__vhost_t;


typedef struct
{
	boa_2__socket_fd rendezvous_socket;
	fd_set *recv_fd_set;
	size_t recv_fd_set_size;
	size_t recv_fd_sets_max;
	boa_2__connection_t *conn;
	size_t connections_max;
	unsigned char nbuf_1_size;
	unsigned short nbuf_2_size;
	unsigned short nbuf_3_size;

	size_t connections_active_count;
	size_t connections_available_tag;
	size_t select_function_timeout__seconds;
	size_t select_function_timeout__microseconds;
	unsigned short ip_v4_port;

	time_t socket_inactivity_timeout__seconds;
	signed char *header_name_flag;
	signed char *header_vhost_name_flag;
	size_t *state_0_connection;
	size_t *state_1_connection;
	size_t *state_2_connection;
	size_t *state_3_connection;
	size_t send_buffer_size;
	char *send_buffer;

	boa_2__vhost_t *vhost;

	int vhosts_max;
	boa_2__buffer_t *vhost_name;
	size_t *vhosts__request_body;
	boa_2__log_message_t *log_message;
	unsigned short log_messages_max;

	int listen_function__backlog;

	unsigned int time;
	unsigned char form_data_boundary_len_max;


	/*
	 * limits
	 */
	unsigned short uri__len_max;
	unsigned char content_length__len_max;
	unsigned char host__len_max;
	unsigned char connection__len_max;
	unsigned short cookie__len_max;
	unsigned char content_type__len_max;

	unsigned char header_name__len_max;


} boa_2__config_t;



int boa_2__init (void);
int boa_2__config (boa_2__config_t *config);
int boa_2__start (void);
int boa_2__stop (void);
int boa_2__get_state (void);
void boa_2__task (void);
void boa_2__set_time (unsigned int t);
int boa_2__open_vhost (char *vhost_name);

int boa_2__read_semaphore (int vhost_fd);
void boa_2__write_semaphore (int vhost_fd, int value);
void boa_2__write_return_code (int vhost_fd, int value);
int boa_2__read_return_code (int vhost_fd);

boa_2__connection_data_t * boa_2__get_data (int vhost_fd);
boa_2__log_message_t *boa_2__dequeue_log_message (void);
unsigned char boa_2__get_mime_type (char *file_name);



#endif