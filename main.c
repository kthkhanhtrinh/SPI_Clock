#include "Gpio.h"
#include "Lpuart.h"
#include "Softimer.h"
#include "Spi.h"
#include "Gpio_Register.h"


volatile uint8 stateClock = PENDING;


int main(void)
{
	Gpio_init();
	Lpspi_init();
	Uart_init();
	unsigned int i;
	for(i = 0;i < SOFTTIMER_NUM;i++)
	{
		Softtimer_Init(&softTimer[i]);		
	}
	/* 5 second - blink blue 5s*/
	Softtimer_StartTimer(&softTimer[TIMER_ID_0], timeCounterMs, 
												TRUE, 5, CONTINUOUS_MODE, &Lpsi_clockBlinking);
	/* 1 second */
	Softtimer_StartTimer(&softTimer[TIMER_ID_1], timeCounterMs, 
												TRUE, 10, CONTINUOUS_MODE, &Lpsi_clockIncrease);
	/*1 second */
	Softtimer_StartTimer(&softTimer[TIMER_ID_2], timeCounterMs, 
												TRUE, 5, CONTINUOUS_MODE, &Ggio_blinkLed);
	/*0.5 sec*/
	Softtimer_StartTimer(&softTimer[TIMER_ID_3], timeCounterMs, 
												TRUE, 5, CONTINUOUS_MODE, &Ggio_blinkLed_Blue);
	Buffer_init();
	Gpio_ledOff();
	Lpspi_AlarmInit();
	//Lpspi_AlarmSend();
	stateClock = PENDING;
	
	//Buffer_init();
	Uart_Transmit("\nWelcome, please set the time\n", 30);
		
	while(1)
	{
		Uart_TxMainFunction();
		Uart_ReceiveData(rxBuffer.u1_RxBufferData);
		
		if(stateClock == RUN)
		{
			Gpio_ledOff();
			Lpspi_Alarmshow(alarm);	
		}
		else if(stateClock == PENDING)
		{
			Softtimer_MainFunction(&softTimer[TIMER_ID_0]); /*alarm blinky*/
			//Lpspi_Alarmshow(alarm);
		}
		else if(stateClock == ALARM_SETTING)
		{
			Softtimer_MainFunction(&softTimer[TIMER_ID_3]); /*blink blue led*/
			//Lpspi_Alarmshow(tmp_alarm);
		}
		else if(stateClock == ALARM_OFF)
		{
			Lpspi_Alarmshow(tmp_alarm);
			Softtimer_MainFunction(&softTimer[TIMER_ID_2]);
		}
		
		Softtimer_MainFunction(&softTimer[TIMER_ID_1]);
		
	}
	
}
