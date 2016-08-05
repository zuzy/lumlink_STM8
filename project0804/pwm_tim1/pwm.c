/******************** (C) COPYRIGHT  ���iCreateǶ��ʽ���������� ***************************
 * �ļ���  ��pwm.c
 * ����    ��PWM���ú�����   
 * ʵ��ƽ̨��iCreate STM8������
 * �Ĵ����汾  ��V1.0.0
 * ����    ��ling_guansheng  QQ��779814207
 * ����    ��
 *�޸�ʱ�� ��2011-12-20



****************************************************************************************/
#include "pwm.h"
#define ARR ((uint8_t)499)
static void Delay(u16 nCount);
u16 Beep_Frequency[7]={3816,3400,3029,2864,2550,2272,2023};
/**************************************************************************
 * ��������PWM_Init
 * ����  ��PWM��ʼ��
 * ����  ����
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� 
 *************************************************************************/
void PWM_Init(void)
{
    TIM1_PSCRH = 0x00;
    TIM1_PSCRL = 0x0f;
    /* Set the Autoreload value */
    TIM1_ARRH = (uint8_t)(ARR >> 8);
    TIM1_ARRL = (uint8_t)(ARR);
    /*TIM1 Frequency=16M/16/(499+1)=2K*/
    /* PWM1 Mode configuration: Channel1
    TIM1 Channel1 duty cycle = [TIM1_CCR1/(TIM1_ARR + 1)] * 100 = 50%*/ 
    /*TIM1 Frequency = TIM1 counter clock/(ARR + 1) */
    TIM1_EGR |= 0x01;                          //���³�ʼ��TIM1 
    TIM1_CR1 = 0X00;
    TIM1_RCR = 0X00;

    TIM1_OC1Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE,250, TIM1_OCPOLARITY_HIGH);
    
    TIM1_CR1 |= 0x01;
 
    
  //TIM1_CR1 |= (uint8_t)MASK_TIM1_CR1_CEN;
  
}

/**************************************************************************
 * ��������TIM1_OC1Init
 * ����  ��TIM1 ��һͨ��PWM��ʼ��
 * ����  ��TIM1_OCMode   ���ò���TIM1_OCMODE_PWM1:0x60 ,TIM1_OCMODE_PWM2:0x70
           TIM1_OutputState  TIM1_OUTPUTSTATE_ENABLE:0x11
           TIM1_Pulse     ռ�ձ�
           TIM1_OCPolarity  TIM1_OCPOLARITY_HIGH:0x00 ,TIM1_OCPOLARITY_LOW:0x22
 *
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ���� 
 *************************************************************************/
void TIM1_OC1Init(uint8_t TIM1_OCMode,uint8_t TIM1_OutputState,uint16_t TIM1_Pulse,uint8_t TIM1_OCPolarity )
{
      /* Disable the Channel 1: Reset the CCE Bit, Set the Output State , the Output Polarity */
    TIM1_CCER1 &= (uint8_t)(~( MASK_TIM1_CCER1_CC1E | MASK_TIM1_CCER1_CC1P));
    /* Set the Output State &  Set the Output Polarity  */
    TIM1_CCER1 |= (uint8_t)((uint8_t)(TIM1_OutputState & MASK_TIM1_CCER1_CC1E ) | 
                             (uint8_t)(TIM1_OCPolarity & MASK_TIM1_CCER1_CC1P));

    /* Reset the Output Compare Bits  & Set the Ouput Compare Mode */
    TIM1_CCMR1 = (uint8_t)((uint8_t)(TIM1_CCMR1 & (uint8_t)(~(uint8_t)MASK_TIM1_CCMR1_OC1M)) |
                            (uint8_t)TIM1_OCMode);
    /* Set the Pulse value */
    TIM1_CCR1H = (uint8_t)(TIM1_Pulse >> 8);
    TIM1_CCR1L = (uint8_t)(TIM1_Pulse);
    TIM1_CCMR1 |= (uint8_t)MASK_TIM1_CCMR1_OC1PE;
}

void SetTIM1_PWM_Frequency(uint16_t TIM1_Period)
{
      /* Set the Autoreload value */
  
    TIM1_ARRH = (uint8_t)(TIM1_Period >> 8);
    TIM1_ARRL = (uint8_t)(TIM1_Period);
}

void SetTIM1_PWM_DutyCycle( uint16_t TIM1_Pulse)
{
    /* Set the Pulse value */
    TIM1_CCR1H = (uint8_t)(TIM1_Pulse >> 8);
    TIM1_CCR1L = (uint8_t)(TIM1_Pulse);
}

void TestPWM_LED(void)
{
  u16 Duty_Val;
  for(Duty_Val=0;Duty_Val<499;Duty_Val++)
  {
    SetTIM1_PWM_DutyCycle(Duty_Val);
    Delay(0xfff);
  }
}

void TestPWM_Beep(void)
{
  u8 i;
  for(i=0;i<7;i++)
  {
    SetTIM1_PWM_Frequency(Beep_Frequency[i]);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);
    Delay(0xffff);

  }
}
static void Delay(u16 nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}


/******************* (C) COPYRIGHT ���iCreateǶ��ʽ���������� *****END OF FILE****/