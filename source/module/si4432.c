/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include "si4432.h"  


volatile UINT8 rfend;  
volatile UINT8 rxflag;   
/****************************************
*��������:RF4432_ReadReg
*��    ��:reg �Ĵ�����ַ
*��    ��:��
*��    ��:RF4432�Ĵ�����ȡһ���ֽ�����
******************************************/
VOID RF4432_ReadReg(UINT8 addr,UINT8 *Reg)
{ 
	RF4432_SEL=0; 
	SPI_Write(addr|0x00);     // ���Ͷ��Ĵ�������
	*Reg = SPI_Read();        // ���ض�ȡ������ 
	RF4432_SEL=1; 
}

/****************************************
*��������:RF4432_WriteReg
*��    ��: addr  �Ĵ�����ַ
 *         value  д��ֵ
*��    ��:��
*��    ��:RF4432�Ĵ���д��һ���ֽ�����
******************************************/ 
VOID RF4432_WriteReg(UINT8 addr,UINT8 value)
{    
	RF4432_SEL=0;   
	SPI_Write(addr|0x80);  	// ����д�Ĵ�������   
	SPI_Write(value);      	// д����       
	RF4432_SEL=1; 
}  
/****************************************
*��������:RF4432_SetRxMode
*��    ��:
*��    ��:��
*��    ��:RF4432���ý���ģʽ
******************************************/  
VOID RF4432_SetRxMode(VOID)
{
	UINT8 RegisterData;
	//enable receiver chain        
	RF4432_WriteReg(0x07, 0x05);
	//enable the packet valid interrupt
	RF4432_WriteReg(0x05, 0x03); 
	RF4432_WriteReg(0x06, 0x00);        
	RF4432_ReadReg(0x03, &RegisterData);
	RF4432_ReadReg(0x04, &RegisterData);
	rxflag = 1;
}
/****************************************
*��������:RF4432_RxPacket
*��    ��:
*��    ��:��
*��    ��:RF4432�������ģʽ
******************************************/ 
VOID RFIdle(VOID)
{
	UINT8 RegisterData;                                        
	RF4432_WriteReg(0x07, 0x01);
	//diasble all ITs
	RF4432_WriteReg(0x05, 0x00);
	RF4432_WriteReg(0x06, 0x00);        
	RF4432_ReadReg(0x03, &RegisterData);
	RF4432_ReadReg(0x04, &RegisterData);        
}
/****************************************
*��������:RF4432_Tx
*��    ��:
*��    ��:��
*��    ��:RF4432��������
******************************************/
VOID RF4432_Tx(UINT8 *packet,UINT8 length)
{
	UINT8 temp;
	UINT8 RegisterData;    
	rxflag = 0;                                             
	RF4432_WriteReg(0x3e, length);//д�������                                     
	for(temp=0;temp<length;temp++)
	{
		RF4432_WriteReg(0x7f,packet[temp]);                
	}                                                                                         
	//enable the wanted ITs
	RF4432_WriteReg(0x05, 0x04);
	RF4432_WriteReg(0x06, 0x00);        
	RF4432_ReadReg(0x03, &RegisterData);
	RF4432_ReadReg(0x04, &RegisterData);
	//enable transmitter
	RF4432_WriteReg(0x07, 0x09);         
	while(RF4432_IRQ);                       
	RF4432_ReadReg(0x03, &RegisterData);
	RF4432_ReadReg(0x04, &RegisterData);  
	
	RF4432_SetRxMode();//RF4432���ý���ģʽ 
} 
/****************************************
*��������:Init_RF4432 
*��    ��:
*��    ��:��
*��    ��:RF4432��ƵоƬ��ʼ��
******************************************/  
UINT8 RF4432_CF_SET[11][3]={//Ƶ������
	//0x75,0x76,0x77  //�Ĵ�����ַ
	{0x53,0x4b,0x00 },	//433MHZ	//Ĭ��	
	{0x53,0x00,0x00 },	//430MHZ
 	{0x52,0xaf,0x00 },	//427MHZ
 	{0x53,0x96,0x00 },	//436MHZ
	{0x52,0x64,0x00 },	//424MHZ
	{0x53,0xe1,0x00 },	//439MHZ
 	{0x51,0xe1,0x00 },	//419MHZ 
	{0x52,0x19,0x00 },	//421MHZ 
	{0x53,0x4b,0x00 },	//433MHZ	 
 	{0x54,0x32,0x00 },	//442MHZ	
	{0x54,0x7d,0x00 },	//445MHZ			
}; 

