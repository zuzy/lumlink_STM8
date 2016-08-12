/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ***************************

 * 文件名  ：uart.c
 * 描述    ：串口通信配置函数库     
 * 实验平台：iCreate STM8开发板
 * 寄存器版本  ：V1.0.0
 * 作者    ：ling_guansheng  QQ：779814207
 * 博客    ：
 *修改时间 ：2011-12-20
  iCreate STM8开发板硬件连接
    |--------------------|
    |  USART1_RX-PA4     |
    |  USART1_TX-PA5     |
    |--------------------|

****************************************************************************************/

#include "uart.h"
u8 RxBuffer[RxBufferSize];
u8 UART_RX_NUM=0;


/**************************************************************************
 * 函数名：uart_conf
 * 描述  ：uart配置函数
 * 输入  ：无
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 *************************************************************************/
void uart_conf(void)
{
    unsigned int baud_div=0;
    
    UART1_CR1 = (0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0); 
    /*1位起始位 8位数据位 结束位由CR3设置 不使用奇偶校验 不使能奇偶校验中断*/
    UART1_CR2 = (0<<7)|(0<<6)|(1<<5)|(0<<4)|(1<<3)|(1<<2); 
    /*使能发送和接收 接收中断使能 禁止发送中断*/
    UART1_CR3 = (0<<6)|(0<<4)|(0<<3); /*设置1位停止位 不使能SCLK*/        
    UART1_CR5 = (0<<2)|(0<<1);     
    /*使用智能卡模式需要设置的，基本上保持默认就行了 */ 
    
    /*设置波特率*/
    baud_div =HSIClockFreq/BaudRate;  /*求出分频因子*/
    UART1_BRR2 = baud_div & 0x0f;
    UART1_BRR2 |= ((baud_div & 0xf000) >> 8);
    UART1_BRR1 = ((baud_div & 0x0ff0) >> 4);    /*先给BRR2赋值 最后再设置BRR1*/
    
    UART1_CR1 &= (0<<5);         /*使能UART*/

}
/**************************************************************************
 * 函数名：UART1_SendByte
 * 描述  ：uart发送一个字节
 * 输入  ：u8 data
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 * 举例  ：UART1_SendByte('a')
 *************************************************************************/
void UART1_SendByte(u8 data)
{
    
    UART1_DR=data;
   /* Loop until the end of transmission */
   while (!(UART1_SR & UART1_FLAG_TXE));
}

/**********************************************************************************
 * 函数名：UART1_SendByte
 * 描述  ：uart发送字符串
 * 输入  ：u8* Data,u16 len
 *
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用 
 * 举例  ：UART1_SendString("iCreate STM8开发板",sizeof("iCreate STM8开发板"))
 **********************************************************************************/
void UART1_SendString(u8* Data,u16 len)
{
  u16 i=0;
  for(;i<len;i++)
    UART1_SendByte(Data[i]);
  
}
/**********************************************************************************
 * 函数名：UART1_ReceiveByte
 * 描述  ：uart查询接收一个字节
 * 输入  ：无
 *
 * 输出  ：无
 * 返回  ：一个字节 
 * 调用  ：外部调用 
 * 举例  ：temp=UART1_ReceiveByte()
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
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 ***********************************************/
#if 0
int fputc(int ch, FILE *f)
{  
 /*将Printf内容发往串口*/ 
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
    {/*接收中断(接收到的数据必须是0x0d 0x0a结尾)*/
        Res =(uint8_t)UART1_DR;
        /*(USART1->DR);读取接收到的数据,当读完数据后自动取消RXNE的中断标志位*/
        if(( UART_RX_NUM&0x80)==0)/*接收未完成*/
        {
            if( UART_RX_NUM&0x40)/*接收到了0x0d*/
            {
                if(Res!=0x0a) UART_RX_NUM=0;/*接收错误,重新开始*/
                else  UART_RX_NUM|=0x80;	/*接收完成了 */
            }
            else /*还没收到0X0D*/
            {	
                if(Res==0x0d) UART_RX_NUM|=0x40;
                else
                {
                    RxBuffer[ UART_RX_NUM&0X3F]=Res ;
                    UART_RX_NUM++;
                    if( UART_RX_NUM>63) UART_RX_NUM=0;/*接收数据错误,重新开始接收*/  
                }		 
            }
        }  		 
    }
}
#endif
/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/

