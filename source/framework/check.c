/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include"check.h" 
/****************************************************
** 函数名称: CRC16Check
** 输    入: buf 要校验的数据
             len 要校验的数据的长度 
** 输    出: 校验值
** 功能描述: CRC16循环冗余校验
*****************************************************/
UINT16 CRC16Check(UINT8 *buf, UINT8 len) 
{
    UINT8  i, j;
    UINT16 uncrcReg = 0xffff;
    UINT16 uncur;

    for (i = 0; i < len; i++) 
    {
        uncur = buf[i] << 8;

        for (j = 0; j < 8; j++) 
        { 
            if ((INT16)(uncrcReg ^ uncur) < 0)
            {
                 uncrcReg = (uncrcReg << 1) ^ 0x1021;
            }
            else
            {
                  uncrcReg <<= 1; 
            } 
               
            uncur <<= 1;            
        }
    }

    return uncrcReg;
} 
/****************************************************
** 函数名称: CheckSum
** 输    入: buf 要校验的数据  
** 输    出: 校验值
** 功能描述: 8位和校验
*****************************************************/
UINT8 CheckSum(UINT8 *buf, UINT8 len) 
{
    UINT16  i;
    UINT8 sum = 0x00; 

    for (i = 0; i < len; i++) 
    {
        sum += buf[i];
    }

    return sum;
} 
