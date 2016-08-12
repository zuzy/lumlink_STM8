/***************** 1602Һ����ʾ��ʪ�ȡ�PM2.5��Դ���� *******************

���� ��Ŀ���ƣ�PM2.5��ʾ��Դ��Ŀ��������1602Һ����������
���� ���ݼ�飺1602Һ������ʾ��PM2.5ֵ����ʪ�ȣ��ʺ����ɼ��á����ؼ������
���� ��  Ȩ������(HarLn)��ҵ�Ŷ� �������� ���ȴ�������ҵ��
���� ��  ַ��www.harln��com
���� ����Ա������ arndei@126.com
���� ע  ������ҵӦ�����ó����ֽ�ӯ�����ڹ�����ҵ��лл
*****************************************************************/

#ifndef 	__LCD1602_H
#define	__LCD1602_H

#include "type_def.h"

#include "time.h"

//#include <stdio.h>

void Lcd_GPIO_init(void);  //�˿ڳ�ʼ��
void Lcd_Init( void );     //LCD��ʼ��
void Lcd_En_Toggle(void);  //��ʹ������
void Lcd_Busy(void);       //�ж�æ
void Gpio_data(unsigned char x);  //�˿�д����
void Lcd_Write_Command(unsigned char x,char Busy);  //д����
//u8 Lcd_Write_Data(unsigned char x);
void Lcd_Write_Data(unsigned char x);               //д���� 
void Lcd_SetXY(unsigned char x,unsigned char y);   //λ���趨��x��ʾ�У�y��ʾ�� 
void Lcd_Puts(unsigned char x,unsigned char y, unsigned char *string); //��1602дһ���ַ��� 

/*
unsigned char *tr_2(unsigned int outData_2);         //�ѱ���ת��Ϊ2λ�ַ���ʾ
unsigned char *tr_3(unsigned int outData_3);         //�ѱ���ת��Ϊ3λ�ַ���ʾ
unsigned char *tr_4(unsigned int outData_4);         //�ѱ���ת��Ϊ4λ�ַ���ʾ
unsigned char *tr_5(unsigned int outData_5);         //�ѱ���ת��Ϊ5λ�ַ���ʾ
unsigned char *tr_6(unsigned int outData_6);         //�ѱ���ת��Ϊ6λ�ַ���ʾ
unsigned char *tr_7(unsigned int outData_7);         //�ѱ���ת��Ϊ7λ�ַ���ʾ
*/

/*************************************************************************/
/*-------- By HarLn Smart LiuDu --------- www.harln.com -----------------*/
/*************************************************************************/

#endif /* __LCD1602_H */

