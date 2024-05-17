#ifndef LPUART_H
#define LPUART_H
#include "Gpio.h"
#include "Gpio_Register.h"
#include "Spi.h"

#define NG 0
#define OK 1

#define UNINIT 0
#define IDLE 1
#define BUSY 2
#define EMPTY 3
#define NOT_EMP 4

#define UART1_RX 6
#define UART1_TX 7

#define BUFFER_SIZE 100

#define START_STS 0
#define ALARM_STS 1
#define PENDING_STS 2

#define NULL_PTR ((unsigned char*)0)

typedef struct
{
	unsigned char u1_TxBufferData[BUFFER_SIZE];
	uint32 length;
} Tx_Buffer;
typedef struct
{
	unsigned char u1_RxBufferData[BUFFER_SIZE];
	uint32 u4_Read_Counter;
	uint32 u4_Write_Counter;
	uint32 u4_Length;
} Rx_Buffer;
extern Tx_Buffer txBuffer;
extern Rx_Buffer rxBuffer;

void Uart_init(void);
void Buffer_init(void);

unsigned char Uart_Transmit(unsigned char* u1_TxBuffer, unsigned int length);
unsigned char Uart_GetTransmitState(void);
void Uart_TxMainFunction(void);

unsigned int Uart_ReceiveData(unsigned char* u1_RxBuffer);
unsigned char Uart_GetReceiveState(void);
void Uart_RxMainFunction(void);

void LPUART1_RxTx_IRQHandler(void);

#endif
