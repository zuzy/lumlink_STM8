/******************** (C) COPYRIGHT  风驰iCreate嵌入式开发工作室 ********************/
#ifndef __PWM_H
#define __PWM_H
#include "type_def.h"


#define TIM1_Channel   2
#define TIM1_Channel1  1
#define TIM1_Channel2  2
#define TIM1_Channel3  3

#define TIM1_OCMODE_PWM1 0x60 
#define TIM1_OCMODE_PWM2 0x70
#define TIM1_OUTPUTSTATE_ENABLE 0x11
#define TIM1_OCPOLARITY_HIGH 0x00 
#define TIM1_OCPOLARITY_LOW 0x22

void pwm_ch2_output_init();

void PWM_Init(void);
void SetTIM1_PWM_Frequency(uint16_t TIM1_Period);
void SetTIM1_PWM_DutyCycle( uint16_t TIM1_Pulse);
void TIM1_OC1Init(uint8_t TIM1_OCMode,uint8_t TIM1_OutputState,\
                  uint16_t TIM1_Pulse,uint8_t TIM1_OCPolarity );
void TestPWM_LED(void);
void TestPWM_Beep(void);


#endif


/******************* (C) COPYRIGHT 风驰iCreate嵌入式开发工作室 *****END OF FILE****/