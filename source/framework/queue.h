/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "common.h"

#include"uart.h"
#define QUEUEMAXSIZE 255 //ÇëÎðÐÞ¸Ä
#define TQUEUEMAXSIZE 25 
typedef struct
{
	volatile uint8_t data[QUEUEMAXSIZE];
	volatile uint8_t front,rear;
	volatile uint8_t num;
}Queue;

typedef struct
{
	uint16_t data[TQUEUEMAXSIZE];
	uint8_t front,rear;
	uint8_t num;
}TimeQueue;

extern Queue Rx0data;
extern Queue Rx1data;
extern Queue Rfdata;
extern TimeQueue Timedata;
extern uint8_t pnull[1];
extern uint8_t MyTimeout;
extern int8_t  ValidValueIndex; 

void	Init_Queue(void);

int8_t  QueueEnter(Queue *Rxdata,uint8_t x);
uint8_t	QueueOut(Queue *Rxdata);
int8_t	QueueEmpty(Queue *Rxdata);

int8_t TimeQueueEnter(TimeQueue* Tdata,uint16_t time); 
int8_t TimeQueueEmpty(TimeQueue* Tdata);
uint16_t TimeQueueOut(TimeQueue* Tdata); 

#endif

