#ifndef SPI_H
#define SPI_H

#include "Gpio_Register.h"

#define PTB14 14
#define PTB15 15
#define PTB16 16
#define PTB17 17

#define PENDING 0
#define RUN 1
#define ALARM_SETTING 2
#define CLOCK_SETTING 3
#define ALARM_OFF 4

typedef struct
{
	volatile uint16 sec1;
	volatile uint16 sec2;
	volatile uint16 dummy3;
	volatile uint16 min4;
	volatile uint16 min5;
	volatile uint16 dummy6;
	volatile uint16 hour7;
	volatile uint16 hour8;
} Spi_clock;

extern Spi_clock alarm;
extern Spi_clock tmp_alarm;
extern Spi_clock clockDummy;

void Lpspi_init(void);
void Lpspi_sendChar(unsigned short data);

void Lpsi_clockIncrease(void);
void Lpspi_clockSet(unsigned char *u1_rxBuffer, Spi_clock *tmp);
void Lpsi_clockBlinking(void);

void Lpsi_minuteIncrease(void);
void Lpsi_hourIncrease(void);

void Lpspi_AlarmInit(void);
void Lpspi_Alarmshow(Spi_clock tmp);
void Lpspi_AlarmSend(Spi_clock tmp);
void Lpspi_checkAlarmOff(void);

void Lpspi_tmp_alarm_set(uint16 c, short int pos);
#endif
