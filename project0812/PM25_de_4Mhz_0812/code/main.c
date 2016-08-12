#include "head.h"
#include "stdio.h"
#include <string.h>

#define SEC_60 250*60
#define Tim2

static u16 TimeCount = 0;
static u16 Count = 0;

u16 state;

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

#ifdef Tim2
void Time2_Init()
{
    TIM2_PSCR = 0x07;
    TIM2_ARRH = 0x00;
    TIM2_ARRL = 0xFA;
    TIM2_CNTRH = 0;
    TIM2_CNTRL = 0x00;
    TIM2_EGR = 0x01;
    TIM2_IER =  0x01;
    TIM2_CR1 = 0x01;
}

#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
    TIM2_SR1 = 0;      // 清除更新中断标记
    TIM2_ARRH = 0x00;
    TIM2_ARRL = 0xFF;
    TIM2_PSCR = 0x07;
    ++Count;
    if (Count > 10000)
    {
        state = 1;
        TIM2_CR1 = 0x01;
    }
}
#endif
    

void init_bsp(void)
{
    asm("sim");    //禁止中断 

    Clk_conf();                   //初始化时钟，内部16M
    gpio_init();                  //初始化GPIO，初始化LED
    
    Lcd_Init();                   //初始化1602
    Lcd_Write_Command( 0x01,1);   //清屏
    Lcd_Puts(0,0,"init...");
	uart_conf();
    UART1_SendString("\r\nWelcome\r\nInit...\r\n",20);
    adc_init();
    Tim4_Init();
	key_exti_conf();
#ifdef Tim2
    Time2_Init();
#endif
    
    asm("rim");    //开总中断 
}

#pragma vector=5
__interrupt void EXTI_PORTA_IRQHandler(void)
{
	if(!KEY2)
	{
		adjust();
	}
}


int main(void)
{
    bool a=0;
    state = 0;
    init_bsp();
    while(1)
    {  	  
        if(TimeCount>=125)
        {
            TimeCount = 0;
                        
            if(a)
            {
                LED_R = 0;
                show_adc();
                a = !a;
                LED_R = !LED_R;	
            }
            else
            {
                pm25_read();
                read_dht11();
                a = !a;
            }  
#ifndef Tim2
            if(Count < 40){
                Count++;              
            }
            else
            {
				state = 1;
            }
#endif 
        	UART1_SendString("\t---------\r\n",12);
		}
    }
}
  


