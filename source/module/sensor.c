/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

/****************************************************************************
**
** �������˼·
** ������Ƴ���  AD�ɼ�����Ƶ��10KHz   ����������Ƶ��100Hz
**
****************************************************************************/

#include "sensor.h"
/********************************************************************/
/***************************��־λ������*****************************/
/********************************************************************/
uint oldADdata = 0;                                     //��һ�βɼ���AD��ֵ
uchar laserStatus = 0;                                  //��ǰ���ⷢ����״̬
uchar sensorState = 0;                                  //��־Ŀǰ�������Ƿ���յ����µĹ��ź�������
uchar pulseKeep = 0;                                    //������ʾ���Ϸ�������Ľ���Ĵ�����������Ϊ����10��������࣬���ж�Ϊ��Ч���źţ�                                                     //�������10�Σ��ͷ�������жϣ����µȴ��µ���Ч����                                      
uchar timeoutCount = 0;                                 //��ʱ�ȴ���־λ
uchar connectState = 0;                                 //��ȷƥ���־λ
uchar displaycountbit = 0;                              //��ʱˢ��LED��Ļ�Ĵ�����־λ
int valueTemp;                                          //��ʱ�����ǿ��
uchar passonetime = 0;                                  //��������һ����ʾ




/********************************************************************/
/************************ϵͳ���в���������**************************/
/********************************************************************/
uint intensityThreshold = 300;                                //�������趨������ǿ���ż�����
uchar pulseKeepmaxvalue = 1 ;                                 //�ж�Ϊ��������Ҫ���ֵ�������
uchar timeoutmaxvalue = 2;                                    //�������öϿ�����ʱ��

uint buffpoint = 0;                                           //��������λ�ñ�־λ
uchar senddata[30] = {0x00};                                  //���ڷ�����������



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
    data = 5000 - data;                                         //��Ϊ���������ǹ�Խǿ������ߵ�ѹ��Խ�ͣ��������׼��ѹ���
    sendsensordata(data);                                       //��ԭʼADCֵ���д���󴮿ڷ���
    valueTempProcess(data);                                     //����һ�²�ͬ�����״̬�µ�ȡֵ
    
    if(valueTemp >= intensityThreshold)                         //����ﵽ�ż�ǿ�ȣ���������ƥ�䴦��
    {
        connectProcess();
    }
    else
    {
        disconnectProcess();                                           //δ�ﵽ��ǿ���ż�������Ͽ����Ӵ���
    }
    
    if (connectState == 1)
    {
        bit_set(0,1,1);
    }
    else
    {
        bit_set(0,1,0);
    }
    oldADdata = data;                                                   //�������µ�AD��ֵ
    valueTemp = 0;                                                      //�Ƚϱ�������
}


void connectProcess(void)
{
        if(sensorState == 0 && connectState == 0)
        {
            sensorState = 1;                                    //���Ŀǰ�ɼ����µĹ�ǿ�����ź�
        }
        else if(sensorState == 1 && connectState == 0)
        {
            pulseKeep++;                                        //��һ��������ౣ��
    
            if(pulseKeep >= pulseKeepmaxvalue)                  //����ʮ������
            {
                connectState = 1;                               //��ʾ�Ѿ�����
                pulseKeep = 0;                                  //�Ѿ��޸�Ϊ�����ӣ������������
            }
        }
        else if(sensorState == 1 && connectState == 1)          //��������״̬
        {
            timeoutCount = 0;                                   //��ճ�ʱ����
        }
        else                                                    //�����쳣��ȫ������
        {
            sensorState = 0; 
            pulseKeep = 0;
            connectState = 0;
            
        }
}


void disconnectProcess(void)
{
    if(sensorState == 1 && connectState == 0)                    //û�н�������ģʽ������Ƿ�ʱ
    {
        sensorState = 0;                         //�ر��źű�־λ
    }
    else if(sensorState == 1 && connectState == 1)                  //��������ģʽ�����������ж����
    {
        timeoutCount++;                          //��ʱ��־λ����
        if(timeoutCount >= timeoutmaxvalue)                    //�������ڶ���Ĳ���
        {
            timeoutCount = 0;                    //��ʱ��־λ����
            connectState = 0;                    //����״̬��Ϊδ����
            sensorState = 0;                     //׼��״̬��Ϊ���ź�
            
            MySignal ++;                                        //�������ڵ��ź�
        }
    }
}



void valueTempProcess(uint data)
{
    if(laserStatus == 1)                                //�����ʱ������Ǽ���״̬
    {
        valueTemp = data - oldADdata;                   //�ɼ����µ����ݣ��������ݽ��жԱȣ�
    }
    else
    {
        valueTemp = oldADdata - data;                   //�ɼ����µ����ݣ��������ݽ��жԱȣ�
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
        LED_reflash(data);                              //��ʾ�µĴ�������ֵ
        displaycountbit = 0;                               //������ʾ������
    }
    displaycountbit++;                                  //��ʾ������
}


