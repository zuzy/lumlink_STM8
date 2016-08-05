#include "adc.h"
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
  ADC_CR1 = 0x02;
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
  //u16 * value_temp = value;
  u16 temp;
  ADC_CR1 |= 1;
  delay_us(10);         // 由低功耗唤醒，必须有7us的延时后才能开始新的转换  参考pdf p.367对adc低功耗的介绍
  ADC_CR1 |= 1;
  while(!(ADC_CSR | 0x80));
  
  temp = ADC_DB0RH;
  temp = (temp<<8) | ADC_DB0RL;
  *value = temp; 
  
  
  delay_us(10);        // 不知道怎么回事？扫描模式 读取每个数据寄存器需要延时         
  temp = ADC_DB1RH;
  temp = (temp<<8) | ADC_DB1RL;
  *(value+1) = temp;
  
  delay_us(10);
  temp = ADC_DB2RH;
  temp = (temp<<8) | ADC_DB2RL;
  *(value+2) = temp;
  
  delay_us(10);
  temp = ADC_DB3RH;
  temp = (temp<<8) | ADC_DB3RL;
  *(value+3) = temp; 
/*
  *value = adc_input.AdcJq;
  *(value+1) = adc_input.AdcTvoc;
  *(value+2) = adc_input.AdcVref;
*/  
  
  ADC_CSR_EOC = 0;
  ADC_CR1 &= 0xfe;
  
/*
  *value_temp = adc_input.AdcJq;
  *value_temp++ = adc_input.AdcTvoc;
  *value_temp = adc_input.AdcVref;
  */
}

  
  
    
  
    
  
  
    