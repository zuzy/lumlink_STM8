#include "pm2_5.h"
#include "gpio.h"
#include "time.h"
#include "lcd1602.h"
#include "adc.h"
#include "convert.h"

#if 0
u16 read_pm25_byte(bool flag)
{
	int i;
	u8 pm_bit[8];
    u16 ret;
	u16 temp = 0;
	int count = 100;

    while(PM25_I)			//确定为6ms高电平；
        while(--count>0)
        {
            delay_us(7);
            while(!PM25_I);
        }

	for(i = 7;i >= 0; --i) //不能这么写 数据会错
	{
        delay_us(210); 
	  	pm_bit[i] = PM25_I;	
	}
	for(i=0;i<8;++i)
	{
	  	temp |= pm_bit[i];
		temp <<= 1;
	}
	temp >>= 1;
    ret = (u8) temp;
	return temp;
}
#endif

#if 1
u8 read_pm25_byte(void)
{
	int i;
	u8 pm_bit[8];
	u16 temp = 0;
    /*
        count和delay的组合 需要尽量小，以减少在高电平判断中以及判断结束消耗的时间 
        经过测试，当count和delay的组合比较小时会偶尔出现数据无法归零，
    
    */    
	int count = 50;              //确定为6ms高电平；响应第一个低电平，尽量减少delay
	while(PM25_I)			
	  	while(--count>0)
		{
	  		delay_us(6);
			while(!PM25_I);
		}
#if 1
	//delay_us(210);  //210略大于420us delay

	for(i = 7;i >= 0; --i)      //测试结果 一个字节转化下来一共花费大约3500个us
	{
        delay_us(210);          //delay 420us
	  	pm_bit[i] = PM25_I;	
	}
    delay_us(100);              //当90时会跳不出来，100delay时正好没有问题；
#else
    delay_us(210);  //300大概接近500us delay

	for(i = 7;i >= 0; --i)
	{
	  	pm_bit[i] = PM25_I;	
		delay_us(210);
	}
#endif
	for(i=0;i<8;++i)
	{
	  	temp |= pm_bit[i];
		temp <<= 1;
	}
	temp >>= 1;
	return (u8)temp;
}
#endif


void pm25_read()
{
    
    asm("sim");    //禁止中断 

    int i = 7;
    u16 comp;
    u16 value;
    u16 pm25_value[6]={0,0,0,0,0,0};
	u32 break_count = 0;
    char string_pm25[15];
    
    LED_Y = 0;

#if 0 //原始的查找0xff和0xaa函数
    u16 temp_value[2]={0,0};
    while(1)
    {
        temp_value[0] = read_pm25_byte();
        temp_value[1] = read_pm25_byte();
        if((0xff == temp_value[0])&&(0xaa == temp_value[1]))
            break;
    }
#endif
    
    while(!((read_pm25_byte()==0xff)&&(read_pm25_byte()==0xaa)))		//查找0xff与0xaa相连，作为起始，并排除判断中锁死；
	{
		break_count++;
		if (break_count > 20) return;
	}                 
    for(i = 0;i < 6;++i)
        pm25_value[i] = read_pm25_byte();
    
    asm("rim");    //开总中断 
    
    comp = pm25_value[0] + pm25_value[1] + pm25_value[2] + pm25_value[3];
    if(comp >255) comp -= 256;          //处理溢出
    if(comp == pm25_value[4])
    {
        value = (u16)((pm25_value[0] << 8 | pm25_value[1])*1.43); //直接转化为ug/m3；3.5mg/m3对应1V
        /*  
            标准的比例为3.5mg/m3    
            ADC转化为电平信号： ADC/1024*5 
            结合起来，变成  ADC*5/3.5 ug/m3  约为  ADC*1.43 ug/m3;
            之后再经过adc_convert函数转化为 千分之一的小数，单位变为mg/m3
        */
        convert(string_pm25,value,0);     //adc转化为小数
        Lcd_Write_Command( 0x01,1);         //清屏
        Lcd_Puts(0,1,"P25:     mg/m3");
        Lcd_Puts(4,1,(uchar*)string_pm25);     
        LED_Y = 1;
    }
}