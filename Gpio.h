#ifndef GPIO_H
#define GPIO_H

#include "Gpio_Register.h"

#define BTN0 12
#define BTN1 13

#define BLUE_LED 0
#define RED_LED 15
#define GREEN_LED 16

void Gpio_ledOff(void);
void Gpio_init(void);
void Ggio_blinkLed(void);
void Ggio_blinkLed_Blue(void);
void Ggio_blinkLed_Green(void);
void Gpio_blinkWhite(void);
void Gpio_switchColor(void);

void Gpio_TogglePinValue(volatile unsigned int *port, unsigned int pin, const unsigned int value);
unsigned int Gpio_GetPinValue(volatile unsigned int *port, unsigned int pin);
void Gpio_SetPinValue(volatile unsigned int *port, unsigned int pin, const unsigned int value);
void Gpio_ClearPinValue(volatile unsigned int *port, unsigned int pin);

#endif /* GPIO_H */
