#include "adc.h"
#include "string.h"
#include "lcd1602.h"
#include "convert.h"
#include "uart.h"

extern u16 state;
static u16 s_tvoc_count = 11;
static u32 s_tvoc_st = 1600;

static u16 s_jq[4];
static u8  s_index = 0;

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
    
#if 0   
    if(state) 
    {
        temp = ADC_DB1RH;
        temp = (temp<<8) | ADC_DB1RL;
        *(value+1) = temp;
        delay_us(1);
    }
#else
	temp = ADC_DB1RH;
	temp = (temp<<8) | ADC_DB1RL;
	*(value+1) = temp;
	delay_us(1);
#endif
    
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
    int i;
	static u8 index =0;

    u16 AdcValue[4] = {0,0,0,0};
    u16 value_mac,value_light,value_jq;
	u16 value_jq_temp;
	u32 value_tvoc;
    char string_adc[15];

    memset(string_adc,0,15);
    value_mac = 0;
    value_light = 0;
    value_tvoc = 0;
    value_jq = 0;
    i = 5;
    while(i--)
    {
        ReadAdc(AdcValue);
        value_jq += AdcValue[0];
        value_tvoc += AdcValue[1];
        value_light += AdcValue[2];
        value_mac += AdcValue[3];
    }


    Lcd_Write_Command( 0x01,1);   //清屏

    delay_us(10);
    
    
    
    
#if 0
	value_jq *= 0.29;
	value_jq >>= 2;
	if (value_jq > 100)
	{
    	convert(string_adc,value_jq,3);
		Lcd_Puts(0,0,(uchar*)string_adc);
	}
	else
	{
		convert(string_adc,value_jq,2);
    	Lcd_Puts(1,0,(uchar*)string_adc);
	}
	Lcd_Puts(3,0,"ppb");

	convert(string_adc,value_jq,0);
	Lcd_Puts(0,0,(uchar*)string_adc);	
#endif
	
#ifdef PPB
	value_jq = ((value_jq<<1)+(value_jq>>1)+(value_jq>>2)+(value_jq>>3)+(value_jq>>5)+(value_jq>>6) )- 1152;
	if (value_jq > 100)
	{
    	convert(string_adc,value_jq,3);
		Lcd_Puts(0,0,(uchar*)string_adc);
	}
	else
	{
		convert(string_adc,value_jq,2);
    	Lcd_Puts(1,0,(uchar*)string_adc);
	}
	Lcd_Puts(3,0,"ppb");
#else
	
	

	value_jq = ((value_jq<<1)+value_jq+(value_jq>>1))- 1382;
	s_jq[s_index] = value_jq;
	s_index++;
	s_index %= 4;
	value_jq =0;
	if(index < 3)
	{
		index++;
		for(i = 0; i < s_index; i++)
		{
			value_jq += s_jq[i];
		}
		value_jq /= s_index;
	}else
	{
		for(i=0;i<4;i++)
		{
			value_jq += s_jq[i];
		}
		value_jq >>= 2;
	}

	convert(string_adc,value_jq,0);
	Lcd_Puts(0,0,(uchar*)string_adc);
	Lcd_Puts(5,0,"mg");
#if 0
	//printf("甲醛含量： %f",(value_jq/1000.0));
	UART1_SendString("\r\n 甲醛含量：",13);
	UART1_SendString((uint8_t*)string_adc,9);
	UART1_SendString(" mg/m3\r\n",11);
#endif
#endif 
	
	
#if 0
	if(s_tvoc_count > 16){
		convert(string_adc,(value_tvoc<<10)/s_tvoc_st,0);
		Lcd_Puts(10,0,(uchar*)string_adc);
	}
	else if(s_tvoc_count < 8)
	{
		Lcd_Puts(11,0,"R ing");   
		s_tvoc_count++;
	}
	else if(s_tvoc_count < 16)
	{
		Lcd_Puts(10,0,"S");
		s_tvoc_st += value_tvoc;
		convert(string_adc,value_tvoc,0);
		Lcd_Puts(11,0,(uchar*)string_adc);   
		s_tvoc_count++;
	}
	else
	{
		s_tvoc_st >>= 3;
		convert(string_adc,(value_tvoc<<10)/s_tvoc_st,0);
		Lcd_Puts(10,0,(uchar*)string_adc);
		s_tvoc_count++;
	}
#else
	switch (s_tvoc_count){
	case 0:
	case 1:
		s_tvoc_st = 0;
		Lcd_Puts(10,0,"Adjust");
		//printf("\r\n正在校准TVOC\r\n");
  		UART1_SendString("\r\nadjusting\r\n",13);
		s_tvoc_count++;
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		Lcd_Puts(10,0,"A");
		s_tvoc_st += value_tvoc;
		convert(string_adc,value_tvoc,0);
		Lcd_Puts(11,0,(uchar*)string_adc);
		//printf("\r\n正在校准TVOC : %f\r\n",value_tvoc/1000.0);
  		UART1_SendString("\r\nadjusting\r\n",13);
		UART1_SendString((uint8_t*)string_adc,9);
		UART1_SendString("\r\n",2);
		s_tvoc_count++;
		break;
	case 10:
		s_tvoc_st >>= 3;
		s_tvoc_count++;
	default:
		convert(string_adc,(value_tvoc<<10)/s_tvoc_st,0);
		Lcd_Puts(10,0,(uchar*)string_adc);
		//printf("\r\n污染指数TVOC : %f\r\n",value_tvoc*1.0/s_tvoc_st);
		UART1_SendString("\r\n污染指数：",12);
		UART1_SendString((uint8_t*)string_adc,9);
		UART1_SendString("\r\n",2);
	
		break;
	}
#endif

#if 0		
    if(s_tvoc_count < 8)
    {
        Lcd_Puts(11,0,"R ing");   
		s_tvoc_count++;
    }
    else if(s_tvoc_count <16)
    {
        Lcd_Puts(10,0,"S");
		s_tvoc_st += value_tvoc;
        convert(string_adc,value_tvoc,0);
        Lcd_Puts(11,0,(uchar*)string_adc);   
		s_tvoc_count++;
    }
	else if(
	{
		s_tvoc_st>>=13;
		convert(string_adc,value_tvoc/s_tvoc_st,0);
		Lcd_Puts(10,0,(uchar*)string_adc);
		s_tvoc_count++;
	}
#endif
	
	
    Lcd_Puts(0,1,"L");
    convert(string_adc,value_light,0);
    Lcd_Puts(1,1,(uchar*)string_adc); 
	
	Lcd_Puts(10,1,"M");
    convert(string_adc,value_mac,0);
    Lcd_Puts(11,1,(uchar*)string_adc);    
}

		
void Standard()
{
	s_tvoc_count = 0;
}
    