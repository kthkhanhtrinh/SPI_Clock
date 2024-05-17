#include "Lpuart.h"


static volatile uint8 u1_TransmitState = IDLE;
static volatile uint8 u1_ReceiveState = EMPTY;
static volatile unsigned int u4_ReceiveLength = 0;
Tx_Buffer txBuffer;
Rx_Buffer rxBuffer;


//volatile unsigned char stateClock = PENDING;


void Uart_init(void)
{
	NVIC_Reg->NVIC_ISER[33/32] |= 1 << (33%32); 	/* Config NIVIC */
	SCG_Reg->FIRCDIV |= 1 << 8;	/*set clock div 1*/
	PCC_Reg->PCC_PORTC |= 1 << 30; 	/*enable port C*/
	PORTC->PCR[UART1_RX] |= 2 << 8;  	/*1. Set Tx/Rx Pin*/ 
	PORTC->PCR[UART1_TX] |= 2 << 8;
	PCC_Reg->PCC_LPUART1 |= 3 << 24 | 1 << 30; 	/*2. Select source LPUART*/
	
	/*3. Set baud rate*/
	LPUART1->BAUD = 19 << 24;
	LPUART1->BAUD |= 0xFA;
	LPUART1->CTRL &= ~(1u << 4) | ~(1u << 1);	
	
	/*Enable receiver interrupt*/
	LPUART1->CTRL |= 1 << 21 ;
	/*Enable transmitter receiver*/
	LPUART1->CTRL |= 3 << 18;
	
	u1_TransmitState = IDLE;
	u1_ReceiveState = EMPTY;
}

void Buffer_init(void)
{
	txBuffer.length = 0;
	rxBuffer.u4_Length = 0;
	rxBuffer.u4_Read_Counter = 0;
	rxBuffer.u4_Write_Counter = 0;
}

unsigned char Uart_Transmit(unsigned char* u1_TxBuffer, unsigned int len)
{
	uint8 u1_TransmitResult = NG;
	static uint32 u4_LenCount = 0;
	
	if ( ( u1_TransmitState == IDLE )
	  && (u1_TxBuffer != NULL_PTR))
	{
		u1_TransmitResult = OK;

		for(; u4_LenCount < len; u4_LenCount++)
		{
			txBuffer.u1_TxBufferData[u4_LenCount] = *(u1_TxBuffer);
			u1_TxBuffer++;
			txBuffer.length++;
		}
	
		u1_TransmitState = BUSY;
	}
	return u1_TransmitResult;
}


void Uart_TxMainFunction(void)
{
	static uint32 u4_BufferCount = 0;
	
	if(u1_TransmitState == BUSY)
	{
		/*check for transmit buffer to be empty*/
		/*send data*/
		if(txBuffer.length != 0 && (LPUART1->STAT & (1 << 23)))
		{
			LPUART1->DATA = txBuffer.u1_TxBufferData[u4_BufferCount];
			u4_BufferCount++; /*upto buffer limit*/
			txBuffer.length--;	
		}
		
	}
}


unsigned char Uart_GetTransmitState(void)
{
	return u1_TransmitState;
}

void Uart_RxMainFunction(void)
{
	rxBuffer.u1_RxBufferData[rxBuffer.u4_Write_Counter] = (uint8)LPUART1->DATA;
	if (BUFFER_SIZE < rxBuffer.u4_Write_Counter)
	{
		rxBuffer.u4_Write_Counter = 0;
	}
	rxBuffer.u4_Write_Counter++;
	
	u1_ReceiveState = NOT_EMP;
}

unsigned int Uart_ReceiveData(unsigned char* u1_RxBuffer)
{
	if(u1_ReceiveState == NOT_EMP)
	{
		
		*u1_RxBuffer = rxBuffer.u1_RxBufferData[rxBuffer.u4_Read_Counter];
		rxBuffer.u4_Read_Counter++;
		
		if(rxBuffer.u4_Read_Counter >= BUFFER_SIZE)
		{
			rxBuffer.u4_Read_Counter = 0;
		}
		
		if(*u1_RxBuffer == 'r')
		{
			stateClock = RUN;
		}
		else if (*u1_RxBuffer == 'p')
		{
			stateClock = PENDING;
		}
		else if(*u1_RxBuffer == 'a')
		{
			stateClock = ALARM_SETTING;
			//*u1_RxBuffer++;
		} 
		/*Set clock*/
		else if(*u1_RxBuffer < 58 && *u1_RxBuffer > 44)
		{
			if(stateClock == ALARM_SETTING)
			{
				//Ggio_blinkLed_Green();
				Lpspi_clockSet(u1_RxBuffer, &tmp_alarm);
				//Buffer_init();
			}
			if(stateClock == PENDING )
			{
				Lpspi_clockSet(u1_RxBuffer, &alarm);
				//Buffer_init();
			} 
		}
		
		u1_ReceiveState = EMPTY;

	}
	
	return u4_ReceiveLength;
}

unsigned char Uart_GetReceiveState(void)
{
	return u1_ReceiveState;	
}


void LPUART1_RxTx_IRQHandler(void)
{
	if (LPUART1->STAT & (1 << 21))
	{
		Uart_RxMainFunction();
	}
}
