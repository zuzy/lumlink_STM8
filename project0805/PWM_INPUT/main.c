//--------------------------------------------------------------------
#include "type_def.h"
#define uchar              unsigned char
#define uint                unsigned int 

uint IrCycle = 0;                                  //��������
uint IrHigh = 0;                                   //ռ�ձ�

//������ն˿ڳ�ʼ��

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
    PC_DDR_DDR1 = 0;       //PC1Ϊ����
    PC_CR1_C11 = 1;
    PC_CR2_C21 = 0;
} 
//ʹ��TIM1��PWM���벶��
void Ir_PWM_Init(void)
{ 
    TIM1_PSCRH = 0;
    TIM1_PSCRL = 0; 
    TIM1_CCER1 &= 0xee;//��ֹ���벶��1��2
    TIM1_CCMR1 |= 0x31;// ch1��ti1fp1
    TIM1_CCER1 &= 0xec;//ch1 �����ش���
    TIM1_CCMR2 |= 0x32;// ch2ѡ�� ti1fp2��
    TIM1_CCER1 |= 0x20;//ch1 �½��ش��� ic2
    TIM1_SMCR |= 0x54;//ѡԴ����Դ�ʹ�����ʽ ��λ
    TIM1_CCER1 |= 0x11;//ʹ�����벶��1��2
    TIM1_CR1 |= 0x05;
} 

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

void Ir_Receive(void)
{
    if ((TIM1_SR1_CC1IF == 1)&&(TIM1_SR1_CC2IF == 1))
    {
        IrHigh = (uint)(TIM1_CCR2H); 
        IrHigh = (IrHigh << 8) + TIM1_CCR2L;  //IrHighռ�ձ�
        IrCycle = (uint)(TIM1_CCR1H);
        IrCycle = (IrCycle << 8) + TIM1_CCR1L;  //IrCycle����
    }
}


//��ʼ��
void Devices_Init(void)
{
    delay_ms(200);
    CLK_CKDIVR&= (uint8_t)(~0x18);/*ʹ���ڲ�ʱ��*/
    CLK_CKDIVR|= (uint8_t)0x00;/*����ʱ��Ϊ�ڲ�16M����ʱ��*/
    Ir_Init();
    pwm_ch2_output_init();
    Ir_PWM_Init(); 
  
} 
//������
void main( void )
{
  Devices_Init();
  while(1)
  {
    Ir_Receive();
    delay_ms(200);
  }
}