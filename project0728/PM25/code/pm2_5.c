#include "pm2_5.h"
#include "gpio.h"
#include "time.h"
#include "lcd1602.h"
#include "adc.h"
#include "convert.h"

u8 read_pm25_byte(void)
{
	int i;
	u8 pm_bit[8];
        u8 ret;
	u16 temp = 0;
	int count = 100;
	while(PM25_I)			//确定为6ms高电平；
	  	while(--count>0)
		{
	  		delay_us(10);
			//while(!PM25_I);
		}
	
	delay_us(300);  //300大概400us多delay，加上一些push pop这些 时间差不多。

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
  	asm("sim");    //禁止中断 
        LED_G = 0;
  	int i = 7;
        u16 comp;
        u16 value;
	u16 pm25_value[6]={0,0,0,0,0,0};
        char string_pm25[15];
        
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
        while(!((read_pm25_byte()==0xff)&&(read_pm25_byte()==0xaa)));//查找0xff与0xaa相连，作为起始；

            
	for(i = 5;i >= 0;--i)
	{
	  	pm25_value[5-i] = read_pm25_byte();
		//delay_us(4000);
	}
        comp = pm25_value[0] + pm25_value[1] + pm25_value[2] + pm25_value[3];
        if(comp >255)                           //处理数据溢出
            comp -= 256;
	if(comp == pm25_value[4])
	{
		LED_G = 1;
	}
	asm("rim");    //开总中断 
        //value = (pm25_value[0] << 8 | pm25_value[1]) * 5; //转化为mV； 0.2mg/m3对应1V
        value = (pm25_value[0] << 8 | pm25_value[1]); //直接转化为mg/m3 * 1000；0.2mg/m3对应1V
        adc_convert(string_pm25,value);
        Lcd_Write_Command( 0x01,1);   //清屏
        Lcd_Puts(0,1,"P25:     mg/m3");
        Lcd_Puts(4,1,(uchar*)string_pm25);          
}