UINT8 RF4432_RB_SET[9][20]= // //��������
{
//TDR1, TDR0, MMC1,       FDEV, 			IFBW, COSR, CRO2, CRO1, CRO0, CTG1, CTG0, AFC, 
//0x6E, 0x6F, 0x70, 0x58, 0x72, 0x71, 0x1C, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x1D, 0x1E, 0x2A, 0x1F, 0x69    //�Ĵ�����ַ
 {0x4E, 0xA5, 0x2C, 0x80, 0x48, 0x23, 0x1E, 0xD0, 0x00, 0x9D, 0x49, 0x00, 0x45, 0x3C, 0x02, 0xFF, 0X03, 0x60 }, //1 DR: 9.60kbps, 	DEV:+-45kHz, BBBW:112.8kHz
 {0x9D, 0x49, 0x2C, 0x80, 0x48, 0x23, 0xAB, 0x9C, 0x00, 0xD1, 0xB7, 0x00, 0xB5, 0x3C, 0x02, 0xFF, 0X03, 0x60 }, //2 DR: 19.2kbps, 	DEV:+-45kHz, BBBW: 41.7kHz
 {0x07, 0xAE, 0x0C, 0x80, 0x48, 0x23, 0xAC, 0x64, 0x01, 0x47, 0xAE, 0x01, 0xB7, 0x3C, 0x02, 0xFF, 0X03, 0x60 }, //3 DR: 30.0kbps, 	DEV:+-45kHz, BBBW:112.8kHz
 {0x09, 0xD5, 0x0C, 0x80, 0x48, 0x23, 0xAD, 0x4E, 0x01, 0xA3, 0x6E, 0x02, 0xCF, 0x3C, 0x02, 0xFF, 0X03, 0x60 }, //4 DR: 38.4kbps, 	DEV:+-45kHz, BBBW: 45.2kHz
 {0x0C, 0x4A, 0x0C, 0x80, 0x48, 0x23, 0x94, 0x7D, 0x01, 0x06, 0x25, 0x02, 0x31, 0x3C, 0x02, 0xFF, 0X03, 0x60 }, //5 DR: 48.0kbps, 	DEV:+-45kHz, BBBW: 45.2kHz
 {0x0E, 0xBF, 0x0C, 0x80, 0x48, 0x23, 0x95, 0x68, 0x01, 0x3A, 0x93, 0x03, 0x29, 0x3C, 0x02, 0xFF, 0X03, 0x60 }, //6 DR: 57.6kbps, 	DEV:+-45kHz, BBBW:112.8kHz
 {0x1D, 0x7E, 0x0C, 0xC0, 0x48, 0x23, 0x9A, 0x34, 0x02, 0x75, 0x25, 0x07, 0xFF, 0x3C, 0x02, 0xFF, 0X03, 0x60 },//7 DR:115.2kbps, 	DEV:+-45kHz, BBBW: 208 kHz
};

