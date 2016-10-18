/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

//包含编译器框架头文件
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//包含框架头文件

#include "../framework/common.h"
#include "../framework/function.h"
#include "../framework/mytimer.h"
#include "../framework/watchdog.h"
#include "../framework/uart.h"
#include "../framework/GPIO.h" 
#include "../framework/PLL.h"
#include "../framework/dataprocess.h"
#include "../framework/ADC.h"
#include "../framework/check.h"
#include "../framework/I2C.h"
#include "../framework/M051.h"
#include "../framework/queue.h"
#include "../framework/Register_Bit.h"
#include "../framework/spi.h"
#include "../framework/Typedef.h"
// #include "../framework/Macro_SystemClock.h"
// #include "../framework/Macro_Timer.h"


//包含模块头文件
#include "../module/AM2320.h"
#include "../module/DS3231.h"
#include "../module/sensor.h"
#include "../module/si4432.h"
#include "../module/HC164LED.h"
#include "../module/MAX485.h"




#endif
