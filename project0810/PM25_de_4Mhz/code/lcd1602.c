#include "Lcd1602.h"

#define SET_EN  PD_ODR_ODR2 = 1                //EN 使能  输出1
#define CLE_EN  PD_ODR_ODR2 = 0          //      输出0 
#define SET_RW  PD_ODR_ODR3 = 1        //RW 读写  输出1
#define CLE_RW  PD_ODR_ODR3 = 0          //      输出0
#define SET_RS  PD_ODR_ODR4 = 1                  //RS 指令  输出1
#define CLE_RS  PD_ODR_ODR4 = 0          //      输出0


void Lcd_GPIO_init(void)        //初始化1602的IO口，所有口都为推挽输出
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



void Lcd_Init( void )  //初始化，，1602的套路
{  
    Lcd_GPIO_init();
    delay_ms(7);                     //延时15ms
    Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号    
    delay_ms(2);                                      //延时5ms
    Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号
    delay_ms(2);                                          //延时5ms
    Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号
    //以后每次写指令、读/写数据操作之前需检测忙信号
    Lcd_Write_Command( 0x38,1);       //显示模式设置 
    delay_ms(2);                                          //延时5ms
    Lcd_Write_Command( 0x08,1);                  //显示关闭
    delay_ms(2);                                          //延时5ms	
    Lcd_Write_Command( 0x01,1);       //显示清屏
    delay_ms(2);                                          //延时5ms
    Lcd_Write_Command( 0x06,1);       //显示光标移动设置 
    delay_ms(2);                                          //延时5ms       
    Lcd_Write_Command( 0x0C,1);           //显示开、光标不显示

} 
/******************************************************/

void Lcd_En_Toggle(void) //发使能脉冲，EN下降沿触发
{
    SET_EN;        //使能1
    CLE_EN;
}


void Lcd_Busy(void)//判断忙
{
    delay_ms(1);
} 

void Gpio_data(unsigned char x)  //端口置入数据
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
    CLE_RS;                     //RS = 0 命令模式
    delay_us(5);   
    CLE_RW;                     //RW = 0 写模式
    delay_us(20);   
    Gpio_data(x);               //端口置入数据
    delay_us(20);  
    Lcd_En_Toggle();            //发使能脉冲
    delay_us(50);   
    Lcd_Busy();                 //测忙

}

void Lcd_Write_Data( unsigned char x) //向液晶里面写入数据 
{   
    
    Lcd_Busy(); 
    delay_us(5);  
    SET_RS;                     //RS = 1 数据模式
    delay_us(5);   
    CLE_RW;                     //RW = 0 写模式
    delay_us(20);  
    Gpio_data(x);
    delay_us(20);   
    Lcd_En_Toggle();  
    delay_us(50);   
    Lcd_Busy();
} 


void Lcd_SetXY(unsigned char x,unsigned char y)   //字符初始位置设定，x表示列，y表示行 
{ 
     unsigned char addr;                        //D7为位置使能位，D6控制行数        
     if(y==0) 
          addr=0x80+x; 
     else if(y==1)
          addr=0xC0+x; 
     Lcd_Write_Command(addr,1) ; 
} 

void Lcd_Puts(unsigned char x,unsigned char y, unsigned char *str) //向1602写一个字符串 
{ 
   unsigned char * string = str;
   
   Lcd_SetXY(x,y); 
  
    while(*string) 
    { 
        Lcd_Write_Data(*string); 
        string++; 
    } 
}


