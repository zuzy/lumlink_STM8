/***************** 1602液晶显示温湿度、PM2.5开源程序 *******************

×× 项目名称：PM2.5显示开源项目————1602液晶驱动程序
×× 内容简介：1602液晶屏显示出PM2.5值和温湿度，适合做成家用、车载检测仪器
×× 版  权：海联(HarLn)创业团队 ———— 六度传感器事业部
×× 网  址：www.harln。com
×× 程序员：徐晓 arndei@126.com
×× 注  明：商业应用请拿出部分将盈利用于公益事业，谢谢
*****************************************************************/

#ifndef 	__LCD1602_H
#define	__LCD1602_H

#include "type_def.h"

#include "time.h"

//#include <stdio.h>

void Lcd_GPIO_init(void);  //端口初始化
void Lcd_Init( void );     //LCD初始化
void Lcd_En_Toggle(void);  //发使能脉冲
void Lcd_Busy(void);       //判断忙
void Gpio_data(unsigned char x);  //端口写数据
void Lcd_Write_Command(unsigned char x,char Busy);  //写命令
//u8 Lcd_Write_Data(unsigned char x);
void Lcd_Write_Data(unsigned char x);               //写数据 
void Lcd_SetXY(unsigned char x,unsigned char y);   //位置设定，x表示列，y表示行 
void Lcd_Puts(unsigned char x,unsigned char y, unsigned char *string); //向1602写一个字符串 

/*
unsigned char *tr_2(unsigned int outData_2);         //把变量转换为2位字符显示
unsigned char *tr_3(unsigned int outData_3);         //把变量转换为3位字符显示
unsigned char *tr_4(unsigned int outData_4);         //把变量转换为4位字符显示
unsigned char *tr_5(unsigned int outData_5);         //把变量转换为5位字符显示
unsigned char *tr_6(unsigned int outData_6);         //把变量转换为6位字符显示
unsigned char *tr_7(unsigned int outData_7);         //把变量转换为7位字符显示
*/

/*************************************************************************/
/*-------- By HarLn Smart LiuDu --------- www.harln.com -----------------*/
/*************************************************************************/

#endif /* __LCD1602_H */

