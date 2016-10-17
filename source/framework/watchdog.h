/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include "common.h"

#define WTD_TIME TO_2T16_CK;
	/*
			TO_2T14_CK;	//(2^14+1024)*(1000000/10000)=17408*100=1740800us=1.7408s
			TO_2T16_CK;	// 6.6559s		
			TO_2T18_CK; //26.3168s
	*/
extern void Init_WatchDog(void);
extern void Feed_WatchDog(void);

#endif

