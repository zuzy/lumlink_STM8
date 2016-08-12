#include "head.h"
#include "time.h"

void Clk_conf(void)
{
  CLK_CKDIVR&= (uint8_t)(~0x18);/*使能内部时钟*/
  CLK_CKDIVR|= (uint8_t)0x10;/*设置时钟为内部16M高速时钟*/
}


void delay_ms(u32 nTime)
{
          u16 i;
          while(nTime--)  
          for(i=900;i>0;i--) asm("nop");
}


void inline delay_us(unsigned int i)
{
        while(i--) asm("nop");
}
