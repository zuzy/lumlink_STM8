
#include "led.h"

void gpio_init(void)
{
  PA_DDR |= 0x03;
  PA_CR1 |= 0x03;
  PA_CR2 |= 0x03;

  PD_DDR |= 0x80;
  PD_CR1 |= 0x80;
  PD_CR2 |= 0x80;
  
  PB_DDR |= 0x10;
  PB_CR1 |= 0x10;
  PB_CR2 |= 0x10;
}
void Delay(u32 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }

}
  
  
  