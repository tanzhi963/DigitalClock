/****************************************************************************
**
** Copyright (C) 2010-2015 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include"uart.h"
/****************************************
*��������:Uart0Init
*��    ��:Fosc 	 ʱ��Ƶ��
          Baud	 ���ڲ�����
*��    ��:��
*��    ��:����0��������
******************************************/
#define Fosc 22000000 
volatile int16_t rx0end;
volatile int16_t rx1end;

VOID Init_Uart0(UINT32 Baud)
{	 	
    P3_MFP &= ~(P31_TXD0 | P30_RXD0);   
    P3_MFP |= (TXD0 | RXD0);    //P3.0 ʹ��Ϊ����0����
																//P3.1 ʹ��Ϊ����0����
    UART0_Clock_EN;         //����0ʱ��ʹ��
    UARTClkSource_int22MHZ;//����ʱ��ѡ���ڲ�22M
	  CLKDIV &= ~(15<<8); 	//����ʱ�ӷ�ƵΪ0

    IPRSTC2 |= UART0_RST;   //��λ����0
    IPRSTC2 &= ~UART0_RST;  //��λ����
    UA0_FCR |= TX_RST;      //����FIFO��λ
    UA0_FCR |= RX_RST;      //����FIFO��λ

    UA0_LCR &= ~PBE;     	//У��λ����ȡ��
		UA0_LCR &= ~WLS;
    UA0_LCR |= WL_8BIT;     //8λ����λ
    UA0_LCR &= NSB_ONE;     //1λֹͣλ

    UA0_BAUD |= DIV_X_EN|DIV_X_ONE;   //���ò����ʷ�Ƶ 
    UA0_BAUD |= ((Fosc / Baud) -2);	//����������  UART_CLK/(A+2) = 115200, UART_CLK=12MHz
  	
		UA0_IER	|= RDA_IEN;					//���������ж�ʹ��
		NVIC_ISER |= UART0_INT;	 			//ʹ�ܴ���0�ж� 

		rx0end = 0;
//		EN485 = 0;
}

/****************************************
*��������:Uart1Init
*��    ��:Fosc 	 ʱ��Ƶ��
          Baud	 ���ڲ�����
*��    ��:��
*��    ��:����1��������
******************************************/
VOID Init_Uart1(UINT32 Baud)
{		 
    P1_MFP &= ~(P13_AIN3_TXD1 | P12_AIN2_RXD1);   
    P1_MFP |= (TXD1 | RXD1);    	//P1.2 ʹ��Ϊ����1���� P1.3 ʹ��Ϊ����1����

    UART1_Clock_EN;         //����1ʱ��ʹ��
		UARTClkSource_int22MHZ;//����ʱ��ѡ���ڲ�22M
		CLKDIV &= ~(15<<8); 		//����ʱ�ӷ�ƵΪ1 
	
    IPRSTC2 |= UART1_RST;   //��λ����1
    IPRSTC2 &= ~UART1_RST;  //��λ����
    UA1_FCR |= TX_RST;      //����FIFO��λ
    UA1_FCR |= RX_RST;      //����FIFO��λ 
	
    UA1_LCR &= ~PBE;     		//У��λ����ȡ��
		UA1_LCR &= ~WLS;
    UA1_LCR |= WL_8BIT;     //8λ����λ
    UA1_LCR &= NSB_ONE;     //1λֹͣλ 
	
    UA1_BAUD |= DIV_X_EN|DIV_X_ONE;   //���ò����ʷ�Ƶ
    UA1_BAUD |= ((Fosc /  Baud) -2);	//����������  UART_CLK/(A+2) = 115200, UART_CLK=12MHz
		
		UA1_IER	|= RDA_IEN;					//���������ж�ʹ��
		NVIC_ISER |= UART1_INT;	 		//ʹ�ܴ���1�ж� 
    
		rx1end = 0;
}
/****************************************
*��������:Uart0Send
*��    ��:pBuf 			 			�������ݻ�����
          Num	 	�����ֽ�����
*��    ��:��
*��    ��:����0��������
******************************************/
 VOID Uart0Send(UINT8 *pBuf,UINT32 Num)
{
	UINT32 i; 
	for(i=0; i<Num; i++)
	{
		UA0_THR = *(pBuf+i);
		while ((UA0_FSR&TX_EMPTY) == 0x00); //��鷢��FIFO�Ƿ�Ϊ��	 
	} 
}
/****************************************
*��������:Uart1Send
*��    ��:pBuf 			 			�������ݻ�����
          unNumOfBytes	 	�����ֽ�����
*��    ��:��
*��    ��:����0��������
******************************************/
VOID Uart1Send(UINT8 *pBuf,UINT32 Num)
{
	UINT32 i; 
	for(i=0; i<Num; i++)
	{
		UA1_THR = *(pBuf+i); 
		while ((UA1_FSR&TX_EMPTY) == 0x00); //��鷢��FIFO�Ƿ�Ϊ��	 
		
	} 
}


// /****************************************
// *��������:UART0_IRQHandler
// *��    ��:��
// *��    ��:��
// *��    ��:����0�жϷ�����
// ******************************************/
// VOID UART0_IRQHandler(VOID)
// {
//   UINT8 Data; 
// 	if(UA0_ISR & RDA_INT)				 //����Ƿ���������ж�
// 	{	
// 		while(UA0_ISR & RDA_IF) 		 //��ȡ���н��յ�������
// 		{ 
// 			Data = UA0_RBR;			 //��ȡ����	
// 				Uart1Send(&Data,1);			
// 			if(Rx0data.num!= QUEUEMAXSIZE)
// 			{
// 				Rx0data.rear = (Rx0data.rear+1)%QUEUEMAXSIZE;
// 				Rx0data.data[Rx0data.rear] = Data;
// 			}
// 		}
// 		Rx0data.num = (Rx0data.rear + (QUEUEMAXSIZE - Rx0data.front))%QUEUEMAXSIZE;//����Rx0data.num
// 	} 
// }

// /****************************************
// *��������:UART1_IRQHandler
// *��    ��:��
// *��    ��:��
// *��    ��:����1�жϷ�����
// ******************************************/
// VOID UART1_IRQHandler(VOID)
// {
//   UINT8 Data;
// 	if(UA1_ISR & RDA_INT)				 //����Ƿ���������ж�
// 	{	
// 		while(UA1_ISR & RDA_IF) 		 //��ȡ���н��յ�������
// 		{ 
// 			Data = UA1_RBR;			 //��ȡ����	 
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
// 	  Rx1data.num = (Rx1data.rear + (QUEUEMAXSIZE - Rx1data.front))%QUEUEMAXSIZE;//����Rx1data.num
// 	} 
// }
