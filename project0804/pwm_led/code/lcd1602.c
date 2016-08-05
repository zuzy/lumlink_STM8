/***************** 1602液晶显示温湿度、PM2.5开源程序 *******************

×× 项目名称：PM2.5显示开源项目————1602液晶驱动程序
×× 内容简介：1602液晶屏显示出PM2.5值和温湿度，适合做成家用、车载检测仪器
×× 版  权：海联(HarLn)创业团队 ———— 六度传感器事业部
×× 网  址：www.harln。com
×× 程序员：徐晓 arndei@126.com
×× 注  明：商业应用请拿出部分将盈利用于公益事业，谢谢
*****************************************************************/

/**********************使用方法**********************************
主程序中调用：
#include "Lcd1602.h" //包含LCD驱动头文件
Lcd_Init();        //LCD初始化
函数说明在头文件中
*****************************************************************/


#include "Lcd1602.h"

/***********************基本指令***********************************/
/******* 版  权：海联(HarLn)创业团队 ———— 六度传感器事业部*******/
#define SET_EN  PD_ODR_ODR2 = 1                //EN 使能  输出1
#define CLE_EN  PD_ODR_ODR2 = 0          //      输出0 
#define SET_RW  PD_ODR_ODR3 = 1        //RW 读写  输出1
#define CLE_RW  PD_ODR_ODR3 = 0          //      输出0
#define SET_RS  PD_ODR_ODR4 = 1                  //RS 指令  输出1
#define CLE_RS  PD_ODR_ODR4 = 0          //      输出0
/******************************************************************/


/************************端口初始化*******************************/
/******* 版  权：海联(HarLn)创业团队 ———— 六度传感器事业部*******/

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
    delay_ms(15);                     //延时15ms
    Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号    
    delay_ms(5);                                      //延时5ms
    Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号
    delay_ms(5);                                          //延时5ms
    Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号
    //以后每次写指令、读/写数据操作之前需检测忙信号
    Lcd_Write_Command( 0x38,1);       //显示模式设置 
    delay_ms(5);                                          //延时5ms
    Lcd_Write_Command( 0x08,1);                  //显示关闭
    delay_ms(5);                                          //延时5ms	
    Lcd_Write_Command( 0x01,1);       //显示清屏
    delay_ms(5);                                          //延时5ms
    Lcd_Write_Command( 0x06,1);       //显示光标移动设置 
    delay_ms(5);                                          //延时5ms       
    //Lcd_Write_Command( 0x0f,1); 
    Lcd_Write_Command( 0x0C,1);           //显示开、光标不显示
    //delay_ms(5);                                          //延时5ms	
} 
/******************************************************/

void Lcd_En_Toggle(void) //发使能脉冲，EN下降沿触发
{
    SET_EN;        //使能1
    //delay_ms(1);   //延时160us
    CLE_EN;
}


void Lcd_Busy(void)//判断忙
{
//     GPIO_InitTypeDef GPIO_InitStructure;
//     RCC_APB2PeriphClockCmd(RCC_GPIO_DATA, ENABLE);    //打开DATA端口时钟 

//     GPIO_InitStructure.GPIO_Pin  = GPIO_DATA_0_PIN|GPIO_DATA_1_PIN|GPIO_DATA_2_PIN|GPIO_DATA_3_PIN|GPIO_DATA_4_PIN|GPIO_DATA_5_PIN|GPIO_DATA_7_PIN; //  DB8~DB15
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //输入模式 = 上拉输入
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M时钟速度
//     GPIO_Init(GPIO_DATA_7, &GPIO_InitStructure);      //打开忙检测端口

//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //打开端口B时钟 
//     GPIO_InitStructure.GPIO_Pin  = GPIO_Mode_IPU; //  DB8~DB15
//     GPIO_Init(GPIO_DATA_6, &GPIO_InitStructure);      //初始化端口	

//         CLE_RS; //RS = 0
//         delay_us(1);   //延时10us
//         SET_RW; //RW = 1
//         delay_us(1);   //延时10us
//         SET_EN; //EN = 1
//         delay_us(2);   //延时20us
//     while (GPIO_ReadInputDataBit(GPIO_DATA_7,GPIO_DATA_7_PIN)); //循环等待忙检测端口 = 0
//         CLE_EN; //EN = 0

//     //恢复端口为输出状态 
//     RCC_APB2PeriphClockCmd(RCC_GPIO_DATA, ENABLE);    //打开DATA端口时钟 
//     GPIO_InitStructure.GPIO_Pin  = GPIO_DATA_0_PIN|GPIO_DATA_1_PIN|GPIO_DATA_2_PIN|GPIO_DATA_3_PIN|GPIO_DATA_4_PIN|GPIO_DATA_5_PIN|GPIO_DATA_7_PIN; //  DB8~DB15
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M时钟速度
//     GPIO_Init(GPIO_DATA_7, &GPIO_InitStructure);
//		 
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //打开端口B时钟 
//     GPIO_InitStructure.GPIO_Pin  = GPIO_DATA_6_PIN; //  DB8~DB15
//     GPIO_Init(GPIO_DATA_6, &GPIO_InitStructure);      //初始化端口
		 delay_ms(1);
} 

