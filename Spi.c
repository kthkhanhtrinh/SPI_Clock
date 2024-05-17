#include "Spi.h"
#include "Lpuart.h"

Spi_clock alarm;
Spi_clock tmp_alarm;
Spi_clock clockDummy;
static short int pos = 7;
void Lpspi_init(void)
{
	/*Clock init*/
	SCG_Reg->FIRCDIV |= 1 << 8;
	
	/* Pin number        | Function
	* ----------------- |------------------
	* PTB14             | LPSPI1_SCK
	* PTB15             | LPSPI1_SIN
	* PTB16			        | LPSPI1_SOUT
	* PTB17			        | LPSPI1_PCS3 */
	
	/*Setting SCK/PCS/SOUT/SIN pin*/
	PCC_Reg->PCC_PORTB |= 1 << 30;
	PORTB->PCR[PTB14] |= 3 << 8;
	PORTB->PCR[PTB15] |= 3 << 8;
	PORTB->PCR[PTB16] |= 3 << 8;
	PORTB->PCR[PTB17] |= 3 << 8;
	
	/*Select source LPUART*/
	PCC_Reg->PCC_LPSPI1 |= 3 << 24 ;
	PCC_Reg->PCC_LPSPI1 |= 1 << 30;
	
	/*Setting baud rate*/
	LPSPI1_Reg->CCR |= 4 ;
	LPSPI1_Reg->CCR |= 4 << 24 ;
	LPSPI1_Reg->CCR |= 4 << 16;
	
	LPSPI1_Reg->TCR |= (3  << 27) | (15) | (3 << 24);
	
	/*Setting transmit/ Receive fifo*/
	LPSPI1_Reg->FCR |= 3;
	LPSPI1_Reg->CFGR1 |= 1 << 3;
	
	/*Config LPSPI mode*/
	LPSPI1_Reg->CFGR1 |= 1;
	LPSPI1_Reg->CR |= 1 << 3;
	
	/*Enable LPSPI mode*/
	LPSPI1_Reg->CR |= 1;
	
}
void Lpspi_sendChar(unsigned short data)
{
	while((LPSPI1_Reg->SR & 1) == 0){}
	LPSPI1_Reg->TDR = data;
}

void Lpsi_clockIncrease(void)
{
	alarm.sec1+=0x001;
	if(alarm.sec1 > 0x109)
	{
		alarm.sec2 += 0x001;
		alarm.sec1 = 0x100;
	}
	
	if (alarm.sec2 >=0x206)
	{
		alarm.sec2 = 0x200;
		alarm.min4+=0x001;
	}
	if (alarm.min4 > 0x409)
	{
		alarm.min4 = 0x400;
		alarm.min5+=0x001;
	}
	if (alarm.min5 >= 0x506)
	{
		alarm.min5 = 0x500;
		alarm.hour7+=0x001;
	}
	if (alarm.hour7 > 0x709)
	{
		alarm.hour7 = 0x700;
		alarm.hour8+=0x001;
	}
	if(alarm.hour8 > 0x801 && alarm.hour7 > 0x704)
	{
		alarm.hour7 = 0x700;
		alarm.hour8 = 0x800;
	}
	//Lpspi_Alarmshow();
	Lpspi_checkAlarmOff();
}

void Lpspi_Alarmshow(Spi_clock tmp)
{
	Lpspi_AlarmSend(tmp);
}

void Lpspi_clockSet(unsigned char *u1_rxBuffer, Spi_clock *tmp)
{
	
	uint16 c = (*u1_rxBuffer) - '0';
	if(c < 1)
		c = 0;
	if(pos == 7)
	{
		tmp->hour8 = 0x800;
		tmp->hour8 += c;
	}
  if(pos == 6)
	{
		tmp->hour7 = 0x700;
		tmp->hour7 += c;
	}
  if(pos == 5)
	{
		tmp->dummy6 = 0x60a;
	}
  if(pos == 4)
	{
		tmp->min5 = 0x500;
		tmp->min5 += c;
	}
	if(pos == 3)
	{
		tmp->min4 = 0x400;
		tmp->min4 += c;
	}
	if(pos == 2)
	{
		tmp->dummy3 = 0x30a;
	}
  if(pos == 1)
	{
		tmp->sec2 = 0x200;
		tmp->sec2 += c;
	}
	if(pos == 0)
	{
		tmp->sec1 = 0x100;
		tmp->sec1 += c;
		stateClock = RUN;
		//Buffer_init();
		//Lpspi_tmp_alarm_set();
	}
	pos--;
	if(pos < 0)
		pos = 7;
}


