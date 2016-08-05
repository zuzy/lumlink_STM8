
#include "type_def.h"




#define LUM_CLK_4MHZ

#ifdef LUM_CLK_2MHZ

#elif defined(LUM_CLK_4MHZ)

//主时钟频率配置
void lum_clkConfig(void)
{

    CLK_CKDIVR = 0x10;  //fHSI RC输出/4; fCPU = fMASTER  (16MHz/4 = 4MHz)
}


//10Us delay
void lum_delay10Us(U16 delayCount)
{
    U8 i;
    
    while(delayCount--)
    {
        i = 3;
        while(i--)
        {
          asm("nop");
          asm("nop");
          asm("nop");
          asm("nop");
        }
    }
}


//1ms delay
void lum_delay1Ms(U16 delayCount)
{
}




#elif defined(LUM_CLK_8MHZ)

#elif defined(LUM_CLK_16MHZ)

#else
  #error "system clock error";
#endif