/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include "spi.h"
/****************************************
*��������:Spi1MasterInit
*��    ��:��
*��    ��:��
*��    ��:SPI1��ʼ��Ϊ����ģʽ
******************************************/
VOID Init_SPI1(VOID)
{ 
PROTECT_REG	//ISP����ʱ����FLASH�洢��
( 	
	//ʹ��SPI1�������                                    
	P0_MFP &= ~(P05_AD5_SPI1MOSI | P06_AD6_SPI1MISO | P07_AD7_SPI1CLK) ;  
	P0_MFP |= (SPI1MOSI | SPI1MISO | SPI1CLK) ;
	
	APBCLK |= SPI1_CLKEN;  //SPI1ʱ��ʹ��
 
	SPI1_SSR &= ~LVL_H; 					//�ӻ�ѡ��ѡ���ź�ͨ���͵�ƽ���� 
	SPI1_CNTRL &= ~LSB_FIRST; 		//���ȷ���/���������Чλ
	SPI1_CNTRL &= ~CLKP_IDLE_H;  	//SCLK����ʱΪ�͵�ƽ
	SPI1_CNTRL |= TX_NEG_F;     	//SDO �ź���SPICLK���½��ظı�
	SPI1_CNTRL &= ~RX_NEG_F;    	//SDI �ź���SPICLK����������

 
	CLKDIV &= 0xFFFFFFF0;               //HCLK_N = 0, Pclk = SYSclk/(HCLK_N+1)
	SPI1_DIVIDER &= 0xFFFF0000;         //SPIclk = Pclk/((DIVIDER+1)*2)
	SPI1_DIVIDER |= 0x00000001;
  
	SPI1_CNTRL &= ~SPI_MODE_SLAVE;    //SPI1����������ģʽ
//SPI1_SSR |= ASS_AUTO;   					//ʹ���Զ��ӻ�ѡ��
	SPI1_SSR   &= ~ASS_AUTO;       	  //Slave Select non-auto
) 
}
/****************************************
*��������:Spi1Length
*��    ��:len���ݳ���
*��    ��:��
*��    ��:����SPI1���ݳ���
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
*��������: 
*��    ��: 
*��    ��:��
*��    ��: SPI���ֽ�д�뺯��
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
*��������: 
*��    ��: 
*��    ��:��
*��    ��:  SPI���ֽڶ�ȡ����
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
