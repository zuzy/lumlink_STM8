#include "adc.h"
#include "time.h"
#include "lcd1602.h"
#include "stdio.h"

void main(void)
{
  u8 i;
  unsigned int value_ref,value_tvoc;
  float TVOC;
  char string[10];

  Lcd_Init();
  Lcd_Puts(0,0,"hello !");
  delay_ms(200);
  
  while(1)
  {
    Lcd_Write_Command( 0x01,1); 
    
    adc_init(3);
    for(i = 0; i < 4; ++i)
      value_ref += adc_getValue();
    value_ref = value_ref >> 2;
    
    delay_us(10);
    
    adc_init(2);
    value_tvoc = adc_getValue();
    
    TVOC = 2.5 / value_ref * value_tvoc;
    
    sprintf(string,"tvoc = %2.2f",TVOC);  
    Lcd_Puts(0,1,(uchar*)string);
    
    delay_ms(100);
    
    Lcd_Write_Command( 0x01,1); 
    sprintf(string,"ref = %d",value_ref);
    Lcd_Puts(0,1,(uchar*)string);
    delay_ms(100);
    
    value_ref = 0;
  }
}
    