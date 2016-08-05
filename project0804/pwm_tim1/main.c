#include "type_def.h"


void main(void)
{
#if 0
    TIM2_PSCR = 0X00;
    TIM2_ARRH = 0X00;
    TIM2_ARRL = 136;
    TIM2_CR1 &= 0XFE;
    CLK_CKDIVR&= (uint8_t)(~0x18);/*使能内部时钟*/
    CLK_CKDIVR|= (uint8_t)0x00;/*设置时钟为内部16M高速时钟*/
    TIM2_CCER1 &= 0xFC;
    TIM2_CCER1 |= 0x01;
    TIM2_CCMR1 &= 0x8F;
    TIM2_CCMR1 |= 0X6C;
    TIM2_CCR1H = 0X00;
    TIM2_CCR1L = 54;
    TIM2_CR1 |= 0X01;
    while (1); //
#else    
    TIM1_PSCRH = 0X00;
    TIM1_PSCRL = 0X00;
    TIM1_ARRH = 0X00;
    TIM1_ARRL = 136;
    TIM1_CR1 &= 0XFE;
    
    TIM1_BKR = 0X80;                //这个是TIM1和TIM2的最大的区别
    
    CLK_CKDIVR&= (uint8_t)(~0x18);/*使能内部时钟*/
    CLK_CKDIVR|= (uint8_t)0x00;/*设置时钟为内部16M高速时钟*/
    TIM1_CCER1 &= 0xFC;
    TIM1_CCER1 |= 0x01;
    TIM1_CCMR1 &= 0x8F;
    TIM1_CCMR1 |= 0X6C;
    TIM1_CCR1H = 0X00;
    TIM1_CCR1L = 54;
    TIM1_CR1 |= 0X01;
    int i;
    while (1)
    {
        //TIM1_CCER1 &= 0xFE;
        for(i = 0;i<2000;i++);
        //TIM1_CCER1 |= 0x01;
        for(i = 0;i<2000;i++);
    }
#endif
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

/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/
