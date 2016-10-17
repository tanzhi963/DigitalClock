/****************************************************************************
**
** Copyright (C) 2010-2014 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/
#include"watchdog.h"
	
/****************************************
*��������:WatchDogInit
*��    ��:��
*��    ��:��
*��    ��:���Ź���ʼ��
******************************************/
void Init_WatchDog(void)
{
	PROTECT_REG
	(	
	    /* ʹ�ܿ��Ź�ʱ�� */	
		APBCLK |= WDT_CLKEN;		   
	
		/* ���ÿ��Ź�ʱ��ԴΪ10K */
		CLKSEL1 = (CLKSEL1 & (~WDT_CLK)) | WDT_10K;
					
		/* ʹ�ܿ��Ź���ʱ����λ���� */
		WTCR |= WTRE;	
	
		/* ���ÿ��Ź���ʱ���Ϊ1740.8ms */
		WTCR &= ~WTIS;
		WTCR |=  WTD_TIME;	// 6.6559s

	
		/* ʹ�ܿ��Ź��ж� */			
		WTCR |= WTIE;
		NVIC_ISER |= WDT_INT;
	
		/* ʹ�ܿ��Ź� */
		WTCR |= WTE;
	
		/* ��λ���Ź�����ֵ */
		WTCR |= CLRWTR;		
	)	
}

/****************************************
*��������:WDT_IRQHandler
*��    ��:��
*��    ��:��
*��    ��:���Ź��жϷ�����
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
*��������:WatchDogFeed
*��    ��:��
*��    ��:��
*��    ��:ι��
******************************************/
void Feed_WatchDog(void)
{
	PROTECT_REG
	(	 
		WTCR |= CLRWTR;		
	)	
}
