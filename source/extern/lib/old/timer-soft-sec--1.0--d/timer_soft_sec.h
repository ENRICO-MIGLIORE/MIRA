#ifndef TIMER_SOFT_SEC_H
#define TIMER_SOFT_SEC_H

 
#ifndef NULL
#define	NULL ((void *) 0)
#endif


#include <time.h>

typedef struct
{
	time_t time;
	time_t seconds;
	int state;

} timer_soft_sec_t;

int timer_soft_sec_start (timer_soft_sec_t *timer, time_t seconds);
int timer_soft_sec_is_expired (timer_soft_sec_t *timer);


#endif