void Gpio_data(unsigned char x)  //端口置入数据
{
  PD_ODR_ODR0 = 0;
  PC_ODR &= 0x01;
  
  /*
  if(x&0X01)PD_ODR_ODR0 = 1;//DB0
  if(x&0X02)PC_ODR_ODR7 = 1;//DB1
  if(x&0X04)PC_ODR_ODR6 = 1;//DB2
  if(x&0X08)PC_ODR_ODR5 = 1;//DB3
  if(x&0X10)PC_ODR_ODR4 = 1;//DB4
  if(x&0X20)PC_ODR_ODR3 = 1;//DB5
  if(x&0X40)PC_ODR_ODR2 = 1;//DB6
  if(x&0X80)PC_ODR_ODR1 = 1;//DB7
 */ 
 
  PD_ODR_ODR0 = (bool) (x & 0x01);
  PC_ODR_ODR7 = (bool) (x & 0x02);
  PC_ODR_ODR6 = (bool) (x & 0x04);
  PC_ODR_ODR5 = (bool) (x & 0x08);
  PC_ODR_ODR4 = (bool) (x & 0x10);
  PC_ODR_ODR3 = (bool) (x & 0x20);
  PC_ODR_ODR2 = (bool) (x & 0x40);
  PC_ODR_ODR1 = (bool) (x & 0x80);
  
                    
//		GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_0_PIN);  //DB0
//		GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_1_PIN);  //DB1
//		GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_2_PIN);  //DB2
//		GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_3_PIN);  //DB3
//		GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_4_PIN);  //DB4
//		GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_5_PIN);  //DB5
//		GPIO_ResetBits(GPIO_DATA_6, GPIO_DATA_6_PIN);  //DB6
//		GPIO_ResetBits(GPIO_DATA_7, GPIO_DATA_7_PIN);  //DB7
//		if(x&0X01)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_0_PIN);//DB0
//		if(x&0X02)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_1_PIN);//DB1
//		if(x&0X04)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_2_PIN);//DB2
//		if(x&0X08)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_3_PIN);//DB3
//		if(x&0X10)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_4_PIN);//DB4
//		if(x&0X20)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_5_PIN);//DB5
//		if(x&0X40)GPIO_SetBits(GPIO_DATA_6, GPIO_DATA_6_PIN);//DB6
//		if(x&0X80)GPIO_SetBits(GPIO_DATA_7, GPIO_DATA_7_PIN);//DB7
}


