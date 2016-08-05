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

void init_bsp(void)
{
    asm("sim");    //禁止中断 

    Clk_conf();                   //初始化时钟，内部16M
    gpio_init();                  //初始化GPIO，初始化LED
    
    Lcd_Init();                   //初始化1602
    Lcd_Write_Command( 0x01,1);   //清屏
    Lcd_Puts(0,0,"init...");
    
    adc_init();
    Tim4_Init();
    
    asm("rim");    //开总中断 
}


int main(void)
{
    bool a=0;
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
				
		}	
	}
}
  


