#include "time.h"

void delay_1us(void)   
{    
    asm("nop"); //һ��asm("nop")��������ʾ�������Դ���100ns    
    asm("nop");   
    asm("nop");   
    asm("nop");
    asm("nop"); 
    asm("nop"); 
//    asm("nop"); 
//    asm("nop"); 
//    asm("nop"); 
//    asm("nop"); 
//    asm("nop"); 
//    asm("nop"); 
} 

void delay_us(unsigned int i)
{
    while(i--)
    {
      delay_1us();
    }
}

void delay_ms(u32 nTime)
{
  u16 i;
  while(nTime--)  
  for(i=900;i>0;i--)
  delay_1us();
}
