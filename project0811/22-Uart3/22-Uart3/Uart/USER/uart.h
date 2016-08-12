#ifndef __UART_H
#define __UART_H

#include "type_def.h"
#include <stdio.h>
#define HSIClockFreq 16000000
#define BaudRate  115200
#define UART3_FLAG_TXE  (uint8_t)0x80  /*!< Transmit Data Register Empty flag */
#define UART3_FLAG_RXNE (uint8_t)0x20 /*!< Read Data Register Not Empty flag */
#define RxBufferSize 64
void uart_conf(void);
void UART3_SendByte(u8 data);
void UART3_SendString(u8* Data,u16 len);
u8 UART3_ReceiveByte(void);
int fputc(int ch, FILE *f);
#endif