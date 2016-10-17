/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#ifndef __DATAPROCESS_H__
#define __DATAPROCESS_H__


/****************************************************************************
**
** 包含工程所需文件
**
****************************************************************************/

#include "include.h"


/****************************************************************************
**
** 定义项目常量
**
****************************************************************************/

extern volatile UINT8 Time0Signal;

/****************************************************************************
**
** 函数声明
**
****************************************************************************/


VOID Init_Dataprocess(VOID);
VOID Analyze_Rx0data(VOID);
VOID Process_Rx0data(UINT8 data[],UINT8 typeerr);
VOID Analyze_Rx1data(VOID);
VOID Process_Rx1data(UINT8 data[],UINT8 typeerr);
VOID Analyze_Signaldata(VOID);
void Analyze_time1(void);

#endif
