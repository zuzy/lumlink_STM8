#include "dht11.h"
#include "gpio.h"
#include "time.h"
#include "lcd1602.h"
#include <stdio.h>

bool a;

int judge(void);

void dht11_output()
{
  PB_DDR_DDR5 = 1;
  //PB_DDR |= 0x20;
  PB_CR1 |= 0x20;
  PB_CR2 |= 0x20;
}

void dht11_input()
{
  //PB_DDR_DDR5 = 0;
  PB_DDR &= 0xdf;
  PB_CR1 &= 0xdf;
  //PB_CR1 |= 0x20;这个不行？
  PB_CR2 &= 0xdf;  
}

int dht_start(void)
{
  dht11_output();
  a = DHT11_IN;
  DHT11 = 1;
  delay_us(10);
  DHT11 = 0;
  delay_ms(30);
  DHT11 = 1;
  dht11_input();
  delay_us(40);
  a = DHT11_IN;
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
  //u8 count=0xffff;
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

void read_dht11(void)
{
  uint8_t i;
  //u8 j,k;
  u8 sensor[5];
  unsigned char string[10];
  //char hum_string[10],temp_string[10];
  //char hum_string[80],temp_string[80];
  
  if(dht_start())
  {
    for(i = 0;i < 5;++i)
    {
      sensor[i] = read_dht11_byte();
    }
    dht11_output();
    DHT11 = 0;
    //if((sensor[0] + sensor[1] + sensor[2] + sensor[3]) == sensor[4])
    if((sensor[0] + sensor[2]) == sensor[4])
    {
      
      
      /*
      for(j=0;j<2;++j)
      {
        string[0] = sensor[0+j*2]/10+'0';
        string[1] = sensor[0+j*2]%10+'0';
        string[2] = '.';
        string[3] = sensor[1+j*2]/10+'0';
        string[4] = sensor[0+j*2]%10+'0';
        string[5] = '\0';
        Lcd_Puts(4,j,string);
      }
      */
      
      string[0] = sensor[0]/10+'0';
      string[1] = sensor[0]%10+'0';
      string[2] = '%';
      string[3] = ' ';
      string[4] = sensor[2]/10+'0';
      string[5] = sensor[2]%10+'0';
      string[6] = 0xdf;
      string[7] = 'c';
      string[8] = '\0';
      //rintf(string+7,"c");
      Lcd_Puts(0,0,string);

      
/*   
      k=0;
      k += sprintf(string,"%d.",sensor[0]);
      k += sprintf(string+k,"%d%% ",sensor[1]);//小数部分读不出来？dht11精度就是5%和1摄氏度，所以没有小数
      k += sprintf(string+k,"%d.",sensor[2]);
      sprintf(string+k,"%d`c",sensor[3]);
      Lcd_Puts(0,0,string);
      //Lcd_Puts(0,1,temp_string);   
*/    
      
 /*     
      k=0;
      k += sprintf(string,"hum:%d.",sensor[0]);
      k += sprintf(string+k,"%2d ",sensor[1]);
      k += sprintf(string+k,"tem:%d.",sensor[2]);
      sprintf(string+k,"%2d",sensor[3]);
      Lcd_Puts(0,0,string);
      //Lcd_Puts(0,1,temp_string);
*/ 
      
    }
  }
}
/*
int dht_proc(void)
{
  unsigned char DATA[8];
  Lcd_Puts(1,0,"S"); 
  int ret = 0;
  uint8_t n_counter;
  uint8_t i;
  uint8_t comp;
  DHT11 = 0;
  delay_ms(INIT_LOW);
  DHT11 = 1;
  delay_us(INIT_HIGH);
  
  PB_DDR &= 0xdf;
  PB_CR1 |= 0x20;
  PB_CR2 &= 0xdf;
  a = DHT11_IN;

  delay_us(REPLAY);
  a = DHT11_IN;
  delay_us(REPLAY);
  for(n_counter = 0;n_counter < 5; ++n_counter)
  {
    for(i = 0;i < 8; ++i)
    {
      DATA[i] = judge();
      sensor[n_counter] = (sensor[n_counter]<<1)|comp;
      delay_us(DELAY);
    }
  }
  ret = 0;

  Lcd_Puts(0,1,DATA);
  return ret;
}

int judge(void)
{
  int result;
  //if(0 == DHT11_IN)
  //{
    delay_us(READY);
    if(1 == DHT11_IN)
    {
      delay_us(ZERO);
      if(1 == DHT11_IN)
      {
        delay_us(ONE);
        result = 1;
      }
      else
        result = 0;
    }
  //}
  return result;
}
*/        
  
  