void Lpspi_checkAlarmOff(void)
{
	if(alarm.hour8 == tmp_alarm.hour8)
	{
		if (alarm.hour7 == tmp_alarm.hour7)
		{
			if (alarm.min5 == tmp_alarm.min5)
			{
				if (alarm.min4 == tmp_alarm.min4)
				{
					if (alarm.sec2 == tmp_alarm.sec2)
					{
						if (alarm.sec1 == tmp_alarm.sec1)
						{
								stateClock = ALARM_OFF;
						}

					}
						
				}
					
			}
				
		}
			
	}

}

void Lpsi_minuteIncrease(void)
{
	alarm.min4++;
	if (alarm.min4 > 0x409)
	{
		alarm.min4 = 0x400;
		alarm.min5+=0x001;
	}
	if (alarm.min5 > 0x505)
	{
		alarm.min5 = 0x500;
	}
}
void Lpsi_hourIncrease(void)
{
	alarm.hour7++;
	if (alarm.hour7 > 0x709 )
	{
		alarm.hour7 = 0x700;
		alarm.hour8+=0x001;
	}
	if(alarm.hour8 > 0x801 && alarm.hour7 > 0x703)
	{
		alarm.hour7 = 0x700;
		alarm.hour8 = 0x800;
	}
}


void Lpspi_AlarmInit(void)
{
	alarm.sec1 = 0x100;	
	alarm.sec2 = 0x200;
	alarm.min4 = 0x400;
	alarm.min5 = 0x500;
	alarm.hour7 = 0x700;
	alarm.hour8 = 0x800;
	alarm.dummy3 = 0x30a;
	alarm.dummy6 = 0x60a;
	
	tmp_alarm.sec1 = 0x100;	
	tmp_alarm.sec2 = 0x200;
	tmp_alarm.min4 = 0x400;
	tmp_alarm.min5 = 0x500;
	tmp_alarm.hour7 = 0x700;
	tmp_alarm.hour8 = 0x800;
	tmp_alarm.dummy3 = 0x30a;
	tmp_alarm.dummy6 = 0x60a;
}

void Lpspi_AlarmSend(Spi_clock tmp)
{
	Lpspi_sendChar(tmp.hour7);
	Lpspi_sendChar(tmp.hour8);
	Lpspi_sendChar(tmp.min4);
	Lpspi_sendChar(tmp.min5);
	Lpspi_sendChar(tmp.sec1);
	Lpspi_sendChar(tmp.sec2);
	Lpspi_sendChar(tmp.dummy3);
	Lpspi_sendChar(tmp.dummy6);
}

void Lpsi_clockBlinking(void)
{
	static uint8 blinkState = 0;
	blinkState = 1 - blinkState;
	if(blinkState == 1)
	{
		clockDummy.sec1 = 0x10f;	
		clockDummy.sec2 = 0x20f;
		clockDummy.min4 = 0x40f;
		clockDummy.min5 = 0x50f;
		clockDummy.hour7 = 0x70f;
		clockDummy.hour8 = 0x80f;
		clockDummy.dummy3 = 0x30f;
		clockDummy.dummy6 = 0x60f;
	}
	else
	{
		clockDummy.sec1 = 0x10a;	
		clockDummy.sec2 = 0x20a;
		clockDummy.min4 = 0x40a;
		clockDummy.min5 = 0x50a;
		clockDummy.hour7 = 0x70a;
		clockDummy.hour8 = 0x80a;
		clockDummy.dummy3 = 0x30a;
		clockDummy.dummy6 = 0x60a;
	}
	Lpspi_Alarmshow(clockDummy);
}

