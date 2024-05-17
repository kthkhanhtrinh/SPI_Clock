#ifndef S32K144_H
#define S32K144_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef enum Led_Color{
	BLUE,
	RED, 
	GREEN
} led_color;
extern volatile led_color tmp_color;


typedef enum program{
	NON, 
	PG1,
	PG2
} button_num;

extern volatile button_num tmp_program;



extern volatile uint8 stateClock;

#define PORT_PCR_COUNT	1000


typedef struct{
	volatile uint32 PCR[PORT_PCR_COUNT];
} PORT_Type;

#define PORTD_BASE_ADDRS 0x4004C000
#define PORTD						((PORT_Type *)PORTD_BASE_ADDRS)

#define PORTC_BASE_ADDRS	0x4004B000
#define PORTC						((PORT_Type *)PORTC_BASE_ADDRS)

#define PORTB_BASE_ADDRS	0x4004A000
#define PORTB						((PORT_Type *)PORTB_BASE_ADDRS)


/* PCC */
typedef struct 
{
	char dummy0[180];
	volatile uint32 PCC_LPSPI1;
	char dummy[108];
	volatile uint32 PCC_PORTA; //0X124
	volatile uint32 PCC_PORTB; //0X128
	volatile uint32 PCC_PORTC; //0X12C
	volatile uint32 PCC_PORTD; //0X130
	volatile uint32 PCC_PORTE; //0X134
	uint32 dummy2[29];
	volatile uint32 PCC_LPUART1; //0x1AC
}PCC;

#define PCC_BASE_ADDRS	0x40065000
#define PCC_Reg					((PCC *)PCC_BASE_ADDRS)

/* GPIO */
typedef struct{
	volatile uint32 GPIO_PDOR;
	volatile uint32 GPIO_PSOR;
	volatile uint32 GPIO_PCOR;
	volatile uint32 GPIO_PTOR;
	volatile uint32 GPIO_PDIR;
	volatile uint32 GPIO_PDDR;
	volatile uint32 GPIO_PIDR;
} GPIO_Type;

#define GPIOC_BASE_ADDRS 0x400FF080
#define GPIOC_Reg 				((GPIO_Type *)GPIOC_BASE_ADDRS)

#define GPIOD_BASE_ADDRS 0x400FF0C0
#define GPIOD_Reg 				((GPIO_Type *)GPIOD_BASE_ADDRS)

/* NVIC */

#define ISER_COUNT 8

typedef struct{
	volatile uint32 NVIC_ISER[ISER_COUNT];
} NVIC;

#define NVIC_BASE_ADDRS 0xE000E100
#define NVIC_Reg				((NVIC*)NVIC_BASE_ADDRS)

/* SYSTEM TICK TIMER */
typedef struct
{
	volatile uint32 STK_CSR;
	volatile uint32 STK_RVR;
	volatile uint32 STK_CVR;
	volatile uint32 STK_CALIB;	
} Systick_Timer;
#define SYSTICK_BASE_ADDRS	0xE000E010
#define STK_Reg							((Systick_Timer *)SYSTICK_BASE_ADDRS)

/* SCG */
typedef struct{
	volatile uint32 FIRCDIV;
} SCG_Type;

#define SCG_FIRCDIV_BASE_ADDRS 0x40064304
#define SCG_Reg 				((SCG_Type*)SCG_FIRCDIV_BASE_ADDRS)


/* SPI */
/** LPSPI - Register Layout Typedef */
typedef struct {
  volatile const uint32 VERID;                             
  volatile const uint32 PARAM;                             
  unsigned char dummy0[8];
  volatile uint32 CR;                                
  volatile uint32 SR;                                
  volatile uint32 IER;                               
  volatile uint32 DER;                               
  volatile uint32 CFGR0;                             
  volatile uint32 CFGR1;                             
  unsigned char dummy1[8];
  volatile uint32 DMR0;                              
  volatile uint32 DMR1;                              
  unsigned char dummy2[8];
  volatile uint32 CCR;                               
  unsigned char dummy3[20];
  volatile uint32 FCR;                               
  volatile const uint32 FSR;                        
  volatile uint32 TCR;                               
  volatile uint32 TDR;                              
  unsigned char dummy4[8];
  volatile const uint32 RSR;                               
  volatile const uint32 RDR;                               
} LPSPI_Type;
/** Peripheral LPSPI base address */
#define LPSPI0_base_address  (0x4002C000u)
#define LPSPI1_base_address  (0x4002D000u)
#define LPSPI2_base_address  (0x4002E000u)

#define LPSPI0_Reg	((LPSPI_Type *)LPSPI0_base_address)
#define LPSPI1_Reg	((LPSPI_Type *)LPSPI1_base_address)
#define LPSPI2_Reg	((LPSPI_Type *)LPSPI2_base_address)

/*__LPUART__*/

typedef struct{
	const volatile uint32 VERID;
	const volatile uint32 PARAM;
	volatile uint32 GLOBAL;
	volatile uint32 PINCFG;
	volatile uint32 BAUD;
	volatile uint32 STAT;
	volatile uint32 CTRL;
	volatile uint32 DATA;
	volatile uint32 MATCH;
	volatile uint32 MODIR;
	volatile uint32 FIFO;
	volatile uint32 WATER;
	
} LPUART;

#define LPUART1_BASE_ADDRS 0x4006B000
#define LPUART1 ((LPUART*)LPUART1_BASE_ADDRS)

#endif /* S32K144_H */
