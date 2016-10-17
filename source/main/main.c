/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "main.h"




void SystemInit(void)
{
    Init_Clock();                   //初始化系统时钟
	Init_WatchDog();                //初始化看门狗
	Init_GPIO();                    //初始化GPIO
	Init_Uart0(57600);				//串口0初始化 
	Init_TMR0();                    //初始化计时器0
    Init_TMR1();                    //初始化计时器1
    Init_TMR2();                    //初始化定时器2
	Init_Dataprocess();	            //初始化数据处理 

}


/****************************************
*函数名称:main
*输    入:无
*输    出:无
*功    能:函数主体
******************************************/
INT32 main(VOID)
{
    
	SystemInit();          //全局初始化函数
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
        if(Time0Signal == 1)//一段时间处理一次触发信息
		{
			Time0Signal = 0;
			
		}   
        Feed_WatchDog();            //复位看门狗		
	}
    
    
}


