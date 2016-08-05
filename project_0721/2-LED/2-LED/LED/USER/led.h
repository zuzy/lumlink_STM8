
#ifndef __LED_CONF_H
#define __LED_CONF_H
#include "type_def.h"

#define LED_1 PA_ODR_ODR2
#define LED_2 PA_ODR_ODR1
#define LED_3 PD_ODR_ODR7

#define DHT11 PB_ODR_ODR5

void gpio_int(void);

#endif




