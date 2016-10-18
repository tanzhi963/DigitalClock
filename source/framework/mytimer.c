/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "mytimer.h"

UINT16 Time0out;
UINT16 Time1out;
UINT16 Time2out;

/****************************************
*函数名称:TMR0Init
*输    入:无
*输    出:无
*功    能:定时器0初始化
******************************************/
void Init_TMR0(void)
{
    PROTECT_REG
	(
	  APBCLK |= TMR0_CLKEN;		//使能TMR0时钟源 
		CLKSEL1 = (CLKSEL1 & (~TM0_CLK)) | TM0_22M;// 选择TMR0时钟源为内部22MHz

		//复位TMR0
		IPRSTC2 |=  TMR0_RST;
		IPRSTC2 &= ~TMR0_RST;
	
		//选择TMR1的工作模式为周期模式	
		TCSR0 &= ~TMR_MODE;
		TCSR0 |=  MODE_PERIOD;		
		
		/* 溢出周期 = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
		TCSR0  = TCSR0 & 0xFFFFFF00;		// 设置预分频值 [0~255] 

		TCSR0 |= TMR_IE;					//使能TMR0中断
		NVIC_ISER |= TMR0_INT;	 
	)
}
/****************************************
*函数名称:TMR1Init
*输    入:无
*输    出:无
*功    能:定时器1初始化
******************************************/
void Init_TMR1(void)
{
    PROTECT_REG
	(
	  APBCLK |= TMR1_CLKEN;		//使能TMR1时钟源 
		CLKSEL1 = (CLKSEL1 & (~TM1_CLK)) | TM1_22M;// 选择TMR1时钟源为内部22MHz

		//复位TMR1
		IPRSTC2 |=  TMR1_RST;
		IPRSTC2 &= ~TMR1_RST;
	
		//选择TMR1的工作模式为周期模式	
		TCSR1 &= ~TMR_MODE;
		TCSR1 |=  MODE_PERIOD;		
		
		/* 溢出周期 = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
		TCSR1  = TCSR1 & 0xFFFFFF00;		// 设置预分频值 [0~255] 

		TCSR1 |= TMR_IE;					//使能TMR1中断
		NVIC_ISER |= TMR1_INT;	 
	)
}

/****************************************
*函数名称:Init_TMR2
*输    入:无
*输    出:无
*功    能:定时器2初始化
******************************************/
void Init_TMR2(void)
{
    PROTECT_REG
	(
        APBCLK |= TMR2_CLKEN;		//使能TMR2时钟源 
        CLKSEL1 = (CLKSEL1 & (~TM2_CLK)) | TM2_22M;// 选择TMR2时钟源为内部22MHz

        //复位TMR2
        IPRSTC2 |=  TMR2_RST;
        IPRSTC2 &= ~TMR2_RST;

        //选择TMR2的工作模式为周期模式	
        TCSR2 &= ~TMR_MODE;
        TCSR2 |=  MODE_PERIOD;

        /* 溢出周期 = (Period of timer clock input) * (8-bit Prescale + 1) * (24-bit TCMP)*/
        TCSR2  = TCSR2 & 0xFFFFFF00;		// 设置预分频值 [0~255] 

        TCSR2 |= TMR_IE; //使能TMR2中断
        NVIC_ISER |= TMR2_INT;	 
	)
}
/****************************************
*函数名称:StarTime0
*输    入:time  定时时间  单位毫秒
*输    出:无
*功    能:启动定时器0
******************************************/
void StarTime0(UINT16 time)
{
	Time0out = 0; 
	TCMPR0 = 22*time;		// 设置比较值 [0~16777215]
	TCSR0 |= CRST;					//复位TMR0计数器				
	TCSR0 |= CEN;						//使能TMR0  
}

/****************************************
*函数名称:StarTime1
*输    入:time  定时时间  单位毫秒
*输    出:无
*功    能:启动定时器1
******************************************/
void StarTime1(UINT16 time)
{
	Time1out = 0; 
	TCMPR1 = 22*time;		// 设置比较值 [0~16777215]
	TCSR1 |= CRST;					//复位TMR1计数器				
	TCSR1 |= CEN;						//使能TMR1
}


/****************************************
*函数名称:StarTime2
*输    入:time  定时时间
*输    出:无
*功    能:启动定时器2  10us计数
******************************************/
void StarTime2(UINT16 time)
{
	Time2out = 0; 
	TCMPR2 = 22*time;		// 设置比较值 [0~16777215]  
	TCSR2 |= CRST;					//复位TMR2计数器				
	TCSR2 |= CEN;						//使能TMR2  
}
/****************************************
*函数名称:StopTime0
*输    入:无
*输    出:无
*功    能:关闭定时器0
******************************************/
void StopTime0(void)
{
	TCSR0 |= CRST;		//复位TMR0计数器				
	TCSR0 &= ~CEN;		//关闭TMR0 
	Time0out = 0;
} 

/****************************************
*函数名称:StopTime1
*输    入:无
*输    出:无
*功    能:关闭定时器1
******************************************/
void StopTime1(void)
{
	TCSR1 |= CRST;		//复位TMR1计数器				
	TCSR1 &= ~CEN;		//关闭TMR1 
	Time1out = 0;
}  

/****************************************
*函数名称:StopTime2
*输    入:无
*输    出:无
*功    能:关闭定时器2
******************************************/
void StopTime2(void)
{
    TCSR2 |= CRST;		//复位TMR2计数器				
    TCSR2 &= ~CEN;		//关闭TMR2 
    Time2out = 0;
} 

/****************************************
*函数名称:Delayms
*输    入:无
*输    出:无
*功    能:系统时钟微秒延时
******************************************/ 
void Delayus(uint32_t unCnt)
{
    SYST_RVR = unCnt*22;
    SYST_CVR = 0;
    SYST_CSR |=1UL<<0;

    while((SYST_CSR & 1UL<<16)==0); 
}

 
/****************************************
*函数名称:Delayms
*输    入:无
*输    出:无
*功    能:系统时钟毫秒延时
******************************************/ 
void Delayms(uint32_t DelayTime)
{
 
    SYST_RVR = DelayTime*22000;
    SYST_CVR = 0;
    SYST_CSR |=1UL<<0;
  
    while((SYST_CSR & 1UL<<16)==0);  
}


/****************************************
*函数名称:TMR0_IRQHandler
*输    入:无
*输    出:无
*功    能:定时器0中断服务函数
******************************************/
VOID TMR0_IRQHandler(VOID)
{
	//清除TMR0中断标志位
	TISR0 |= TMR_TIF; 
	Time0out++;
}
 
/****************************************
*函数名称:TMR1_IRQHandler
*输    入:无
*输    出:无
*功    能:定时器1中断服务函数
******************************************/  
VOID TMR1_IRQHandler(VOID)
{
	//清除TMR1中断标志位
	TISR1 |= TMR_TIF; 
    Time1out++;
}

/****************************************
*函数名称:TMR2_IRQHandler
*输    入:无
*输    出:无
*功    能:定时器2中断服务函数
******************************************/ 

VOID TMR2_IRQHandler(VOID)
{
	//清除TMR2中断标志位
	TISR2 |= TMR_TIF;  
    Time2out++;
}

