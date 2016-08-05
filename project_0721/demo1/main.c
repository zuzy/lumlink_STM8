#include "gpio.h"
#include "time.h"
#include "dht11.h"
#include "lcd1602.h"

int main( void )
{
  Clk_conf();
  //Tim1_Time_Upmode_conf(16,1000,0);
  //EnableInterrupt;
  
  //int ret;
  gpio_init();
  LED_1 = 1;
  LED_2 = 1;
  LED_3 = 1;

  Lcd_Init();
  Lcd_Puts(0,0,"hello !");
  delay_ms(200);
  Lcd_Write_Command( 0x01,1); 
//  Lcd_Puts(0,0,"HUM:"); //��1602дһ���ַ��� 
//  Lcd_Puts(0,1,"TEM:"); //��1602дһ���ַ���
  //delay_ms(1200);
  //Lcd_Write_Command( 0x01,1);       //��ʾ����

  
  while(1)
  {
    read_dht11();
    
    LED_2 = !LED_2;    /* PD0�������0 */
    delay_ms(500); 
    //Lcd_Write_Command( 0x01,1);       //��ʾ����   
  }
}