//向液晶里面写入指令  时序：RS=L,RW=L,Data0-Data7=指令码，E=高脉冲
//******* 版  权：海联(HarLn)创业团队 ———— 六度传感器事业部******
void Lcd_Write_Command(unsigned char x,char Busy) 
{ 
    if(Busy) Lcd_Busy();
    delay_us(10);   
    CLE_RS;                     //RS = 0 命令模式
    delay_us(10);   
    CLE_RW;                     //RW = 0 写模式
    delay_us(40);   
    Gpio_data(x);               //端口置入数据
    delay_us(40);  
    Lcd_En_Toggle();            //发使能脉冲
    delay_us(100);   
    Lcd_Busy();                 //测忙

}
//向液晶里面写入数据  时序：RS=H,RW=L,Data0-Data7=指令码，E=高脉冲
//******* 版  权：海联(HarLn)创业团队 ———— 六度传感器事业部******
void Lcd_Write_Data( unsigned char x) //向液晶里面写入数据 
{   
    
    Lcd_Busy(); 
    delay_us(10);  
    SET_RS;                     //RS = 1 数据模式
    delay_us(10);   
    CLE_RW;                     //RW = 0 写模式
    delay_us(40);  
    Gpio_data(x);
    delay_us(40);   
    Lcd_En_Toggle();  
    delay_us(100);   
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
/******************************************************/

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



/*
unsigned char strTemp2[2];
unsigned char strTemp3[3];
unsigned char strTemp4[4];
unsigned char strTemp5[5];
unsigned char strTemp6[6];
unsigned char strTemp7[7];

unsigned char *tr_2(unsigned int outData_2)        
{
        strTemp2[0]=(unsigned char)(((outData_2/10) % 10) + 0x30);
        strTemp2[1]=(unsigned char)((outData_2%10) + 0x30);
        return strTemp2;
}

unsigned char *tr_3(unsigned int outData3)
{
        strTemp3[0]=(unsigned char)(((outData3/100) % 10) + 0x30);
        strTemp3[1]=(unsigned char)(((outData3/10) % 10) + 0x30);
        strTemp3[2]=(unsigned char)((outData3%10) + 0x30);
        return strTemp3;
}

unsigned char *tr_4(unsigned int outData4)
{
        strTemp4[0]=(unsigned char)(((outData4/1000)% 10) + 0x30);
        strTemp4[1]=(unsigned char)(((outData4/100)% 10) + 0x30);
        strTemp4[2]=(unsigned char)(((outData4/10)% 10) + 0x30);
        strTemp4[3]=(unsigned char)((outData4%10) + 0x30);
        return strTemp4;
}


unsigned char *tr_5(unsigned int outData5)
{
        strTemp5[0]=(unsigned char)(((outData5/10000)% 10) + 0x30);
        strTemp5[1]=(unsigned char)(((outData5/1000)% 10) + 0x30);
        strTemp5[2]=(unsigned char)(((outData5/100)% 10) + 0x30);
        strTemp5[3]=(unsigned char)(((outData5/10)% 10) + 0x30);
        strTemp5[4]=(unsigned char)((outData5%10) + 0x30);
        return strTemp5;
}

unsigned char *tr_6(unsigned int outData6)
{
        strTemp6[0]=(unsigned char)(((outData6/100000)% 10) + 0x30);
        strTemp6[1]=(unsigned char)(((outData6/10000)% 10) + 0x30);
        strTemp6[2]=(unsigned char)(((outData6/1000)% 10) + 0x30);
        strTemp6[3]=(unsigned char)(((outData6/100)% 10) + 0x30);
        strTemp6[4]=(unsigned char)(((outData6/10)% 10) + 0x30);
        strTemp6[5]=(unsigned char)((outData6%10) + 0x30);
        return strTemp6;
}

unsigned char *tr_7(unsigned int outData7)
{
        strTemp7[0]=(unsigned char)(((outData7/1000000)% 10) + 0x30);
        strTemp7[1]=(unsigned char)(((outData7/100000)% 10) + 0x30);
        strTemp7[2]=(unsigned char)(((outData7/10000)% 10) + 0x30);
        strTemp7[3]=(unsigned char)(((outData7/1000)% 10) + 0x30);
        strTemp7[4]=(unsigned char)(((outData7/100)% 10) + 0x30);
        strTemp7[5]=(unsigned char)(((outData7/10)% 10) + 0x30);
        strTemp7[6]=(unsigned char)((outData7%10) + 0x30);
        return strTemp7;
}
*/

/*************************************************************************/
/*-------- By HarLn Smart LiuDu --------- www.harln.com -----------------*/
/*************************************************************************/
