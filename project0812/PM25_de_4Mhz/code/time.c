#include "head.h"
#include "time.h"

void Clk_conf(void)
{
  CLK_CKDIVR&= (uint8_t)(~0x18);/*ʹ���ڲ�ʱ��*/
  CLK_CKDIVR|= (uint8_t)0x10;/*����ʱ��Ϊ�ڲ�16M����ʱ��*/
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
