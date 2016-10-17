/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/


#ifndef __GPIO_H__
#define __GPIO_H__


#include "common.h"

/****************************************
*函数名称:init_GPIO
*输    入:无
*输    出:无
*功    能:通用输入输出初始化
******************************************/
void Init_GPIO(void);


/****************************************
*函数名称:GPIO_set
*输    入:uchar port,uchar bit,uchar direct
*输    出:无
*功    能:设置某一位通用IO的方向
******************************************/
void GPIO_set(uchar port,uchar bit,uchar direct);

/****************************************
*函数名称:bit_set
*输    入:uchar port,uchar bit,uchar value
*输    出:无
*功    能:设置某一位通用输出高低电平
******************************************/


void bit_set(uchar port,uchar bit,uchar value);

/****************************************
*函数名称:bit_turn
*输    入:uchar port,uchar bit
*输    出:无
*功    能:转换某一位通用输出高低电平
******************************************/


void bit_turn(uchar port,uchar bit);

/****************************************
*函数名称:bit_get
*输    入:uchar port,uchar bit,uchar value
*输    出:无
*功    能:获取某一位通用输入高低电平
******************************************/


bool bit_get(uchar port,uchar bit);



#endif

