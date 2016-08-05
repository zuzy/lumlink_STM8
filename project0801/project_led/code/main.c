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
	TIM4_CNTR=0;        //������ֵ
	TIM4_ARR=0xFA;      //�Զ���װ�Ĵ���  250������125�ζ�ʱ1S
	TIM4_PSCR=0x07;     //Ԥ��Ƶϵ��Ϊ128
	TIM4_EGR=0x01;      //�ֶ�����һ�������¼�,����PSC��Ч       ע�⣬���ֶ�����
	
	TIM4_IER=0x01;      //�����¼��ж� ʹ��
	TIM4_CR1=0x01;      //ʹ�ܼ�ʱ����TIM4_CR0ֹͣ��ʱ��
#endif	
}

#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{

        TIM4_SR = 0;      // ��������жϱ��
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
	
	asm("sim");    //��ֹ�ж� 
        
        Clk_conf();                   //��ʼ��ʱ�ӣ��ڲ�16M
        gpio_init();                  //��ʼ��GPIO����ʼ��LED
        Lcd_Init();                   //��ʼ��1602

        //read_dht11(str);              //Ԥ��һ��DHT11�����ݣ���Ȼ��һ��dht11û�ж�����
        Lcd_Write_Command( 0x01,1);   //����
        adc_init();
	
        Lcd_Puts(0,0,"init...");
        delay_ms(500);
	Tim4_Init();
	asm("rim");    //�����ж� 
        //ReadAdc(AdcValue);
        /*
        for(i = 0; i < 4; ++i)
        value_ref += adc_getValue();
        value_ref = value_ref >> 2;
        */

        //adc_init(2);                  //����ADCͨ��ΪTVOC��ģ����
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


				Lcd_Write_Command( 0x01,1);   //����

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
  


