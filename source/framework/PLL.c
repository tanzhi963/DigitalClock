/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "PLL.h"


/****************************************
*函数名称:Init_Clock
*输    入:无
*输    出:无
*功    能:时钟初始化
******************************************/
void Init_Clock(void)
{ 	
	 PROTECT_REG											//ISP下载时保护FLASH存储器
	 (  						                   
			PWRCON |= OSC22M_EN;//默认时钟源为内部晶振
			while((CLKSTATUS & OSC22M_STB) == 0); 		//等待22MHz时钟稳定	
		  
			PWRCON |= OSC10K_EN;		// 使能内部10K时钟 
			while((CLKSTATUS & OSC10K_STB) == 0); // 等待10K时钟稳定 
			
			CLKSEL0 = (CLKSEL0 & (~HCLK)) | HCLK_22M;	//设置内部晶振为系统时钟 
	 ) 
}


