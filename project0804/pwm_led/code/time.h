#ifndef __TIM1_H
#define __TIM1_H
#include "type_def.h"

#define TIM1_COUNTERMODE_UP 0x00
#define TIM1_IT_UPDATE 0x01
/*
void Tim1_Time_Upmode_conf(uint16_t TIM1_Prescaler,
                           uint16_t TIM1_Period,
                           uint8_t TIM1_RepetitionCounter);
void TimingDelay_Decrement(void);
void Delay_ms(u32 nTime);
void Delay_us_20(u32 nTime);
*/


void Clk_conf();
void delay_ms(u32 nTime);
void delay_us(unsigned int i);

void Tim2_Init();
void delay_tens_of_us_tim4( u16 us);
void delay10Us(u16 delayCount);

#endif