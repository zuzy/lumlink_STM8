#include "pm2_5.h"
#include "gpio.h"
#include "time.h"
#include "lcd1602.h"
#include "adc.h"
#include "convert.h"

#if 0
u16 read_pm25_byte(bool flag)
{
	int i;
	u8 pm_bit[8];
    u16 ret;
	u16 temp = 0;
	int count = 100;

    while(PM25_I)			//ȷ��Ϊ6ms�ߵ�ƽ��
        while(--count>0)
        {
            delay_us(7);
            while(!PM25_I);
        }

	for(i = 7;i >= 0; --i) //������ôд ���ݻ��
	{
        delay_us(210); 
	  	pm_bit[i] = PM25_I;	
	}
	for(i=0;i<8;++i)
	{
	  	temp |= pm_bit[i];
		temp <<= 1;
	}
	temp >>= 1;
    ret = (u8) temp;
	return temp;
}
#endif

#if 1
u8 read_pm25_byte(void)
{
	int i;
	u8 pm_bit[8];
	u16 temp = 0;
    /*
        count��delay����� ��Ҫ����С���Լ����ڸߵ�ƽ�ж����Լ��жϽ������ĵ�ʱ�� 
        �������ԣ���count��delay����ϱȽ�Сʱ��ż�����������޷����㣬
    
    */    
	int count = 50;              //ȷ��Ϊ6ms�ߵ�ƽ����Ӧ��һ���͵�ƽ����������delay
	while(PM25_I)			
	  	while(--count>0)
		{
	  		delay_us(6);
			while(!PM25_I);
		}
#if 1
	//delay_us(210);  //210�Դ���420us delay

	for(i = 7;i >= 0; --i)      //���Խ�� һ���ֽ�ת������һ�����Ѵ�Լ3500��us
	{
        delay_us(210);          //delay 420us
	  	pm_bit[i] = PM25_I;	
	}
    delay_us(100);              //��90ʱ������������100delayʱ����û�����⣻
#else
    delay_us(210);  //300��Žӽ�500us delay

	for(i = 7;i >= 0; --i)
	{
	  	pm_bit[i] = PM25_I;	
		delay_us(210);
	}
#endif
	for(i=0;i<8;++i)
	{
	  	temp |= pm_bit[i];
		temp <<= 1;
	}
	temp >>= 1;
	return (u8)temp;
}
#endif


void pm25_read()
{
    
    asm("sim");    //��ֹ�ж� 

    int i = 7;
    u16 comp;
    u16 value;
    u16 pm25_value[6]={0,0,0,0,0,0};
	u32 break_count = 0;
    char string_pm25[15];
    
    LED_Y = 0;

#if 0 //ԭʼ�Ĳ���0xff��0xaa����
    u16 temp_value[2]={0,0};
    while(1)
    {
        temp_value[0] = read_pm25_byte();
        temp_value[1] = read_pm25_byte();
        if((0xff == temp_value[0])&&(0xaa == temp_value[1]))
            break;
    }
#endif
    
    while(!((read_pm25_byte()==0xff)&&(read_pm25_byte()==0xaa)))		//����0xff��0xaa��������Ϊ��ʼ�����ų��ж���������
	{
		break_count++;
		if (break_count > 20) return;
	}                 
    for(i = 0;i < 6;++i)
        pm25_value[i] = read_pm25_byte();
    
    asm("rim");    //�����ж� 
    
    comp = pm25_value[0] + pm25_value[1] + pm25_value[2] + pm25_value[3];
    if(comp >255) comp -= 256;          //�������
    if(comp == pm25_value[4])
    {
        value = (u16)((pm25_value[0] << 8 | pm25_value[1])*1.43); //ֱ��ת��Ϊug/m3��3.5mg/m3��Ӧ1V
        /*  
            ��׼�ı���Ϊ3.5mg/m3    
            ADCת��Ϊ��ƽ�źţ� ADC/1024*5 
            ������������  ADC*5/3.5 ug/m3  ԼΪ  ADC*1.43 ug/m3;
            ֮���پ���adc_convert����ת��Ϊ ǧ��֮һ��С������λ��Ϊmg/m3
        */
        convert(string_pm25,value,0);     //adcת��ΪС��
        Lcd_Write_Command( 0x01,1);         //����
        Lcd_Puts(0,1,"P25:     mg/m3");
        Lcd_Puts(4,1,(uchar*)string_pm25);     
        LED_Y = 1;
    }
}