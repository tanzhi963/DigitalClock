/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include"watchdog.h"
	
/****************************************
*函数名称:WatchDogInit
*输    入:无
*输    出:无
*功    能:看门狗初始化
******************************************/
void Init_WatchDog(void)
{
	PROTECT_REG
	(	
	    /* 使能看门狗时钟 */	
		APBCLK |= WDT_CLKEN;		   
	
		/* 设置看门狗时钟源为10K */
		CLKSEL1 = (CLKSEL1 & (~WDT_CLK)) | WDT_10K;
					
		/* 使能看门狗定时器复位功能 */
		WTCR |= WTRE;	
	
		/* 设置看门狗超时间隔为1740.8ms */
		WTCR &= ~WTIS;
		WTCR |=  WTD_TIME;	// 6.6559s

	
		/* 使能看门狗中断 */			
		WTCR |= WTIE;
		NVIC_ISER |= WDT_INT;
	
		/* 使能看门狗 */
		WTCR |= WTE;
	
		/* 复位看门狗计数值 */
		WTCR |= CLRWTR;		
	)	
}

/****************************************
*函数名称:WDT_IRQHandler
*输    入:无
*输    出:无
*功    能:看门狗中断服务函数
******************************************/
void WDT_IRQHandler(void) 
{ 
	PROTECT_REG
	(
		WTCR |= WTWKF;
		WTCR |= WTIF;	
	)
}
/****************************************
*函数名称:WatchDogFeed
*输    入:无
*输    出:无
*功    能:喂狗
******************************************/
void Feed_WatchDog(void)
{
	PROTECT_REG
	(	 
		WTCR |= CLRWTR;		
	)	
}
