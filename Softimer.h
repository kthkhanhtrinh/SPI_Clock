#ifndef SOFTTIMER_H
#define SOFTTIMER_H

#include "Gpio.h"
#include "Gpio_Register.h"


#define COUNTER1MS  4800000U
#define COUNTER5MS 24000000U
#define COUNTER10S (unsigned int)48000000000U
	
#define SOFTTIMER_NUM				((unsigned char)4)

#define TIMER_ID_0  ((unsigned int)(0u))
#define TIMER_ID_1  ((unsigned int)(1u))
#define TIMER_ID_2  ((unsigned int)(2u))
#define TIMER_ID_3  ((unsigned int)(3u))
#define TIMER_ID_4  ((unsigned int)(4u))
#define TIMER_ID_5  ((unsigned int)(5u))
	
#define NULL_PTR				((void*)0)
#define TRUE						((unsigned char)1)
#define FALSE						((unsigned char)0)

#define INIT_MODE           ((unsigned char)(0))
#define ONE_SHOT_MODE       ((unsigned char)(1))
#define CONTINUOUS_MODE     ((unsigned char)(2))
#define TWO_SHOT_MODE				((unsigned char)(3))
	
typedef void (*CALLBACK)(void);

void function(void);

typedef struct Softtimer
{
	unsigned int timerID;
	unsigned int startTime;
	unsigned int enableFlag;
	unsigned int timeoutVal;
	unsigned int timerMode;
	CALLBACK callback;	
} SoftTimer;

#define SOFTTIMER_START_SECT_DATA_UNINIT
#include "Memmap.h"
extern volatile unsigned int timeCounterMs;
extern volatile unsigned int TIMER_ID;
#define SOFTTIMER_STOP_SECT_DATA_UNINIT
#include "Memmap.h"

static SoftTimer softTimer[SOFTTIMER_NUM];

void Softtimer_Init(SoftTimer *softTimer);
void Softtimer_StartTimer( SoftTimer *softTimer, unsigned int curTimeVal,
													unsigned int enableFlag, unsigned int timeoutVal,
													unsigned int timeMode, CALLBACK callback);
void Softtimer_StopTimer(SoftTimer *softTimer);
void Softtimer_MainFunction( SoftTimer *softTimer );
void SysTick_Handler( void );


#endif /*SOFTTIMER_H*/
