/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

/****************************************************************************
**
** 包含所有的系统文件
**
****************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "M051.h"
#include "Register_Bit.h"
#include "Macro_SystemClock.h"
#include "Macro_Timer.h"

/****************************************************************************
**
** 用户自定义包含文件
**
****************************************************************************/

#include "typedef.h"






#ifndef __DEBUG
#define __DEBUG
#endif

#ifdef  __DEBUG
#define DEBUGMSG	 printf
#else
#define DEBUGMSG(x)	 (void)0
#endif

#ifndef LITTLE_ENDPOINT
#define LITTLE_ENDPOINT
#endif

#ifdef  LITTLE_ENDPOINT
#define SWAP16(x)   (x)
#else
#define SWAP16(x)  (((UINT8)(x)<<8)|(UINT8)((x)>>8))
#endif

#define LSB(x)     ((UINT8)(x))
#define MSB(x)     ((UINT8)(((UINT16)(x))>>8)) 

#define __WFI				  __wfi

#define PROTECT_REG(__CODE)		  {Un_Lock_Reg();__CODE;Lock_Reg();}


#define CLOCK_SETUP           1
#define CLOCK_EN              0xF
#define PLL_Engine_Enable     1 
#define PLL_SEL               0x00000000 
#define CLOCK_SEL             0x0    





void Un_Lock_Reg(void);
void Lock_Reg(void);
void PLL_Enable(void);
void NSR_Enable(void);
void NSR_Disable(void);
#endif
