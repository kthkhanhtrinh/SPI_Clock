#include "Gpio_Isr.h"

#define ISR_START_SECT_DATA_ZEROINIT
#include "Memmap.h"
volatile button_num tmp_program = PG1;
#define ISR_STOP_SECT_DATA_ZEROINIT
#include "Memmap.h"

#define IRS_START_SECT_CODE
#include "Memmap.h"
void PORTC_IRQHandler(void){
	/*Check interrupt btn0 = 12*/
	if( Gpio_GetPinValue(&PORTC->PCR[BTN0], 24) == 1)
	{
		/*write 1 to clear interrupt signal*/
		Gpio_SetPinValue(&PORTC->PCR[BTN0], 24, 1);
		Lpsi_minuteIncrease();
	}
	
	if( Gpio_GetPinValue(&PORTC->PCR[BTN1], 24) == 1)
	{
		Gpio_SetPinValue(&PORTC->PCR[BTN1], 24, 1);
		Lpsi_hourIncrease();
	}
}
#define IRS_STOP_SECT_CODE
#include "Memmap.h"
