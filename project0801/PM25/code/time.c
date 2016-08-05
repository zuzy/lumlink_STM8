#include "head.h"

void Clk_conf(void)
{
  CLK_CKDIVR&= (uint8_t)(~0x18);/*使能内部时钟*/
  CLK_CKDIVR|= (uint8_t)0x00;/*设置时钟为内部16M高速时钟*/
  
}

void delay_1us(void)   
{    
        asm("nop");  
        asm("nop");   
        asm("nop");   
        asm("nop");
//        asm("nop"); 
//        asm("nop"); 
} 

void delay_ms(u32 nTime)
{
          u16 i;
          while(nTime--)  
          for(i=900;i>0;i--)
          delay_1us();
}


void inline delay_us(unsigned int i)
{
        while(i--)
        {
                delay_1us();
        }
}


/*

static u32 TimingDelay;

void Tim1_Time_Upmode_conf(uint16_t TIM1_Prescaler,
                           uint16_t TIM1_Period,
                           uint8_t TIM1_RepetitionCounter)
{
  TIM1_ARRH = (uint8_t)((TIM1_Period - 1)>> 8);
  TIM1_ARRL = (uint8_t)(TIM1_Period - 1);
  
  TIM1_PSCRH = (uint8_t)(TIM1_Prescaler >> 8);
  TIM1_PSCRL = (uint8_t)(TIM1_Prescaler);
  
  TIM1_CR1 = (uint8_t)((uint8_t)(TIM1_CR1 & (uint8_t)(~(MASK_TIM1_CR1_CMS  | MASK_TIM1_CR1_DIR)))
                           | (uint8_t)(TIM1_COUNTERMODE_UP));


  TIM1_RCR = TIM1_RepetitionCounter;

  TIM1_CR1 |= MASK_TIM1_CR1_ARPE;

  TIM1_IER |= (uint8_t)TIM1_IT_UPDATE;

  TIM1_CR1 |= MASK_TIM1_CR1_CEN;
}

void TimingDelay_Decrement(void)
{
  if(TimingDelay != 0x00)
    TimingDelay--;
}

void Delay_ms(u32 nTime)  
{  
  TimingDelay = 50*nTime;

  while(TimingDelay != 0);
}  

void Delay_us_20(u32 nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}



#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{
  TimingDelay_Decrement();
  // Clear the IT pending Bit 
  TIM1_SR1 = (uint8_t)(~(uint8_t)TIM1_IT_UPDATE);
  
}
*/
