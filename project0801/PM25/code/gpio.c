
#include "gpio.h"
void gpio_init(void)    //LED灯
{
  PA_DDR |= 0x06;
  PA_CR1 |= 0x06;
  PA_CR2 |= 0x06;
  
  PE_DDR_DDR5 = 1;
  PE_CR1_C15 = 1;
  PE_CR2_C25 = 1;

  PB_DDR_DDR6 = 1;
  PB_CR1_C16 = 1;
  PB_CR2_C26 = 1;
  
  PB_DDR &= 0xEF;
  PB_CR1 &= 0xEF;
  PB_CR2 &= 0xEF;  
  
  
  LED_G = 1;
  LED_Y = 1;
  LED_R = 1;
  LCD_LIGHT = 1;
}

void dht11_output()     //设置dht11的data为输出
{
  PB_DDR_DDR5 = 1;
  PB_CR1 |= 0x20;
  PB_CR2 |= 0x20;
}


void dht11_input()      //设置dht11的data为采集
{
  PB_DDR &= 0xdf;
  PB_CR1 &= 0xdf;
  PB_CR2 &= 0xdf;  
}


  
  
  