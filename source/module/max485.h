/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __MAX485_H__
#define __MAX485_H__

#include "../framework/include.h"

void Init_max485(void);
void max485send(uchar *p);
void max485sendtest(void);


#endif

