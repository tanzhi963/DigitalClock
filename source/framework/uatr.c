/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include"uart.h"
/****************************************
*函数名称:Uart0Init
*输    入:Fosc 	 时钟频率
          Baud	 出口波特率
*输    出:无
*功    能:串口0发送数据
******************************************/
#define Fosc 22000000 
volatile int16_t rx0end;
volatile int16_t rx1end;

VOID Init_Uart0(UINT32 Baud)
{	 	
    P3_MFP &= ~(P31_TXD0 | P30_RXD0);   
    P3_MFP |= (TXD0 | RXD0);    //P3.0 使能为串口0接收
																//P3.1 使能为串口0发送
    UART0_Clock_EN;         //串口0时钟使能
    UARTClkSource_int22MHZ;//串口时钟选择内部22M
	  CLKDIV &= ~(15<<8); 	//串口时钟分频为0

    IPRSTC2 |= UART0_RST;   //复位串口0
    IPRSTC2 &= ~UART0_RST;  //复位结束
    UA0_FCR |= TX_RST;      //发送FIFO复位
    UA0_FCR |= RX_RST;      //接收FIFO复位

    UA0_LCR &= ~PBE;     	//校验位功能取消
		UA0_LCR &= ~WLS;
    UA0_LCR |= WL_8BIT;     //8位数据位
    UA0_LCR &= NSB_ONE;     //1位停止位

    UA0_BAUD |= DIV_X_EN|DIV_X_ONE;   //设置波特率分频 
    UA0_BAUD |= ((Fosc / Baud) -2);	//波特率设置  UART_CLK/(A+2) = 115200, UART_CLK=12MHz
  	
		UA0_IER	|= RDA_IEN;					//接收数据中断使能
		NVIC_ISER |= UART0_INT;	 			//使能串口0中断 

		rx0end = 0;
//		EN485 = 0;
}

/****************************************
*函数名称:Uart1Init
*输    入:Fosc 	 时钟频率
          Baud	 出口波特率
*输    出:无
*功    能:串口1发送数据
******************************************/
VOID Init_Uart1(UINT32 Baud)
{		 
    P1_MFP &= ~(P13_AIN3_TXD1 | P12_AIN2_RXD1);   
    P1_MFP |= (TXD1 | RXD1);    	//P1.2 使能为串口1接收 P1.3 使能为串口1发送

    UART1_Clock_EN;         //串口1时钟使能
		UARTClkSource_int22MHZ;//串口时钟选择内部22M
		CLKDIV &= ~(15<<8); 		//串口时钟分频为1 
	
    IPRSTC2 |= UART1_RST;   //复位串口1
    IPRSTC2 &= ~UART1_RST;  //复位结束
    UA1_FCR |= TX_RST;      //发送FIFO复位
    UA1_FCR |= RX_RST;      //接收FIFO复位 
	
    UA1_LCR &= ~PBE;     		//校验位功能取消
		UA1_LCR &= ~WLS;
    UA1_LCR |= WL_8BIT;     //8位数据位
    UA1_LCR &= NSB_ONE;     //1位停止位 
	
    UA1_BAUD |= DIV_X_EN|DIV_X_ONE;   //设置波特率分频
    UA1_BAUD |= ((Fosc /  Baud) -2);	//波特率设置  UART_CLK/(A+2) = 115200, UART_CLK=12MHz
		
		UA1_IER	|= RDA_IEN;					//接收数据中断使能
		NVIC_ISER |= UART1_INT;	 		//使能串口1中断 
    
		rx1end = 0;
}
/****************************************
*函数名称:Uart0Send
*输    入:pBuf 			 			发送数据缓冲区
          Num	 	发送字节总数
*输    出:无
*功    能:串口0发送数据
******************************************/
 VOID Uart0Send(UINT8 *pBuf,UINT32 Num)
{
	UINT32 i; 
	for(i=0; i<Num; i++)
	{
		UA0_THR = *(pBuf+i);
		while ((UA0_FSR&TX_EMPTY) == 0x00); //检查发送FIFO是否为空	 
	} 
}
/****************************************
*函数名称:Uart1Send
*输    入:pBuf 			 			发送数据缓冲区
          unNumOfBytes	 	发送字节总数
*输    出:无
*功    能:串口0发送数据
******************************************/
VOID Uart1Send(UINT8 *pBuf,UINT32 Num)
{
	UINT32 i; 
	for(i=0; i<Num; i++)
	{
		UA1_THR = *(pBuf+i); 
		while ((UA1_FSR&TX_EMPTY) == 0x00); //检查发送FIFO是否为空	 
		
	} 
}


// /****************************************
// *函数名称:UART0_IRQHandler
// *输    入:无
// *输    出:无
// *功    能:串口0中断服务函数
// ******************************************/
// VOID UART0_IRQHandler(VOID)
// {
//   UINT8 Data; 
// 	if(UA0_ISR & RDA_INT)				 //检查是否接收数据中断
// 	{	
// 		while(UA0_ISR & RDA_IF) 		 //获取所有接收到的数据
// 		{ 
// 			Data = UA0_RBR;			 //读取数据	
// 				Uart1Send(&Data,1);			
// 			if(Rx0data.num!= QUEUEMAXSIZE)
// 			{
// 				Rx0data.rear = (Rx0data.rear+1)%QUEUEMAXSIZE;
// 				Rx0data.data[Rx0data.rear] = Data;
// 			}
// 		}
// 		Rx0data.num = (Rx0data.rear + (QUEUEMAXSIZE - Rx0data.front))%QUEUEMAXSIZE;//更新Rx0data.num
// 	} 
// }

// /****************************************
// *函数名称:UART1_IRQHandler
// *输    入:无
// *输    出:无
// *功    能:串口1中断服务函数
// ******************************************/
// VOID UART1_IRQHandler(VOID)
// {
//   UINT8 Data;
// 	if(UA1_ISR & RDA_INT)				 //检查是否接收数据中断
// 	{	
// 		while(UA1_ISR & RDA_IF) 		 //获取所有接收到的数据
// 		{ 
// 			Data = UA1_RBR;			 //读取数据	 
// 			if(Rx1data.num!= QUEUEMAXSIZE)
// 			{
// 				Rx1data.rear = (Rx1data.rear+1)%QUEUEMAXSIZE;
// 				Rx1data.data[Rx1data.rear] = Data;
// 			} 
// 		
// 			if(Data == PCEND)
// 			{
// 				rx1end ++;
// 			}
// 		}
// 	  Rx1data.num = (Rx1data.rear + (QUEUEMAXSIZE - Rx1data.front))%QUEUEMAXSIZE;//更新Rx1data.num
// 	} 
// }
