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
}



#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
        TIM4_SR = 0;      // ��������жϱ��
        TIM4_ARR = 0xFF;
        TIM4_PSCR = 7;
	++TimeCount;
}

#if 0

#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
  	TIM2_SR1 &= 0xBE;
	--uCount;
}
#endif


#if 0
u8 read_pm25_byte(void)
{
	int i;
	u8 pm_bit[8];
        u8 ret;
	u16 temp = 0;
	int count = 100;
	while(PM25_I)			//ȷ��Ϊ6ms�ߵ�ƽ��
	  	while(--count>0)
		{
	  		delay_us(10);
			//while(!PM25_I);
		}
	
	delay_us(300);  //300���400us��delay������һЩpush pop��Щ ʱ���ࡣ

	for(i = 7;i >= 0; --i)
	{
	  	pm_bit[i] = PM25_I;	
		delay_us(300);
	}
	for(i=0;i<8;++i)
	{
	  	temp += pm_bit[i];
		temp <<= 1;
	}
	temp >>= 1;
        ret = (u8) temp;
	return ret;
}

void pm25_read()
{
  	asm("sim");    //��ֹ�ж� 
  	int i = 7;
        u16 comp;
	u16 pm25_value[6]={0,0,0,0,0,0};
        
#if 0        
        u16 temp_value[2]={0,0};
        while(1)
        {
            temp_value[0] = read_pm25_byte();
            temp_value[1] = read_pm25_byte();
            if((0xff == temp_value[0])&&(0xaa == temp_value[1]))
                break;
        }
#endif      
        while(!((read_pm25_byte()==0xff)&&(read_pm25_byte()==0xaa)));//����0xff��0xaa��������Ϊ��ʼ��

            
	for(i = 5;i >= 0;--i)
	{
	  	pm25_value[5-i] = read_pm25_byte();
		//delay_us(4000);
	}
        comp = pm25_value[0] + pm25_value[1] + pm25_value[2] + pm25_value[3];
        if(comp >255)                           //�����������
            comp -= 256;
	if(comp == pm25_value[4])
	{
		LED_G = !LED_G;
	}
	asm("rim");    //�����ж� 
}
	  	
#endif	


int main(void)
{
  
#if 1  
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
    Tim2_Init();
    asm("rim");    //�����ж� 
#endif	
	
	
	while(1)
	{  	  
        if(TimeCount>=1000)
		{
		  	TimeCount = 0;
			LED_R = 0;
			//pm25_read();
			
#if 1			
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
                                pm25_read();
				read_dht11();
				//Lcd_Puts(0,0,(unsigned char *)string_adc);
				a = !a;
			}
#endif			
			
			LED_R = !LED_R;
			
		
		}	
	}
}
  


