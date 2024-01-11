#ifndef NBUF_PRIVATE_H
#define NBUF_PRIVATE_H


typedef struct
{
	nbuf__config_t config;
	int configured;

	//size_t buffer_size;

	unsigned char buffer_1_size;
	unsigned short buffer_2_size;
	unsigned short buffer_3_size;

	nbuf_stats_t stats;

	nbuf_stats_t stats_1;
	nbuf_stats_t stats_2;
	nbuf_stats_t stats_3;

} nbuf_private_t;

extern nbuf_private_t nbuf;

#endif
