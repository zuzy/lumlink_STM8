
#include "gpio.h"
void gpio_init(void)    //LED��
{
  PA_DDR |= 0x03;
  PA_CR1 |= 0x03;
  PA_CR2 |= 0x03;
  
  LED_2 = 1;
}

void dht11_output()     //����dht11��dataΪ���
{
  PB_DDR_DDR5 = 1;
  PB_CR1 |= 0x20;
  PB_CR2 |= 0x20;
}


void dht11_input()      //����dht11��dataΪ�ɼ�
{
  PB_DDR &= 0xdf;
  PB_CR1 &= 0xdf;
  PB_CR2 &= 0xdf;  
}


  
  
  