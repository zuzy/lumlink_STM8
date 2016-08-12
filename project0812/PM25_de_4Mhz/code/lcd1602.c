#include "Lcd1602.h"

#define SET_EN  PD_ODR_ODR2 = 1                //EN ʹ��  ���1
#define CLE_EN  PD_ODR_ODR2 = 0          //      ���0 
#define SET_RW  PD_ODR_ODR3 = 1        //RW ��д  ���1
#define CLE_RW  PD_ODR_ODR3 = 0          //      ���0
#define SET_RS  PD_ODR_ODR4 = 1                  //RS ָ��  ���1
#define CLE_RS  PD_ODR_ODR4 = 0          //      ���0


void Lcd_GPIO_init(void)        //��ʼ��1602��IO�ڣ����пڶ�Ϊ�������
{
  PD_DDR |= 0x1d;
  PD_CR1 |= 0x1d;
  PD_CR2 |= 0x1d;

  PC_DDR |= 0xFE;
  PC_CR1 |= 0xFE;
  PC_CR2 |= 0xFE;

  Gpio_data(0);                 
}
/******************************************************************/



void Lcd_Init( void )  //��ʼ������1602����·
{  
    Lcd_GPIO_init();
    delay_ms(7);                     //��ʱ15ms
    Lcd_Write_Command( 0x38,0);       // дָ��38H �����æ�ź�    
    delay_ms(2);                                      //��ʱ5ms
    Lcd_Write_Command( 0x38,0);       // дָ��38H �����æ�ź�
    delay_ms(2);                                          //��ʱ5ms
    Lcd_Write_Command( 0x38,0);       // дָ��38H �����æ�ź�
    //�Ժ�ÿ��дָ���/д���ݲ���֮ǰ����æ�ź�
    Lcd_Write_Command( 0x38,1);       //��ʾģʽ���� 
    delay_ms(2);                                          //��ʱ5ms
    Lcd_Write_Command( 0x08,1);                  //��ʾ�ر�
    delay_ms(2);                                          //��ʱ5ms	
    Lcd_Write_Command( 0x01,1);       //��ʾ����
    delay_ms(2);                                          //��ʱ5ms
    Lcd_Write_Command( 0x06,1);       //��ʾ����ƶ����� 
    delay_ms(2);                                          //��ʱ5ms       
    Lcd_Write_Command( 0x0C,1);           //��ʾ������겻��ʾ

} 
/******************************************************/

void Lcd_En_Toggle(void) //��ʹ�����壬EN�½��ش���
{
    SET_EN;        //ʹ��1
    CLE_EN;
}


void Lcd_Busy(void)//�ж�æ
{
    delay_ms(1);
} 

void Gpio_data(unsigned char x)  //�˿���������
{
    PD_ODR_ODR0 = 0;
    PC_ODR &= 0x01;

    PD_ODR_ODR0 = (bool) (x & 0x01);
    PC_ODR_ODR7 = (bool) (x & 0x02);
    PC_ODR_ODR6 = (bool) (x & 0x04);
    PC_ODR_ODR5 = (bool) (x & 0x08);
    PC_ODR_ODR4 = (bool) (x & 0x10);
    PC_ODR_ODR3 = (bool) (x & 0x20);
    PC_ODR_ODR2 = (bool) (x & 0x40);
    PC_ODR_ODR1 = (bool) (x & 0x80);
}


void Lcd_Write_Command(unsigned char x,char Busy) 
{ 
    if(Busy) Lcd_Busy();
    delay_us(5);   
    CLE_RS;                     //RS = 0 ����ģʽ
    delay_us(5);   
    CLE_RW;                     //RW = 0 дģʽ
    delay_us(20);   
    Gpio_data(x);               //�˿���������
    delay_us(20);  
    Lcd_En_Toggle();            //��ʹ������
    delay_us(50);   
    Lcd_Busy();                 //��æ

}

void Lcd_Write_Data( unsigned char x) //��Һ������д������ 
{   
    
    Lcd_Busy(); 
    delay_us(5);  
    SET_RS;                     //RS = 1 ����ģʽ
    delay_us(5);   
    CLE_RW;                     //RW = 0 дģʽ
    delay_us(20);  
    Gpio_data(x);
    delay_us(20);   
    Lcd_En_Toggle();  
    delay_us(50);   
    Lcd_Busy();
} 


void Lcd_SetXY(unsigned char x,unsigned char y)   //�ַ���ʼλ���趨��x��ʾ�У�y��ʾ�� 
{ 
     unsigned char addr;                        //D7Ϊλ��ʹ��λ��D6��������        
     if(y==0) 
          addr=0x80+x; 
     else if(y==1)
          addr=0xC0+x; 
     Lcd_Write_Command(addr,1) ; 
} 

void Lcd_Puts(unsigned char x,unsigned char y, unsigned char *str) //��1602дһ���ַ��� 
{ 
   unsigned char * string = str;
   
   Lcd_SetXY(x,y); 
  
    while(*string) 
    { 
        Lcd_Write_Data(*string); 
        string++; 
    } 
}


