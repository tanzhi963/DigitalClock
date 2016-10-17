/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

/****************************************************************************
**
** 整体设计思路
** 采样设计初步  AD采集设置频率10KHz   激光器开关频率100Hz
**
****************************************************************************/

#include "sensor.h"
/********************************************************************/
/***************************标志位设置区*****************************/
/********************************************************************/
uint oldADdata = 0;                                     //上一次采集的AD数值
uchar laserStatus = 0;                                  //当前激光发射器状态
uchar sensorState = 0;                                  //标志目前传感器是否接收到了新的光信号上升沿
uchar pulseKeep = 0;                                    //用来表示符合发送脉冲的节奏的次数，初步定为满足10个脉冲节奏，就判断为有效光信号，                                                     //如果不足10次，就放弃这次判断，重新等待新的有效数据                                      
uchar timeoutCount = 0;                                 //超时等待标志位
uchar connectState = 0;                                 //正确匹配标志位
uchar displaycountbit = 0;                              //延时刷新LED屏幕的次数标志位
int valueTemp;                                          //临时储存光强差
uchar passonetime = 0;                                  //用来跳过一次显示




/********************************************************************/
/************************系统运行参数设置区**************************/
/********************************************************************/
uint intensityThreshold = 300;                                //在这里设定触发的强度门槛！！
uchar pulseKeepmaxvalue = 1 ;                                 //判断为已连接需要保持的脉冲数
uchar timeoutmaxvalue = 2;                                    //这里设置断开触发时长

uint buffpoint = 0;                                           //发送数组位置标志位
uchar senddata[30] = {0x00};                                  //串口发送数据数组



void Init_Sensor(void)
{
    uint i;
    for(i = 0;i<30;i=i+3)
    {
        senddata[i] = 0xff;
    }
}

void SensordataProcess(uint data)
{
    data = 5000 - data;                                         //因为硅光二极管是光越强，与地线的压差越低，所以与基准电压相减
    sendsensordata(data);                                       //将原始ADC值进行处理后串口发送
    valueTempProcess(data);                                     //处理一下不同激光管状态下的取值
    
    if(valueTemp >= intensityThreshold)                         //如果达到门槛强度，进行脉冲匹配处理
    {
        connectProcess();
    }
    else
    {
        disconnectProcess();                                           //未达到光强度门槛，进入断开连接处理
    }
    
    if (connectState == 1)
    {
        bit_set(0,1,1);
    }
    else
    {
        bit_set(0,1,0);
    }
    oldADdata = data;                                                   //更新最新的AD数值
    valueTemp = 0;                                                      //比较变量清零
}


void connectProcess(void)
{
        if(sensorState == 0 && connectState == 0)
        {
            sensorState = 1;                                    //标记目前采集到新的光强上升信号
        }
        else if(sensorState == 1 && connectState == 0)
        {
            pulseKeep++;                                        //计一次脉冲节奏保持
    
            if(pulseKeep >= pulseKeepmaxvalue)                  //符合十次脉冲
            {
                connectState = 1;                               //表示已经连接
                pulseKeep = 0;                                  //已经修改为已连接，清零脉冲计数
            }
        }
        else if(sensorState == 1 && connectState == 1)          //保持连接状态
        {
            timeoutCount = 0;                                   //清空超时计数
        }
        else                                                    //出现异常，全部重置
        {
            sensorState = 0; 
            pulseKeep = 0;
            connectState = 0;
            
        }
}


void disconnectProcess(void)
{
    if(sensorState == 1 && connectState == 0)                    //没有进入连接模式，检测是否超时
    {
        sensorState = 0;                         //关闭信号标志位
    }
    else if(sensorState == 1 && connectState == 1)                  //进入连接模式，发生连接中断情况
    {
        timeoutCount++;                          //超时标志位计数
        if(timeoutCount >= timeoutmaxvalue)                    //计数大于定义的参数
        {
            timeoutCount = 0;                    //超时标志位清零
            connectState = 0;                    //连接状态改为未连接
            sensorState = 0;                     //准备状态改为无信号
            
            MySignal ++;                                        //发出被遮挡信号
        }
    }
}



void valueTempProcess(uint data)
{
    if(laserStatus == 1)                                //如果此时激光管是激发状态
    {
        valueTemp = data - oldADdata;                   //采集到新的数据，跟旧数据进行对比，
    }
    else
    {
        valueTemp = oldADdata - data;                   //采集到新的数据，跟旧数据进行对比，
    }
    
    if(valueTemp < 0)
    {
        valueTemp = 0;
    }
}



void sendsensordata(uint data)
{
    uchar data_L = data & 0xff;
    uchar data_H = (data >> 8) & 0xff;
    buffpoint++;
    senddata[buffpoint] = data_L;
    buffpoint++;
    senddata[buffpoint] = data_H;
    buffpoint++;
    if(buffpoint >= 30)
    {
        Uart0Send(senddata,30);
        buffpoint = 0;
    }
}



void displaycount(int data)
{
    if(passonetime == 0)
    {
        passonetime = 1;
        return;
    }
    if (displaycountbit >= 10)
    {       
        LED_reflash(data);                              //显示新的传感器数值
        displaycountbit = 0;                               //清零显示计数器
    }
    displaycountbit++;                                  //显示计数器
}


