
/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ********************
 * �ļ���  ��main.c
 * ����    ������ͨ��   
 * ʵ��ƽ̨��iCreate STM8������
 * �Ĵ����汾  ��V1.0.0
 * ����    ��ling_guansheng  QQ��779814207
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 *�޸�ʱ�� ��2011-12-20
**********************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "clk_conf.h"
#include "uart.h"



/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern u8 RxBuffer[RxBufferSize];
extern u8 UART_RX_NUM;
int main(void)
{
  /* Infinite loop */
   u8 len ;
  /*�����ڲ�����ʱ��16MΪ��ʱ��*/ 
  Clk_conf();
  uart_conf();
  EnableInterrupt;
  printf("\r\nӲ��ƽ̨Ϊ:%s\r\n","iCreate STM8 ������");
  printf("\r\n%s\r\n","���ڷ�����̼Ĵ����汾V1.0.0");
  printf("\r\n���ߣ�%s\r\n","���");
  printf("\r\n�޸�ʱ�䣺%s\r\n","2012-6-13");
  printf("\r\n�����̲��Է�����%s\r\n","�ڴ������������ַ������ַ�������Ҫ���»س������ٵ������");
  while(1)
  {
    /* �����Ĵ���  */
      if(UART_RX_NUM&0x80)
      {
        len=UART_RX_NUM&0x3f;/*�õ��˴ν��յ������ݳ���*/
        UART3_SendString("You sent the messages is:",sizeof("You sent the messages is"));
        UART3_SendString(RxBuffer,len);
        printf("\r\n�õ��˴ν��յ������ݳ���:%dByte\r\n",len);
        UART_RX_NUM=0;
      }

  
  }
}






#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/
