#include "fgg__system.h"


/*
 * "INFO,FPW,sdfsdfsdfsdfsd"
 */
typedef struct
{
	size_t head;
	size_t tail;
	size_t count;
	size_t size;
    char *data[1024];
	size_t len[1024];

} fgg__system__message_queue_t;


fgg__system__message_queue_t message_queue;


int fgg__system__message_queue__init (void)
{
	char *buffer;
	int i;

	for (i = 0; i < 1024; i++)
	{
		buffer = (char *) malloc(256);

		message_queue.data[i] = buffer;
		message_queue.len[i] = 0;
	}

	message_queue.head = 0;
	message_queue.tail = 0;
	message_queue.count = 0;
	message_queue.size = 256;
}

int fgg__system__message_enque (char *message)
{
	size_t len;
	 
	
	if (message_queue.count >= message_queue.size)
	{
		return -10;
	}

	len = strlen(message);

	if (len >= message_queue.size)
	{
		return -20;
	}

	strcpy(message_queue.data[message_queue.head], message);

	message_queue.head++;

	if (message_queue.head >= message_queue.size)
	{
		message_queue.head = 0;  /* rollover */
	}

	message_queue.count++;
}


int fgg__system__message_deque (char *message ,size_t message_size)
{
	if (message_queue.count == 0)
	{
		return -10;
	}

	if (message_queue.len[message_queue.tail] >= message_size)
	{
		return -20;
	}

	strcpy(message, message_queue.data[message_queue.tail]);

	message_queue.tail++;
	if (message_queue.tail >= message_queue.size)
	{
		message_queue.tail = 0;  /* rollover */
	}

	message_queue.count--;
}



void fgg__system__printf (int level, int channel, const char *source, const char* message, ...)
{

	FILE *f;
	fgg__buffer_t buffer;
	fgg__date_t date;
	fgg__time_t time;
	int rc;
	char *info;
	char *warning;
	char *error;
	char *p;
	va_list argptr;
	int len;

#if 0	

	f = fopen ((const char *) fgg__system.log__file_name.data, "ab");
	if (f == NULL)
	{
		return;
	}

	rc = fgg__util__get_date(&date);
	rc |= fgg__util_get_time(&time);
	if (rc != 0)
	{
		return;
	}

	date.iso_extended.data[date.iso_extended.len] = '\0';
	time.iso_extended.data[time.iso_extended.len] = '\0';

	error =  "ERROR";
	info =  "INFO";
	warning =  "WARNING";


	if (level == FGG__SYSTEM__LOG__INFO)
	{
		p = info;
	}
	else if (level == FGG__SYSTEM__LOG__WARNING)
	{
		p = warning;
	}
	else 
	{
		p = error;
	}

	len = sprintf (buffer.data, "[%s %s] [%s] [%s] ",date.iso_extended.data, time.iso_extended.data, source, p);

	if (len <= 0)
	{
		return;
	}

	buffer.len = (size_t) len;
	(void) fwrite (buffer.data, 1, buffer.len, f);

	va_start(argptr, message);
	vfprintf(f, message, argptr);	
	va_end(argptr);

	(void) fwrite ("\r\n", 1, 2, f);

	fclose (f);

#endif
}

