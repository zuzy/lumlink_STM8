/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ***************************

 * �ļ���  ��uart.c
 * ����    ������ͨ�����ú�����     
 * ʵ��ƽ̨��iCreate STM8������
 * �Ĵ����汾  ��V1.0.0
 * ����    ��ling_guansheng  QQ��779814207
 * ����    ��
 *�޸�ʱ�� ��2011-12-20
  iCreate STM8������Ӳ������
    |--------------------|
    |  USART1_RX-PA4     |
    |  USART1_TX-PA5     |
    |--------------------|

****************************************************************************************/

#include "uart.h"
u8 RxBuffer[RxBufferSize];
u8 UART_RX_NUM=0;


/**************************************************************************
 * ��������uart_conf
 * ����  ��uart���ú���
 * ����  ����
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� 
 *************************************************************************/
void uart_conf(void)
{
    unsigned int baud_div=0;
    
    UART1_CR1 = (0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0); 
    /*1λ��ʼλ 8λ����λ ����λ��CR3���� ��ʹ����żУ�� ��ʹ����żУ���ж�*/
    UART1_CR2 = (0<<7)|(0<<6)|(1<<5)|(0<<4)|(1<<3)|(1<<2); 
    /*ʹ�ܷ��ͺͽ��� �����ж�ʹ�� ��ֹ�����ж�*/
    UART1_CR3 = (0<<6)|(0<<4)|(0<<3); /*����1λֹͣλ ��ʹ��SCLK*/        
    UART1_CR5 = (0<<2)|(0<<1);     
    /*ʹ�����ܿ�ģʽ��Ҫ���õģ������ϱ���Ĭ�Ͼ����� */ 
    
    /*���ò�����*/
    baud_div =HSIClockFreq/BaudRate;  /*�����Ƶ����*/
    UART1_BRR2 = baud_div & 0x0f;
    UART1_BRR2 |= ((baud_div & 0xf000) >> 8);
    UART1_BRR1 = ((baud_div & 0x0ff0) >> 4);    /*�ȸ�BRR2��ֵ ���������BRR1*/
    
    UART1_CR1 &= (0<<5);         /*ʹ��UART*/

}
/**************************************************************************
 * ��������UART1_SendByte
 * ����  ��uart����һ���ֽ�
 * ����  ��u8 data
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� 
 * ����  ��UART1_SendByte('a')
 *************************************************************************/
void UART1_SendByte(u8 data)
{
    
    UART1_DR=data;
   /* Loop until the end of transmission */
   while (!(UART1_SR & UART1_FLAG_TXE));
}

/**********************************************************************************
 * ��������UART1_SendByte
 * ����  ��uart�����ַ���
 * ����  ��u8* Data,u16 len
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� 
 * ����  ��UART1_SendString("iCreate STM8������",sizeof("iCreate STM8������"))
 **********************************************************************************/
void UART1_SendString(u8* Data,u16 len)
{
  u16 i=0;
  for(;i<len;i++)
    UART1_SendByte(Data[i]);
  
}
/**********************************************************************************
 * ��������UART1_ReceiveByte
 * ����  ��uart��ѯ����һ���ֽ�
 * ����  ����
 *
 * ���  ����
 * ����  ��һ���ֽ� 
 * ����  ���ⲿ���� 
 * ����  ��temp=UART1_ReceiveByte()
 **********************************************************************************/
#if 0
u8 UART1_ReceiveByte(void)
{
     u8 USART1_RX_BUF; 
     while (!(UART1_SR & UART1_FLAG_RXNE));
     USART1_RX_BUF=(uint8_t)UART1_DR;
     return  USART1_RX_BUF;
    
}
#endif

/***********************************************
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 ***********************************************/
#if 0
int fputc(int ch, FILE *f)
{  
 /*��Printf���ݷ�������*/ 
  UART1_DR=(unsigned char)ch;
  while (!(UART1_SR & UART1_FLAG_TXE));
  return (ch);
}
#endif

#if 0
#pragma vector=0x14
__interrupt void UART1_RX_IRQHandler(void)
{ 
    u8 Res;
    if(UART1_SR & UART1_FLAG_RXNE)  
    {/*�����ж�(���յ������ݱ�����0x0d 0x0a��β)*/
        Res =(uint8_t)UART1_DR;
        /*(USART1->DR);��ȡ���յ�������,���������ݺ��Զ�ȡ��RXNE���жϱ�־λ*/
        if(( UART_RX_NUM&0x80)==0)/*����δ���*/
        {
            if( UART_RX_NUM&0x40)/*���յ���0x0d*/
            {
                if(Res!=0x0a) UART_RX_NUM=0;/*���մ���,���¿�ʼ*/
                else  UART_RX_NUM|=0x80;	/*��������� */
            }
            else /*��û�յ�0X0D*/
            {	
                if(Res==0x0d) UART_RX_NUM|=0x40;
                else
                {
                    RxBuffer[ UART_RX_NUM&0X3F]=Res ;
                    UART_RX_NUM++;
                    if( UART_RX_NUM>63) UART_RX_NUM=0;/*�������ݴ���,���¿�ʼ����*/  
                }		 
            }
        }  		 
    }
}
#endif
/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/

