#ifndef __ADC_ZIZY_H
#define __ADC_ZIZY_H
#include "time.h"
#include "type_def.h"

//void adc_init(u8 ch);
void adc_init(void);
u16 adc_getValue(void);
void ReadAdc(u16 * value);

struct ADC_DATA
{
  u16 AdcJq;
  u16 AdcVref;
  u16 AdcTvoc;
};

#endif