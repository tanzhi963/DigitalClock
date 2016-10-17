/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include"queue.h"

Queue Rx0data;
Queue Rx1data;
Queue Rfdata;
TimeQueue Timedata;

uint8_t MyTimeout = 0;
uint8_t pnull[1]={0};
int8_t ValidValueIndex = -1;


VOID Init_Queue(VOID)
{ 
	Rx0data.front = QUEUEMAXSIZE-1;
	Rx0data.rear = QUEUEMAXSIZE-1;
	Rx0data.num = 0;
	
	Rx1data.front = QUEUEMAXSIZE-1;
	Rx1data.rear = QUEUEMAXSIZE-1;
	Rx1data.num = 0;
	
	Rfdata.front = QUEUEMAXSIZE-1;
	Rfdata.rear = QUEUEMAXSIZE-1;
	Rfdata.num = 0;
	
	Timedata.front = TQUEUEMAXSIZE-1;
	Timedata.rear = TQUEUEMAXSIZE-1;
	Timedata.num = 0;
}

INT8 QueueEnter(Queue* Rxdata,UINT8 x)
{
    if(Rxdata->num == QUEUEMAXSIZE)
    {
        return -1;
    }
    else
    {
        Rxdata->rear=(Rxdata->rear+1)%QUEUEMAXSIZE;
        Rxdata->data[Rxdata->rear]=x;
        Rxdata->num++;
        return 1;
    }
}

UINT8 QueueOut(Queue* Rxdata)
{
    if(Rxdata->num == 0)
    { 
        return 255;
    }
    else
    {
        Rxdata->front=(Rxdata->front+1)%QUEUEMAXSIZE;
        Rxdata->num--;
        return Rxdata->data[Rxdata->front];
    }
}

INT8 QueueEmpty(Queue* Rxdata)
{
 if(Rxdata->num==0)
    {
        return 1;
    }
 else
    {
        return -1;
    }
}
INT8 TimeQueueEnter(TimeQueue* Tdata,UINT16 time)//数据超过容量时允许覆盖
{
    Tdata->rear=(Tdata->rear+1)%TQUEUEMAXSIZE;
    Tdata->data[Tdata->rear] = time; 
    Tdata->num++;

    if(Tdata->num > TQUEUEMAXSIZE)//队列已满
    {
        Tdata->num = TQUEUEMAXSIZE;
        Tdata->front = Tdata->rear;//被覆盖的数据不能读取 将读取指针移动和写指针相同的位置
    }

    if(Tdata->rear == ValidValueIndex)
    {
        MyTimeout = 1;//出现有效值被覆盖的情况
        ValidValueIndex = -1;
    }

    return 1;
}


UINT16 TimeQueueOut(TimeQueue* Tdata)
{
    if(Tdata->num == 0)
    { 
        return 0;
    }
    else
    {
        Tdata->front=(Tdata->front+1)%TQUEUEMAXSIZE;
        Tdata->num--;
        return  Tdata->data[Tdata->front] ;
    }
}

INT8 TimeQueueEmpty(TimeQueue* Tdata)
{
    if(Tdata->num==0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
