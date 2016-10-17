/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "ADC.h"

#define DEBUGMSG              printf
#define ADC_CLOCK_DIVIDER     0x00040000
#define ADC_CLK_Source        0x00000008
#define AREF_VOLTAGE          5000




void Init_ADC(void)
{
//     if(ADC_CLK_Source==0x00000004)
//     {
//         PLLCON |= PLL_SEL;
//         PLL_Enable();

// 		while((CLKSTATUS & PLL_STB) == 0);        //等待PLL稳定
// 	} 
//    
//     set_ADC_RST;                                  //复位ADC
//     clr_ADC_RST;
//       
//     set_ADEN_CLK;                                 //ADC时钟使能
//     if (ADC_CLK_Source==0x00000000 )
//     {
//         ADCClkSource_ex12MHZ;                     //使能为外部12MHz时钟
//     }
//     else if(ADC_CLK_Source==0x00000004 )
//     {
//         ADCClkSource_PLL;                          //使能为锁相环时钟
//     }
//     else if(ADC_CLK_Source==0x00000008 )
//     {
//         ADCClkSource_int22MHZ;                     //使能为内部22MHz时钟
//     }

//     CLKDIV=ADC_CLOCK_DIVIDER;                      //设置ADC分频器
// 	 
//     set_ADEN;                                       //ADC使能
//     set_CALEN;			                            //开始ADC自校准

// 	while(!(ADCALR&CALDONE));                       //等待自校准完成

//     setAD_SIG;                                      //单次转换模式         
//     clr_DIFFEN;                                     //差分输入模式

//     set_CHEN0;                                      //设置ADC通道0
//     set_ADC0_channel;                               //使能P1.0为模拟输入引脚
// 	P1_OFFD |= OFFD0;                               //禁止P1.0数字输入通道
//     P10_InputOnly;                                  //设置P1.0引脚为输入模式Configure P1.0 as input mode
//     set_ADF;  		                                //清除ADC中断标志位  
//     
    
/*   set_ADEN_CLK;                                   // ADC block reset
    clr_ADEN_CLK;                                    // ADC block normal operation
    set_ADEN_CLK;
    
    
    
    ADCR &= ~DIFFEN;                                 //关闭差分输入模式，单输入模式
    ADCR &= ~TRGE_EN;                                //关闭外部触发
    ADCR |= MD_CON_SCN;                              //采集模式是连续采集模式
    ADCR |= ADIE;                                    //中断使能
    ADCR |= ADEN;                                    //打开ADC模块（转换使能）*/

	IPRSTC2 |= ADC_RST;                        		//复位ADC外设
	IPRSTC2 &= ~ADC_RST;                        	//ADC模块从复位状态恢复到正常工作状态
	APBCLK  |= ADC_CLKEN;                        	//使能ADC时钟
	CLKSEL1  = CLKSEL1 & (~ADC_CLK) | ADC_22M;  	//选择內部晶振作为ADC时钟源
	CLKDIV  |= 0x000f0000;                       	//ADC时钟16分频
	ADCR    |= ADEN;                             	//使能ADC
	ADCALR |= CALEN;                             	//使能ADC自校验功能
	while(!(ADCALR & CALDONE));                  	//等待校验完成
  
	setAD_CONSCAN;					//设置ADC连续转换        
	clr_DIFFEN;							//设定AD模拟电压输入模式为单端输入
	set_CHEN0; 							//设置ADC通道为通道5 
	set_ADC0_channel;				//使能P1.5为模拟输入引脚 
	P1_OFFD |= OFFD0;				//禁止P1.5数字输入通道
	P10_InputOnly; 					//设置P1.5引脚为输入模式
	
	ADSR |= ADF;   					//清除ADC中断标志位 

}

/*void enable_ADchannel(uchar ch)
{
    ADCHER |= CH7_VBGI;
    ADCHER |= (1<<ch);
}*/


uint start_ADC(void)
{

    uint unVoltageValue;
    
    set_ADST;  							        	  //启动ADC
    while(ADSR&ADF==0);					        	  //等待ADC结束
    set_ADF;							        	  //清空ADC结束标志位

    unVoltageValue = AREF_VOLTAGE*(ADDR0&0xFFF)/4096; //将ADC值转换为电压值
    
    return unVoltageValue;
}



