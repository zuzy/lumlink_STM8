#include "dht11.h"
#include "gpio.h"
#include "time.h"
#include "lcd1602.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//char table[10] = {'0','1','2','3','4','5','6','7','8','9'};
char string[10];

int dht_start(void)
{
    dht11_output();
    DHT11 = 1;
    delay_us(10);
    DHT11 = 0;
    delay_tens_of_us_tim4(200);
    DHT11 = 1;
    dht11_input();
    delay_tens_of_us_tim4(4);
    if(!DHT11_IN)
    {
        while(!DHT11_IN)
            asm("nop");
        while(DHT11_IN)
            asm("nop");
        return 1;
    }
    return 0;
}

u8 read_dht11_byte(void)
{
    u8 i,temp,comdata;
    for(i = 0;i < 8;++i)
    {
        while(!DHT11_IN);
        delay_tens_of_us_tim4(3);
        temp = 0;
        if(DHT11_IN ==1)
        {
            temp = 1;
        }
        comdata = comdata << 1;
        comdata = comdata | temp;
        while(DHT11_IN);
    }
    return comdata;
}

void read_dht11(void)
{
    uint8_t i;
    u8 sensor[5];

    if(dht_start())
    {
        for(i = 0;i < 5;++i)
        {
            sensor[i] = read_dht11_byte();
        }
        dht11_output();
        DHT11 = 1;
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
        Lcd_Puts(0,0,(unsigned char *)string);
    }  
}
  