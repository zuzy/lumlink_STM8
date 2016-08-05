#ifndef __GPIO_CONF_H
#define __GPIO_CONF_H
#include "type_def.h"

#define BitStatus bool

#define LED_1 PA_ODR_ODR2
#define LED_2 PA_ODR_ODR1
#define LED_3 PD_ODR_ODR7

#define DHT11 PB_ODR_ODR5
//#define DHT11_IN PB_IDR_IDR5
//PD5_In  (BitStatus)(PD_IDR&0x20)
#define DHT11_IN  (BitStatus)(PB_IDR&0x20)

void gpio_init(void);

#endif