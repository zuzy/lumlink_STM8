#include "head.h"
#include "stdio.h"
#include <string.h>

static u16 TimeCount = 0;

void Tim4_Init()
{
    TIM4_CNTR = 0;
    TIM4_ARR = 0xFA;
    TIM4_PSCR = 0x07;
    TIM4_EGR = 0x01;
    TIM4_IER = 0X01;
    TIM4_CR1 = 0X01;  
}

#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
    TIM4_SR = 0;      // 清除更新中断标记
    TIM4_ARR = 0xFF;
    TIM4_PSCR = 7;
    ++TimeCount;
}



int main(void)
{ 
    gpio_init();
    
}
  


