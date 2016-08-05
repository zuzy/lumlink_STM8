#include "pwm.h"
void pwm_ch2_output_init()
{
    TIM2_PSCR = 0X01;
    TIM2_ARRH = 0X00;
    TIM2_ARRL = 100;
    TIM2_CR1 &= 0XFE;
    CLK_CKDIVR&= (uint8_t)(~0x18);/*ʹ���ڲ�ʱ��*/
    CLK_CKDIVR|= (uint8_t)0x00;/*����ʱ��Ϊ�ڲ�16M����ʱ��*/
    TIM2_CCER1 &= 0xFC;
    TIM2_CCER1 |= 0x01;
    TIM2_CCMR1 &= 0x8F;
    TIM2_CCMR1 |= 0X60;
    TIM2_CCR1H = 0X00;
    TIM2_CCR1L = 52;
    TIM2_CR1 |= 0X01;
}