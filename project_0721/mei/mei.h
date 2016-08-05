#ifndef __LUM_DHT11_H__
#define __LUM_DHT11_H__


/**************宏定义****************/


#define DHT11_DATA_OUT          PB_DDR_DDR5 = 1 //输出 
#define DHT11_DATA_IN           PB_DDR_DDR5 = 0 //输入 
#define DHT11_DATA_HIGH         PB_ODR_ODR5 = 1 //拉高 
#define DHT11_DATA_LOW          PB_ODR_ODR5 = 0 //拉低 
#define DHT11_DATA_PULL_UP      PB_CR1_C15 = 1 //上拉 
#define DHT11_DATA_FLOATING     PB_CR1_C15 = 0 //浮空 
#define DHT11_DATA_PUSH_PULL    PB_CR1_C15 = 1 //推挽 
#define DHT11_DATA_OPEN_DRAIN   PB_CR1_C15 = 0 //开漏 
#define DHT11_DATA_VALUE        PB_IDR_IDR5 //DQ值

#define SIZE 5

/**************接口函数***************/
void lum_ReadTempAndHumi(void);

#endif

