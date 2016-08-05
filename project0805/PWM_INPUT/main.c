//--------------------------------------------------------------------
#include "type_def.h"
#define uchar              unsigned char
#define uint                unsigned int 

uint IrCycle = 0;                                  //红外周期
uint IrHigh = 0;                                   //占空比

//红外接收端口初始化

void delay_1us(void)   
{    
    asm("nop");  
    asm("nop");   
    asm("nop");   
    asm("nop");
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

void Ir_Init(void)
{
    PC_DDR_DDR1 = 0;       //PC1为输入
    PC_CR1_C11 = 1;
    PC_CR2_C21 = 0;
} 
//使用TIM1的PWM输入捕获
void Ir_PWM_Init(void)
{ 
    TIM1_PSCRH = 0;
    TIM1_PSCRL = 0; 
    TIM1_CCER1 &= 0xee;//禁止输入捕获1，2
    TIM1_CCMR1 |= 0x31;// ch1到ti1fp1
    TIM1_CCER1 &= 0xec;//ch1 上升沿触发
    TIM1_CCMR2 |= 0x32;// ch2选择 ti1fp2上
    TIM1_CCER1 |= 0x20;//ch1 下降沿触发 ic2
    TIM1_SMCR |= 0x54;//选源触发源和触发方式 复位
    TIM1_CCER1 |= 0x11;//使能输入捕获1，2
    TIM1_CR1 |= 0x05;
} 

void pwm_ch2_output_init()
{
    TIM2_PSCR = 0X01;
    TIM2_ARRH = 0X00;
    TIM2_ARRL = 100;
    TIM2_CR1 &= 0XFE;
    CLK_CKDIVR&= (uint8_t)(~0x18);/*使能内部时钟*/
    CLK_CKDIVR|= (uint8_t)0x00;/*设置时钟为内部16M高速时钟*/
    TIM2_CCER1 &= 0xFC;
    TIM2_CCER1 |= 0x01;
    TIM2_CCMR1 &= 0x8F;
    TIM2_CCMR1 |= 0X60;
    TIM2_CCR1H = 0X00;
    TIM2_CCR1L = 52;
    TIM2_CR1 |= 0X01;
}

void Ir_Receive(void)
{
    if ((TIM1_SR1_CC1IF == 1)&&(TIM1_SR1_CC2IF == 1))
    {
        IrHigh = (uint)(TIM1_CCR2H); 
        IrHigh = (IrHigh << 8) + TIM1_CCR2L;  //IrHigh占空比
        IrCycle = (uint)(TIM1_CCR1H);
        IrCycle = (IrCycle << 8) + TIM1_CCR1L;  //IrCycle周期
    }
}


//初始化
void Devices_Init(void)
{
    delay_ms(200);
    CLK_CKDIVR&= (uint8_t)(~0x18);/*使能内部时钟*/
    CLK_CKDIVR|= (uint8_t)0x00;/*设置时钟为内部16M高速时钟*/
    Ir_Init();
    pwm_ch2_output_init();
    Ir_PWM_Init(); 
  
} 
//主程序
void main( void )
{
  Devices_Init();
  while(1)
  {
    Ir_Receive();
    delay_ms(200);
  }
}