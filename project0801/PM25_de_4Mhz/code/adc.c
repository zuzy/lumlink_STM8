#include "adc.h"
#include "string.h"
#include "lcd1602.h"
#include "convert.h"

/*
void adc_init(u8 ch)
{
  ADC_CR1 = 0x02;
  ADC_CR2 = 0x08;
  ADC_CSR = ch;
  if(ch > 7)
    ADC_TDRH |= 1 << (ch - 8);
  else 
    ADC_TDRL |= 1 << ch;
  ADC_CR1 |= 1;
  ADC_CR1 |= 1;
}
*/

/*

u16 adc_getValue(void)
{
  u16 value,temph;
  u8 templ;
  while(!(ADC_CSR & 0x80))
    asm("nop");
  templ = ADC_DRL;
  temph = ADC_DRH;
  value = (unsigned int)(templ | (temph << 8));
  
  ADC_CSR_EOC = 0;
  
  return value;
}
*/

//static struct ADC_DATA adc_input;

void adc_init(void)
{
  ADC_CR1 = 0x00;
  //ADC_CR2 = 0x08;     //右对齐，单次不扫描
  ADC_CR2 = 0x0A;       //右对齐 使能扫描模式；
  ADC_CSR = 0x03;
  /*
  if(ch > 7)
    ADC_TDRH |= 1 << (ch - 8);
  else 
    ADC_TDRL |= 1 << ch;
  */
  //ADC_CR1 |= 1;
  //ADC_CR1 |= 1;
}
/*
void GetAdcValue(void)
{
  u16 temp;
  
  temp = ADC_DB1RH;
  temp = (temp<<8) | ADC_DB1RL;
  adc_input.AdcJq = temp;

  temp = ADC_DB2RH;
  temp = (temp<<8) | ADC_DB2RL;
  adc_input.AdcTvoc = temp;

  temp = ADC_DB3RH;
  temp = (temp<<8) | ADC_DB3RL;
  adc_input.AdcVref = temp;
}
*/

void ReadAdc(u16 * value)
{
    
    u16 temp;
#if 0    
    ADC_CR1 = 0x00;
    //ADC_CR2 = 0x08;     //右对齐，单次不扫描
    ADC_CR2 = 0x0A;       //右对齐 使能扫描模式；
    ADC_CSR = 0x03;
#endif    
    
    ADC_CR1 |= 1;
    delay_us(5);         // 由低功耗唤醒，必须有7us的延时后才能开始新的转换  参考pdf p.367对adc低功耗的介绍
    ADC_CR1 |= 1;
    while(!(ADC_CSR | 0x80));
    delay_us(1);

    temp = ADC_DB0RH;
    temp = (temp<<8) | ADC_DB0RL;
    *value = temp; 
    delay_us(1);
    
    temp = ADC_DB1RH;
    temp = (temp<<8) | ADC_DB1RL;
    *(value+1) = temp;
    delay_us(1);
    
    temp = ADC_DB2RH;
    temp = (temp<<8) | ADC_DB2RL;
    *(value+2) = temp;
    delay_us(1);
    
    temp = ADC_DB3RH;
    temp = (temp<<8) | ADC_DB3RL;
    *(value+3) = temp; 
    //delay_us(5);
    
    ADC_CSR_EOC = 0;
    ADC_CR1 &= 0xfe;
}

void show_adc(void)
{
    u8 i;
    u16 AdcValue[4] = {0,0,0,0};
    u16 value_mac,value_light,value_tvoc,value_jq;
    char string_adc[15];

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

    convert(string_adc,value_jq);
    Lcd_Puts(1,0,(uchar*)string_adc);
    convert(string_adc,value_light);
    Lcd_Puts(1,1,(uchar*)string_adc); 
    convert(string_adc,value_tvoc);
    Lcd_Puts(11,0,(uchar*)string_adc);    
    convert(string_adc,value_mac);
    Lcd_Puts(11,1,(uchar*)string_adc);    
}

  
  
    
  
    
  
  
    