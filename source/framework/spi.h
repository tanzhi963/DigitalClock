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
UINT8 SPI_Read(VOID);//SPI���ֽڶ�ȡ����
VOID SPI_Write(UINT8 txdata);//SPI���ֽ�д�뺯��
#endif
