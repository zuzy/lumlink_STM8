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
    TIM4_SR = 0;      // ��������жϱ��
    TIM4_ARR = 0xFF;
    TIM4_PSCR = 7;
    ++TimeCount;
}

void init_bsp(void)
{
    asm("sim");    //��ֹ�ж� 

    Clk_conf();                   //��ʼ��ʱ�ӣ��ڲ�16M
    gpio_init();                  //��ʼ��GPIO����ʼ��LED
    
    Lcd_Init();                   //��ʼ��1602
    Lcd_Write_Command( 0x01,1);   //����
    Lcd_Puts(0,0,"init...");
    
    adc_init();
    Tim4_Init();
    
    asm("rim");    //�����ж� 
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
  


