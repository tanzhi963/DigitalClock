/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "max485.h"


void Init_max485(void)
{
    GPIO_set(4,3,1);
    bit_set(4,3,1);
}

void max485send(uchar *p)
{
    uint num = strlen((const char*)p);                      //�жϴ���ָ�����ݳ���

    bit_set(4,3,1);
    Uart0Send(p,num);                                       //����0��������
    bit_set(4,3,0);
    
}

void max485sendtest(void)
{
    bit_set(4,3,1);
    Uart0Send("max485test",10);
    bit_set(4,3,0);
}

