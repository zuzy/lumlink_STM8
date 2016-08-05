#include "mei.h"
#include "clock.h"

int main(void)
{
  lum_clkConfig();
  while(1)
    lum_ReadTempAndHumi();
}