#ifndef __DHT11_H
#define __DHT11_H
#include "type_def.h"

#define INIT_LOW 18
#define INIT_HIGH 40

#define REPLAY 80

#define READY 50

#define ZERO 27
#define ONE 3

#define DELAY 40

int dht_proc(void);
void read_dht11(void);

#endif