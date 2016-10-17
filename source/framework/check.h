/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __CHECK_H__
#define __CHECK_H__
#include "stdint.h"
#include "typedef.h"

uint16_t CRC16Check(uint8_t *buf, uint8_t len);
UINT8 CheckSum(UINT8 *buf, UINT8 len);

#endif
