#include "exti_key.h"
void key_exti_conf()
{
	PA_DDR &= 0XF7;
	PA_CR1 |= 0X08;
	PA_CR2 |= 0X08;
	EXTI_CR1 &= 0XFC;
	EXTI_CR1 |= 0X02;
}