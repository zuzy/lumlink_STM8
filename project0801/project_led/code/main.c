#include "head.h"
#include "stdio.h"
#include <string.h>

static u16 TimeCount = 0;

void Tim4_Init()
{
  
        TIM4_CNTR = 0;
        TIM4_ARR = 0xFF;
        TIM4_PSCR = 0x07;
        TIM4_EGR = 0x01;
        TIM4_IER = 0X01;
        TIM4_CR1 = 0X01;  
  
	
#if 0	
	TIM4_CNTR=0;        //计数器值
	TIM4_ARR=0xFA;      //自动重装寄存器  250，产生125次定时1S
	TIM4_PSCR=0x07;     //预分频系数为128
	TIM4_EGR=0x01;      //手动产生一个更新事件,用于PSC生效       注意，是手动更新
	
	TIM4_IER=0x01;      //更新事件中断 使能
	TIM4_CR1=0x01;      //使能计时器，TIM4_CR0停止计时器
#endif	
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
	u8 i;
        u16 AdcValue[4] = {0,0,0,0};
        bool a=0;
        u16 value_mac,value_light,value_tvoc,value_jq;
        char string_adc[15];
	
	asm("sim");    //禁止中断 
        
        Clk_conf();                   //初始化时钟，内部16M
        gpio_init();                  //初始化GPIO，初始化LED
        Lcd_Init();                   //初始化1602

        //read_dht11(str);              //预读一个DHT11的数据，不然第一秒dht11没有读数？
        Lcd_Write_Command( 0x01,1);   //清屏
        adc_init();
	
        Lcd_Puts(0,0,"init...");
        delay_ms(500);
	Tim4_Init();
	asm("rim");    //开总中断 
        //ReadAdc(AdcValue);
        /*
        for(i = 0; i < 4; ++i)
        value_ref += adc_getValue();
        value_ref = value_ref >> 2;
        */

        //adc_init(2);                  //更换ADC通道为TVOC的模拟量
        while(1)
        {  	
                if(TimeCount==512)
		{
		  	TimeCount = 0;
			LED_R = 0;
			if(a)
			{
				memset(string_adc,0,15);
				value_mac = 0;
				value_light = 0;
				value_tvoc = 0;
				value_jq = 0;
				i = 6;
				while(--i)
				{
					ReadAdc(AdcValue);
					value_jq += AdcValue[0];
					value_tvoc += AdcValue[1];
					value_light += AdcValue[2];
					value_mac += AdcValue[3];
				}


				Lcd_Write_Command( 0x01,1);   //清屏

				delay_us(10);
				Lcd_Puts(0,0,"J");
				Lcd_Puts(0,1,"L");
				Lcd_Puts(10,0,"T");
				Lcd_Puts(10,1,"M");

				adc_convert(string_adc,value_jq);
				Lcd_Puts(1,0,(uchar*)string_adc);
				adc_convert(string_adc,value_light);
				Lcd_Puts(1,1,(uchar*)string_adc); 
				adc_convert(string_adc,value_tvoc);
				Lcd_Puts(11,0,(uchar*)string_adc);    
				adc_convert(string_adc,value_mac);
				Lcd_Puts(11,1,(uchar*)string_adc);    
				a = !a;
			}
			else
			{
				read_dht11();
				//Lcd_Puts(0,0,(unsigned char *)string_adc);
				a = !a;
			}
			LED_R = !LED_R;
		
		}	
	}
}
  


