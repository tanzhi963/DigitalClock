/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "../framework/include.h"


extern uchar laserStatus;

void Init_Sensor(void);
void SensordataProcess(uint data);
void disconnect(void);
void displaycount(int data);
void valueTempProcess(uint data);
void disconnectProcess(void);
void connectProcess(void);
void sendsensordata(uint data);

#endif

