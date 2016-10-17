/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#ifndef __UART_H__
#define __UART_H__
#include "common.h"
extern volatile int16_t rx0end;
extern volatile int16_t rx1end;
extern void Init_Uart0(uint32_t Baud);
extern void Init_Uart1(uint32_t Baud);
extern void Uart0Send(uint8_t *pBuf,uint32_t Num);
extern void Uart1Send(uint8_t *pBuf,uint32_t Num);


#endif
