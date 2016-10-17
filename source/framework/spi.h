/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#include "common.h"

VOID Init_SPI1(VOID);
UINT8 SPI_Read(VOID);//SPI单字节读取函数
VOID SPI_Write(UINT8 txdata);//SPI单字节写入函数
#endif
