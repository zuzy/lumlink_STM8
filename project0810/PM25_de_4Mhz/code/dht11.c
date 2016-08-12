#include "dht11.h"
#include "gpio.h"
#include "time.h"
#include "lcd1602.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char string[10];

int dht_start(void)
{
	int break_count = 0;
    dht11_output();
    DHT11 = 1;
    delay_us(10);
    DHT11 = 0;
    delay_ms(30);
    DHT11 = 1;
    dht11_input();
    delay_us(30);
    if(!DHT11_IN)
    {
		while(!DHT11_IN)
		{
			break_count ++;
			if (break_count >500)
				return 0;
		}
		break_count = 0;
        while(DHT11_IN)
		{
			break_count ++;
			if (break_count >500)
				return 0;
		}
		return 1;
    }
	if (break_count >= 1)
		break_count = 1;
    return 0;
}

u8 read_dht11_byte(void)
{
	int break_count = 0;
    u8 i,temp,comdata;
    for(i = 0;i < 8;++i)
    {
        while(!DHT11_IN);
        delay_us(20);
        temp = 0;
        if(DHT11_IN ==1)
        {
            temp = 1;
        }
        comdata = comdata << 1;
        comdata = comdata | temp;
        while(DHT11_IN)
		{
			break_count ++;
			if (break_count >500)
				return 0;
		};
    }
    return comdata;
}

void read_dht11(void)
{
    uint8_t i;
    u8 sensor[5];
    LED_G = 0;
	asm("sim");    //禁止中断 
	
    if(dht_start())
    {
        for(i = 0;i < 5;++i)
        {
            sensor[i] = read_dht11_byte();
        }
        dht11_output();
        DHT11 = 1;
		asm("rim");    //开总中断 
        if(sensor[0])
        {
            memset(string,0,10);
            if((sensor[0] + sensor[1] + sensor[2] + sensor[3]) == sensor[4])    //校验
            {
            string[0] = sensor[0]/10+'0';     //DHT11精度为1，实际没有小数位，所以1和3的小数位忽略
            string[1] = sensor[0]%10+'0';
            string[2] = '%';
            string[3] = ' ';
            string[4] = sensor[2]/10+'0';
            string[5] = sensor[2]%10+'0';
            string[6] = 0xdf;
            string[7] = 'c';
            string[8] = '\0';  
            }
            //Lcd_Write_Command( 0x01,1);   //清屏
            Lcd_Puts(0,0,(unsigned char *)string);
        }
        else
        {
            //Lcd_Write_Command( 0x01,1);   //清屏
            Lcd_Puts(0,0,(unsigned char *)string);
        }
    }  
    LED_G = 1;
}
  