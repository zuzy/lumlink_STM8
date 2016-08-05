#ifndef __LUM_DHT11_H__
#define __LUM_DHT11_H__


/**************�궨��****************/


#define DHT11_DATA_OUT          PB_DDR_DDR5 = 1 //��� 
#define DHT11_DATA_IN           PB_DDR_DDR5 = 0 //���� 
#define DHT11_DATA_HIGH         PB_ODR_ODR5 = 1 //���� 
#define DHT11_DATA_LOW          PB_ODR_ODR5 = 0 //���� 
#define DHT11_DATA_PULL_UP      PB_CR1_C15 = 1 //���� 
#define DHT11_DATA_FLOATING     PB_CR1_C15 = 0 //���� 
#define DHT11_DATA_PUSH_PULL    PB_CR1_C15 = 1 //���� 
#define DHT11_DATA_OPEN_DRAIN   PB_CR1_C15 = 0 //��© 
#define DHT11_DATA_VALUE        PB_IDR_IDR5 //DQֵ

#define SIZE 5

/**************�ӿں���***************/
void lum_ReadTempAndHumi(void);

#endif

