#include "Softimer.h"
#include "Spi.h"

#define SOFTTIMER_START_SECT_DATA_UNINIT
#include "Memmap.h"
volatile unsigned int timeCounterMs = 0;
volatile unsigned int control_2 = 2;
#include "Memmap.h"
#define SOFTTIMER_STOP_SECT_DATA_UNINIT

#define SOFTTIMER_START_SECT_CODE
#include "Memmap.h"
void Softtimer_Init(SoftTimer *timer)
{
	
	STK_Reg->STK_CVR = 0; /* Disable systick timer */
	STK_Reg->STK_RVR = COUNTER1MS - 0x1; /* count down 1ms -> jump to interrupt --> counter++*/
	STK_Reg->STK_CVR = 0; /* Clear current value before enable it */
	
	/* Enable systick control */
	STK_Reg->STK_CSR |= (1 << 2); /* sellect clock source */
	STK_Reg->STK_CSR |= (1u << 1); /* enable systick interrupt */
	STK_Reg->STK_CSR |= 1; /* Counter enable */
	
	/*timer.timerID = count;*/
	timer->startTime = 0;
	timer->enableFlag = TRUE;
	timer->timeoutVal = 0;
	timer->timerMode = ONE_SHOT_MODE;
	timer->callback = NULL_PTR;
	
}

void Softtimer_StartTimer(SoftTimer *timer, unsigned int curTimeVal,
													unsigned int enableFlag, unsigned int timeoutVal,
													unsigned int timeMode, CALLBACK callback)
{
	timer->startTime = timeCounterMs;
	timer->enableFlag = enableFlag;
	timer->timeoutVal = timeoutVal;
	timer->timerMode = timeMode;
	timer->callback = callback;
	
}														
													
void Softtimer_StopTimer(SoftTimer *timer)
{
	timer->enableFlag = FALSE;
}

void Softtimer_MainFunction(SoftTimer *timer)
{
	
	if(timer->enableFlag == TRUE)
	{
		
		if(timeCounterMs >= (timer->startTime + timer->timeoutVal))
		{
			timer->callback();
			if (timer->timerMode == ONE_SHOT_MODE)
			{
					timer->enableFlag = FALSE;
			}
			else if (timer->timerMode == CONTINUOUS_MODE)
			{
				timer->startTime = timeCounterMs;
			}
		} 
	}
}

void SysTick_Handler( void )
{
	timeCounterMs++;
}

#define SOFTTIMER_STOP_SECT_CODE
#include "Memmap.h"

