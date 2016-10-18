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
	
	uint a=0;
    
	SystemInit();          //全局初始化函数
	printf("hello\r\n");
	
	StarTime0(50000);
	LED_reflash(a);
	while(1)
    {
        
		LED_show();
        
        if(Time0out > 0)
        {
            Time0out = 0;
			a++;
			LED_reflash(a);
        }
		
        if(Time1out > 0)
        {
            Time1out = 0;
        }
		
        Feed_WatchDog();            //复位看门狗		
	}
    
    
}


