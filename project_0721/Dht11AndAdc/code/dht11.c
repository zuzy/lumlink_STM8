#include "dht11.h"
#include "gpio.h"
#include "time.h"
#include "lcd1602.h"
#include <stdio.h>

char table[10] = {'0','1','2','3','4','5','6','7','8','9'};

int dht_start(void)
{
  dht11_output();
  DHT11 = 1;
  delay_us(10);
  DHT11 = 0;
  delay_ms(30);
  DHT11 = 1;
  dht11_input();
  delay_us(40);
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
    delay_us(20);
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

void read_dht11(char *str)
{
  uint8_t i;
  u8 sensor[5];
  char * string = str;
  if(dht_start())
  {
    for(i = 0;i < 5;++i)
    {
      sensor[i] = read_dht11_byte();
    }
    dht11_output();
    DHT11 = 0;
    if((sensor[0] + sensor[1] + sensor[2] + sensor[3]) == sensor[4])    //校验
    {
      *str++ = sensor[0]/10+'0';     //DHT11精度为1，实际没有小数位，所以1和3的小数位忽略
      *str++ = sensor[0]%10+'0';
      *str++ = '%';
      *str++ = ' ';
      *str++ = sensor[2]/10+'0';
      *str++ = sensor[2]%10+'0';
      *str++ = 0xdf;
      *str++ = 'c';
      *str = '\0';  
    }
  }
  str = string;
}
  