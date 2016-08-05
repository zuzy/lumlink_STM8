
#include "type_def.h"
#include "clock.h"
#include "mei.h"
//#include "lum_lcd1602.h"


U8 lum_ComDHT11(void)
{
	U8 i,temp,comdata;

    
	for(i = 8; i>0; i--)
	{
		while(!DHT11_DATA_VALUE)
        {
            ;
        }

		lum_delay10Us(1);
		lum_delay10Us(1);
		lum_delay10Us(1);
		lum_delay10Us(1);
        
		temp = 0;
		if(DHT11_DATA_VALUE)
		{
			temp = 1;
		}
		comdata = comdata<<1;
		comdata = comdata|temp;

		while(DHT11_DATA_VALUE);
	}
	return comdata;
}


void lum_ReadTempAndHumi(void)
{
    U8 data[] = {1, 0};
	U8 ui_TempValue = 0;
	U8 ui_HumiValue = 0;
	U8 uc_DHT11Value[SIZE];
    
    
	DHT11_DATA_OUT;
	DHT11_DATA_LOW;

	lum_delay10Us(2000);

	DHT11_DATA_HIGH;
	DHT11_DATA_IN;

	lum_delay10Us(1);
	lum_delay10Us(1);
	lum_delay10Us(1);

	while(!DHT11_DATA_VALUE); //80us的应答信号 DHT11 TO MCU 
    while(DHT11_DATA_VALUE); //80us的通知信号 DHT11 TO MCU
    
    uc_DHT11Value[0] = lum_ComDHT11();
	uc_DHT11Value[1] = lum_ComDHT11();
	uc_DHT11Value[2] = lum_ComDHT11();
	uc_DHT11Value[3] = lum_ComDHT11();
	uc_DHT11Value[4] = lum_ComDHT11();

	if((uc_DHT11Value[0] + uc_DHT11Value[1] + uc_DHT11Value[2] + uc_DHT11Value[3]) == uc_DHT11Value[4])
	{
		ui_HumiValue = uc_DHT11Value[0];
		ui_TempValue = uc_DHT11Value[2];
        
        //lum_lcdDispNum(0, 1, ui_TempValue, data);
        //lum_lcdDispChar(2, 1, 1);
        //lum_lcdDispNum(13, 1, ui_HumiValue, "%");
	}
}
