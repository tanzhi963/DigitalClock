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
*函数名称:RF4432_ReadReg
*输    入:reg 寄存器地址
*输    出:无
*功    能:RF4432寄存器读取一个字节数据
******************************************/
VOID RF4432_ReadReg(UINT8 addr,UINT8 *Reg)
{ 
	RF4432_SEL=0; 
	SPI_Write(addr|0x00);     // 发送读寄存器命令
	*Reg = SPI_Read();        // 返回读取的数据 
	RF4432_SEL=1; 
}

/****************************************
*函数名称:RF4432_WriteReg
*输    入: addr  寄存器地址
 *         value  写入值
*输    出:无
*功    能:RF4432寄存器写入一个字节数据
******************************************/ 
VOID RF4432_WriteReg(UINT8 addr,UINT8 value)
{    
	RF4432_SEL=0;   
	SPI_Write(addr|0x80);  	// 发送写寄存器命令   
	SPI_Write(value);      	// 写数据       
	RF4432_SEL=1; 
}  
/****************************************
*函数名称:RF4432_SetRxMode
*输    入:
*输    出:无
*功    能:RF4432设置接收模式
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
*函数名称:RF4432_RxPacket
*输    入:
*输    出:无
*功    能:RF4432进入空闲模式
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
*函数名称:RF4432_Tx
*输    入:
*输    出:无
*功    能:RF4432发送数据
******************************************/
VOID RF4432_Tx(UINT8 *packet,UINT8 length)
{
	UINT8 temp;
	UINT8 RegisterData;    
	rxflag = 0;                                             
	RF4432_WriteReg(0x3e, length);//写入包长度                                     
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
	
	RF4432_SetRxMode();//RF4432设置接收模式 
} 
/****************************************
*函数名称:Init_RF4432 
*输    入:
*输    出:无
*功    能:RF4432射频芯片初始化
******************************************/  
UINT8 RF4432_CF_SET[11][3]={//频段配置
	//0x75,0x76,0x77  //寄存器地址
	{0x53,0x4b,0x00 },	//433MHZ	//默认	
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

UINT8 RF4432_RB_SET[9][20]= // //速率配置
{
//TDR1, TDR0, MMC1,       FDEV, 			IFBW, COSR, CRO2, CRO1, CRO0, CTG1, CTG0, AFC, 
//0x6E, 0x6F, 0x70, 0x58, 0x72, 0x71, 0x1C, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x1D, 0x1E, 0x2A, 0x1F, 0x69    //寄存器地址
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
	
	//读0x03和0x04中断状态寄存器，当读这个地址时，中断标志位将被自动清除
	RF4432_ReadReg(0x03,&RegisterData);//读取中断Status1寄存器
	RF4432_ReadReg(0x04,&RegisterData);//读取中断Status2寄存器
	
	//软件复位所有的内部寄存器
	RF4432_WriteReg(0x07, 0x80); 
	//等待芯片中断
	
	while(RF4432_IRQ);
	RF4432_ReadReg(0x03, &RegisterData);
	RF4432_ReadReg(0x04, &RegisterData);
	
	while(RF4432_IRQ);
	RF4432_ReadReg(0x03, &RegisterData);
	RF4432_ReadReg(0x04, &RegisterData); 
/////////////////////////////////////////////////////////////////////////////
	
	//设置通信频率 
	RF4432_WriteReg(0x75, RF4432_CF_SET[n][0]); 
	RF4432_WriteReg(0x76, RF4432_CF_SET[n][1]);
	RF4432_WriteReg(0x77, RF4432_CF_SET[n][2]); 
		//0x1c,0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x6E, 0x6F, 0x70, 0x72, 0x1D, 0x58 
	//设置发射速率  9.6kbps
	RF4432_WriteReg(0x6E, RF4432_RB_SET[m][0]);		//TXDataRate 1 register
	RF4432_WriteReg(0x6F, RF4432_RB_SET[m][1]);		//TXDataRate 0 register
	RF4432_WriteReg(0x70, RF4432_RB_SET[m][2]);		//Modulation Mode Control 1 register
	RF4432_WriteReg(0x72, RF4432_RB_SET[m][4]);		//set the Tx deviation register (+-45kHz)


	//设置	RX GFSK/FSK 调制器 WDS 指令
	RF4432_WriteReg(0x1C,RF4432_RB_SET[m][ 6]);//IF滤波器带宽
	RF4432_WriteReg(0x20,RF4432_RB_SET[m][ 7]);//时钟恢复过抽样率
	RF4432_WriteReg(0x21,RF4432_RB_SET[m][ 8]);//时钟恢复偏差2
	RF4432_WriteReg(0x22,RF4432_RB_SET[m][ 9]);//时钟恢复偏差1
	RF4432_WriteReg(0x23,RF4432_RB_SET[m][10]);//时钟恢复偏差0
	RF4432_WriteReg(0x24,RF4432_RB_SET[m][11]);//时钟恢复定时循环增益1
	RF4432_WriteReg(0x25,RF4432_RB_SET[m][12]);//时钟恢复定时循环增益0
	RF4432_WriteReg(0x1D,RF4432_RB_SET[m][13]);//AFC Loop Gearshift Override register		
	RF4432_WriteReg(0x1E,RF4432_RB_SET[m][14]);//AFC Timing Control register		
	RF4432_WriteReg(0x2A,RF4432_RB_SET[m][15]);//AFC Limiter register
		
///////////////////////////////////////////////////////////////////////////// 
	
	//设置前导码长度为5字节
	RF4432_WriteReg(0x34, 0x0A); 
	RF4432_WriteReg(0x35, 0x2A); 
	
	//禁用报头字节;设置变量包长度(定义的有效负载的长度接收数据包的包长度字段);
	//将同步字设置为两个字节长  使用同步字3,同步字2
	RF4432_WriteReg(0x33, 0x02); 
	
	//将同步字设置为0x2D 0xD4
	RF4432_WriteReg(0x36, 0x2D); //同步字3 设置为0x2D
	RF4432_WriteReg(0x37, 0xD4); //同步字2 设置为0xD4
	
	//使能数据包处理程序和CRC-16(IBM)检查
	RF4432_WriteReg(0x30, 0x8D);
	//禁用帧头过滤
	RF4432_WriteReg(0x32, 0x00 );
	//启用FIFO模式和GFSK调制
	RF4432_WriteReg(0x71, 0x63); 

	//设置GPIO's
	RF4432_WriteReg(0x0B, 0x12); //设置为发送状态
	RF4432_WriteReg(0x0C, 0x15); //设置为接收状态
	
	//设置30M晶体震荡电容
	RF4432_WriteReg(0x09, 0xD7); 
	
	//设置AGC 
	RF4432_WriteReg(0x69, 0x60); //使能自动增益功能 0x40
	
	//设置通信功率
	RF4432_WriteReg(0x6D, 0x1E);//设置功率为20dbm
 
 
	//复位Tx FIFO 
	RF4432_WriteReg(0x08, 0x01);
	RF4432_WriteReg(0x08, 0x00);

	//复位Rx FIFO
	RF4432_WriteReg(0x08, 0x02);
	RF4432_WriteReg(0x08, 0x00);

	Init_Si4432IRQ(); 
}

/****************************************
*函数名称:Init_Si4432IRQ
*输    入:无
*输    出:无
*功    能:数据接收中断初始化
******************************************/
VOID Init_Si4432IRQ(VOID)
{
	PROTECT_REG								    //ISP下载时保护FLASH存储器
	(
		P3_MFP = (P3_MFP & (~P32_EINT0)) | EINT0;  //P3.2引脚设置为外部中断
		DBNCECON &= ~ICLK_ON;
		DBNCECON &= DBCLK_HCLK;
		DBNCECON |= SMP_256CK;					   //设置防反弹采样周期选择
		P3_DBEN |= DBEN2;						   //使能P3.2防反弹功能	
		P3_IMD &= IMD2_EDG;				
		P3_IEN |= IF_EN2;						   //设置外部中断0为下降沿触发
		NVIC_ISER |= EXT_INT0;
	) 
		rfend = 0;	
		rxflag = 1; 
}

/****************************************
*函数名称:EINT0_IRQHandler
*输    入:无
*输    出:无
*功    能:数据接收中断服务函数
******************************************/ 
UINT8 sdata[30];//
VOID EINT0_IRQHandler(VOID)
{ 
	UINT8 i=0,len;
	UINT8 reg;
	P3_ISRC = P3_ISRC;//清空中断	 
	
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
		Rfdata.num = (Rfdata.rear + (QUEUEMAXSIZE - Rfdata.front))%QUEUEMAXSIZE;//更新Rfdata.num 
		//Uart1Send(sdata,len);//	
		RF4432_SetRxMode(); 

	}	   
}