VOID Init_RF4432(UINT8 num)
{
	UINT8 RegisterData;
	UINT8 m = num;
	UINT8 n = 3;//436MHZ
	RF4432_EN = 0;
	
	Delayms(20);  
	
	//��0x03��0x04�ж�״̬�Ĵ��������������ַʱ���жϱ�־λ�����Զ����
	RF4432_ReadReg(0x03,&RegisterData);//��ȡ�ж�Status1�Ĵ���
	RF4432_ReadReg(0x04,&RegisterData);//��ȡ�ж�Status2�Ĵ���
	
	//�����λ���е��ڲ��Ĵ���
	RF4432_WriteReg(0x07, 0x80); 
	//�ȴ�оƬ�ж�
	
	while(RF4432_IRQ);
	RF4432_ReadReg(0x03, &RegisterData);
	RF4432_ReadReg(0x04, &RegisterData);
	
	while(RF4432_IRQ);
	RF4432_ReadReg(0x03, &RegisterData);
	RF4432_ReadReg(0x04, &RegisterData); 
/////////////////////////////////////////////////////////////////////////////
	
	//����ͨ��Ƶ�� 
	RF4432_WriteReg(0x75, RF4432_CF_SET[n][0]); 
	RF4432_WriteReg(0x76, RF4432_CF_SET[n][1]);
	RF4432_WriteReg(0x77, RF4432_CF_SET[n][2]); 
		//0x1c,0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x6E, 0x6F, 0x70, 0x72, 0x1D, 0x58 
	//���÷�������  9.6kbps
	RF4432_WriteReg(0x6E, RF4432_RB_SET[m][0]);		//TXDataRate 1 register
	RF4432_WriteReg(0x6F, RF4432_RB_SET[m][1]);		//TXDataRate 0 register
	RF4432_WriteReg(0x70, RF4432_RB_SET[m][2]);		//Modulation Mode Control 1 register
	RF4432_WriteReg(0x72, RF4432_RB_SET[m][4]);		//set the Tx deviation register (+-45kHz)


	//����	RX GFSK/FSK ������ WDS ָ��
	RF4432_WriteReg(0x1C,RF4432_RB_SET[m][ 6]);//IF�˲�������
	RF4432_WriteReg(0x20,RF4432_RB_SET[m][ 7]);//ʱ�ӻָ���������
	RF4432_WriteReg(0x21,RF4432_RB_SET[m][ 8]);//ʱ�ӻָ�ƫ��2
	RF4432_WriteReg(0x22,RF4432_RB_SET[m][ 9]);//ʱ�ӻָ�ƫ��1
	RF4432_WriteReg(0x23,RF4432_RB_SET[m][10]);//ʱ�ӻָ�ƫ��0
	RF4432_WriteReg(0x24,RF4432_RB_SET[m][11]);//ʱ�ӻָ���ʱѭ������1
	RF4432_WriteReg(0x25,RF4432_RB_SET[m][12]);//ʱ�ӻָ���ʱѭ������0
	RF4432_WriteReg(0x1D,RF4432_RB_SET[m][13]);//AFC Loop Gearshift Override register		
	RF4432_WriteReg(0x1E,RF4432_RB_SET[m][14]);//AFC Timing Control register		
	RF4432_WriteReg(0x2A,RF4432_RB_SET[m][15]);//AFC Limiter register
		
///////////////////////////////////////////////////////////////////////////// 
	
	//����ǰ���볤��Ϊ5�ֽ�
	RF4432_WriteReg(0x34, 0x0A); 
	RF4432_WriteReg(0x35, 0x2A); 
	
	//���ñ�ͷ�ֽ�;���ñ���������(�������Ч���صĳ��Ƚ������ݰ��İ������ֶ�);
	//��ͬ��������Ϊ�����ֽڳ�  ʹ��ͬ����3,ͬ����2
	RF4432_WriteReg(0x33, 0x02); 
	
	//��ͬ��������Ϊ0x2D 0xD4
	RF4432_WriteReg(0x36, 0x2D); //ͬ����3 ����Ϊ0x2D
	RF4432_WriteReg(0x37, 0xD4); //ͬ����2 ����Ϊ0xD4
	
	//ʹ�����ݰ���������CRC-16(IBM)���
	RF4432_WriteReg(0x30, 0x8D);
	//����֡ͷ����
	RF4432_WriteReg(0x32, 0x00 );
	//����FIFOģʽ��GFSK����
	RF4432_WriteReg(0x71, 0x63); 

	//����GPIO's
	RF4432_WriteReg(0x0B, 0x12); //����Ϊ����״̬
	RF4432_WriteReg(0x0C, 0x15); //����Ϊ����״̬
	
	//����30M�����𵴵���
	RF4432_WriteReg(0x09, 0xD7); 
	
	//����AGC 
	RF4432_WriteReg(0x69, 0x60); //ʹ���Զ����湦�� 0x40
	
	//����ͨ�Ź���
	RF4432_WriteReg(0x6D, 0x1E);//���ù���Ϊ20dbm
 
 
	//��λTx FIFO 
	RF4432_WriteReg(0x08, 0x01);
	RF4432_WriteReg(0x08, 0x00);

	//��λRx FIFO
	RF4432_WriteReg(0x08, 0x02);
	RF4432_WriteReg(0x08, 0x00);

	Init_Si4432IRQ(); 
}

/****************************************
*��������:Init_Si4432IRQ
*��    ��:��
*��    ��:��
*��    ��:���ݽ����жϳ�ʼ��
******************************************/
VOID Init_Si4432IRQ(VOID)
{
	PROTECT_REG								    //ISP����ʱ����FLASH�洢��
	(
		P3_MFP = (P3_MFP & (~P32_EINT0)) | EINT0;  //P3.2��������Ϊ�ⲿ�ж�
		DBNCECON &= ~ICLK_ON;
		DBNCECON &= DBCLK_HCLK;
		DBNCECON |= SMP_256CK;					   //���÷�������������ѡ��
		P3_DBEN |= DBEN2;						   //ʹ��P3.2����������	
		P3_IMD &= IMD2_EDG;				
		P3_IEN |= IF_EN2;						   //�����ⲿ�ж�0Ϊ�½��ش���
		NVIC_ISER |= EXT_INT0;
	) 
		rfend = 0;	
		rxflag = 1; 
}

/****************************************
*��������:EINT0_IRQHandler
*��    ��:��
*��    ��:��
*��    ��:���ݽ����жϷ�����
******************************************/ 
UINT8 sdata[30];//
VOID EINT0_IRQHandler(VOID)
{ 
	UINT8 i=0,len;
	UINT8 reg;
	P3_ISRC = P3_ISRC;//����ж�	 
	
//    bit_turn(0,1);
	if(rxflag == 0)
	{
		return;
	}
	RF4432_ReadReg(0x03,&reg); 
	if( (reg & 0x02) == 0x02 )//packet received
	{   
		RF4432_ReadReg(0x4b,&len);		 
		for(i=0;i<len;i++) 
		{
			RF4432_ReadReg(0x7f,&reg);
			Rfdata.rear = (Rfdata.rear+1)%QUEUEMAXSIZE;
			Rfdata.data[Rfdata.rear] = reg; 
			//sdata[i] = reg;	//
			if(reg == 0x8f)
			{
				rfend ++;
			}
		}
		Rfdata.num = (Rfdata.rear + (QUEUEMAXSIZE - Rfdata.front))%QUEUEMAXSIZE;//����Rfdata.num 
		//Uart1Send(sdata,len);//	
		RF4432_SetRxMode(); 

	}	   
}
