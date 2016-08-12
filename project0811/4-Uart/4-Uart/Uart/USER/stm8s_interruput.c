/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ***************************
 * �ļ���  ��
 * ����    ���жϷ����Ӻ�����   
 * ʵ��ƽ̨��iCreate STM8������
 * �Ĵ����汾  ��V1.0.0
 * ����    ��ling_guansheng  QQ��779814207
 * ����    ��
 *�޸�ʱ�� ��2011-12-20



****************************************************************************************/
#include "uart.h"
u8 RxBuffer[RxBufferSize];
u8 UART_RX_NUM=0;
#pragma vector=1
__interrupt void TRAP_IRQHandler(void)
{
  
}
#pragma vector=2
__interrupt void TLI_IRQHandler(void)
{
  
}
#pragma vector=3
__interrupt void AWU_IRQHandler(void)
{
  
}
#pragma vector=4
__interrupt void CLK_IRQHandler(void)
{
  
  
}
#pragma vector=5
__interrupt void EXTI_PORTA_IRQHandler(void)
{
  
}
#pragma vector=6
__interrupt void EXTI_PORTB_IRQHandler(void)
{
  
}
#pragma vector=7
__interrupt void EXTI_PORTC_IRQHandler(void)
{
  
}
#pragma vector=8
__interrupt void EXTI_PORTD_IRQHandler(void)
{
 
  
}
#pragma vector=9
__interrupt void EXTI_PORTE_IRQHandler(void)
{
   
}


#pragma vector=0xC
__interrupt void SPI_IRQHandler(void)
{
  
}
#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{
  

}
#pragma vector=0xE
__interrupt void TIM1_CAP_COM_IRQHandler(void)
{
  
}

#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
     
}
#pragma vector=0x10
__interrupt void TIM2_CAP_COM_IRQHandler(void)
{
  
}


#pragma vector=0x11
__interrupt void TIM3_UPD_OVF_BRK_IRQHandler(void)
{
  
}
#pragma vector=0x12
__interrupt void TIM3_CAP_COM_IRQHandler(void)
{
  
}


#pragma vector=0x13
__interrupt void UART1_TX_IRQHandler(void)
{
  
}
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

#pragma vector=0x15
__interrupt void I2C_IRQHandler(void)
{
  
}


#pragma vector=0x16
__interrupt void UART3_TX_IRQHandler(void)
{
  
}
#pragma vector=0x17
__interrupt void UART3_RX_IRQHandler(void)
{
  
}


#pragma vector=0x18
__interrupt void ADC2_IRQHandler(void)
{
   
}


#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
  
}

#pragma vector=0x1A
__interrupt void EEPROM_EEC_IRQHandler(void)
{
  
}


/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/