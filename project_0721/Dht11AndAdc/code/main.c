#include "head.h"
#include "stdio.h"
#include <string.h>
int main(void)
{
  
  u8 i;
  u16 AdcValue[3] = {0,0,0};
  
  //memset(AdcValue,0,3*(sizeof(u16)));
  
  //unsigned int value_ref=0,value_tvoc=0;
  u16 value_jq,value_tvoc,value_vref;
  float TVOC;
  float JQ;
  char string_adc[15];
  char string_JQ[15];
  char str[10]={0};
  
  Clk_conf();                   //��ʼ��ʱ�ӣ��ڲ�16M
  gpio_init();                  //��ʼ��GPIO����ʼ��LED
  Lcd_Init();                   //��ʼ��1602

  //read_dht11(str);              //Ԥ��һ��DHT11�����ݣ���Ȼ��һ��dht11û�ж�����
  Lcd_Write_Command( 0x01,1);   //����
  //adc_init(3);                  //��ʼ��adc���ɼ�2.5V Vref ��У׼

  adc_init();
  Lcd_Puts(0,0,"hello !");
  delay_ms(1500);
  /*
  for(i = 0; i < 4; ++i)
    value_ref += adc_getValue();
  value_ref = value_ref >> 2;
  */
  
  //adc_init(2);                  //����ADCͨ��ΪTVOC��ģ����
  while(1)
  {
    
    i = 5;
    value_jq = 0;
    value_tvoc = 0;
    value_vref = 0;
    while(--i)
    {
      ReadAdc(AdcValue);
      value_jq += AdcValue[0];
      value_tvoc += AdcValue[1];
      value_vref += AdcValue[2];
    }
    value_jq = value_jq << 2;
    value_tvoc = value_tvoc << 2;
    value_vref = value_vref << 2;
    
    
    
      
    LED_2 = 0;  
    
    /*
    delay_us(10);    
    ReadAdc(AdcValue);
    //value_tvoc = adc_getValue();        //��ȡTVOCģ����
    */
    
     JQ = (value_jq * 2500.0)/(value_vref*736.6) - 0.3085;
    
    delay_us(10);
    num2char(string_adc,TVOC,1,4);
    //num2char(string_adc,-TVOC,1,4);
    //delay_ms(100);
    //num2char(string_JQ,JQ,1,4);
    num2char(string_JQ,JQ,1,2);
    
    read_dht11(str);
    Lcd_Write_Command( 0x01,1);
    Lcd_Puts(0,0,(unsigned char *)str);
    Lcd_Puts(0,1,"      V");
    Lcd_Puts(0,1,(uchar*)string_adc);
    
    Lcd_Puts(8,1,(uchar*)string_JQ);

    LED_2 = !LED_2;
    delay_ms(1000);
  }
}
  


