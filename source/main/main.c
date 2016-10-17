/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "main.h"




void SystemInit(void)
{
    Init_Clock();                   //��ʼ��ϵͳʱ��
	Init_WatchDog();                //��ʼ�����Ź�
	Init_GPIO();                    //��ʼ��GPIO
	Init_Uart0(57600);				//����0��ʼ�� 
	Init_TMR0();                    //��ʼ����ʱ��0
    Init_TMR1();                    //��ʼ����ʱ��1
    Init_TMR2();                    //��ʼ����ʱ��2
	Init_Dataprocess();	            //��ʼ�����ݴ��� 

}


/****************************************
*��������:main
*��    ��:��
*��    ��:��
*��    ��:��������
******************************************/
INT32 main(VOID)
{
    
	SystemInit();          //ȫ�ֳ�ʼ������
	printf("hello\r\n");
	
	StarTime0(50000);
	
	while(1)
    {
        
        
		Delayms(500);
        bit_turn(0,1);
        
		
        if(Time1out > 0)
        {
            Time1out = 0;
            Analyze_time1();
        }
        if(Time0Signal == 1)//һ��ʱ�䴦��һ�δ�����Ϣ
		{
			Time0Signal = 0;
			
		}   
        Feed_WatchDog();            //��λ���Ź�		
	}
    
    
}


