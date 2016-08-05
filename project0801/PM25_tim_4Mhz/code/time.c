#include "head.h"

static u16 g_PM25Count;

void Clk_conf(void)
{
    CLK_CKDIVR&= (uint8_t)(~0x18);/*使能内部时钟*/
    CLK_CKDIVR|= (uint8_t)0x10;//16Mhz 4分频，4Mhz  F_master
}


void delay_ms(u32 nTime)
{
    u16 i;
    while(nTime--)  
        for(i=900;i>0;i--)
            asm("nop");
}


void inline delay_us(unsigned int i)
{       
    while(i--)
        asm("nop"); 
}


void Tim2_Init()
{
    TIM2_ARRH = 0;
    TIM2_ARRL = 0x04;
    TIM2_PSCR = 0x04;
    TIM2_EGR = 0x01;
    TIM2_IER = 0X01;
    TIM2_CR1 |= 0X81; 
}


#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
  	TIM2_SR1 &= 0xBE;
	++g_PM25Count;
}

void delay_tens_of_us_tim4( u16 us)
{
    g_PM25Count = 0;
    while(g_PM25Count < us);
}

