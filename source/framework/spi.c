/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include "spi.h"
/****************************************
*函数名称:Spi1MasterInit
*输    入:无
*输    出:无
*功    能:SPI1初始化为主机模式
******************************************/
VOID Init_SPI1(VOID)
{ 
PROTECT_REG	//ISP下载时保护FLASH存储器
( 	
	//使能SPI1相关引脚                                    
	P0_MFP &= ~(P05_AD5_SPI1MOSI | P06_AD6_SPI1MISO | P07_AD7_SPI1CLK) ;  
	P0_MFP |= (SPI1MOSI | SPI1MISO | SPI1CLK) ;
	
	APBCLK |= SPI1_CLKEN;  //SPI1时钟使能
 
	SPI1_SSR &= ~LVL_H; 					//从机选择选择信号通过低电平激活 
	SPI1_CNTRL &= ~LSB_FIRST; 		//优先发送/接收最高有效位
	SPI1_CNTRL &= ~CLKP_IDLE_H;  	//SCLK空闲时为低电平
	SPI1_CNTRL |= TX_NEG_F;     	//SDO 信号在SPICLK的下降沿改变
	SPI1_CNTRL &= ~RX_NEG_F;    	//SDI 信号在SPICLK上升沿锁存

 
	CLKDIV &= 0xFFFFFFF0;               //HCLK_N = 0, Pclk = SYSclk/(HCLK_N+1)
	SPI1_DIVIDER &= 0xFFFF0000;         //SPIclk = Pclk/((DIVIDER+1)*2)
	SPI1_DIVIDER |= 0x00000001;
  
	SPI1_CNTRL &= ~SPI_MODE_SLAVE;    //SPI1工作在主机模式
//SPI1_SSR |= ASS_AUTO;   					//使能自动从机选择
	SPI1_SSR   &= ~ASS_AUTO;       	  //Slave Select non-auto
) 
}
/****************************************
*函数名称:Spi1Length
*输    入:len数据长度
*输    出:无
*功    能:设置SPI1数据长度
******************************************/
VOID SPI1Length(UINT8 len) 
{
    if(len <= 0x20)
    {
        if((len & 0x01) == 0)
            SPI1_CNTRL &= ~(1<<3);
        else
            SPI1_CNTRL |= (1<<3);
        if((len & 0x02) == 0)
            SPI1_CNTRL &= ~(1<<4);
        else
            SPI1_CNTRL |= (1<<4);

        if((len & 0x04) == 0)
            SPI1_CNTRL &= ~(1<<5);
        else
            SPI1_CNTRL |= (1<<5);

        if((len & 0x08) == 0)
            SPI1_CNTRL &= ~(1<<6);
        else
            SPI1_CNTRL |= (1<<6);

        if((len & 0x10) == 0)
            SPI1_CNTRL &= ~(1<<7);
        else
            SPI1_CNTRL |= (1<<7);
    } 
}
/****************************************
*函数名称: 
*输    入: 
*输    出:无
*功    能: SPI单字节写入函数
******************************************/
VOID SPI_Write(UINT8 data)
{ 
	SPI1_SSR |= SSR_ACT;

	SPI1_CNTRL &= TX_NUM_ONE;  

    SPI1Length(0x08);

	SPI1_TX0 = data;

	SPI1_CNTRL |= GO_BUSY;      

	while((SPI1_CNTRL & GO_BUSY)!=0);

	SPI1_SSR &= ~SSR_ACT;
	 
}
/****************************************
*函数名称: 
*输    入: 
*输    出:无
*功    能:  SPI单字节读取函数
******************************************/
UINT8 SPI_Read(VOID)
{	 
	
	SPI1_SSR |= SSR_ACT;

	SPI1_CNTRL &= TX_NUM_ONE;   

	SPI1Length(0x08);

	SPI1_TX0 = 0xFF;

	SPI1_CNTRL |= GO_BUSY;      

	while((SPI1_CNTRL & GO_BUSY)!=0);

	SPI1_SSR &= ~SSR_ACT;
	
	return (UINT8)SPI1_RX0;
	
}
