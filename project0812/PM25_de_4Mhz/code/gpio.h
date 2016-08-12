#ifndef __GPIO_CONF_H
#define __GPIO_CONF_H
#include "type_def.h"

#define BitStatus bool

#define LED_G PE_ODR_ODR5
#define LED_Y PA_ODR_ODR2
#define LED_R PA_ODR_ODR1

#define VOC_EN PB_ODR_ODR7

#define LCD_LIGHT PB_ODR_ODR6

#define DHT11 PB_ODR_ODR5
//#define DHT11_IN PB_IDR_IDR5
//PD5_In  (BitStatus)(PD_IDR&0x20)

#define DHT11_IN  (BitStatus)(PB_IDR&0x20)

#define PM25_I PB_IDR_IDR4

void gpio_init(void);
void dht11_output();
void dht11_input();

#endif