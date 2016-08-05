#include "type_def.h"

void num2char(char *string, double number, uint8_t g, uint8_t l)
{
    uint8_t i;
    int temp;
    double t = 0.0;
    
    char * str;

    if(number < 0)
    {
      *string = 0x2d;           //Ğ´Èë¸ººÅ
      str = &string[1];
      number = - number;
    }     
    else 
      str = string;
    temp = (int) number;

      
    
    for (i = 1; i<=g; ++i)
    {
        str[g-i] = temp % 10 + '0';
        temp /= 10;
    }
    *(str+g) = '.';
    temp = 0;
    t = number;
    for(i=1; i<=l; ++i)
    {
        temp = (int)(t*10);
        str[g+i] = temp % 10 + '0';
        t *= 10;
    }
    *(str+g+l+1) = '\0';
}
