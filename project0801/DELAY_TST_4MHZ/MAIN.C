#include "time.h"

int main()
{
  PD_DDR_DDR0 = 1;
  PD_CR1_C10 = 1;
  PD_CR2_C20 = 1;
  Clk_conf();
  PD_ODR_ODR0 = 0;
  while(1)
  {
    PD_ODR_ODR0 = !PD_ODR_ODR0;
    delay_us(10);
  }
}