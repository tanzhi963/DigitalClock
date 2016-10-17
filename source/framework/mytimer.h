/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __MYTIMER_H__
#define __MYTIMER_H__


#include "include.h"


extern UINT16 Time0out;
extern UINT16 Time1out;
extern UINT16 Time2out;


void Init_TMR0(void);
void StarTime0(UINT16 time);
void StopTime0(void);

void Init_TMR1(void); 
void StarTime1(UINT16 time);
void StopTime1(void); 

void Init_TMR2(void); 
void StarTime2(UINT16 time);
void StopTime2(void);

/****************************************
*函数名称:Delayms
*输    入:无
*输    出:无
*功    能:系统时钟微秒延时
******************************************/ 
void Delayus(uint32_t unCnt);
 
/****************************************
*函数名称:Delayms
*输    入:无
*输    出:无
*功    能:系统时钟毫秒延时
******************************************/ 
void Delayms(uint32_t DelayTime);


#endif

