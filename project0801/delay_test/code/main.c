#include "head.h"
#include "stdio.h"
#include <string.h>	  


static u8 TimeCount;


void Tim4_Init()
{
    TIM4_CNTR = 0;
    TIM4_ARR = 0x02;
    TIM4_PSCR = 0x02;
    TIM4_EGR = 0x01;
    TIM4_IER = 0X01;
    TIM4_CR1 = 0X01;  
}


void Tim2_Init()
{
        TIM2_CNTRH = 0;
	TIM2_CNTRL = 0;
	TIM2_ARRH = 0;
        TIM2_ARRL = 0x04;
	TIM2_PSCR = 0x04;
        TIM2_CR1 |=0x80;
        TIM2_EGR = 0x01;
        TIM2_IER = 0X01;
        TIM2_CR1 |= 0X01; 
}


#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
  	TIM2_SR1 &= 0xBE;
	++TimeCount;
}


#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
        TIM4_SR = 0;      // 清除更新中断标记
        TIM4_ARR = 0xFF;
        TIM4_PSCR = 0;
	++TimeCount;
}

int main(void)
{
        
    asm("sim");    //禁止中断 
    Clk_conf(); 
    Tim2_Init();    
    gpio_init();
    asm("rim");    //开总中断 
  
    while(1)
    { 
#if 1      
        if(TimeCount >=2)
        {
            TimeCount = 0;
            PD_ODR_ODR0 = !PD_ODR_ODR0;
        }
#endif
        //delay_us(297);
        //delay_us(600);
        //PD_ODR_ODR0 = !PD_ODR_ODR0;
    }
}
  


